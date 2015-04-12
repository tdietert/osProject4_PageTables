#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "basicPT.h"
#include "hashedPT.h"
#include "invertedPT.h"

using namespace std;

float timePageTableVersion(void ptFunction(std::ifstream&, std::ifstream&))
{	

	//open file
	ifstream logical("logicalAddress.txt");
	ifstream physical("physical_memory.txt");
   
 	//make sure both files open correctly
 	if (!logical.good()) {
    	cout << "file opening error" << endl;
 	}

 	if (!physical.good()) {
    	cout << "file opening error" << endl;
 	}

 	cout << "results: ";

	clock_t t1,t2;
	t1 = clock();

	// run the function passed as arg
	ptFunction(logical, physical);

	t2 = clock();
	float t_diff(((float)t2 - (float)t1) / CLOCKS_PER_SEC);
	return t_diff;

	logical.close();
	physical.close();
}

int main() {
 
 	float timeDiff;

 	// Time basic page table algorithm
	cout << "Basic Page Table Algorithm Started..." << endl;
	timeDiff = timePageTableVersion(runPagePT);
	cout << "Basic Page Table finished in " << timeDiff << " sec\n" << endl;

    // Time hashed page table algorithm
	cout << "Hashed Page Table Algorithm Started..." << endl;
	timeDiff = timePageTableVersion(runHashedPT);
	cout << "Hashed Page Table finished in " << timeDiff << " sec\n" << endl;

    // Time inverted table algorithm
	cout << "Inverted Page Table Algorithm Started..." << endl;
	timeDiff = timePageTableVersion(runInvertedPT);
	cout << "Inverted Page Table finished in " << timeDiff << " sec\n" << endl;


	return 0;
}