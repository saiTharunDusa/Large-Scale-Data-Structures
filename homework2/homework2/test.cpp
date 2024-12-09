#include <deepstate/DeepState.hpp>
#include <deepstate/DeepState.h>
#include "header.h"
#include <fstream>

// This test file is based on the style of the provided DeepState test code snippet.
// It tests the Queries_AR class by creating a small, controlled input file and verifying
// that queries can be read, searched, sorted, and retrieved correctly.

using namespace deepstate;

class QueriesARTest : public Test {
protected:
    std::string queries_path;
    Queries_AR *queries_obj;

    virtual void SetUp() {
        // Create a temporary queries file with known fragments
        queries_path = "test_queries.fa";
        std::ofstream out(queries_path);
        // Insert a few lines with '>' to simulate FASTA headers
        out << ">query_header_1" << "\n"
            << "ACGTACGTACGTACGTACGTACGTACGTACGT" << "\n"
            << ">query_header_2" << "\n"
            << "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG" << "\n"
            << ">query_header_3" << "\n"
            << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << "\n"
            << ">query_header_4" << "\n"
            << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT" << "\n";
        out.close();

        queries_obj = new Queries_AR(queries_path);
        queries_obj->Read_Queries();
    }

    virtual void TearDown() {
        // Cleanup
        if (queries_obj) {
            delete queries_obj;
            queries_obj = nullptr;
        }
        remove(queries_path.c_str());
    }
};

TEST_F(QueriesARTest, SearchExistingFragment) {
    // Search for a known fragment
    char target[33] = "ACGTACGTACGTACGTACGTACGTACGTACGT";
    ASSERT_TRUE(queries_obj->search(target) != -1)
        << "Known fragment not found using linear search.";
}

TEST_F(QueriesARTest, SearchNonExistingFragment) {
    // Search for a random fragment that doesn't exist
    char target[33] = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
    ASSERT_TRUE(queries_obj->search(target) == -1)
        << "Non-existing fragment found unexpectedly.";
}

TEST_F(QueriesARTest, BinarySearchExistingFragment) {
    // Sort the queries first
    queries_obj->sort();
    char target[33] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    ASSERT_TRUE(queries_obj->binarySearch(target) != -1)
        << "Known fragment not found using binary search after sorting.";
}

TEST_F(QueriesARTest, BinarySearchNonExistingFragment) {
    queries_obj->sort();
    char target[33] = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
    ASSERT_TRUE(queries_obj->binarySearch(target) == -1)
        << "Non-existing fragment found unexpectedly by binary search.";
}

TEST_F(QueriesARTest, QueryNameRetrieval) {
    // Ensure we can retrieve a known fragment by index
    char target[33] = "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT";
    long long idx = queries_obj->search(target);
    ASSERT_TRUE(idx != -1) << "Target fragment not found.";
    ASSERT_EQ(queries_obj->Query_name(idx), std::string(target))
        << "Returned fragment does not match the expected query.";
}
