#include <gtest/gtest.h>
#include "header.h"

// Mock genomic and query data for testing.
const char *genomeMock = "ACGTACGTACGTACGTACGTACGTACGTACGTACGT";
const char *queryMock[] = {"ACGTACGT", "CGTACGTA", "GTACGTAC", "TACGTACG", "ACGTACGTACGT"};

class QueriesARMock : public Queries_AR {
public:
    QueriesARMock() : Queries_AR("") {}
    void Mock_Read_Queries() {
        Query_fragments = queryMock;
        num_queries = 5;
    }
};

TEST(ArgumentHandlingTest, InvalidArguments) {
    char *argv[] = {(char *)"./homework", (char *)"partA"};
    int argc = 2;
    ASSERT_EXIT(main(argc, argv), ::testing::ExitedWithCode(-1), "Error: 2 input parameters expected");
}

TEST(GenomicDataTest, ReadGenomeData) {
    char genome[40];
    long long genomeIndex = 0;
    genomeSeqRead("mock_file.fa", genome, genomeIndex); // Mock file function.
    ASSERT_STREQ(genome, genomeMock);
}

TEST(SearchFunctionalityTest, LinearSearch) {
    QueriesARMock queriesAR;
    queriesAR.Mock_Read_Queries();
    ASSERT_EQ(queriesAR.search("ACGTACGT"), 0);
    ASSERT_EQ(queriesAR.search("GTACGTAC"), 2);
    ASSERT_EQ(queriesAR.search("NOEXIST"), -1);
}

TEST(SearchFunctionalityTest, BinarySearch) {
    QueriesARMock queriesAR;
    queriesAR.Mock_Read_Queries();
    queriesAR.sort(); // Ensures binary search is sorted.
    ASSERT_EQ(queriesAR.binarySearch("ACGTACGT"), 0);
    ASSERT_EQ(queriesAR.binarySearch("GTACGTAC"), 2);
    ASSERT_EQ(queriesAR.binarySearch("NOEXIST"), -1);
}

TEST(ExecutionTimeTest, Performance) {
    // Mock the genome and query sizes to test timing.
    char genome[100000]; // 100K characters
    for (int i = 0; i < 100000; ++i) {
        genome[i] = "ACGT"[i % 4];
    }

    QueriesARMock queriesAR;
    queriesAR.Mock_Read_Queries();

    clock_t start = clock();
    for (long long i = 0; i < 10000; ++i) {
        char temp[33] = {0};
        strncpy(temp, &genome[i], 32);
        queriesAR.search(temp);
    }
    clock_t end = clock();
    double execTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    ASSERT_LT(execTime, 5.0); // Ensure it runs within 5 seconds for mock data.
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
