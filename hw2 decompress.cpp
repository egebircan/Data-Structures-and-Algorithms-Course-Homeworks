#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {

  ifstream ifile;
  ifile.open ("compout.txt");
   
	int num;
	string entry;
	char ch;
  int previous, current;
	int counter = 256; 
	int counter2 = 0;

  ifile >> num;
	previous = num;

	string dictionary[4096];

  for(int a = 0; a < 256; a++) {
		dictionary[a] = a;
	} 
	 
	string output[4096];
	
	ofstream ofile;
	ofile.open("decompout.txt");

	output[counter2] = dictionary[previous];
	counter2++;

  while (ifile >> num) {
		 
		current = num;
	  entry = dictionary[current];

	  output[counter2] = entry;
	  counter2++;

	  ch = entry.at(0);

		dictionary[counter] = dictionary[previous] + ch;

		previous = current;
		counter++;

  } 
       
	for(int i=0;i<4096;i++) {
		ofile<<output[i]; 
	}

	return 0;
}