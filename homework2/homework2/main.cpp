// !!! Use the head command to make a smaller version of the dataset file to transfer to your laptop... for example
// head -2000 /common/contrib/classroom/inf503/hw_dataset.fa > /scratch/vyf2/sample_hw_dataset.fa
//... this will take 2000 lines from the time of file (1000 reads)
#include "header.h"

int main(int argc, char **argv)
{

    ////////////////////////////////////////////////////////////////////////////////////
    // Lets do sanity checks to make sure the proper number of parameters were passed in
    ////////////////////////////////////////////////////////////////////////////////////

    if (argc != 4)
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
    }

    ////////////////////////////////////////////////////////////////////////////////////
    // Lets open our sample file and read in the first set of sequences
    ////////////////////////////////////////////////////////////////////////////////////
    string part = argv[3];
    string path1 = argv[1];
    string path2 = argv[2];

    if (part == "partA")
    {
        // to store the genome i.e, subject data.
        char genome[4000000000];
        // maintaing the size of genome array.
        long long int genomeIndex = 0;
        // reading the genome sequence into genome array.
        genomeSeqRead(path2, genome, genomeIndex);
        // An instance to the Queries_AR class.
        Queries_AR Queries_AR_obj = Queries_AR(path1);
        // Reading the 100M queries into the Query_fragments array which is a private member of class Queries_AR class.
        Queries_AR_obj.Read_Queries();
        // For each genome index upto 10M, storing query_index if a hit is found or else -1.
        // Maintaining this array so that it helps in printing the 20Query fragments of first 10K,100K,1M of larger indices.
        long long int Query_Index[maxQueriesLen];

        /*
            For each genome index upto 10K indices, taking the substring of length 32. This substring is treated as target fragment that is to be searched in the Query_Fragments[] array. If a hit is found, then search function would return index of the Query_fragments[] array or else -1. The search function implementation is linear search.
        */
        clock_t startTime = clock(); // Record the start time
        for (long long int i = 0; i < 10000; i++)
        {
            char temp[32 + 1]; // +1 for null-terminator
            for (long long int j = i; j < i + 32; j++)
            {
                temp[j - i] = genome[j];
            }
            temp[32] = '\0'; // Null-terminate the char array

            Query_Index[i] = Queries_AR_obj.search(temp);
        }
        clock_t endTime = clock(); // Record the end time
        double executionTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
        // Output the time taken in seconds
        cout << "Time taken for first 10k fragments: " << executionTime << " seconds" << endl;

        /*
            For each genome index upto 100K indices, taking the substring of length 32. This substring is treated as target fragment that is to be searched in the Query_Fragments[] array. If a hit is found, then search function would return index of the Query_fragments[] array or else -1. The search function implementation is linear search.
        */
        // first 100k fragments
        for (long long int i = 10000; i < 100000; i++)
        {
            char temp[32 + 1]; // +1 for null-terminator
            for (long long int j = i; j < i + 32; j++)
            {
                temp[j - i] = genome[j];
            }
            temp[32] = '\0'; // Null-terminate the char array

            Query_Index[i] = Queries_AR_obj.search(temp);
        }
        clock_t endTime1 = clock(); // Record the end time
        executionTime = static_cast<double>(endTime1 - startTime) / CLOCKS_PER_SEC;
        cout << "Time taken for first 100k: " << executionTime << " seconds" << endl;

        /*
            For each genome index upto 1M indices, taking the substring of length 32. This substring is treated as target fragment that is to be searched in the Query_Fragments[] array. If a hit is found, then search function would return index of the Query_fragments[] array or else -1. The search function implementation is linear search.
        */
        // first 1M fragments
        for (long long int i = 100000; i < maxQueriesLen; i++)
        {
            char temp[32 + 1]; // +1 for null-terminator
            for (long long int j = i; j < i + 32; j++)
            {
                temp[j - i] = genome[j];
            }
            temp[32] = '\0'; // Null-terminate the char array

            Query_Index[i] = Queries_AR_obj.search(temp);
        }
        clock_t endTime2 = clock(); // Record the end time
        executionTime = static_cast<double>(endTime2 - startTime) / CLOCKS_PER_SEC;
        cout << "Time taken for 1M fragments: " << executionTime << " seconds" << endl;

        /*
            Print the 20 query fragments found within the subject dataset that have the largest indices (i.e. found later in the subject) for the first 10K.
            Since, we need to print the query_fragments of the larger indices of the subject dataset. Therefore, traversing from 9999 for the first 10K fragments.
            We have already maintained Query_Index[] arr which gives the query_index of query_fragments[] array if there is a hit from substring formed from the subject index or else -1.
            So, if there is a hit, we are printing the query_fragment using the Query_name() method from the Query_AR class using the instance of that class.
            And maintaining a count variable to exit the loop after printing the 20 query fragments.
        */
        cout << "Printing the 20 query fragments found within the subject dataset that have the largest indices (i.e. found later in the subject) for the first 10K." << endl;
        int count = 0;
        for (long long int i = 9999; i >= 0; i--)
        {
            if (Query_Index[i] != -1)
            {
                cout << "The fragment " << Queries_AR_obj.Query_name(Query_Index[i]) << " found at index - " << i << endl;
                count++;
            }
            if (count == 20)
                break;
        }

        /*
            Making the count variable  to 0 to print the 20 query fragments for the first 100K fragments of larger indices.
            Process is same as 10K fragments.
        */
        cout << "Printing the 20 query fragments found within the subject dataset that have the largest indices (i.e. found later in the subject) for the first 100K." << endl;
        count = 0;
        for (long long int i = 99999; i >= 0; i--)
        {
            if (Query_Index[i] != -1)
            {
                cout << "The fragment " << Queries_AR_obj.Query_name(Query_Index[i]) << " found at index - " << i << endl;
                count++;
            }
            if (count == 20)
                break;
        }

        /*
            Making the count variable  to 0 to print the 20 query fragments for the first 1M fragments of larger indices.
            Process is same as 10K fragments.
        */
        cout << "Printing the 20 query fragments found within the subject dataset that have the largest indices (i.e. found later in the subject) for the first 1M." << endl;
        count = 0;
        for (long long int i = 999999; i >= 0; i--)
        {
            if (Query_Index[i] != -1)
            {
                cout << "The fragment " << Queries_AR_obj.Query_name(Query_Index[i]) << " found at index - " << i << endl;
                count++;
            }
            if (count == 20)
                break;
        }

        /*
            How long would it take to search for every possible 32-character long fragment of the subject dataset within the query dataset?
        */
        clock_t begin = clock();
        for (long long int i = 0; i <= genomeIndex - 32; i++)
        {
            char temp[32 + 1]; // +1 for null-terminator
            for (long long int j = i; j < i + 32; j++)
            {
                temp[j - i] = genome[j];
            }
            temp[32] = '\0'; // Null-terminate the char array
            Queries_AR_obj.search(temp);
        }
        clock_t end = clock();
        executionTime = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
        cout << "Time taken for every possible 32-character long fragment of the subject dataset within the query dataset: " << executionTime << " seconds" << endl;
    }

    if (part == "partB")
    {
        // to store the genome i.e, subject data.
        char genome[4000000000];
        // maintaing the size of genome array.
        long long int genomeIndex = 0;
        // reading the genome sequence into genome array.
        genomeSeqRead(path2, genome, genomeIndex);
        // An instance to the Queries_AR class.
        Queries_AR Queries_AR_obj = Queries_AR(path1);
        // Reading the 100M queries into the Query_fragments array which is a private member of class Queries_AR class.
        Queries_AR_obj.Read_Queries();
        // sorting the query_fragments using the quick sort method from Queries_AR class.
        Queries_AR_obj.sort();
        // For each genome index upto 10M, storing query_index if a hit is found or else -1.
        // Maintaining this array so that it helps in printing the 20Query fragments of first 10K,100K,1M of larger indices.
        long long int Query_Index[maxQueriesLen];

        /*
            For each genome index upto 10K indices, taking the substring of length 32. This substring is treated as target fragment that is to be searched in the Query_Fragments[] array. If a hit is found, then search function would return index of the Query_fragments[] array or else -1. The search function implementation is binary search.
        */
        clock_t startTime = clock(); // Record the start time
        for (long long int i = 0; i < 10000; i++)
        {
            char temp[32 + 1]; // +1 for null-terminator
            for (long long int j = i; j < i + 32; j++)
            {
                temp[j - i] = genome[j];
            }
            temp[32] = '\0'; // Null-terminate the char array

            Query_Index[i] = Queries_AR_obj.binarySearch(temp);
        }
        clock_t endTime = clock(); // Record the end time
        double executionTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
        // Output the time taken in seconds
        cout << "Time taken for first 10k fragments: " << executionTime << " seconds" << endl;

        /*
            For each genome index upto 100K indices, taking the substring of length 32. This substring is treated as target fragment that is to be searched in the Query_Fragments[] array. If a hit is found, then search function would return index of the Query_fragments[] array or else -1. The search function implementation is binary search.
        */
        for (long long int i = 10000; i < 100000; i++)
        {
            char temp[32 + 1]; // +1 for null-terminator
            for (long long int j = i; j < i + 32; j++)
            {
                temp[j - i] = genome[j];
            }
            temp[32] = '\0'; // Null-terminate the char array

            Query_Index[i] = Queries_AR_obj.binarySearch(temp);
        }
        clock_t endTime1 = clock(); // Record the end time
        executionTime = static_cast<double>(endTime1 - startTime) / CLOCKS_PER_SEC;
        cout << "Time taken for first 100k: " << executionTime << " seconds" << endl;

        /*
            For each genome index upto 1M indices, taking the substring of length 32. This substring is treated as target fragment that is to be searched in the Query_Fragments[] array. If a hit is found, then search function would return index of the Query_fragments[] array or else -1. The search function implementation is binary search.
        */
        for (long long int i = 100000; i < maxQueriesLen; i++)
        {
            char temp[32 + 1]; // +1 for null-terminator
            for (long long int j = i; j < i + 32; j++)
            {
                temp[j - i] = genome[j];
            }
            temp[32] = '\0'; // Null-terminate the char array

            Query_Index[i] = Queries_AR_obj.binarySearch(temp);
        }
        clock_t endTime2 = clock(); // Record the end time
        executionTime = static_cast<double>(endTime2 - startTime) / CLOCKS_PER_SEC;
        cout << "Time taken for 1M fragments: " << executionTime << " seconds" << endl;

        /*
            Print the 20 query fragments found within the subject dataset that have the largest indices (i.e. found later in the subject) for the first 10K.
            Since, we need to print the query_fragments of the larger indices of the subject dataset. Therefore, traversing from 9999 for the first 10K fragments.
            We have already maintained Query_Index[] arr which gives the query_index of query_fragments[] array if there is a hit from substring formed from the subject index or else -1.
            So, if there is a hit, we are printing the query_fragment using the Query_name() method from the Query_AR class using the instance of that class.
            And maintaining a count variable to exit the loop after printing the 20 query fragments.
        */
        cout << "Printing the 20 query fragments found within the subject dataset that have the largest indices (i.e. found later in the subject) for the first 10K." << endl;
        int count = 0;
        for (long long int i = 9999; i >= 0; i--)
        {
            if (Query_Index[i] != -1)
            {
                cout << "The fragment " << Queries_AR_obj.Query_name(Query_Index[i]) << " found at index - " << i << endl;
                count++;
            }
            if (count == 20)
                break;
        }

        /*
            Making the count variable  to 0 to print the 20 query fragments for the first 100K fragments of larger indices.
            Process is same as 10K fragments.
        */
        cout << "Printing the 20 query fragments found within the subject dataset that have the largest indices (i.e. found later in the subject) for the first 100K." << endl;
        count = 0;
        for (long long int i = 99999; i >= 0; i--)
        {
            if (Query_Index[i] != -1)
            {
                cout << "The fragment " << Queries_AR_obj.Query_name(Query_Index[i]) << " found at index - " << i << endl;
                count++;
            }
            if (count == 20)
                break;
        }

        /*
             Making the count variable  to 0 to print the 20 query fragments for the first 100K fragments of larger indices.
             Process is same as 10K fragments.
         */
        cout << "Printing the 20 query fragments found within the subject dataset that have the largest indices (i.e. found later in the subject) for the first 1M." << endl;
        count = 0;
        for (long long int i = 999999; i >= 0; i--)
        {
            if (Query_Index[i] != -1)
            {
                cout << "The fragment " << Queries_AR_obj.Query_name(Query_Index[i]) << " found at index - " << i << endl;
                count++;
            }
            if (count == 20)
                break;
        }

        /*
            How long would it take to search for every possible 32-character long fragment of the subject dataset within the query dataset?
        */
        clock_t begin = clock();
        for (long long int i = 0; i <= genomeIndex - 32; i++)
        {
            char temp[32 + 1]; // +1 for null-terminator
            for (long long int j = i; j < i + 32; j++)
            {
                temp[j - i] = genome[j];
            }
            temp[32] = '\0'; // Null-terminate the char array
            Queries_AR_obj.binarySearch(temp);
        }
        clock_t end = clock();
        executionTime = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
        cout << "Time taken for every possible 32-character long fragment of the subject dataset within the query dataset: " << executionTime << " seconds" << endl;
    }

    return (0);
}
