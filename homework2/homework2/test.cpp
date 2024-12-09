#include <deepstate/DeepState.hpp>
#include "header.h"

using namespace deepstate;

// Test fixture for Queries_AR class
class QueriesARTest : public ::testing::Test {
protected:
    Queries_AR queries;
};

// Test case for constructor
TEST(QueriesARTest, DefaultConstructor) {
    Queries_AR emptyQueries;
    // Verify initial state
    ASSERT_EQ(emptyQueries.Query_name(-1), "");
}

// Parametric test for search method
TEST(QueriesARTest, SearchMethodTest) {
    // Symbolic input generation
    char* target = DeepState_CString(32);
    
    Queries_AR queries;
    queries.Read_Queries(); // Load predefined queries

    // Perform search
    long long int result = queries.search(target);
    
    // Assertions
    ASSERT_GE(result, -1);
    ASSERT_LT(result, maxQueriesLen);
    
    // Optional: If target is found, verify query match
    if (result != -1) {
        ASSERT_STREQ(queries.Query_name(result).c_str(), target);
    }
}

// Binary search test with symbolic input
TEST(QueriesARTest, BinarySearchTest) {
    // Ensure queries are sorted before binary search
    Queries_AR sortedQueries;
    sortedQueries.Read_Queries();
    sortedQueries.sort();

    // Symbolic input generation
    char* target = DeepState_CString(32);
    
    // Perform binary search
    long long int result = sortedQueries.binarySearch(target);
    
    // Assertions
    ASSERT_GE(result, -1);
    ASSERT_LT(result, maxQueriesLen);
    
    // Optional: If target is found, verify query match
    if (result != -1) {
        ASSERT_STREQ(sortedQueries.Query_name(result).c_str(), target);
    }
}

// Memory allocation test
TEST(QueriesARTest, MemoryAllocationTest) {
    Queries_AR* queries = new Queries_AR();
    queries->Read_Queries();

    // Verify memory allocation for queries
    for (int i = 0; i < 10; ++i) {
        ASSERT_NE(queries->Query_name(i).c_str(), nullptr);
    }

    delete queries;
}

// Fuzz testing for genome sequence reading
TEST(GenomeTest, GenomeSequenceReadFuzz) {
    // Generate symbolic filepath
    const char* filepath = DeepState_CString(256);
    
    // Large genome buffer
    char genome[4000000000];
    long long int genomeIndex = 0;

    // Attempt to read genome sequence
    genomeSeqRead(filepath, genome, genomeIndex);

    // Assertions
    ASSERT_GE(genomeIndex, 0);
    ASSERT_LE(genomeIndex, 4000000000);
}

// Complex scenario test: Search after sorting
TEST(QueriesARTest, SearchAfterSortTest) {
    Queries_AR queries;
    queries.Read_Queries();
    queries.sort();

    // Symbolic target generation
    char* target = DeepState_CString(32);

    // Linear search after sorting
    long long int linearResult = queries.search(target);
    
    // Binary search
    long long int binaryResult = queries.binarySearch(target);

    // Results should be consistent
    ASSERT_EQ(linearResult, binaryResult);
}

// Edge case: Empty target search
TEST(QueriesARTest, EmptyTargetSearch) {
    Queries_AR queries;
    queries.Read_Queries();

    char emptyTarget[33] = {0};  // All null bytes
    long long int result = queries.search(emptyTarget);
    
    ASSERT_EQ(result, -1);
}

int main(int argc, char** argv) {
    return DeepState_Run(argc, argv);
}
