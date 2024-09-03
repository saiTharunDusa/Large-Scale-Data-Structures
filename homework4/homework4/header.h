#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <random>
#include <algorithm>

#define maxQueriesLen 100000000

using namespace std;

void genomeSeqRead(string filename, char *genome, unsigned int &genomeIndex);

class Queries_NW
{
private:
    int match = 2, mismatch = -1, gap = -1;
    char *Query_Fragments[maxQueriesLen];
    string filepath;
    int NW[33][33];

public:
    Queries_NW();
    Queries_NW(string path);
    void Read_Queries();
    int Needleman_Wunsch(char *genome_fragment, long long int query_size);
    ~Queries_NW();
};

class Queries_BL
{
private:
    int match = 2, mismatch = -1, gap = -1;
    char *Query_Fragments[maxQueriesLen];
    int SW[33][33];
    string filepath;
    struct ListNode
    {
        char fragment[17];
        long long int query_index;
        ListNode *next;
    };
    ListNode **hashTable;

public:
    Queries_BL();
    Queries_BL(string path);
    void Read_Queries();
    void insert16_mers_into_HT();
    int seed_extension(char *arr, int genome_ind, char *genome, long long int query_index, bool flag);
    int Smith_waterman(char *frag1, char *frag2);
    void insert(char *s, long long int query_index);
    void delete_hash_table();
    int search(char *s);
    long long int radixVal(char *s);
    // ~Queries_BL();
};

#endif
