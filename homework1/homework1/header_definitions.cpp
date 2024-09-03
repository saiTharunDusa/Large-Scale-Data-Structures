#include "header.h"
/*
    Function : genomeSeqRead()
    Process : Reads the file line by line. If the line[0] == '>', then storing names of the scaffolds. Else storing
              the scaffolds lengths and adding the sequence of ACTGN to genome string variable.
    Input parameters:-> string filepath - contains the path of the file .
                     -> string &genome - stores the genome sequence.
                     -> long long int noOfScaffold - storing the no of scaffolds.
                     -> long long int scaffoldLengths - an array that stores the lengths of each scaffolds.
                     -> char **scaffoldNames - array of char pointers to store the names of the scaffolds.
    Output parameters:->scaffoldsNames, scaffoldLengths, genome.
    Output return: None
    Dependencies: ifstream, cerr.

*/
void genomeSeqRead(string filepath, char *genome, long long int &noOfScaffolds, long long int *scaffoldLengths, char **scaffoldNames, long long int &genomeIndex)
{
    ifstream input(filepath);
    if (!input.is_open())
    {
        cerr << "Error opening the file." << endl;
        exit(EXIT_FAILURE);
    }

    // each line contains 80 characters
    string line;
    long long int scaffoldIndex = -1;
    while (getline(input, line))
    {
        if (!line.empty() && line[0] == '>' && scaffoldIndex < maxScaffoldLength)
        {
            scaffoldIndex++;
            scaffoldNames[scaffoldIndex] = new char[line.length()];       // Allocate memory
            strcpy(scaffoldNames[scaffoldIndex], line.substr(1).c_str()); // Copy substring (excluding '>') to the allocated memory
            noOfScaffolds++;
        }
        else
        {
            // genome sequence
            long long int lineLength = line.length(); // Include null terminator
            scaffoldLengths[scaffoldIndex] += lineLength;
            strcpy(genome + genomeIndex, line.c_str());
            genomeIndex += lineLength;
        }
    }
    input.close();
}

/*
    Function : computeGenomeStatistics()
    Process : Traversing the scaffoldLengths array to calculate the maxlen, second maxLen and total lengths.
              total length is again used in calculating the average length.(total length) / no of scaffolds.
    Input parameters:-> long long int noOfScaffold - storing the no of scaffolds.
                     -> long long int scaffoldLengths - an array that stores the lengths of each scaffolds.
                     -> char **scaffoldNames - array of char pointers to store the names of the scaffolds.
                     -> long long int totLength - sum of all the lengths of scaffolds.
                     -> bool flag - to control the print statements of the function.

    Output parameters:None
    Output return: None
    Dependencies: None

*/
void computeGenomeStatistics(long long int noOfScaffolds, long long int &totLength, long long int *scaffoldLengths, char **scaffoldNames, bool flag)
{
    int longestLengthIndex = 0, secondLongestLengthIndex = 0;
    int maxLen = 0, secondMaxLen = 0;
    for (long long int i = 0; i < noOfScaffolds; i++)
    {
        totLength += scaffoldLengths[i];
        if (scaffoldLengths[i] > maxLen)
        {
            secondMaxLen = maxLen;
            secondLongestLengthIndex = longestLengthIndex;
            maxLen = scaffoldLengths[i];
            longestLengthIndex = i;
        }
        else if (scaffoldLengths[i] > secondMaxLen)
        {
            secondMaxLen = scaffoldLengths[i];
            secondLongestLengthIndex = i;
        }
    }
    if (flag == true)
    {
        cout << "The total Length is : " << totLength << endl;
        cout << "Number of Scaffolds : " << noOfScaffolds << endl;
        cout << "The longest scaffold is : " << scaffoldNames[longestLengthIndex] << " and the length is " << maxLen << endl;
        cout << "The second longest scaffold is : " << scaffoldNames[secondLongestLengthIndex] << " and the length is " << secondMaxLen << endl;
        cout << "The average scaffold length : " << (totLength) / noOfScaffolds << endl;
    }
}

/*
    Function : countChars()
    Process : Traverses the entire genome sequence to count no of chars equal to the given char ch.
    Input parameters: -> string &genome - genome sequence
                      -> char ch : character to count the no of occurrences.
    Output parameters:None
    Output return: long long int count
    Dependencies: None

*/

long long int countChars(char *genome, char ch, long long int genomeIndex)
{
    long long int count = 0;
    for (long long int i = 0; i < genomeIndex; i++)
    {
        if (genome[i] == ch)
            count++;
    }
    return count;
}

/*
    Function : calculateGCContent()
    Process : For each character A,C,T,G calls the function countChars() function and then stores the count values.
              And then GC content percentage is calculated.
    Input parameters: ->string &genome - contains genome sequence.
                      ->long long int totalLength - contains the sum of all the lengths of the scaffolds.
    Output parameters:None
    Output return: None
    Dependencies: None

*/
void calculateGCContent(char *genome, long long int &totalLength, long long int genomeIndex)
{
    long long int countA = 0, countC = 0, countT = 0, countG = 0;
    char tempArray[4] = {'A', 'C', 'T', 'G'};
    long long int counts[4] = {0};
    for (int i = 0; i < 4; i++)
    {
        char ch = tempArray[i];
        counts[i] = countChars(genome, ch, genomeIndex);
    }
    countA = counts[0];
    countC = counts[1];
    countT = counts[2];
    countG = counts[3];

    cout << "The content A : " << countA << endl;
    cout << "The content C : " << countC << endl;
    cout << "The content T : " << countT << endl;
    cout << "The content G : " << countG << endl;
    if (totalLength == 0)
        cout << "The GC content percentage is 0%" << endl;
    else
    {
        long long int totalGC = countG + countC;
        double percentage = (static_cast<double>(totalGC) / totalLength) * 100.0;
        cout << "The GC content percentage is " << percentage << endl;
    }
}
