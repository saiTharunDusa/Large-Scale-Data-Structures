void Queries_BL::fuzzySearch(const char *genome, unsigned long long int numFragments)
{
    srand(time(nullptr));

    cout << "Fuzzy Search Started..." << endl;
    int hits;
    int queryLength = 32;

    hits = 0;
    for (unsigned long long int i = 0; i < numFragments; ++i)
    {
        // Randomly select a position in the genome
        int index = rand() % (strlen(genome) - queryLength);
        string subjectFragment = string(genome + index, queryLength);

        Node **subjectHashTable;
        int fragmentLength = 16;
        int n_mers = queryLength - fragmentLength + 1;
        for (int k = 0; k < n_mers; k++)
        {
            string fragment = subjectFragment.substr(k, fragmentLength);
            insert(subjectHashTable, fragment.c_str(), k);
        }

        // Perform fuzzy searching within the query dataset using NW algorithm
        for (unsigned long long int j = 0; j < numQueries; ++j)
        {
            string query = queries[j];
            int t_index;
            for (int k = 0; k < n_mers; k++)
            {
                string fragment = query.substr(k, fragmentLength);
                t_index = search(subjectHashTable, fragment.c_str());
                if (t_index != -1)
                {
                    string searchFragment = string(genome + index + t_index - 32, queryLength);
                    int similarityScore = needleman_wunsch(queries[j], subjectFragment.c_str(), queryLength);
                    if (similarityScore >= 58)
                    { // Assuming 30 as the threshold for a hit with up to 2 mismatches
                        ++hits;
                        break; // Break out of the inner loop once a hit is found
                    }
                    searchFragment = string(genome + index + t_index + 32, queryLength);
                    similarityScore = needleman_wunsch(queries[j], subjectFragment.c_str(), queryLength);
                    if (similarityScore >= 58)
                    { // Assuming 30 as the threshold for a hit with up to 2 mismatches
                        ++hits;
                        break; // Break out of the inner loop once a hit is found
                    }
                }
            }
        }
    }
    cout << "Hits with up to 2 mismatches for fragments = " << input_num_queries
         << " and numQueries = " << numQueries << ": " << hits << endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    cout << "Time taken for search: " << duration.count() << " seconds" << endl;
}