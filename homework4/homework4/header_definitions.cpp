#include "header.h"

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
    Dependencies: ifstream, cerr.

*/
void genomeSeqRead(string path, char *genome, unsigned int &genomeIndex)
{
    ifstream input(path);
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

// Implementing the methods of Queries_AR class.

/*
    Constructor : Queries_AR()
    Process : Whenever an instance of the class is created, it initializes all the data members to default values.
    Input parameters: None
    Output parameters:->Query_Fragments[], filepath, this->NW[][].
    Output return: None
    Dependencies: None.

*/
Queries_NW::Queries_NW()
{

    for (int i = 0; i < maxQueriesLen; i++)
    {
        this->Query_Fragments[i] = NULL;
    }
    this->filepath = "";
    this->NW[0][0] = 0;
    // initialize the 0th row and 0th col with gap penalty;
    for (long long int j = 1; j < 33; j++)
    {
        this->NW[0][j] = this->NW[0][j - 1] - this->gap;
        this->NW[j][0] = this->NW[j - 1][0] - this->gap;
    }
}

/*
    Custom Constructor : Queries_AR(path)
    Process : Whenever an instance of the class is created using this custom constructor, it initializes the string filepath
    with the given string value.
    Input parameters: None
    Output parameters:->filepath.
    Output return: None
    Dependencies: None.

*/
Queries_NW::Queries_NW(string path)
{
    this->filepath = path;
}

/*
    Function : Read_Queries()
    Process : Reads the file line by line. If the line[0] != '>', then storing  the sequence of 32 characters length
    fragment in the Query_Fragments array.
    Output parameters:->Query_Fragments[].
    Output return: None
    Dependencies: None.

*/
void Queries_NW::Read_Queries()
{
    ifstream input(this->filepath);
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
            this->Query_Fragments[query_index] = new char[line.length() + 1];
            strncpy(this->Query_Fragments[query_index], line.c_str(), line.length());
            this->Query_Fragments[query_index][line.length()] = '\0'; // Null-terminate
            query_index++;
        }
    }
    cout << "The total no of queries is " << query_index << endl;
    input.close();
}

/*
    Function : Needleman_Wunsch(char *genome_fragment, long long int query_size)
    Process : It takes a 32 length genome fragment, and compares it with all the 32 length fragments of Queries_Fragments[]. And if the score is greater than or equal to 58, then it returns the score.
    Output parameters: None.
    Output return: int score.
    Dependencies: <algorithm> for max function.

*/
int Queries_NW::Needleman_Wunsch(char *genome_fragment, long long int query_size)
{
    int max_score = -100;
    for (long long int i = 0; i < query_size; i++)
    {
        char *query_fragment = this->Query_Fragments[i];
        /*
            query_fragment is considered in the vertical direction of NW matrix, where as genome_fragment is considered in the horizontal direction.
        */
        for (int j = 1; j < 33; j++)
        {
            for (int k = 1; k < 33; k++)
            {
                int diag_val = this->NW[j - 1][k - 1];
                int top_val = this->NW[j - 1][k];
                int left_val = this->NW[j][k - 1];
                if (query_fragment[j - 1] == genome_fragment[k - 1])
                {
                    diag_val += this->match;
                }
                else
                {
                    diag_val += this->mismatch;
                }
                top_val += this->gap;
                left_val += this->gap;
                this->NW[j][k] = max(diag_val, max(top_val, left_val));
            }
        }
        max_score = max(max_score, this->NW[32][32]);
        if (max_score >= 58)
            break;
    }
    return max_score;
}

/*
    Destructor: This helps in deallocating the memory if that memory was allocated dynamically.
*/
Queries_NW::~Queries_NW()
{
    for (long long int i = 0; i < maxQueriesLen; i++)
    {
        delete this->Query_Fragments[i];
    }
    cout << "Destructor executed successfully!" << endl;
}

// implementing methods of the class Queries_BL

/*
    Constructor : Queries_BL()
    Process : Whenever an instance of the class is created, it initializes all the data members to default values.
    Input parameters: None
    Output parameters:->Query_Fragments[], filepath, this->SW[][].
    Output return: None
    Dependencies: None.

*/
Queries_BL::Queries_BL()
{
    for (int i = 0; i < maxQueriesLen; i++)
    {
        this->Query_Fragments[i] = NULL;
    }
    this->filepath = "";
    this->hashTable = nullptr;
    this->SW[0][0] = 0;
    // initialize the 0th row and 0th col with 0
    for (long long int j = 1; j < 33; j++)
    {
        this->SW[0][j] = 0;
        this->SW[j][0] = 0;
    }
}

/*
    Custom Constructor : Queries_BL(path)
    Process : Whenever an instance of the class is created using this custom constructor, it initializes the string filepath
    with the given string value. And also creates a hash table of size 1000000 and points them to nullptr.
    Input parameters: None
    Output parameters:->filepath, this->hashTable.
    Output return: None
    Dependencies: None.

*/
Queries_BL::Queries_BL(string path)
{
    this->filepath = path;
    this->hashTable = new ListNode *[200000000];
    for (long long int i = 0; i < 200000000; i++)
    {
        this->hashTable[i] = nullptr;
    }
}

/*
    Function : Read_Queries()
    Process : Reads the file line by line. If the line[0] != '>', then storing  the sequence of 32 characters length
    fragment in the Query_Fragments array.
    Output parameters:->Query_Fragments[].
    Output return: None
    Dependencies: None.

*/
void Queries_BL::Read_Queries()
{
    ifstream input(this->filepath);
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
            this->Query_Fragments[query_index] = new char[line.length() + 1];
            strncpy(this->Query_Fragments[query_index], line.c_str(), line.length());
            this->Query_Fragments[query_index][line.length()] = '\0'; // Null-terminate

            query_index++;
        }
    }
    cout << "The total no of queries is " << query_index << endl;
    input.close();
}

/*
    Function: insert(char *s)
    Process : Takes a 32-length fragment and a variable for collisions. The fragment is passed to a radix function. The generated value is then hashed to obtain an index in the hash table array. Finally, the fragment is inserted at the front of the generated index.
    Input parameters:char* s.
    Output parameters:None
    Output return: None
    Dependencies: strcpy()

*/
void Queries_BL ::insert(char *s, long long int query_index)
{
    long long int radix = radixVal(s);
    long long int hash = radix % 200000000;
    ListNode *curr = hashTable[hash];
    ListNode *newNode = new ListNode;
    strcpy(newNode->fragment, s);
    newNode->query_index = query_index;
    newNode->fragment[16] = '\0';
    newNode->next = nullptr;
    if (curr == nullptr)
    {
        hashTable[hash] = newNode;
    }
    else
    {
        newNode->next = curr;
        hashTable[hash] = newNode;
    }
}

/*
    Function: search(char *s)
    Process : Takes a 32-length fragment. The fragment is passed to a radix function. The generated value is then hashed to obtain an index in the hash table array. Finally, the fragment is searched at the generated index. Each index of the hash table is a linked list. Therefore a linear search is performed. And if the fragment is found, this function returns true or else false.
    Input parameters: char* s.
    Output parameters: None.
    Output return: boolean value.
    Dependencies: strcmp()

*/
int Queries_BL ::search(char *s)
{
    long long int radix = radixVal(s);
    long long int hash = radix % 200000000;
    ListNode *curr = this->hashTable[hash];
    while (curr != nullptr)
    {
        if (strcmp(curr->fragment, s) == 0)
            return curr->query_index;
        curr = curr->next;
    }
    return -1;
}

/*
    Function: radixVal(char *s)
    Process : Takes a 32-length fragment. A radix function is implemented to return a radix value for the given 32 length fragment.
    Input parameters: char* s.
    Output parameters: None.
    Output return: long long int
    Dependencies: pow()

*/
long long int Queries_BL ::radixVal(char *s)
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
    Function: insert16_mers_into_HT()
    Process : Traverses all the query fragments. And for each query_fragment all its 16-mers are stored in a hash table.
    Input parameters: None.
    Output parameters: None.
    Output return: None.
    Dependencies: None.

*/
void Queries_BL::insert16_mers_into_HT()
{
    for (long long int i = 0; i < maxQueriesLen; i++)
    {
        char *query_fragment = this->Query_Fragments[i];
        // break the query_fragment into 16-mers
        for (int j = 0; j < 32 - 16 + 1; j++)
        {
            char query_16_mer[17];
            int index = 0;
            for (int k = j; k < j + 16; k++)
            {
                query_16_mer[index] = query_fragment[k];
                index++;
            }
            query_16_mer[index] = '\0';
            this->insert(query_16_mer, i);
        }
    }
}

/*
    Function: seed_extension(char *genome_frag, int actual_ind, char *genome, long long int query_index, bool flag)
    Process : If a 16-mer of genome_fragment is found. Then we take the query_fragment of that query_index where 16-mer was found. And from the actual_genome index we take a 32 sized genome fragment by performing left extension. And Smith waterman is performed between this 32 - sized genome fragment and query fragment. If the score is not greater than or equal to 58, then we perform right extension.
    For completely random generated fragment, there is no need to perform seed extension. We could directly perform smith waterman between the completely random generated fragmetn and query_fragment.
    So the seed extension is controlled by using a flag variable.
    Output parameters: None.
    Output return: int score.
    Dependencies: None.

*/
int Queries_BL::seed_extension(char *genome_frag, int actual_ind, char *genome, long long int query_index, bool flag)
{
    char *query_fragment = this->Query_Fragments[query_index];
    if (flag == true)
    {
        // we expand to left and right from the actual genome index.
        char fragment1[33];
        int index = 0;
        // expanding to the left
        if (actual_ind >= 32)
        {
            for (long long int it = actual_ind; it > actual_ind - 32; it--)
            {
                fragment1[index] = genome[it];
                index++;
            }
            fragment1[index] = '\0';
            // perform smithwaterman
            int score = this->Smith_waterman(fragment1, query_fragment);
            if (score >= 58)
                return score;
        }
        // if the score is not greater than or equal to 58 for the left expansion, then perform right expansion.
        index = 0;
        // expanding to the right
        for (long long int it = actual_ind; it < actual_ind + 32; it++)
        {
            fragment1[index] = genome[it];
            index++;
        }
        fragment1[index] = '\0';
        int score = this->Smith_waterman(fragment1, query_fragment);
        if (score >= 58)
            return score;
    }
    // For completely random, if a hit is found. Then compare 32 Fragment length of completely random genomefragment with the query fragment. Because it can not have a real_genome_index for expansion.
    else
    {
        int score = this->Smith_waterman(genome_frag, query_fragment);
        if (score >= 58)
            return score;
    }
    return -1;
}

/*
    Function : Smith_waterman(char *genome_fragment, char *query_fragment)
    Process : It takes a 32 length genome fragment, and compares it with the 32 length query_fragment. And then it returns max_score.
    It is same like Needleman_Wunsch() function, but in this algorithm we do not consider negative values. If there is a negative value, then we initialize it to zero.
    Output parameters: None.
    Output return: int score.
    Dependencies: <algorithm> for max function.

*/
int Queries_BL::Smith_waterman(char *genome_fragment, char *query_fragment)
{
    int max_score = -100;
    for (int j = 1; j < 33; j++)
    {
        for (int k = 1; k < 33; k++)
        {
            int diag_val = this->SW[j - 1][k - 1];
            int top_val = this->SW[j - 1][k];
            int left_val = this->SW[j][k - 1];
            if (query_fragment[j - 1] == genome_fragment[k - 1])
            {
                diag_val += this->match;
            }
            else
            {
                diag_val += this->mismatch;
            }
            top_val += this->gap;
            left_val += this->gap;
            if (diag_val < 0)
                diag_val = 0;
            if (top_val < 0)
                top_val = 0;
            if (left_val < 0)
                left_val = 0;
            this->SW[j][k] = max(diag_val, max(top_val, left_val));
            max_score = max(max_score, this->SW[j][k]);
        }
    }
    return max_score;
}