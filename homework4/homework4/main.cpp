#include "header.h"

int main(int argc, char **argv)
{
    string path1 = argv[1];
    string path2 = argv[2];
    string part = argv[3];
    string problem = argv[4];

    if (problem == "problem1")
    {
        // initializing the random seed.
        srand(time(NULL));
        char genome[4000000000];
        unsigned int genomeIndex = 0;
        // reading the genome sequence into genome array.
        genomeSeqRead(path2, genome, genomeIndex);
        cout << "The size of the genome is " << genomeIndex << endl;
        // Precomputing the 32 length genome fragment by implementing 2D array of genome fragments.
        char *genome_fragments[genomeIndex - 32 + 1];
        // initialize to nullptr
        for (long long int i = 0; i < genomeIndex - 32 + 1; i++)
        {
            genome_fragments[i] = nullptr;
        }
        for (long long int i = 0; i < genomeIndex - 32 + 1; i++)
        {
            genome_fragments[i] = new char[33];
            strncpy(genome_fragments[i], genome + i, 32);
            genome_fragments[i][32] = '\0';
        }
        if (part == "partA")
        {

            //  reading the query fragments.
            Queries_NW obj = Queries_NW(path1);
            obj.Read_Queries();

            /*
                Comparing 100 random generated genome fragments of size 32 with 100Million query fragments to conduct fuzzy searching using NW algorithm would take more than 24 hours. So I would like to estimate the time for it by comparing
                100 genome fragments - 1K query fragments
                100 genome fragments - 10k query fragments
                1000 genome fragments - 100k query fragments.
            */
            for (long long int it = 0; it < 3; it++)
            {
                long long int query_size = 0;
                if (it == 0)
                    query_size = 1000;
                else if (it == 1)
                    query_size = 10000;
                else
                    query_size = 100000;
                clock_t startTime = clock(); // Record the start time
                long long int hits = 0;
                // for random 0.1K, iterating 0.1K times.
                for (long long int i = 0; i < 100; i++)
                {
                    long long int genomeSize = genomeIndex - 32 + 1;
                    long long int randomInd = (long long int)(rand() % genomeSize);
                    int score = obj.Needleman_Wunsch(genome_fragments[randomInd], query_size);
                    //  we have to find the no of hits with upto 2 mismatches
                    //  For 32 matches , 0 mismatches - the score is 64.
                    //  For 31 mathces, 1 mismatch - the score is (31 * 2) - 1 = 61
                    //  For 30 matches, 2 mismatches - the score is (30 * 2) - 2 = 58;
                    //  therefore, if the score is greater than or equal to 58, then it is a hit.
                    if (score >= 58)
                        hits++;
                }
                clock_t endTime = clock(); // Record the end time
                double executionTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
                // Output the time taken in seconds
                cout << "Time taken for randomly picked 0.1k fragments by comparing with " << query_size << "query fragments is : " << executionTime << " seconds" << endl;
                cout << "The total number of hits with up to 2 mismatches for randomly picked 0.1k fragments by comparing with " << query_size << "query fragments is : " << hits << endl;
            }
            /*
                Comparing 1000 random generated genome fragments of size 32 with 100Million query fragments to conduct fuzzy searching using NW algorithm would take more than 24 hours. So I would like to estimate the time for it by comparing
                1000 genome fragments - 1K query fragments
                1000 genome fragments - 10k query fragments
                1000 genome fragments - 100k query fragments.
            */
            for (long long int it = 0; it < 3; it++)
            {
                long long int query_size = 0;
                if (it == 0)
                    query_size = 1000;
                else if (it == 1)
                    query_size = 10000;
                else
                    query_size = 100000;
                clock_t startTime = clock(); // Record the start time
                long long int hits = 0;
                // for random 1K, iterating 1K times.
                for (long long int i = 0; i < 1000; i++)
                {
                    long long int genomeSize = genomeIndex - 32 + 1;
                    long long int randomInd = (long long int)(rand() % genomeSize);
                    int score = obj.Needleman_Wunsch(genome_fragments[randomInd], query_size);
                    //  we have to find the no of hits with upto 2 mismatches
                    //  For 32 matches , 0 mismatches - the score is 64.
                    //  For 31 mathces, 1 mismatch - the score is (31 * 2) - 1 = 61
                    //  For 30 matches, 2 mismatches - the score is (30 * 2) - 2 = 58;
                    //  therefore, if the score is greater than or equal to 58, then it is a hit.
                    if (score >= 58)
                        hits++;
                }
                clock_t endTime = clock(); // Record the end time
                double executionTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
                // Output the time taken in seconds
                cout << "Time taken for randomly picked 1k fragments by comparing with " << query_size << "query fragments is : " << executionTime << " seconds" << endl;
                cout << "The total number of hits with up to 2 mismatches for randomly picked 1k fragments by comparing with " << query_size << "query fragments is : " << hits << endl;
            }

            /*
                Comparing 10k random generated genome fragments of size 32 with 100Million query fragments to conduct fuzzy searching using NW algorithm would take more than 24 hours. So I would like to estimate the time for it by comparing
                10k genome fragments - 1K query fragments
                10k genome fragments - 10k query fragments
                10k genome fragments - 100k query fragments.
            */
            for (long long int it = 0; it < 3; it++)
            {
                long long int query_size = 0;
                if (it == 0)
                    query_size = 1000;
                else if (it == 1)
                    query_size = 10000;
                else
                    query_size = 100000;
                clock_t startTime = clock(); // Record the start time
                long long int hits = 0;
                // for random 10K, iterating 10K times.
                for (long long int i = 0; i < 10000; i++)
                {
                    long long int genomeSize = genomeIndex - 32 + 1;
                    long long int randomInd = (long long int)(rand() % genomeSize);
                    int score = obj.Needleman_Wunsch(genome_fragments[randomInd], query_size);
                    //  we have to find the no of hits with upto 2 mismatches
                    //  For 32 matches , 0 mismatches - the score is 64.
                    //  For 31 mathces, 1 mismatch - the score is (31 * 2) - 1 = 61
                    //  For 30 matches, 2 mismatches - the score is (30 * 2) - 2 = 58;
                    //  therefore, if the score is greater than or equal to 58, then it is a hit.
                    if (score >= 58)
                        hits++;
                }
                clock_t endTime = clock(); // Record the end time
                double executionTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
                // Output the time taken in seconds
                cout << "Time taken for randomly picked 10k fragments by comparing with " << query_size << "query fragments is : " << executionTime << " seconds" << endl;
                cout << "The total number of hits with up to 2 mismatches for randomly picked 10k fragments by comparing with " << query_size << "query fragments is : " << hits << endl;
            }

            /*
                Comparing 100k random generated genome fragments of size 32 with 100Million query fragments to conduct fuzzy searching using NW algorithm would take more than 24 hours. So I would like to estimate the time for it by comparing
                1000 genome fragments - 1K query fragments
                1000 genome fragments - 10k query fragments
                1000 genome fragments - 100k query fragments.
            */
            for (long long int it = 0; it < 3; it++)
            {
                long long int query_size = 0;
                if (it == 0)
                    query_size = 1000;
                else if (it == 1)
                    query_size = 10000;
                else
                    query_size = 100000;
                clock_t startTime = clock(); // Record the start time
                long long int hits = 0;
                // for random 100K, iterating 100K times.
                for (long long int i = 0; i < 100000; i++)
                {
                    long long int genomeSize = genomeIndex - 32 + 1;
                    long long int randomInd = (long long int)(rand() % genomeSize);
                    int score = obj.Needleman_Wunsch(genome_fragments[randomInd], query_size);
                    //  we have to find the no of hits with upto 2 mismatches
                    //  For 32 matches , 0 mismatches - the score is 64.
                    //  For 31 mathces, 1 mismatch - the score is (31 * 2) - 1 = 61
                    //  For 30 matches, 2 mismatches - the score is (30 * 2) - 2 = 58;
                    //  therefore, if the score is greater than or equal to 58, then it is a hit.
                    if (score >= 58)
                        hits++;
                }
                clock_t endTime = clock(); // Record the end time
                double executionTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
                // Output the time taken in seconds
                cout << "Time taken for randomly picked 100k fragments by comparing with " << query_size << "query fragments is : " << executionTime << " seconds" << endl;
                cout << "The total number of hits with up to 2 mismatches for randomly picked 100k fragments by comparing with " << query_size << "query fragments is : " << hits << endl;
            }
        }

        if (part == "partB")
        {
            // reading the query fragments.
            Queries_NW obj = Queries_NW(path1);
            obj.Read_Queries();
            srand(time(NULL));
            /*
                Comparing 100 completely random generated genome fragments of size 32 with 100Million query fragments to conduct fuzzy searching using NW algorithm would take more than 24 hours. So I would like to estimate the time for it by comparing
                100 genome fragments - 1K query fragments
                100 genome fragments - 10k query fragments
                100 genome fragments - 100k query fragments.
            */
            for (long long int it = 0; it < 3; it++)
            {
                long long int query_size = 0;
                if (it == 0)
                    query_size = 1000;
                else if (it == 1)
                    query_size = 10000;
                else
                    query_size = 100000;
                clock_t startTime = clock(); // Record the start time
                long long int hits = 0;
                // for random 0.1K, iterating 0.1K times.
                for (long long int i = 0; i < 100; i++)
                {
                    char tempArr[33];
                    // length of each fragment is 32.
                    for (int j = 0; j < 32; j++)
                    {
                        // A - 0, C - 1, T - 2, G - 3.
                        int random_number = rand() % 4;
                        if (random_number == 0)
                            tempArr[j] = 'A';
                        else if (random_number == 1)
                            tempArr[j] = 'C';
                        else if (random_number == 2)
                            tempArr[j] = 'T';
                        else
                            tempArr[j] = 'G';
                    }
                    tempArr[32] = '\0';
                    int score = obj.Needleman_Wunsch(tempArr, query_size);
                    //  we have to find the no of hits with upto 2 mismatches
                    //  For 32 matches , 0 mismatches - the score is 64.
                    //  For 31 mathces, 1 mismatch - the score is (31 * 2) - 1 = 61
                    //  For 30 matches, 2 mismatches - the score is (30 * 2) - 2 = 58;
                    //  therefore, if the score is greater than or equal to 58, then it is a hit.
                    if (score >= 58)
                        hits++;
                }
                clock_t endTime = clock(); // Record the end time
                double executionTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
                // Output the time taken in seconds
                cout << "Time taken for completely randomly picked 0.1k fragments by comparing with " << query_size << "query fragments is : " << executionTime << " seconds" << endl;
                cout << "The total number of hits with up to 2 mismatches for completely randomly picked 0.1k fragments by comparing with " << query_size << "query fragments is : " << hits << endl;
            }

            /*
                Comparing 1000 completely random generated genome fragments of size 32 with 100Million query fragments to conduct fuzzy searching using NW algorithm would take more than 24 hours. So I would like to estimate the time for it by comparing
                1000 genome fragments - 1K query fragments
                1000 genome fragments - 10k query fragments
                1000 genome fragments - 100k query fragments.
            */
            for (long long int it = 0; it < 3; it++)
            {
                long long int query_size = 0;
                if (it == 0)
                    query_size = 1000;
                else if (it == 1)
                    query_size = 10000;
                else
                    query_size = 100000;
                clock_t startTime = clock(); // Record the start time
                long long int hits = 0;
                // for random 1K, iterating 1K times.
                for (long long int i = 0; i < 1000; i++)
                {
                    char tempArr[33];
                    // length of each fragment is 32.
                    for (int j = 0; j < 32; j++)
                    {
                        // A - 0, C - 1, T - 2, G - 3.
                        int random_number = rand() % 4;
                        if (random_number == 0)
                            tempArr[j] = 'A';
                        else if (random_number == 1)
                            tempArr[j] = 'C';
                        else if (random_number == 2)
                            tempArr[j] = 'T';
                        else
                            tempArr[j] = 'G';
                    }
                    tempArr[32] = '\0';
                    int score = obj.Needleman_Wunsch(tempArr, query_size);
                    //  we have to find the no of hits with upto 2 mismatches
                    //  For 32 matches , 0 mismatches - the score is 64.
                    //  For 31 mathces, 1 mismatch - the score is (31 * 2) - 1 = 61
                    //  For 30 matches, 2 mismatches - the score is (30 * 2) - 2 = 58;
                    //  therefore, if the score is greater than or equal to 58, then it is a hit.
                    if (score >= 58)
                        hits++;
                }
                clock_t endTime = clock(); // Record the end time
                double executionTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
                // Output the time taken in seconds
                cout << "Time taken for completely randomly picked 1k fragments by comparing with " << query_size << "query fragments is : " << executionTime << " seconds" << endl;
                cout << "The total number of hits with up to 2 mismatches for completely randomly picked 1k fragments by comparing with " << query_size << "query fragments is : " << hits << endl;
            }

            /*
                Comparing 10k completely random generated genome fragments of size 32 with 100Million query fragments to conduct fuzzy searching using NW algorithm would take more than 24 hours. So I would like to estimate the time for it by comparing
                10k genome fragments - 1K query fragments
                10k genome fragments - 10k query fragments
                10k genome fragments - 100k query fragments.
            */
            for (long long int it = 0; it < 3; it++)
            {
                long long int query_size = 0;
                if (it == 0)
                    query_size = 1000;
                else if (it == 1)
                    query_size = 10000;
                else
                    query_size = 100000;
                clock_t startTime = clock(); // Record the start time
                long long int hits = 0;
                // for random 10K, iterating 10K times.
                for (long long int i = 0; i < 10000; i++)
                {
                    char tempArr[33];
                    // length of each fragment is 32.
                    for (int j = 0; j < 32; j++)
                    {
                        // A - 0, C - 1, T - 2, G - 3.
                        int random_number = rand() % 4;
                        if (random_number == 0)
                            tempArr[j] = 'A';
                        else if (random_number == 1)
                            tempArr[j] = 'C';
                        else if (random_number == 2)
                            tempArr[j] = 'T';
                        else
                            tempArr[j] = 'G';
                    }
                    tempArr[32] = '\0';
                    int score = obj.Needleman_Wunsch(tempArr, query_size);
                    //  we have to find the no of hits with upto 2 mismatches
                    //  For 32 matches , 0 mismatches - the score is 64.
                    //  For 31 mathces, 1 mismatch - the score is (31 * 2) - 1 = 61
                    //  For 30 matches, 2 mismatches - the score is (30 * 2) - 2 = 58;
                    //  therefore, if the score is greater than or equal to 58, then it is a hit.
                    if (score >= 58)
                        hits++;
                }
                clock_t endTime = clock(); // Record the end time
                double executionTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
                // Output the time taken in seconds
                cout << "Time taken for completely randomly picked 10k fragments by comparing with " << query_size << "query fragments is : " << executionTime << " seconds" << endl;
                cout << "The total number of hits with up to 2 mismatches for completely randomly picked 10k fragments by comparing with " << query_size << "query fragments is : " << hits << endl;
            }

            /*
                Comparing 100k completely random generated genome fragments of size 32 with 100Million query fragments to conduct fuzzy searching using NW algorithm would take more than 24 hours. So I would like to estimate the time for it by comparing
                100k genome fragments - 1K query fragments
                100k genome fragments - 10k query fragments
                100k genome fragments - 100k query fragments.
            */
            for (long long int it = 0; it < 3; it++)
            {
                long long int query_size = 0;
                if (it == 0)
                    query_size = 1000;
                else if (it == 1)
                    query_size = 10000;
                else
                    query_size = 100000;
                clock_t startTime = clock(); // Record the start time
                long long int hits = 0;
                // for random 100K, iterating 100K times.
                for (long long int i = 0; i < 100000; i++)
                {
                    char tempArr[33];
                    // length of each fragment is 32.
                    for (int j = 0; j < 32; j++)
                    {
                        // A - 0, C - 1, T - 2, G - 3.
                        int random_number = rand() % 4;
                        if (random_number == 0)
                            tempArr[j] = 'A';
                        else if (random_number == 1)
                            tempArr[j] = 'C';
                        else if (random_number == 2)
                            tempArr[j] = 'T';
                        else
                            tempArr[j] = 'G';
                    }
                    tempArr[32] = '\0';
                    int score = obj.Needleman_Wunsch(tempArr, query_size);
                    //  we have to find the no of hits with upto 2 mismatches
                    //  For 32 matches , 0 mismatches - the score is 64.
                    //  For 31 mathces, 1 mismatch - the score is (31 * 2) - 1 = 61
                    //  For 30 matches, 2 mismatches - the score is (30 * 2) - 2 = 58;
                    //  therefore, if the score is greater than or equal to 58, then it is a hit.
                    if (score >= 58)
                        hits++;
                }
                clock_t endTime = clock(); // Record the end time
                double executionTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
                // Output the time taken in seconds
                cout << "Time taken for completely randomly picked 100k fragments by comparing with " << query_size << "query fragments is : " << executionTime << " seconds" << endl;
                cout << "The total number of hits with up to 2 mismatches for completely randomly picked 100k fragments by comparing with " << query_size << "query fragments is : " << hits << endl;
            }
        }
    }

    if (problem == "problem2")
    {
        // to store the genome i.e, subject data.
        char genome[4000000000];
        // maintaing the size of genome array.
        unsigned int genomeIndex = 0;
        // reading the genome sequence into genome array.
        genomeSeqRead(path2, genome, genomeIndex);
        cout << "The size of the genome array is " << genomeIndex << endl;
        // Precomputing the 32 length genome fragment by implementing 2D array of genome fragments.
        char *genome_fragments[genomeIndex - 32 + 1];
        // initialize to nullptr
        for (long long int i = 0; i < genomeIndex - 32 + 1; i++)
        {
            genome_fragments[i] = nullptr;
        }
        for (long long int i = 0; i < genomeIndex - 32 + 1; i++)
        {
            genome_fragments[i] = new char[33];
            strncpy(genome_fragments[i], genome + i, 32);
            genome_fragments[i][32] = '\0';
        }
        cout << "32 - size genome fragments are precomputed. " << endl;
        if (part == "partA")
        {
            // reading the query fragments.
            Queries_BL obj = Queries_BL(path1);
            obj.Read_Queries();
            // Storing all the 16-mers of the query_fragments in a hash table.
            obj.insert16_mers_into_HT();
            cout << "16 - mers of 100Million queries are stored in the hash table" << endl;
            clock_t startTime0 = clock(); // Record the start time
            // for random 1K, iterating 1K times.
            long long int hits = 0;
            for (long long int i = 0; i < 1000; i++)
            {
                long long int genomeSize = genomeIndex - 32 + 1;
                long long int randomInd = (long long int)(rand() % genomeSize);
                char *genome_frag = genome_fragments[randomInd];
                // breaking into 16 mers and storing them in a hash table.
                for (int j = 0; j < 32 - 16 + 1; j++)
                {
                    char genome_16_mer[17];
                    int index = 0;
                    for (int k = j; k < j + 16; k++)
                    {
                        genome_16_mer[index] = genome_frag[k];
                        index++;
                    }
                    genome_16_mer[index] = '\0';
                    // if 16-mer of a genome_fragment is found in the 16-mers of query_framgent. Then we perform seed extension for smith waterman.
                    long long int query_index = obj.search(genome_16_mer);
                    if (query_index != -1)
                    {
                        long long int actual_index = randomInd + j;
                        int score = obj.seed_extension(genome_frag, actual_index, genome, query_index, true);
                        //  we have to find the no of hits with upto 2 mismatches
                        //  For 32 matches , 0 mismatches - the score is 64.
                        //  For 31 mathces, 1 mismatch - the score is (31 * 2) - 1 = 61
                        //  For 30 matches, 2 mismatches - the score is (30 * 2) - 2 = 58;
                        //  therefore, if the score is greater than or equal to 58, then it is a hit.
                        if (score >= 58)
                            hits++;
                    }
                }
            }
            clock_t endTime0 = clock(); // Record the end time
            double executionTime = static_cast<double>(endTime0 - startTime0) / CLOCKS_PER_SEC;
            // Output the time taken in seconds
            cout << "Time taken for randomly picked 1K fragments: " << executionTime << " seconds" << endl;
            cout << "The total number of hits with up to 2 mismatches for randomly picked 1K fragments: " << hits << endl;

            clock_t startTime1 = clock(); // Record the start time
            // for random 10K, iterating 10K times.
            hits = 0;
            for (long long int i = 0; i < 10000; i++)
            {
                long long int genomeSize = genomeIndex - 32 + 1;
                long long int randomInd = (long long int)(rand() % genomeSize);
                char *genome_frag = genome_fragments[randomInd];
                // breaking into 16 mers and storing them in a hash table.
                for (int j = 0; j < 32 - 16 + 1; j++)
                {
                    char genome_16_mer[17];
                    int index = 0;
                    for (int k = j; k < j + 16; k++)
                    {
                        genome_16_mer[index] = genome_frag[k];
                        index++;
                    }
                    genome_16_mer[index] = '\0';
                    long long int query_index = obj.search(genome_16_mer);
                    if (query_index != -1)
                    {
                        long long int actual_index = randomInd + j;
                        int score = obj.seed_extension(genome_frag, actual_index, genome, query_index, true);
                        //  we have to find the no of hits with upto 2 mismatches
                        //  For 32 matches , 0 mismatches - the score is 64.
                        //  For 31 mathces, 1 mismatch - the score is (31 * 2) - 1 = 61
                        //  For 30 matches, 2 mismatches - the score is (30 * 2) - 2 = 58;
                        //  therefore, if the score is greater than or equal to 58, then it is a hit.
                        if (score >= 58)
                            hits++;
                    }
                }
            }
            clock_t endTime1 = clock(); // Record the end time
            executionTime = static_cast<double>(endTime1 - startTime1) / CLOCKS_PER_SEC;
            // Output the time taken in seconds
            cout << "Time taken for randomly picked 10K fragments: " << executionTime << " seconds" << endl;
            cout << "The total number of hits with up to 2 mismatches for randomly picked 10K fragments: " << hits << endl;

            clock_t startTime2 = clock(); // Record the start time
            // for random 100K, iterating 100K times.
            hits = 0;
            for (long long int i = 0; i < 100000; i++)
            {
                long long int genomeSize = genomeIndex - 32 + 1;
                long long int randomInd = (long long int)(rand() % genomeSize);
                char *genome_frag = genome_fragments[randomInd];
                // breaking into 16 mers and storing them in a hash table.
                for (int j = 0; j < 32 - 16 + 1; j++)
                {
                    char genome_16_mer[17];
                    int index = 0;
                    for (int k = j; k < j + 16; k++)
                    {
                        genome_16_mer[index] = genome_frag[k];
                        index++;
                    }
                    genome_16_mer[index] = '\0';
                    long long int query_index = obj.search(genome_16_mer);
                    if (query_index != -1)
                    {
                        long long int actual_index = randomInd + j;
                        int score = obj.seed_extension(genome_frag, actual_index, genome, query_index, true);
                        //  we have to find the no of hits with upto 2 mismatches
                        //  For 32 matches , 0 mismatches - the score is 64.
                        //  For 31 mathces, 1 mismatch - the score is (31 * 2) - 1 = 61
                        //  For 30 matches, 2 mismatches - the score is (30 * 2) - 2 = 58;
                        //  therefore, if the score is greater than or equal to 58, then it is a hit.
                        if (score >= 58)
                            hits++;
                    }
                }
            }
            clock_t endTime2 = clock(); // Record the end time
            executionTime = static_cast<double>(endTime2 - startTime2) / CLOCKS_PER_SEC;
            // Output the time taken in seconds
            cout << "Time taken for randomly picked 100K fragments: " << executionTime << " seconds" << endl;
            cout << "The total number of hits with up to 2 mismatches for randomly picked 100K fragments: " << hits << endl;
        }
        if (part == "partB")
        {
            srand(time(nullptr));
            // reading the query fragments.
            Queries_BL obj = Queries_BL(path1);
            obj.Read_Queries();
            obj.insert16_mers_into_HT();
            long long int size = 0;
            long long int hits = 0;
            for (int it = 0; it < 3; it++)
            {
                if (it == 0)
                    size = 1000;
                else if (it == 1)
                    size = 10000;
                else
                    size = 100000;
                for (long long int i = 0; i < size; i++)
                {
                    // A - 0, C - 1, T - 2, G - 3.
                    int index = 0;
                    char tempArr[33];
                    // Generating completely random fragment.
                    for (long long int j = 0; j < 32; j++)
                    {
                        int random_number = rand() % 4;

                        if (random_number == 0)
                            tempArr[j] = 'A';
                        else if (random_number == 1)
                            tempArr[j] = 'C';
                        else if (random_number == 2)
                            tempArr[j] = 'T';
                        else
                            tempArr[j] = 'G';
                    }
                    tempArr[index] = '\0';
                    // break into 16 mers and storing them in a hash table.
                    for (int j = 0; j < 32 - 16 + 1; j++)
                    {
                        char genome_16_mer[17];
                        int index = 0;
                        for (int k = j; k < j + 16; k++)
                        {
                            genome_16_mer[index] = tempArr[k];
                            index++;
                        }
                        genome_16_mer[index] = '\0';
                        long long int query_index = obj.search(genome_16_mer);
                        if (query_index != -1)
                        {
                            int score = obj.seed_extension(tempArr, 0, tempArr, query_index, false);
                            //  we have to find the no of hits with upto 2 mismatches
                            //  For 32 matches , 0 mismatches - the score is 64.
                            //  For 31 mathces, 1 mismatch - the score is (31 * 2) - 1 = 61
                            //  For 30 matches, 2 mismatches - the score is (30 * 2) - 2 = 58;
                            //  therefore, if the score is greater than or equal to 58, then it is a hit.
                            if (score >= 58)
                                hits++;
                        }
                    }
                }
            }
        }
    }
    return (0);
}
