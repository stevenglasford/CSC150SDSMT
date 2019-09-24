#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cerrno>
#include <random>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <random>
#include "wave.h"



using namespace std;

const int fileNameLength = 100;
const int samplingRate = 44100;
const int arrayLen = 5395;
const int maxMidi = 128;

void parameters(char filename[], double& tempo) {
	cout << "Please enter a filename in which to convert: " << flush;
	cin.getline(filename,100);
	cin.ignore(100,'\n');
	cout << "Please enter a tempo, for the output: " << flush;
	cin >> tempo;
	return;
}

void nameChange(char input[], char output[]) {
	for (int i = 0; i < fileNameLength; i++) {
		if (input[i] == '.') {
			if (input[i+1] == 'n') {
				if (input[i+2] == 'o') {
					if (input[i+3] == 't') {
						if (input[i+4] == 'e') {
							if (input[i+5] == 's') {
								output[i] = '.';
								output[i+1] = 'w';
								output[i+2] = 'a';
								output[i+3] = 'v';
								output[i+4] = '\0';
								return;
							}
						}
					}
				}
			}
		}
		else {
			output[i] = input[i];
		}
	}	
	return;
}

int aFundFreq(int midiNum) {
	return floor(((static_cast<double>(samplingRate))/(pow(2.0,(midiNum-69.0)/12.0)*440)));
}

void ring_down() {
	return;
}

int when_to_stop(int8_t *midi, double *time) {
	int i = 0;
	while (!(midi[i] == -1)) {
		i++;
	}
	return static_cast<int>(time[i] * 441);
}

void initialize_pluck(double *time, int8_t *midi, int64_t place, 
	int numEntries, double *volume, double volumeMatrix[][arrayLen]) {
	for (int i = 0; i < numEntries; i++) {
		//checks if a string has been plucked yet
		if (place == 441 * time[i]) {
			//if the system finds a string has been plucked it will initialize
			//  generation of random numbers in that midi row
			int mtemp = midi[i]; 
			//temporarily stores the maximum volume for a particular note
			double vtemp = volume[i];
			//fills the midi row with the random numbers
			for (int j = 0; j < arrayLen; j++) {
				volumeMatrix[mtemp][j] = static_cast<double>(
					((rand() % static_cast<int>(10000 * vtemp)) / 10000));
			}
		}
	}
	return;
}

void sound(double *time, int8_t *midi, double *volume, double tempo, 
	int numNotes, char *output) {
	//This is the large array full of all of the notes and volumes
	double volumeMatrix[maxMidi][arrayLen] = {0};
	double averageNum = 0;
	double sum = 0;
	//This is the average of all of the notes
	double average = 0;
	//This will be the point in which the simulation will just end
	int64_t stop = when_to_stop(midi, time);
	//This variable will be counting until the very last sample
	int k = 0;
	//this is a dynamically allocated array which will be the place where 
	// the volumes will be stored temporarily;
	double* sound = NULL;
	sound = new double[stop];
	//open the file
	ofstream intermediate("intermediate.txt");
	ofstream wavywave(output);
	
	
	
	for (int64_t i = 0; i < stop; i++) {
		initialize_pluck(time, midi, i, numNotes, volume,volumeMatrix);
		for (int j = 0; j < maxMidi; j++) {
			if (abs(volumeMatrix[j][i % arrayLen]) > .00001) {
				averageNum++;
			}
			//determines whether or not the sound should be played
			// based on random numbers, it should produce a frequency
			// equal to the frequency of the note being played.
			if ((rand() % arrayLen) > aFundFreq(j)); {
				sum += volumeMatrix[j][i % arrayLen];
			}
			//rings down the volume of the entry
			volumeMatrix[j][i % arrayLen] = .996 *
				(volumeMatrix[j][i % arrayLen] + volumeMatrix[j]
					[i % arrayLen + 1]) / 2;
		}
		//write the bitdepth to the dynamic array
		sound[i] = sum / averageNum;
		intermediate << sum / averageNum << endl;
		//reset sum and averageNum to their default values
		sum = 0;
		averageNum = 0;
		
	}

	intermediate.close();
	//Data from the sound array needs to writen before it is deleted
	//This deletes the sound array
	delete[] sound;
	sound = NULL;
}

void read_data(char *input, ifstream& notes, double *time, int8_t *midi, double *volume, int& numEntries) {
	while (notes >> time[numEntries]) {
		notes >> midi[numEntries];
		notes >> volume[numEntries];
		numEntries++;
	}
	cout << "Read in " << numEntries << " number of notes" << endl;
	return;
}



int main(int argc, char *argv[]) {
	ifstream input (argv[1]);
	char outputFilename[fileNameLength];
	double time[1000];
	int8_t midi[1000];
	double volume[1000];
	double tempo = 1;
	int numNotes = 0;
	random_device rd;
	srand(rd());
	double tempo = 0;
	parameters(argv[1], tempo);
	ifstream notes (argv[1]);
	if (!notes) {
		perror("The following error occured: ");
	}
	read_data(argv[1], notes, time, midi, volume,numNotes);
	sound(time, midi, volume, tempo,numNotes, argv[2]);
	nameChange(argv[1], outputFilename);
	
    return 0;
}



/*int convert_to_wave(const char input_filename[], const char output_filename[], int sample_rate, bool noclobber = true) {
	int temp = 0;
	double musicRing[samplingRate];

	
	return temp;
}
*/
*/