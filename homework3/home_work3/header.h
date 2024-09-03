#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <limits>
#include <math.h>
#include <chrono>

using namespace std;

class Queries_HT
{
private:
    long long int hash_table_size;
    struct ListNode
    {
        char fragment[17];
        ListNode *next;
    };
    ListNode **hashTable;

public:
    // constructor.
    Queries_HT();
    Queries_HT(long long int size);

    void insert(char *s, long long int &collisions);

    long long int radixVal(char *s);

    bool search(char *s);

    void read_queries(string path, long long int &collisions);

    void genomeSeqRead(string filename, char *genome, long long int &genomeIndex);

    ~Queries_HT();
};

#endif