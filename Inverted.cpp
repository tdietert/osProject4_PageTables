#include "Inverted.h"

Inverted::Inverted()
{
}


void Inverted::printTable(element_inv * table){
	for (int i = 0; i < sizeof(table)/sizeof(*table); ++i){
		//element_inv * head = table[i];
		printf("%d: ", i);
		/*while (head != NULL)
		/{
			printf("%d,%d-> ", head->VirtualPageNum, head->PhysicalPageNum);
			head = head->next;
		}*/
		printf("%d,%d -> ", table[i].vpn, table[i].pid);
		printf("\n");
	}
}

//provide array table, process id, virtual page number and table size
void Inverted::buildTable(element_inv * table, int pid, int framesize, int tableSize){
	for (int i = 0; i < tableSize; ++i){
		//virtual address
		int j = floor(i / framesize);// %tableSize;

		//add elements to array
		table[i].pid = pid;
		table[i].vpn = j;
		
	}

	// THIS SEEMS TO BE SLIGHTLY BROKEN
	//	printTable(table);
	// --------------------------------
}

// search table for virtual page number; returns index (ppn)
int Inverted::searchTable(element_inv * table, int vpage){
	//walk the list until you find the page number
	int index = 0;
	try{
		while (table[index].vpn != vpage){
			++index;
		}
	}
	catch(int trash){
		printf("/nPage not Found./n");
	}

	return index;
}


void Inverted::setTableSize(int fileSize){
	table_size = fileSize;
}

Inverted::~Inverted()
{
}
