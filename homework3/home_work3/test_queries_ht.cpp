#include <deepstate/DeepState.hpp>
#include "header.h"

using namespace deepstate;

// Define a test fixture for the Queries_HT class
class QueriesHTTest : public Test {
protected:
    // Utility function to generate a random DNA fragment of length 16
    std::string GenerateRandomFragment() {
        static const char nucleotides[] = {'A', 'C', 'G', 'T'};
        std::string fragment;
        for (int i = 0; i < 16; i++) {
            fragment += nucleotides[DeepState_Choose(4)];
        }
        return fragment;
    }
};

// Test case to check if fragments are inserted correctly into the hash table
TEST_F(QueriesHTTest, InsertAndSearchFragment) {
    long long int hashTableSize = DeepState_IntInRange(100, 100000);  // Random hash table size between 100 and 100000
    Queries_HT ht(hashTableSize);
    long long int collisions = 0;

    // Generate a random fragment and insert it into the hash table
    std::string fragment = GenerateRandomFragment();
    char fragmentArr[17];
    strcpy(fragmentArr, fragment.c_str());
    ht.insert(fragmentArr, collisions);

    // Verify that the fragment can be found in the hash table
    ASSERT_TRUE(ht.search(fragmentArr)) << "Fragment was not found after insertion.";
}

// Test case to check for collisions during insertion
TEST_F(QueriesHTTest, InsertCollisions) {
    long long int hashTableSize = 100;  // Small hash table to force collisions
    Queries_HT ht(hashTableSize);
    long long int collisions = 0;

    // Insert multiple random fragments to increase the chance of collisions
    for (int i = 0; i < 50; i++) {
        std::string fragment = GenerateRandomFragment();
        char fragmentArr[17];
        strcpy(fragmentArr, fragment.c_str());
        ht.insert(fragmentArr, collisions);
    }

    // Check that collisions have occurred
    ASSERT_GT(collisions, 0) << "Expected collisions, but none occurred.";
}

// Test case to check behavior with an empty hash table
TEST_F(QueriesHTTest, SearchInEmptyTable) {
    long long int hashTableSize = DeepState_IntInRange(100, 1000);
    Queries_HT ht(hashTableSize);

    // Generate a random fragment and attempt to search for it
    std::string fragment = GenerateRandomFragment();
    char fragmentArr[17];
    strcpy(fragmentArr, fragment.c_str());

    ASSERT_FALSE(ht.search(fragmentArr)) << "Found fragment in an empty hash table, which is unexpected.";
}

// Test case for the radixVal function
TEST_F(QueriesHTTest, RadixValComputation) {
    long long int hashTableSize = 1000;
    Queries_HT ht(hashTableSize);

    std::string fragment = "ACGTACGTACGTACGT";
    char fragmentArr[17];
    strcpy(fragmentArr, fragment.c_str());

    long long int radixValue = ht.radixVal(fragmentArr);
    ASSERT_GE(radixValue, 0) << "Radix value should be non-negative.";
}

