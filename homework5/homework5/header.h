#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <limits>
#include <math.h>
#include <chrono>
#include <stdlib.h>

using namespace std;

#define maxQueriesLen 100000000
// to read the genome data.
void genomeSeqRead(string filename, char *genome, long long int &genomeIndex);

class Prefix_Trie
{
public:
    struct TrieNode
    {
        TrieNode *ptr_A = NULL;
        TrieNode *ptr_C = NULL;
        TrieNode *ptr_G = NULL;
        TrieNode *ptr_T = NULL;
    };
    struct stackNode
    {
        TrieNode *node;
        string used_characters;
        string remaining_characters;
        int mismatches;
        stackNode *next = NULL;
    };
    string path;
    char *Query_Fragments[maxQueriesLen];
    TrieNode *root;
    stackNode *top;
    Prefix_Trie();
    Prefix_Trie(string query_path);
    void Read_Queries();
    void traverse_queries();
    long long int insert(char *fragment);
    bool tree_traversal(char *fragment, bool flag);
    ~Prefix_Trie();
};

#endif