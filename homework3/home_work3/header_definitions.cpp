#include "header.h"

/*
    Constructor: Queries_HT()
    Process : Whenever an instance of the class is created, it initializes all the data members to default values.
             ->hash_table_size = 0, hashtable = nullptr;
    Input parameters:None
    Output parameters:None
    Output return: None
    Dependencies: None

*/
Queries_HT ::Queries_HT()
{
    this->hash_table_size = 0;
    this->hashTable = nullptr;
}

/*
    custom constructor: Queries_HT(long long int size)
    Process :Whenever an instance of the class is created, it initializes all the data members to the given value.
             ->hash_table_size = size and hashTable[i] = nullptr.
    Input parameters:long long int size.
    Output parameters:None
    Output return: None
    Dependencies: None

*/
Queries_HT ::Queries_HT(long long int size)
{
    this->hash_table_size = size;
    this->hashTable = new ListNode *[size];
    for (long long int i = 0; i < size; i++)
    {
        this->hashTable[i] = nullptr;
    }
}

/*
    Function: insert(char *s, long long int &collisions)
    Process : Takes a 16-length fragment and a variable for collisions. The fragment is passed to a radix function. The generated value is then hashed to obtain an index in the hash table array. Finally, the fragment is inserted at the front of the generated index.
    Input parameters:long long int collisions, char* s.
    Output parameters:None
    Output return: None
    Dependencies: strcpy()

*/
void Queries_HT ::insert(char *s, long long int &collisions)
{
    long long int radix = radixVal(s);
    long long int hash = radix % hash_table_size;
    ListNode *curr = hashTable[hash];
    ListNode *newNode = new ListNode;
    strcpy(newNode->fragment, s);
    newNode->next = nullptr;
    if (curr == nullptr)
    {
        hashTable[hash] = newNode;
    }
    else
    {
        collisions++;
        newNode->next = curr;
        hashTable[hash] = newNode;
    }
}

/*
    Function: search(char *s)
    Process : Takes a 16-length fragment. The fragment is passed to a radix function. The generated value is then hashed to obtain an index in the hash table array. Finally, the fragment is searched at the generated index. Each index of the hash table is a linked list. Therefore a linear search is performed. And if the fragment is found, this function returns true or else false.
    Input parameters: char* s.
    Output parameters: None.
    Output return: boolean value.
    Dependencies: strcmp()

*/
bool Queries_HT ::search(char *s)
{
    long long int radix = radixVal(s);
    long long int hash = radix % hash_table_size;
    ListNode *curr = this->hashTable[hash];
    while (curr != nullptr)
    {
        if (strcmp(curr->fragment, s) == 0)
            return true;
        curr = curr->next;
    }
    return false;
}

/*
    Function: radixVal(char *s)
    Process : Takes a 16-length fragment. A radix function is implemented to return a radix value for the given 16length fragment.
    Input parameters: char* s.
    Output parameters: None.
    Output return: long long int
    Dependencies: pow()

*/
long long int Queries_HT ::radixVal(char *s)
{
    long long int val = 0;
    int charNumber_A = 0, charNumber_C = 1, charNumber_G = 2, charNumber_T = 3;
    int n = 16;
    for (int i = n - 1; i >= 0; i--)
    {
        int powerNum = n - i - 1;
        if (s[i] == 'A')
        {
            val += (charNumber_A * (long long int)pow(4, powerNum));
        }
        else if (s[i] == 'C')
        {
            val += (charNumber_C * (long long int)pow(4, powerNum));
        }
        else if (s[i] == 'G')
        {
            val += (charNumber_G * (long long int)pow(4, powerNum));
        }
        else
            val += (charNumber_T * (long long int)pow(4, powerNum));
    }
    return val;
}

/*
    Function: read_queries(string path, long long int &collisions)
    Process : Reads the file line by line. If the line[0] != '>', then storing  the sequence of 16 characters length
    fragment in the tempArr array. And then this array is passed to insert() function to insert in the hash table.
    Input parameters: string path, long long int &collisions.
    Output parameters: None.
    Output return: None.
    Dependencies: ifstream, cerr, strcpy().

*/
void Queries_HT ::read_queries(string path, long long int &collisions)
{
    cout << "hash table size - " << hash_table_size << endl;
    ifstream input(path);
    if (!input.is_open())
    {
        cerr << "Error opening the file." << endl;
        exit(EXIT_FAILURE);
    }
    // each line contains 32 characters
    string line;
    long long int query_index = 0;
    while (getline(input, line))
    {
        if (!line.empty() && line[0] != '>')
        {
            char *tempArr = new char[16 + 1];
            strcpy(tempArr, line.c_str());
            tempArr[16] = '\0';
            insert(tempArr, collisions);
            query_index++;
        }
    }
    cout << "The total no of queries is " << query_index << endl;
    input.close();
}
/*
    Function : genomeSeqRead()
    Process : Reads the file line by line. If the line[0] != '>', then storing  the sequence of ACTGN to genome character
    array.
    Input parameters:-> string filepath - contains the path of the file .
                     -> string &genome - stores the genome sequence.
                     -> long long int &genomeIndex - maintains the index of the genome array. Typically, we could call it
                        as the size of the genome array.
    Output parameters:->genome, genomeIndex.
    Output return: None
    Dependencies: ifstream, cerr, strcpy().

*/
void Queries_HT ::genomeSeqRead(string filename, char *genome, long long int &genomeIndex)
{
    ifstream input(filename);
    if (!input.is_open())
    {
        cerr << "Error opening the file." << endl;
        exit(EXIT_FAILURE);
    }

    // each line contains 80 characters
    string line;
    while (getline(input, line))
    {
        if (!line.empty() && line[0] != '>')
        {
            strcpy(genome + genomeIndex, line.c_str());
            genomeIndex += line.length();
        }
    }
}

/*
    Destructor: This helps in deallocating the memory if that memory was allocated dynamically.
*/

Queries_HT::~Queries_HT()
{
    for (long long int i = 0; i < this->hash_table_size; i++)
    {
        ListNode *curr = this->hashTable[i];
        while (curr != nullptr)
        {
            ListNode *tempNode = curr;
            curr = curr->next;
            delete tempNode;
        }
    }
    delete[] hashTable;
    cout << "Destructor executed successfully!" << endl;
}
