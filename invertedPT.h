#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

#include "Inverted.h"

#define PAGENUM_INV 58
#define FRAMESIZE_INV 5


//---------------------------
// This func is called from osProject4.cpp 
// where our project's "main()" is located
//---------------------------
void runInvertedPT(std::ifstream &logical, std::ifstream &physical){
	//process replecation
	int processid = 1;

	//create and initialize table
	element_inv table[PAGENUM_INV*FRAMESIZE_INV];

	Inverted InvertTable;
	//build the table
	InvertTable.buildTable(table, processid, FRAMESIZE_INV, PAGENUM_INV * FRAMESIZE_INV);

	std::string line;
	std::vector<std::string> elems;
	char charFromFile[1];

	/* While there is still a line. */
	while (getline(logical, line)) {

		//split string
		std::stringstream ss(line);
		std::string item;
		while (std::getline(ss, item, ',')) {
			elems.push_back(item);
		}

		//table look up and add offset
		int location = InvertTable.searchTable(table, std::stoi(elems[0])) + std::stoi(elems[1]);


		//print that location in thr physical mem file
		physical.seekg(location); //seekg sets the reading position 
		physical.read(charFromFile, 1); //read(where it goes, length)
		std::cout << charFromFile[0];


		elems.clear();
	}

	std::cout << std::endl;
}