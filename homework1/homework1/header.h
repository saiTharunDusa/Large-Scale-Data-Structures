#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <limits>

using namespace std;

#define maxGenomeSize 4000000000
#define maxScaffoldLength 299999999

void genomeSeqRead(string filename, char *genome, long long int &numScaffolds, long long int *scaffoldLengths, char **scaffoldNames, long long int &genomeIndex);

void computeGenomeStatistics(long long int numScaffolds, long long int &totLength, long long int *scaffoldLengths, char **scaffoldNames, bool flag);

long long int countChars(char *genome, char ch, long long int genomeIndex);

void calculateGCContent(char *genome, long long int &totLength, long long int genomeIndex);

#endif // HEADER_H
