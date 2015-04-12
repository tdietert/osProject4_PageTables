#pragma once
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
typedef struct{
	int vpn; //virtual page number
	int pid; //process id
} element_inv;

class Inverted
{

private:
	int table_size;

public:
	void freeMem(element_inv *, int);
	void printTable(element_inv *);
	void buildTable(element_inv *, int, int, int);
	int searchTable(element_inv *, int);
	void setTableSize(int);
	Inverted();
	~Inverted();
};


