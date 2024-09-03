#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <limits>
#include <chrono>

using namespace std;

#define maxQueriesLen 100000000

// to read the genome data.
void genomeSeqRead(string filename, char *genome, long long int &genomeIndex);

// class template for the Query_fragments.
class Queries_AR
{
private:
    char *Query_Fragments[maxQueriesLen];
    string filepath;

public:
    Queries_AR();
    Queries_AR(string path);
    void Read_Queries();
    long long int search(char *target);
    void sort();
    void quickSort(long long int left, long long int right);
    long long int partition(long long int left, long long int right);
    long long int binarySearch(char *target);
    string Query_name(long long int index);
    ~Queries_AR();
};

#endif