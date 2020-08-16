#include <iostream>
#include "Header.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;


int main() {
	int number = 0;

	ifstream inFile;
	inFile.open("input.txt");

	inFile>>number;

	int buildingNum = number;
	
	BinaryHeap *heap = new BinaryHeap(buildingNum + 1);
	CoordArr *arr = new CoordArr(buildingNum);
	
	int x1, h, x2;
	int id = 1;

  while (inFile>>number) {
	
		x1 = number;
		inFile>>number;

		h = number;
		inFile>>number;

		x2 = number;

		heap->insert(h, id);
		arr->insert(x1, x2, id);

		id++;
	}  

	int maxX2 = 0;

	for(int i = 0; i<buildingNum; i++) {
		if(maxX2 < arr->coordArr[i]->x2) {
			maxX2 = arr->coordArr[i]->x2;
		}
	} 

	Skyline *finalArr = new Skyline(maxX2 + 1);

	for(int i=0 ; i <= maxX2  ; i++) {
  	finalArr->insert(0, "F");		
	} 
	
	int maxHeight = 0;

	for (int i = 0; i<buildingNum; i++) {
		int id = heap->getMax(maxHeight);

		int x1;
		int x2;

		for(int i = 0; i<buildingNum; i++) {
			if(arr->coordArr[i]->id == id) {
				x2 = arr->coordArr[i]->x2;
			}
		}

		for(int i = 0; i<buildingNum; i++) {
			if(arr->coordArr[i]->id == id) {
				x1 = arr->coordArr[i]->x1;
		 	}
		}

		while ( x1 < x2) {
			if(finalArr->skyArr[x1]->check == "F") {
				finalArr->skyArr[x1]->check = "T";
				finalArr->skyArr[x1]->height = maxHeight;
			}
			x1++;		
		} 
	} 

	int currheight =  finalArr->skyArr[0]->height;
		
	cout<<0<<" "<<currheight<<endl;

	for(int i = 0; i < maxX2; i++) {	
		if(currheight != finalArr->skyArr[i + 1]->height) {
			cout<<i+1<<" "<<finalArr->skyArr[i+1]->height<<endl;
			currheight = finalArr->skyArr[i + 1]->height;
		}
	}		
}