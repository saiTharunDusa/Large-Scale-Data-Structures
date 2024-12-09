#include <deepstate/DeepState.hpp>
#include "header.h"
#include <cstring>

using namespace deepstate;

// Symbolic test for search method
TEST(SearchTest, SymbolicSearchTest) {
    // Create test object
    Queries_AR queries;
    queries.Read_Queries(); 

    // Generate symbolic input
    char target[33];  // 32 chars + null terminator
    for (int i = 0; i < 32; i++) {
        target[i] = DeepState_Char();
    }
    target[32] = '\0';  // Ensure null termination
    
    // Perform search
    long long int result = queries.search(target);
    
    // Basic assertions
    ASSERT(result >= -1);
    ASSERT(result < maxQueriesLen);
}

// Symbolic test for binary search
TEST(SearchTest, SymbolicBinarySearchTest) {
    // Create sorted queries
    Queries_AR queries;
    queries.Read_Queries();
    queries.sort();

    // Generate symbolic input
    char target[33];  // 32 chars + null terminator
    for (int i = 0; i < 32; i++) {
        target[i] = DeepState_Char();
    }
    target[32] = '\0';  // Ensure null termination
    
    // Perform binary search
    long long int result = queries.binarySearch(target);
    
    // Basic assertions
    ASSERT(result >= -1);
    ASSERT(result < maxQueriesLen);
}

// Test genome sequence reading
TEST(GenomeTest, GenomeReadTest) {
    // Generate symbolic filepath
    char filepath[256];
    for (int i = 0; i < 255; i++) {
        filepath[i] = DeepState_Char();
    }
    filepath[255] = '\0';

    // Genome buffer
    char genome[4000000000];
    long long int genomeIndex = 0;

    // Attempt to read genome sequence (will likely fail for random paths)
    try {
        genomeSeqRead(filepath, genome, genomeIndex);
    } catch (...) {
        // Expect file open failure for random paths
    }

    // Basic sanity checks
    ASSERT(genomeIndex >= 0);
}

// Memory allocation test
TEST(QueriesTest, MemoryAllocationTest) {
    Queries_AR* queries = new Queries_AR();
    
    // Verify object creation
    ASSERT(queries != nullptr);

    // Cleanup
    delete queries;
}

// Destructor behavior test
TEST(QueriesTest, DestructorTest) {
    // Scope-based test to check destructor behavior
    {
        Queries_AR queries;
        queries.Read_Queries();
    } // Destructor called here
    
    // If we reach here without crash, destructor worked
    ASSERT(true);
}

// Entry point for DeepState
int main(int argc, char** argv) {
    return DeepState_Run();
}
