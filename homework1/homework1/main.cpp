// !!! Use the head command to make a smaller version of the dataset file to transfer to your laptop... for example
// head -2000 /common/contrib/classroom/inf503/hw_dataset.fa > /scratch/vyf2/sample_hw_dataset.fa
//... this will take 2000 lines from the time of file (1000 reads)
#include "header.h"

int main(int argc, char **argv)
{

	////////////////////////////////////////////////////////////////////////////////////
	// Lets do sanity checks to make sure the proper number of parameters were passed in
	////////////////////////////////////////////////////////////////////////////////////

	if (argc != 3)
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
	string part = argv[2];
	string path = argv[1];

	// storing the genome sequence data.
	char genome[4000000000];
	long long int genomeIndex = 0;
	// storing the names of scaffolds.
	char *scaffoldNames[maxScaffoldLength];
	// storing the lengths of scaffolds.
	long long int scaffoldLengths[maxScaffoldLength];
	// total no of scaffolds that would be useful in computing the genome statistics.
	long long int noOfScaffolds = 0;
	// totalLength of the scaffolds which would be useful in calculating the GC content.
	long long int totalLength = 0;

	if (part == "problem1A")
	{

		// reading the file and storing the genome sequence as well as scaffolds lengths,names.
		genomeSeqRead(path, genome, noOfScaffolds, scaffoldLengths, scaffoldNames, genomeIndex);
		// calculating the longest,second longest and average length of scaffolds.
		computeGenomeStatistics(noOfScaffolds, totalLength, scaffoldLengths, scaffoldNames, true);
	}
	else if (part == "problem1B")
	{

		// calling below two functions to store the genome data which would be useful in calculating GC content.
		// in the computeGenomeStastics functions flase flag variable is passed to control the print statments.
		// so that we could execute problem1A and problem1B separately.
		genomeSeqRead(path, genome, noOfScaffolds, scaffoldLengths, scaffoldNames, genomeIndex);
		computeGenomeStatistics(noOfScaffolds, totalLength, scaffoldLengths, scaffoldNames, false);
		clock_t startTime = clock();
		// calculating the GC content of the genome sequence.
		calculateGCContent(genome, totalLength, genomeIndex);
		clock_t endTime = clock();
		// calculating the time taken to execute this calculateGCContent() function using system time.
		double executionTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
		cout << "Execution time: " << executionTime << " seconds" << endl;
	}
	else
	{
		cerr << "Invalid part specified. Please choose 'part-A' or 'part-B'." << endl;
		return 1;
	}

	return (0);
}
