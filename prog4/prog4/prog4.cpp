#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cerrno>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits.h>
#include <stdint.h>
#include <errno.h>
#include <cstring>
#include "wave.h"

using namespace std;

const int fileNameLength = 100;
const int samplingRate = 44100;
const int arrayLen = 5395;
const int maxMidi = 128;

int aFundFreq(int midiNum) {
	return static_cast<int>(floor(((static_cast<double>(samplingRate)) / (pow(2.0, (midiNum - 69.0) / 12.0) * 440))));
}

int when_to_stop(int *midi, double *t) {
	int i = 0;
	while (!(midi[i] == -1)) {
		i++;
	}
	return static_cast<int>(t[i] * 441);
}

void initialize_pluck(double *t, int *midi, int64_t place,
	int numEntries, double *volume, double volumeMatrix[][arrayLen]) {
	for (int i = 0; i < numEntries; i++) {
		//checks if a string has been plucked yet
		if (place == 441 * t[i]) {
			//if the system finds a string that has been plucked it
			//	will initialize a particular string by filling
			//	that string with random number in that midi row
			//temporarily stores the maximum volume for a particular note
			double vtemp = volume[i];
			//fills the midi row with the random numbers
			for (int j = 0; j < arrayLen; j++) {
				volumeMatrix[midi[i]][j] = static_cast<double>(((rand() % static_cast<int>(10000 * vtemp)) / 10000));
			}
		}
	}
	return;
}

void read_data(char *input, ifstream& notes, double *t, int *midi,
	double *volume, int& numEntries) {
	while (notes >> t[numEntries]) {
		notes >> midi[numEntries];
		notes >> volume[numEntries];
		numEntries++;
	}
	cout << "Read in " << numEntries - 1 << " number of notes" << endl;
	return;
}

void sound(double *t, int *midi, double *volume, double tempo,
	int numNotes, char *output, char *input) {
	//This is the large array full of all of the notes and volumes
	double volumeMatrix[maxMidi][arrayLen] = { 0 };

	double averageNum = 0;
	double sum = 0;

	//This is the average of all of the notes
	double average = 0;

	//This will be the point in which the simulation will just end
	int stop = when_to_stop(midi, t);

	//This variable will be counting until the very last sample
	int k = 0;

	//open the output file
	ofstream intermediate("intermediate.txt");

	//The actual algorithm
	for (int64_t i = 0; i< stop; i++) {
		initialize_pluck(t, midi, i, numNotes, volume, volumeMatrix);
		for (int j = 0; j < maxMidi; j++) {
			if (abs(volumeMatrix[j][i%arrayLen]) > .00001) {
				averageNum++;
			}
			//determines whether or not the sound should be played
			//	based on random numbers, it should produce a
			//	frequency equal to the frequency of the note
			//	being played
			if ((rand() % arrayLen) > aFundFreq(j)) {
				sum += volumeMatrix[j][i%arrayLen];
			}
			//rings down the volume matrix
			volumeMatrix[j][i%arrayLen] = .996*(volumeMatrix[j][i%arrayLen] + volumeMatrix[j][i%arrayLen + 1]) / 2;
		}
		//write the bitdepth data to the dynamic array
		intermediate << sum / averageNum << endl;
		sum = 0;
		averageNum = 0;
	}
	intermediate.close();
	return;
}

/*convert_to_wave()
Author: Larry Pyeatt
Date: 11-1-2012
(C) All rights reserved

convert_to_wave reads an input file consisting of a sequence of
numbers in ASCII format, and converts it to Microsoft (tm) Wave (tm)
format, and writes it to the output file.
*/

/* I have done minimal error checking.  I really should do more */
int write_wave(const char filename[],
	int16_t data[], int size, int sample_rate)
{
	ofstream outfile(filename, ofstream::binary);
	uint32_t chunksize;
	uint32_t subchunk1size;
	uint32_t subchunk2size;
	uint16_t audioformat;
	uint16_t numchannels;
	uint32_t samplerate;
	uint32_t byterate;
	uint16_t blockalign;
	uint16_t bitspersample;

	if (!outfile.good())
	{
		cout << "convert_to_wave: Unable to open file \"";
		cout << filename;
		cout << "\" for output." << endl;
		cout << strerror(errno) << "\n" << endl;
		return 0;
	}
	subchunk1size = 16;  // always 16 for PCM data
	audioformat = 1;    // this is the code for PCM
	numchannels = 1;
	samplerate = sample_rate;
	bitspersample = sizeof(int16_t) * 8;
	byterate = samplerate * numchannels * bitspersample / 8;
	blockalign = numchannels * bitspersample / 8;
	subchunk2size = size * numchannels * sizeof(int16_t);
	chunksize = 4 + (8 + subchunk1size) + (8 + subchunk2size);

	outfile.write("RIFF", 4);
	outfile.write((char*)&chunksize, 4);
	outfile.write("WAVE", 4);

	outfile.write("fmt ", 4);
	outfile.write((char*)&subchunk1size, sizeof(subchunk1size));
	outfile.write((char*)&audioformat, sizeof(audioformat));
	outfile.write((char*)&numchannels, sizeof(numchannels));
	outfile.write((char*)&samplerate, sizeof(samplerate));
	outfile.write((char*)&byterate, sizeof(byterate));
	outfile.write((char*)&blockalign, sizeof(blockalign));
	outfile.write((char*)&bitspersample, sizeof(bitspersample));

	outfile.write("data", 4);
	outfile.write((char*)&subchunk2size, sizeof(subchunk2size));
	outfile.write((char*)data, size * sizeof(int16_t));
	if (!outfile.good())
	{
		cout << "convert_to_wave: Error writing to \"";
		cout << filename;
		cout << "\"." << endl;
		cout << strerror(errno) << endl;
		return 0;
	}
	outfile.close();
	return 1;
}

/* should return 0 on failure, but I'm in a hurry */
int convert_to_wave(const char input_filename[],
	const char output_filename[],
	int sample_rate,
	bool noclobber)
{
	ifstream input;
	float tmp, max;
	int16_t *data16;
	int size, i;
	int return_code;
	char yn;

	if (noclobber)
	{
		input.open(output_filename);
		if (input)
		{
			do {
				cout << "The output file \"" << output_filename <<
					"\" already exists." << endl;
				cout << "Do you want to overwrite it? (N/y)";
				cin >> yn;
				yn = toupper(yn);
			} while (yn != 'Y' && yn != 'N');
			if (yn == 'N')
				return 1;
		}
		input.close();
		input.clear();
	}

	input.open(input_filename);
	if (!input.good())
	{
		cout << "convert_to_wave: Unable to open file \"";
		cout << input_filename;
		cout << "\" for input." << endl;
		cout << strerror(errno) << endl;
		return 0;
	}
	// count how many numbers we can read from the file
	size = 0;
	max = 0;
	input >> tmp;
	while (!input.fail())
	{
		size++;
		input >> tmp;
		if (fabs(tmp)>max)
			max = fabs(tmp);
	}
	// clear the fail flag so we can read the file again
	input.clear();
	// go back to the beginning of the file
	input.seekg(ios_base::beg);
	if (!input.good())
	{
		cout << "convert_to_wave: Error reading input file \"";
		cout << input_filename;
		cout << "\"." << endl;
		cout << strerror(errno) << endl;
		return 0;
	}
	if (size == 0)
	{
		cout << "convert_to_wave: Input file \"";
		cout << input_filename;
		cout << "\" is empty or does not contain only numbers." << endl;
		return 0;
	}
	// allocate enough space to store all of the numbers
	data16 = new(nothrow) int16_t[size];
	if (data16 == NULL)
	{
		cout << "convert_to_wave: Memory allocation failed." << endl;
		cout << strerror(errno) << endl;
		return 0;
	}
	// read them all in as floats, then convert to 16 bit ints
	for (i = 0; i<size; i++)
	{
		input >> tmp;
		data16[i] = (int16_t)((tmp / max) * (SHRT_MAX - 1));
	}
	if (!input.good())
	{
		cout << "convert_to_wave: Error reading input file \"";
		cout << input_filename;
		cout << "\"." << endl;
		cout << strerror(errno) << endl;
		return 0;
	}
	input.close();
	return_code = write_wave(output_filename, data16, size, sample_rate);
	delete[] data16;
	return return_code;
}

int main(int argc, char** argv) {
	//char outputFilename[fileNameLength];
	double t[1000];
	int midi[1000];
	double volume[1000];
	double tempo = atof(argv[3]);
	int numNotes = 0;
	srand(time(NULL));
	ifstream notes(argv[1]);
	if (!notes.good()) {
		cout << "Sorry but there was an error trying to open the"
			" .notes file, exiting." << endl;
		return 1;
	}
	else {
		read_data(argv[1], notes, t, midi, volume, numNotes);
	}
	notes.close();
	sound(t, midi, volume, tempo, numNotes, argv[2], argv[1]);
	int OK = convert_to_wave("intermediate.txt", argv[2], samplingRate);
	return 0;
}

