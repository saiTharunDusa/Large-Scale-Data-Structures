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

// Implementing the methods of Queries_AR class.

/*
    Constructor : Queries_AR()
    Process : Whenever an instance of the class is created, it initializes all the data members to default values.
    Input parameters: None
    Output parameters:->Query_Fragments[], filepath.
    Output return: None
    Dependencies: None.

*/
Queries_AR::Queries_AR()
{
    for (int i = 0; i < maxQueriesLen; i++)
    {
        this->Query_Fragments[i] = NULL;
    }
    this->filepath = "";
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
Queries_AR::Queries_AR(string path)
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
void Queries_AR::Read_Queries()
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
    Function : search()
    Process : Performs the linear search for the all the fragments of the Query_Fragments[] array. If any of the fragment matches with the given target, then returning the matched index. Or else -1.
    Input parameters:->string target - the target string that is to be searched in the Query_Fragments[] array.
    Output parameters: None
    Output return: ->index of the Query_Fragments[] array.
    Dependencies: None.

*/
long long int Queries_AR::search(char *target)
{
    for (long long int i = 0; i < maxQueriesLen; i++)
    {
        char *ans = this->Query_Fragments[i];
        if (strcmp(ans, target) == 0)
            return i;
    }
    return -1;
}

/*
    Function : sort()
    Process : calls the quick sort method to sort the Query_Fragments array lexicographically.
    Input parameters:None.
    Output parameters: Sorted Query_Fragments[] array.
    Output return: None.
    Dependencies: None.

*/

void Queries_AR::sort()
{
    this->quickSort(0, maxQueriesLen - 1);
}

/*
    Function : quicksort()
    Process : Implements the quicksort algorithm to recursively sort the Query_Fragments[] array..
    Input parameters:long long int low, long long int high.
    Output parameters: None.
    Output return: None.
    Dependencies: None.

*/

void Queries_AR::quickSort(long long int low, long long int high)
{
    if (low < high)
    {
        long long int pi = partition(low, high);

        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

/*
    Function: partition()
    Process: Partitions the Query_Fragments[] array for the quicksort algorithm.
             Iterates through the array elements between 'low' and 'high', rearranging them
             based on their relation to the chosen pivot (the last element).
    Input parameters: long long int low, long long int high.
    Output parameters: Modified Query_Fragments[] array after partitioning.
    Output return: The pivot index after partitioning.
    Dependencies: The swap() function.
*/
long long int Queries_AR::partition(long long int low, long long int high)
{
    char *pivot = this->Query_Fragments[high];
    long long int i = low - 1;

    for (long long int j = low; j <= high - 1; j++)
    {
        if (strcmp(this->Query_Fragments[j], pivot) <= 0)
        {
            i++;
            swap(this->Query_Fragments[i], this->Query_Fragments[j]);
        }
    }

    swap(this->Query_Fragments[i + 1], this->Query_Fragments[high]);
    return i + 1;
}

/*
    Function : binarySearch()
    Process : if the target is less than the Query_Fragments[mid], then excluding the right half and searching the fragment
    in the left half. And if it is greater than the Query_Fragments[mid], then excluding the left half and searching the fragment in the right half.
    Input parameters:string target.
    Output parameters: None.
    Output return: Index of the Query_Fragments[] array if a hit is found or else -1.
    Dependencies: None.

*/

long long int Queries_AR::binarySearch(char *target)
{
    long long int left = 0, right = maxQueriesLen - 1;
    while (left <= right)
    {
        long long int mid = left + (right - left) / 2;
        if (strcmp(target, this->Query_Fragments[mid]) < 0)
        {
            right = mid - 1;
        }
        else if (strcmp(target, this->Query_Fragments[mid]) > 0)
        {
            left = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

/*
    Function : Query_name()
    Process : Takes the index, and then returns the 32 character fragment as a string at that index from Query_Fragments[]
    array.
    Input parameters:long long int index.
    Output parameters: None.
    Output return: returns the fragment which is present in the Query_Fragment[] array at the given index.
    Dependencies: None.

*/

string Queries_AR ::Query_name(long long int index)
{
    return this->Query_Fragments[index];
}

/*
    Destructor: This helps in deallocating the memory if that memory was allocated dynamically.
*/

Queries_AR::~Queries_AR()
{
    for (long long int i = 0; i < maxQueriesLen; i++)
    {
        delete this->Query_Fragments[i];
    }
    delete[] this->Query_Fragments;
    cout << "Destructor executed successfully!" << endl;
}
