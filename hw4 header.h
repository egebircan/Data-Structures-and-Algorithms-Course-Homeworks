#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;


struct coord {
	public:
		int x1;
		int x2;
		int id;
		coord(int a,int b, int c);
};


coord::coord(int a, int b, int c) {
	this->x1 = a;
	this->x2 = b;
	this->id = c;
} 


class CoordArr 
{

	public:
		//CoordArr (int capacity = 200);
		//void insert(int , int , int);
		coord **coordArr;
		int size;
		int capacity;


	void CoordArr::insert(int x1, int x2, int  id) {
		
		coord *tmp = new coord(x1, x2, id);
		coordArr[size] = tmp;

		coordArr[size]->x1 = x1;
		coordArr[size]->x2 = x2;
		coordArr[size]->id = id;

		size++;
	};

	CoordArr::CoordArr(int x) { 
		capacity = x; 
		size=0; 
		coordArr = new coord*[capacity]; 
	};


	int CoordArr::getX1(int  id) {
		for(int i = 0; i<size; i++) {

			if(coordArr[i]->id == id) {
				return coordArr[i]->x1;
			}
			else
				cout<<"bulunamadi"<<endl;
		}
	};

		int CoordArr::getX2(int  id) {
			for(int i = 0; i<size; i++) {
				if(coordArr[i]->id == id) {
					return coordArr[i]->x2;
				}
				else
					cout<<"bulunamadi"<<endl;
			}
	};
};


struct skynode {
	public:
		int height;
		string check;
		skynode(int a, string b);
};

skynode::skynode(int a, string b) {
	this->height=a;
	this->check=b;
}

class Skyline 
{

	public:
		int currsize;
		int capacity;
		skynode **skyArr;

		
	Skyline::Skyline(int x) { 
		capacity = x; 
		currsize=0; 
		skyArr = new skynode*[capacity]; 	
	};


	void Skyline::insert(int height, string check) {
		skynode *tmp = new skynode(height, check);
		skyArr[currsize] = tmp;
		skyArr[currsize]->height = height;
		skyArr[currsize]->check = check;
		
		currsize++;
	};
};


struct node {
	public:
		int id;
		int value;
		node(int a,int b);
};

node::node(int a, int b) {
	this->id=a;
	this->value=b;
} 


class BinaryHeap {
  
	public:
		int capacity;
  	int currentSize; // Number of elements in heap
  	node **array;// The heap array
			

	BinaryHeap::BinaryHeap(int x) { 
		capacity = x; 
    currentSize=0; 
    array = new node*[capacity]; 
  };
	
		
  void BinaryHeap::insert(  int x , int id ) {
    int hole = ++currentSize;
    for( ; hole > 1 && x > array[ hole / 2 ]->value; hole /= 2 ) {
      array[ hole ] = array[ hole / 2 ];
		}
    node *tmp = new node(x,id);

		array[hole]=tmp;
		array[hole]->id = id;
		array[hole]->value = x;
  };



  int BinaryHeap::getMax(int & maxItem ) {
		maxItem = array[ 1 ]->value;
		int id = array[1]->id;
		array[1] = array[ currentSize-- ];
		percolateDown( 1 );

		return id;
  };


  void BinaryHeap::percolateDown( int hole ) {
		int child;
		node* tmp = array[ hole ];

		for( ; hole * 2 <= currentSize; hole = child ) {
			child = hole * 2;
			if( child != currentSize && array[ child + 1 ]->value > array[ child ] ->value )
				child++;
										
			if( array[ child ]->value > tmp->value )
				array[ hole ] = array[ child ];
										
			else
				break;
		}
		array[ hole ] = tmp;   
  };
};