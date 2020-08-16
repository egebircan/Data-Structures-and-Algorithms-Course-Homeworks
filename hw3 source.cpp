#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

	
class HashNode { 
    public: 
    int value; 
    int key; 
      
    //Constructor of hashnode  
    HashNode(int key, int value) 
    { 
        this->value = value; 
        this->key = key; 
    } 
}; 
  

class HashMap 
{ 
    //hash element array 
    HashNode **arr; 
    int capacity; 
    //current size 
    int size; 
    //dummy node 
    HashNode *dummy; 
  
    public: 
	    HashMap() { 
            capacity = 1009; 
            size=0; 
            arr = new HashNode*[capacity]; 
            
            //Initialise all elements of array as NULL 
            for(int i=0 ; i < capacity ; i++) 
                arr[i] = NULL; 
            
            //dummy node with value and key -1 
            dummy = new HashNode(-1, -1); 
        } 
 
    int hashCode(int key) 
    { 
        return key % capacity; 
    } 
      
    
    int insertNode(int value) 
    { 
		if(size == capacity) {
			cout<<"no free space available."<<endl;
			return -1;
		}

		else if(size < capacity) {
            int counter = 0;
            int hashIndex = hashCode(value);
            HashNode *temp = new HashNode(hashIndex, value); 
            
            //find next free space  
            while(arr[hashIndex] != NULL) 
            { 
                hashIndex++; 
                hashIndex %= capacity; 
                counter++;
            } 
            
            //if new node to be inserted increase the current size 
            if(arr[hashIndex] == NULL || arr[hashIndex]->key == -1) {
                size++; 
                arr[hashIndex] = temp; 
                arr[hashIndex]->key = hashIndex;
                arr[hashIndex]->value = value;
                
                return counter;
            }

            return -1;
		}
	} 
      
    
    int deleteNode(int value) 
    { 
        int hashIndex = hashCode(value); 
        int counter = 0;
        //finding the node with given key 
        while(arr[hashIndex] != NULL) 
        { 

			if(counter + 1>capacity)  //to avoid infinite loop 
                return capacity - 1;         
            //if node found 
            if(arr[hashIndex]->value == value) 
            { 
                HashNode *temp = arr[hashIndex]; 
                  
                //Insert dummy node here for further use 
                arr[hashIndex] = dummy; 
                  
                // Reduce size 
                size--; 
                return counter; 
				
            } 
          
		    hashIndex++; 
            hashIndex %= capacity; 
			counter++;
        } 
          
        //If not found return null 
        return capacity - 1; 
    } 
      
  
	//Function to search the value for a given key 
    int get(int value) 
    { 
		// Apply hash function to find index for given key 
		int hashIndex = hashCode(value); 
        int counter = 0;
        //finding the node with given key    
        while(arr[hashIndex] != NULL) 
        {    
            if(counter + 1>capacity)  //to avoid infinite loop 
                return capacity - 1;         
            //if node found return its value 
            if(arr[hashIndex]->value == value) {
                return counter; 
			}

            hashIndex++; 
            hashIndex %= capacity;  
            counter++;  
        } 
          
        //If not found return null 
        return capacity - 1; 
    } 
      
    //Return current size  
    int sizeofMap() 
    { 
        return size; 
    } 
      
    //Function to display the stored key value pairs 
    void display() 
    { 
        for(int i=0 ; i<capacity ; i++) 
        { 
            if(arr[i] != NULL && arr[i]->key != -1) 
                cout << "key = " << arr[i]->key  
                     <<"  value = "<< arr[i]->value << endl; 
        } 
    } 
}; 

class Container 
{ 
    public: 
    float loadFactor; 
    int probes; 
      
    //Constructor of container 
    Container(int loadFactor, int probes) 
    { 
        this->loadFactor = loadFactor; 
        this->probes = probes; 
    } 
}; 
  
   
class GraphCont 
{ 
    //hash element array 
    Container **arr; 
    int capacity; 
    //current size 
    int size; 
    //dummy node 
    Container *dummy; 
	ofstream outData;
	
    public:	
    GraphCont() { 
        capacity = 1010; 
        size=0; 
        arr = new Container*[capacity]; 
            
        //Initialise all elements of array as NULL 
        for(int i=0 ; i < capacity ; i++) 
            arr[i] = NULL; 
            
        //dummy node with value and key -1 
        dummy = new Container(-1, -1); 
    } 


    void insertNode(float loadFactor, int probes) 
    { 
		if(size == capacity) {
			cout<<"table is full"<<endl;	
		}

		else if(size < capacity) {
            Container *temp = new Container(loadFactor, probes); 
          
            arr[size] = temp;
            arr[size]->loadFactor = loadFactor;
            arr[size]->probes = probes;
            
            size++;
		}		
	} 

	void display(int i) 
    { 
		string filename[6] = {"Succesful Insert.csv", "Failed Insert.csv", "Succesful Delete.csv", "Failed Delete.csv", "Succesful Find.csv", "Failed Find.csv"};
		outData.open(filename[i].c_str(), ios::app);	
		outData<<"Load Factor"<<"; "<<"Number of Probes"<<endl;

		for(int k=0 ; k<capacity ; k++) 
        { 
            if(arr[k] != NULL)  {
                cout << "Load Factor = " << arr[k]->loadFactor
                     <<"  Number of Probes = "<< arr[k]->probes << endl; 

				outData<<arr[k]->loadFactor<<"; "<<arr[k]->probes<<endl;
			}
        }
    } 

	int sizeofMap() 
    { 
        return size; 
    } 
};

int main() 
{ 
	HashMap *h = new HashMap;  //our main hashtable 
 
	GraphCont *insS = new GraphCont;    //succesful insert table
	GraphCont *insF = new GraphCont;	//failed insert table
	GraphCont *delS = new GraphCont;	//succesful delete table
	GraphCont *delF = new GraphCont;	//failed delete table
	GraphCont *findS = new GraphCont;	//succesful find table
	GraphCont *findF = new GraphCont;	//failed find table

	int random;
	int random2;
	int outputCounter = 0;

	for(int i = 0; i<1000000; i++) {
		random = rand() % 8;
		random2 = rand();

		if (random <=5 && random >= 0 ) {

		int a = h->insertNode(random2);
		float ans1 = (insS -> sizeofMap() + 1 ) / (1010.0);
		float ans2 = (insF -> sizeofMap() + 1 ) / (1010.0);

			if(a != -1) {
			    insS->insertNode(ans1, a);
	        } else  {
			    insF->insertNode(ans2, 1008);
			    cout<<"table fullendi"<<endl;
			    break; 
			}
		}

		else if (random == 6) {
			int b = h->deleteNode(random2);
			float ans3 = float(delS -> sizeofMap() + 1 ) / float(1010);
			float ans4 = float(delF -> sizeofMap() + 1 ) / float(1010);

			if(b != 1008) {
		        delS->insertNode(ans3, b);
	        } else {
                delF->insertNode(ans4, b);
            }
		} else {
			int c = h->get(random2);
			float ans5 = float(findS -> sizeofMap() + 1 ) / float(1010);
			float ans6 = float(findF -> sizeofMap() + 1 ) / float(1010);

			if(c != 1008) {
		        findS->insertNode(ans5, c);
		    } else {
		        findF->insertNode(ans6, c);
            }
		}

		if (i == 4) {
			srand (1);
		}
	}  

	insS->display(outputCounter);

	cout<<endl;
	outputCounter++;


    insF->display(outputCounter);

	cout<<endl;
	outputCounter++;


	delS->display(outputCounter);

	cout<<endl;
	outputCounter++;


	delF->display(outputCounter);

	cout<<endl;
	outputCounter++;


	findS->display(outputCounter);

	cout<<endl;
	outputCounter++; 


	findF->display(outputCounter);

	cout<<endl;
	outputCounter++;

	system("pause");
  
    return 0; 
}