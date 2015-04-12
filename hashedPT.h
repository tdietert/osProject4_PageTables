#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#define PAGENUM_HT 680
#define HASH_TABLE_SIZE 10
#define FRAMESIZE_HT 5

// defines element_ht (element hash table)
// to avoid conflicts with inverted
typedef struct element{
	int VirtualPageNum;
	int PhysicalLocation;
	struct element *next;
}element_ht;

void freeMem(element_ht** table, int tableSize){

	for(int i = 0; i < tableSize;++i){
		element_ht* temp = NULL;
		element_ht* head = table[i];
		while(head != NULL){
			temp = head;
			head = head->next;
			free(temp);
		}
	}
}

void printTable(element_ht** table){
	for(int i = 0; i < HASH_TABLE_SIZE; ++i){
		element_ht* head = table[i];
		printf("%d: ",i);
		while (head != NULL)
		{
		    printf("%d,%d-> ",head-> VirtualPageNum,head->PhysicalLocation);
		    head = head->next;
		}

		printf("NULL\n");
	}
}

void buildTable(element_ht** table, int Framesize_HT, int pageNum, int tableSize ){
	for(int i = 0; i < pageNum;++i){
		//hash function 
		int j = i%tableSize;

		//first element_ht to be added
		if(table[j] == NULL){
			table[j] = (element_ht*) malloc(sizeof(element_ht));
			table[j]->next = NULL;
			table[j]->PhysicalLocation = i * FRAMESIZE_HT;
			table[j]->VirtualPageNum = i;
		}
		else{

			//create new element_ht
			element_ht* newNode;
			newNode = (element_ht*) malloc(sizeof(element_ht));
			newNode->next = NULL;
			newNode->PhysicalLocation = i * FRAMESIZE_HT;
			newNode->VirtualPageNum = i;

			//append to end
			element_ht* head = table[j];
			while(head->next != NULL){
				head = head->next;
			}
			head->next = newNode;
		}
	}
	//printTable(table);
}

int searchTable(element_ht** table, int page){ 
	//hash function 
	element_ht* head = table[page%HASH_TABLE_SIZE];

	//walk the list until you find the page number
	while(head->VirtualPageNum != page){
		head = head->next;
	}

	return head->PhysicalLocation;
}

//---------------------------
// This func is called from osProject4.cpp 
// where our project's "main()" is located
//---------------------------
void runHashedPT(std::ifstream &logicalFP, std::ifstream &physicalFP) {

	//create and initialize table
	element_ht* table[HASH_TABLE_SIZE];
	for(int i = 0; i < HASH_TABLE_SIZE; ++i){
		table[i] = NULL;
	}

	//build the table
	buildTable(table,FRAMESIZE_HT,PAGENUM_HT, HASH_TABLE_SIZE);
	
	std::string line;
    std::vector<std::string> elems;
    char charFromFile[1];

	/* While there is still a line. */
    while(getline(logicalFP, line)) {
    	
	   	//split string
	   	std::stringstream ss(line);
	    std::string item;
	    while (std::getline(ss, item, ',')) {
	        elems.push_back(item);
	    }

	    //table look up and add offset
        int location = searchTable(table,std::stoi(elems[0])) + std::stoi( elems[1] );
  
        //print that location in thr physical mem file
        physicalFP.seekg(location); //seekg sets the reading position 
        physicalFP.read (charFromFile,1); //read(where it goes, length)
        std::cout << charFromFile[0];

        elems.clear();
    }

    std::cout << std::endl;
	freeMem(table,HASH_TABLE_SIZE);
}