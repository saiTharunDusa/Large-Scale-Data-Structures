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
void genomeSeqRead(string path, char *genome, long long int &genomeIndex)
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

/*
    Default Constructor.
*/
Prefix_Trie::Prefix_Trie()
{
    root = new TrieNode();
}
/*
    Custom Constructor.
*/
Prefix_Trie::Prefix_Trie(string query_path)
{
    root = new TrieNode();
    this->path = query_path;
}
/*
    Function : insert()
    Process : This function takes in the 32 length character length. It traverses the whole string. For each iteration, if the current character nodes exists in the path then the pointer just moves to that node. Otherwise, it create a node for that character and joins that node to the path. And if the new node is created, then size gets incremented and it is returned.
    Input parameters:-> char *fragment - 32 length character fragment.
    Output parameters:None.
    Output return: long long int size
    Dependencies: None.
*/
long long int Prefix_Trie::insert(char *fragment)
{
    TrieNode *curr = this->root;
    long long int size = 0;
    for (int i = 0; i < 32; i++)
    {
        if (fragment[i] == 'A')
        {
            if (curr->ptr_A == nullptr)
            {
                TrieNode *newNode = new TrieNode();
                curr->ptr_A = newNode;
                curr = curr->ptr_A;
                size++;
            }
            else
            {
                curr = curr->ptr_A;
            }
        }
        if (fragment[i] == 'C')
        {
            if (curr->ptr_C == nullptr)
            {
                TrieNode *newNode = new TrieNode();
                curr->ptr_C = newNode;
                curr = curr->ptr_C;
                size++;
            }
            else
            {
                curr = curr->ptr_C;
            }
        }
        if (fragment[i] == 'G')
        {
            if (curr->ptr_G == nullptr)
            {
                TrieNode *newNode = new TrieNode();
                curr->ptr_G = newNode;
                curr = curr->ptr_G;
                size++;
            }
            else
            {
                curr = curr->ptr_G;
            }
        }
        if (fragment[i] == 'T')
        {
            if (curr->ptr_T == nullptr)
            {
                TrieNode *newNode = new TrieNode();
                curr->ptr_T = newNode;
                curr = curr->ptr_T;
                size++;
            }
            else
            {
                curr = curr->ptr_T;
            }
        }
    }
    return size;
}
/*
    Function : tree_traversal(char *fragment, bool flag)
    Process : This function takes in the 32 length character length. And boolena flag variable. If flag  is true, then the tree traversal is done with atmost one mismatch. Or else the tree traversal is done for perfect matches only. At first, the root node is pushed into the stack.
    Then the below process goes on until the stack is empty.
        -> pop the top node from the stack.
        -> push all the children nodes into the stack.
    If somewhere in the stack traversal, the remaining characters becomes empty, then that means we have found the string.
    Input parameters:-> char *fragment - 32 length character fragment, bool flag.
    Output parameters:None.
    Output return: boolean value.
    Dependencies: None.
*/
bool Prefix_Trie::tree_traversal(char *fragment, bool flag)
{
    int threshold_mismatches = 0;
    if (flag == true)
        threshold_mismatches = 1;
    stackNode *temp = new stackNode;
    temp->next = nullptr;
    temp->node = this->root;
    temp->mismatches = 0;
    temp->used_characters = "";
    temp->remaining_characters = fragment;

    top = temp;
    bool ans = false;
    while (top != nullptr)
    {
        stackNode *current_search = top;
        stackNode *before_current_search = nullptr;
        if (current_search->mismatches > threshold_mismatches)
        {
            top = top->next;
            delete current_search;
            continue;
        }
        else if (current_search->remaining_characters.empty())
        {
            top = top->next;
            delete current_search;
            ans = true;
            continue;
        }
        char current_character = current_search->remaining_characters[0];
        if (current_search->node->ptr_A != nullptr)
        {
            stackNode *newTemp = new stackNode;
            newTemp->node = current_search->node->ptr_A;
            newTemp->remaining_characters = current_search->remaining_characters.substr(1, current_search->remaining_characters.length());
            newTemp->used_characters = newTemp->used_characters + current_character;
            if (current_character == 'A')
            {
                newTemp->mismatches = current_search->mismatches;
            }
            else
            {
                newTemp->mismatches = 1 + current_search->mismatches;
            }
            newTemp->next = top;
            top = newTemp;
            if (before_current_search == nullptr)
                before_current_search = newTemp;
        }
        if (current_search->node->ptr_C != nullptr)
        {
            stackNode *newTemp = new stackNode;
            newTemp->node = current_search->node->ptr_C;
            newTemp->remaining_characters = current_search->remaining_characters.substr(1, current_search->remaining_characters.length());
            newTemp->used_characters = current_search->used_characters + current_character;
            if (current_character == 'C')
            {
                newTemp->mismatches = current_search->mismatches;
            }
            else
            {
                newTemp->mismatches = 1 + current_search->mismatches;
            }
            newTemp->next = top;
            top = newTemp;
            if (before_current_search == nullptr)
                before_current_search = newTemp;
        }
        if (current_search->node->ptr_G != nullptr)
        {
            stackNode *newTemp = new stackNode;
            newTemp->node = current_search->node->ptr_G;
            newTemp->remaining_characters = current_search->remaining_characters.substr(1, current_search->remaining_characters.length());
            newTemp->used_characters = current_search->used_characters + current_character;
            if (current_character == 'G')
            {
                newTemp->mismatches = current_search->mismatches;
            }
            else
            {
                newTemp->mismatches = 1 + current_search->mismatches;
            }
            newTemp->next = top;
            top = newTemp;
            if (before_current_search == nullptr)
                before_current_search = newTemp;
        }
        if (current_search->node->ptr_T != nullptr)
        {
            stackNode *newTemp = new stackNode;
            newTemp->node = current_search->node->ptr_T;
            newTemp->remaining_characters = current_search->remaining_characters.substr(1, current_search->remaining_characters.length());
            newTemp->used_characters = current_search->used_characters + current_character;
            if (current_character == 'T')
            {
                newTemp->mismatches = current_search->mismatches;
            }
            else
            {
                newTemp->mismatches = 1 + current_search->mismatches;
            }
            newTemp->next = top;
            top = newTemp;
            if (before_current_search == nullptr)
                before_current_search = newTemp;
        }
        if (before_current_search != nullptr)
            before_current_search->next = current_search->next;
        else
            top = top->next;
        delete current_search;
    }
    return ans;
}
/*
    Function : Read_Queries()
    Process : Reads the file line by line. If the line[0] != '>', then storing  the sequence of 32 characters length
    fragment in the Query_Fragments array.
    Output parameters:->Query_Fragments[].
    Output return: None
    Dependencies: None.

*/
void Prefix_Trie::Read_Queries()
{
    ifstream input(this->path);
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
    Function : traverse_queries()
    Process : Traverses all the 32 length fragments of 100Million queries and inserts each fragment into the trie.
    Output parameters:None.
    Output return: None
    Dependencies: None.
*/
void Prefix_Trie::traverse_queries()
{
    for (long long int i = 0; i < maxQueriesLen; i++)
    {
        char *fragment = this->Query_Fragments[i];
        this->insert(fragment);
    }
}
/*
    destructor
*/
Prefix_Trie::~Prefix_Trie()
{
    for (long long int i = 0; i < maxQueriesLen; i++)
    {
        delete this->Query_Fragments[i];
    }
    delete this->Query_Fragments;
    cout << "Destructor executed successfully.";
}