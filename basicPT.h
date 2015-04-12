#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#define TABLE_SIZE 10
#define PAGENUM_BPT 680
#define FRAMESIZE_BPT 5

void buildTable(int* table, int Framesize, int pageNum, int tableSize ){
	////////////////////////
	//build your table
	////////////////////////

	for(int i = 0; i < pageNum;++i){
		table[i] = Framesize * i;
	}
}

int searchTable(int* table, int page){ 
	////////////////////////
	//seach your table
	return table[page];
}


//---------------------------
// This func is called from osProject4.cpp 
// where our project's "main()" is located
//---------------------------
void runPagePT(std::ifstream &logical, std::ifstream &physical){
	// initialize page table
	int table[PAGENUM_BPT];

	//build the table
	buildTable(table,FRAMESIZE_BPT,PAGENUM_BPT, TABLE_SIZE);

 	//make sure both files open correctly
 	if (!logical.good()) {
    	std::cout << "file opening error" << std::endl;
 	}

 	if (!physical.good()) {
    	std::cout << "file opening error" << std::endl;
 	}

	std::string line;
    std::vector<std::string> elems;
    char charFromFile[1];

	/* While there is still a line. */
    while(getline(logical, line)) {
	   	//split string
	   	std::stringstream ss(line);
	    std::string item;
	    while (std::getline(ss, item, ',')) {
	        elems.push_back(item);
	    }

	    //table look up and add offset
        int location = searchTable(table,std::stoi(elems[0])) + std::stoi( elems[1] );
        
        //print that location in thr physical mem file
        physical.seekg(location); //seekg sets the reading position 
        physical.read (charFromFile,1); //read(where it goes, length)
        std::cout << charFromFile[0];

        elems.clear();
    }

    std::cout << std::endl;
}