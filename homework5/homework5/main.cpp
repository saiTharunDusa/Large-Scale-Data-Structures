#include "header.h"

int main(int argc, char **argv)
{
    string path1 = argv[1];
    string path2 = argv[2];
    string part = argv[3];
    char genome[4000000000];
    // maintains the size of the genome array.
    long long int genomeIndex = 0;
    // reading the entire genome into single character array.
    genomeSeqRead(path2, genome, genomeIndex);
    srand(time(NULL));
    // Pick a random 50K long segment
    long long int segmentIndex = rand() % (genomeIndex - 50000 + 1);
    long long int segment_size = 50000;
    char *segment_50k = new char[segment_size];
    long long int index = 0;
    for (long long int i = segmentIndex; i < segmentIndex + segment_size; i++)
    {
        if (genome[i] == 'N')
            segment_50k[index] = 'A';
        else
            segment_50k[index] = genome[i];
        index++;
    }
    segment_50k[index] = '\0';

    if (part == "partA")
    {
        Prefix_Trie obj1;
        // Generate the 5k random 32-mers from the segment_50k and store them in a prefix trie.
        long long int size = 0;
        for (long long int i = 0; i < 5000; i++)
        {
            long long int random_index = rand() % (segment_size - 32 + 1);
            char fragment[33];
            index = 0;
            for (long long int j = random_index; j < random_index + 32; j++)
            {
                fragment[index] = segment_50k[j];
                index++;
            }
            fragment[index] = '\0';
            size += obj1.insert(fragment);
        }
        cout << "The size of the trie nodes for 5K random 32 - mers is " << size << "\n";
        size = 0;
        // Generate the 50k random 32-mers from the segment_50k and store them in a prefix trie.
        for (long long int i = 0; i < 50000; i++)
        {
            long long int random_index = rand() % (segment_size - 32 + 1);
            char fragment[33];
            index = 0;
            for (long long int j = random_index; j < random_index + 32; j++)
            {
                fragment[index] = segment_50k[j];
                index++;
            }
            fragment[index] = '\0';
            size += obj1.insert(fragment);
        }
        cout << "The size of the trie nodes for 50K random 32 - mers is " << size << "\n";
        size = 0;
        // Generate the 100k random 32-mers from the segment_50k and store them in a prefix trie.
        for (long long int i = 0; i < 100000; i++)
        {
            long long int random_index = rand() % (segment_size - 32 + 1);
            char fragment[33];
            index = 0;
            for (long long int j = random_index; j < random_index + 32; j++)
            {
                fragment[index] = segment_50k[j];
                index++;
            }
            fragment[index] = '\0';
            size += obj1.insert(fragment);
        }
        cout << "The size of the trie nodes for 100K random 32 - mers is " << size << "\n";
        size = 0;
        // Generate the 1M random 32-mers from the segment_50k and store them in a prefix trie.
        for (long long int i = 0; i < 1000000; i++)
        {
            long long int random_index = rand() % (segment_size - 32 + 1);
            char fragment[33];
            index = 0;
            for (long long int j = random_index; j < random_index + 32; j++)
            {
                fragment[index] = segment_50k[j];
                index++;
            }
            fragment[index] = '\0';
            size += obj1.insert(fragment);
        }
        cout << "The size of the trie nodes for 1M random 32 - mers is " << size << "\n";
        // Iterate through all possible 32-mers in the segment, using each to search / traverse the prefix trie with up to 1 mismatch.
        long long int hits = 0;
        for (long long int i = 0; i < segment_size - 32 + 1; i++)
        {
            char fragment[33];
            int index = 0;
            for (long long int j = i; j < i + 32; j++)
            {
                fragment[index] = segment_50k[j];
                index++;
            }
            fragment[index] = '\0';
            if (obj1.tree_traversal(fragment, true) == true)
            {
                hits++;
            }
        }
        cout << " The total no of hits by iterating through all possible 36-mers in segment, using each to search / traverse the prefix trie with up to 1 mismatch are - " << hits << endl;
    }
    if (part == "partB")
    {
        Prefix_Trie obj2;
        // Generate the 5k random 32-mers from the segment_50k and store them in a prefix trie.
        long long int size = 0;
        for (long long int i = 0; i < 5000; i++)
        {
            long long int random_index = rand() % (segment_size - 32 + 1);
            char fragment[33];
            index = 0;
            for (long long int j = random_index; j < random_index + 32; j++)
            {
                fragment[index] = segment_50k[j];
                double random_error = rand() / static_cast<double>(RAND_MAX);
                if (random_error >= 0.05)
                {
                    // A c G T
                    if (segment_50k[j] == 'A')
                        fragment[index] = 'T';
                    else if (segment_50k[j] == 'C')
                        fragment[index] = 'G';
                    else if (segment_50k[j] == 'G')
                        fragment[index] = 'C';
                    else
                        fragment[index] = 'A';
                }

                index++;
            }
            fragment[index] = '\0';
            size += obj2.insert(fragment);
        }
        // Generate the 50k random 32-mers from the segment_50k and store them in a prefix trie.
        size = 0;
        for (long long int i = 0; i < 50000; i++)
        {
            long long int random_index = rand() % (segment_size - 32 + 1);
            char fragment[33];
            index = 0;
            for (long long int j = random_index; j < random_index + 32; j++)
            {
                fragment[index] = segment_50k[j];
                double random_error = rand() / static_cast<double>(RAND_MAX);
                if (random_error >= 0.05)
                {
                    // A c G T
                    if (segment_50k[j] == 'A')
                        fragment[index] = 'T';
                    else if (segment_50k[j] == 'C')
                        fragment[index] = 'G';
                    else if (segment_50k[j] == 'G')
                        fragment[index] = 'C';
                    else
                        fragment[index] = 'A';
                }
                index++;
            }
            fragment[index] = '\0';
            size += obj2.insert(fragment);
        }
        cout << "The size of the trie nodes for 50K random 32 - mers is " << size << "\n";
        // Generate the 100k random 32-mers from the segment_50k and store them in a prefix trie.
        size = 0;
        for (long long int i = 0; i < 100000; i++)
        {
            long long int random_index = rand() % (segment_size - 32 + 1);
            char fragment[33];
            index = 0;
            for (long long int j = random_index; j < random_index + 32; j++)
            {
                fragment[index] = segment_50k[j];
                double random_error = rand() / static_cast<double>(RAND_MAX);
                if (random_error >= 0.05)
                {
                    // A c G T
                    if (segment_50k[j] == 'A')
                        fragment[index] = 'T';
                    else if (segment_50k[j] == 'C')
                        fragment[index] = 'G';
                    else if (segment_50k[j] == 'G')
                        fragment[index] = 'C';
                    else
                        fragment[index] = 'A';
                }
                index++;
            }
            fragment[index] = '\0';
            size += obj2.insert(fragment);
        }
        cout << "The size of the trie nodes for 100K random 32 - mers is " << size << "\n";
        // Generate the 1M random 32-mers from the segment_50k and store them in a prefix trie.
        size = 0;
        for (long long int i = 0; i < 1000000; i++)
        {
            long long int random_index = rand() % (segment_size - 32 + 1);
            char fragment[33];
            index = 0;
            for (long long int j = random_index; j < random_index + 32; j++)
            {
                fragment[index] = segment_50k[j];
                double random_error = rand() / static_cast<double>(RAND_MAX);
                if (random_error >= 0.05)
                {
                    // A c G T
                    if (segment_50k[j] == 'A')
                        fragment[index] = 'T';
                    else if (segment_50k[j] == 'C')
                        fragment[index] = 'G';
                    else if (segment_50k[j] == 'G')
                        fragment[index] = 'C';
                    else
                        fragment[index] = 'A';
                }
                index++;
            }
            fragment[index] = '\0';
            size += obj2.insert(fragment);
        }
        cout << "The size of the trie nodes for 1M random 32 - mers is " << size << "\n";
        // Iterate through all possible 32-mers in the segment, using each to search / traverse the prefix trie with up to 1 mismatch.
        long long int hits = 0;
        for (long long int i = 0; i < segment_size - 32 + 1; i++)
        {
            char fragment[33];
            int index = 0;
            for (long long int j = i; j < i + 32; j++)
            {
                fragment[index] = segment_50k[j];
                index++;
            }
            fragment[index] = '\0';
            if (obj2.tree_traversal(fragment, true) == true)
            {
                hits++;
            }
        }
        cout << " The total no of hits by iterating through all possible 36-mers in segment, using each to search / traverse the prefix trie with up to 1 mismatch are - " << hits << endl;
    }
    if (part == "partC")
    {
        Prefix_Trie obj3(path1);
        obj3.Read_Queries();
        obj3.traverse_queries();
        long long int hits = 0;
        // estimations
        // For 100K
        long long int segment_100k_index = rand() % (genomeIndex - 100000 + 1);
        char segment_100k[100000];
        long long int index = 0;
        for (long long int i = segment_100k_index; i < segment_100k_index + 100000; i++)
        {
            if (genome[i] == 'N')
                segment_100k[index] = 'A';
            else
                segment_100k[index] = genome[i];
            index++;
        }
        clock_t startTime = clock();
        for (long long int i = 0; i < 100000 - 32 + 1; i++)
        {
            char fragment[33];
            index = 0;
            for (long long int j = i; j < i + 32; j++)
            {
                fragment[index] = segment_100k[j];
                index++;
            }
            fragment[index] = '\0';
            if (obj3.tree_traversal(fragment, false) == true)
            {
                hits++;
            }
        }

        clock_t endTime = clock();
        double executionTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
        cout << "Time taken to find all 32-mers of 100K character segments within the prefix trie is " << executionTime << endl;
        cout << " The total no of perfect hits by iterating through all possible 32-mers in 100K segment, using each to search / traverse the prefix trie - " << hits << endl;
        // For 1M
        hits = 0;
        long long int segment_1M_index = rand() % (genomeIndex - 1000000 + 1);
        char segment_1M[1000000];
        index = 0;
        for (long long int i = segment_1M_index; i < segment_1M_index + 1000000; i++)
        {
            if (genome[i] == 'N')
                segment_1M[index] = 'A';
            else
                segment_1M[index] = genome[i];
            index++;
        }
        clock_t startTime1 = clock();
        for (long long int i = 0; i < 1000000 - 32 + 1; i++)
        {
            char fragment[33];
            index = 0;
            for (long long int j = i; j < i + 32; j++)
            {
                fragment[index] = segment_1M[j];
                index++;
            }
            fragment[index] = '\0';
            if (obj3.tree_traversal(fragment, false) == true)
            {
                hits++;
            }
        }
        clock_t endTime1 = clock();
        double executionTime1 = static_cast<double>(endTime1 - startTime1) / CLOCKS_PER_SEC;
        cout << "Time taken to find all 32-mers of 1M character segments within the prefix trie is " << executionTime1 << endl;
        cout << " The total no of perfect hits by iterating through all possible 32-mers in 1M segment, using each to search / traverse the prefix trie - " << hits << endl;
        // 100million.
        // 100000000
        hits = 0;
        long long int segment_100M_index = rand() % (genomeIndex - 100000000 + 1);
        char segment_100M[100000000];
        index = 0;
        for (long long int i = segment_100M_index; i < segment_100M_index + 100000000; i++)
        {
            if (genome[i] == 'N')
                segment_100M[index] = 'A';
            else
                segment_100M[index] = genome[i];
            index++;
        }
        clock_t startTime2 = clock();
        for (long long int i = 0; i < 100000000 - 32 + 1; i++)
        {
            char fragment[33];
            index = 0;
            for (long long int j = i; j < i + 32; j++)
            {
                fragment[index] = segment_100M[j];
                index++;
            }
            fragment[index] = '\0';
            if (obj3.tree_traversal(fragment, false) == true)
            {
                hits++;
            }
        }
        clock_t endTime2 = clock();
        double executionTime2 = static_cast<double>(endTime2 - startTime2) / CLOCKS_PER_SEC;
        cout << "Time taken to find all 32-mers of 100M character segments within the prefix trie is " << executionTime2 << endl;
        cout << " The total no of perfect hits by iterating through all possible 32-mers in 100M segment, using each to search / traverse the prefix trie - " << hits << endl;
        // For entire genome
        hits = 0;
        index = 0;
        clock_t startTime3 = clock();
        for (long long int i = 0; i < genomeIndex - 32 + 1; i++)
        {
            char fragment[33];
            index = 0;
            for (long long int j = i; j < i + 32; j++)
            {
                fragment[index] = genome[j];
                index++;
            }
            fragment[index] = '\0';
            if (obj3.tree_traversal(fragment, false) == true)
            {
                hits++;
            }
        }
        clock_t endTime3 = clock();
        double executionTime3 = static_cast<double>(endTime3 - startTime3) / CLOCKS_PER_SEC;
        cout << "Time taken to find all 32-mers of entire genome within the prefix trie is " << executionTime3 << endl;
        cout << " The total no of perfect hits by iterating through all possible 32-mers in entire genome, using each to search / traverse the prefix trie - " << hits << endl;
    }
    return (0);
}
