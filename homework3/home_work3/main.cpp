// !!! Use the head command to make a smaller version of the dataset file to transfer to your laptop... for example
// head -2000 /common/contrib/classroom/inf503/hw_dataset.fa > /scratch/vyf2/sample_hw_dataset.fa
//... this will take 2000 lines from the time of file (1000 reads)
#include "header.h"

int main(int argc, char **argv)
{

    ////////////////////////////////////////////////////////////////////////////////////
    // Lets do sanity checks to make sure the proper number of parameters were passed in
    ////////////////////////////////////////////////////////////////////////////////////

    if (argc != 5)
    { // unexpected program call
        cout << endl
             << endl
             << "==========================" << endl;
        cout << "Error: 2 input parameters expected" << endl;
        cout << "Proper usage is:" << endl;
        cout << "./homework <problem-flag> <filepath>" << endl;
        cout << "Example:" << endl;
        cout << "./homework problem1A /scratch/vyf2/HW1/sample_hw_dataset.fa" << endl;
        cout << "==========================" << endl
             << endl;
        cout << "exiting..." << endl;
        exit(-1);
    }
    else
    {

        cout << "The number of arguments passed: " << argc << endl;
        cout << "The first argument is: " << argv[0] << endl;
        cout << "The second argument is: " << argv[1] << endl;
        cout << "The third argument is: " << argv[2] << endl;
        cout << "The fourth argument is: " << argv[3] << endl;
        cout << "The fifth argument is: " << argv[4] << endl;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    // Lets open our sample file and read in the first set of sequences
    ////////////////////////////////////////////////////////////////////////////////////
    string part = argv[3];
    string path1 = argv[1];
    string path2 = argv[2];
    // size of the hash table.
    string size = argv[4];

    if (part == "partA")
    {
        // converting the received size from the command to long long int.
        long long int hash_table_size = stoi(size);
        // creating the instance of Queries_HT class.
        Queries_HT obj = Queries_HT(hash_table_size);
        // to keep track of no of collisions while inserting 16-query length fragment in the hash table.
        long long int collisions = 0;

        clock_t startTime = clock(); // Record the start time
        // reading the query fragments and storing the no of collisions occurred.
        obj.read_queries(path1, collisions);
        clock_t endTime = clock(); // Record the end time

        /* For each of your 4 hash table sizes, how long did it take you to populate the hash table? Do the timing results make sense (provide big O notation)?  Explain.
        ->The time taken to populate the hash table of size 1000000 is 99.2899 seconds
        ->The time taken to populate the hash table of size 50000000 is 97.9511 seconds
        ->The time taken to populate the hash table of size 100000000 is 100.613 seconds
        ->The time taken to populate the hash table of size 200000000 is 100.509 seconds

        -> For all the hash table sizes, the time is almost similar, so the big-O notation would be O(N) which is linear time complexity.

        */
        double executionTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
        cout << "The time taken to populate the hash table of size " << hash_table_size << " is " << executionTime << " seconds" << endl;
        cout << endl;
        // For each of your 4 hash table sizes, how many collisions did you observe while populating the hash?
        cout << "The total no of collisions while populating the hash are " << collisions << endl;
    }

    if (part == "partB")
    {
        // converting the received size from the command to long long int.
        long long int hash_table_size = stoi(size);
        // creating the instance of Queries_HT class.
        Queries_HT obj = Queries_HT(hash_table_size);
        // to keep track of no of collisions while inserting 16-query length fragment in the hash table.
        long long int collisions = 0;
        // reading the query fragments and storing the no of collisions occurred.
        obj.read_queries(path1, collisions);
        // to store the genome i.e, subject data.
        char genome[4000000000];
        // to maintain the size of the genome array.
        long long int genomeIndex = 0;
        // reading the genome data into genome char array.
        obj.genomeSeqRead(path2, genome, genomeIndex);
        /*
        This keeps track of total no of 16-length fragments from the genome data that are found in the hashtable which is created for the query_fragments data set.
        */
        long long int totalFragments = 0;
        /*
            Populating the hash table and searching for 16-character fragments of the subject sequence within the Queries_HT object by iterating through all 16-character long fragments of the subject dataset, searching for each one in the query dataset. And all the 'N' characters of the genome would be replaced by character 'A' in the tempArr.
            And the fragment is searched with the help of a search function implementation in the Queries_HT class.
            If a hit is found, that search function returns true or else false.
        */
        cout << "the first 10 fragments of the subject dataset that you found within the Query_HT" << endl;
        clock_t startTime = clock(); // Record the start time
        for (long long int i = 0; i < genomeIndex - 16; i++)
        {
            char tempArr[17];
            for (long long int j = 0; j < 16; j++)
            {
                if (genome[j + i] == 'N')
                    tempArr[j] = 'A';
                else
                    tempArr[j] = genome[j + i];
            }
            tempArr[16] = '\0';
            if (obj.search(tempArr) == true)
            {
                totalFragments++;
                if (totalFragments <= 10)
                    cout << tempArr << endl;
            }
        }
        clock_t endTime = clock(); // Record the end time
        double executionTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
        // How long did it take to search for every possible 16-character long fragment of the subject dataset within the query dataset?
        cout << "The time taken to search for every possible 16-character long fragment of the subject dataset within the query dataset is " << executionTime << " seconds." << endl;
        // How many such fragments did you find?
        cout << "Total no of fragments found is " << totalFragments << endl;
    }

    return (0);
}
