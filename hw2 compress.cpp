#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


struct node {
    string data;
    int code;
    node *left;
    node *right;
};

class tree
{
public:
    node *head;    
    int count;     
    tree();
    void addnode(string, int);
    
    int search(string);

};

tree::tree()
{
   head=NULL;
   count =0;
}

void tree::addnode(string num, int key)
{
   node *temp= new node;
   temp->data=num;
   temp->code=key;
   temp->left=NULL;
   temp->right=NULL;

   node **ptr=&head;          //double pointer

   while(*ptr!=NULL)
   {
      if(num>(*ptr)->data)
         ptr=&((*ptr)->right);

      else
         ptr=&((*ptr)->left);
   }

   *ptr=temp;
}


int tree::search(string num)
{
    node *temp = head;

    while (temp != NULL)
    {
        if (temp->data == num)
            break;

        if (num > temp->data)
            temp = temp->right;
        else                  
        if (num < temp->data)
            temp = temp->left;
    }

    if (temp == NULL)
        return -1;

    if (temp->data == num)
        return temp->code;

    return -1;
}   
 

int main()
{
    tree tree;

    string ascii[256];

    for(int a = 0; a < 256; a++) {

        ascii[a] = a;
    }


    string s;
    string ch;
    int keycode = 256;
    s = "";

    std::ifstream fsFile("compin.txt");
    std::string line;
    string maintxt = "";
    while(std::getline(fsFile, line)) {
        maintxt += line;
    }


    int length = maintxt.length();

    std::vector< int > arr;

    for (int i = 0; i < length; i++) {

        ch = maintxt.at(i);

        if(i == length - 1) {
                if(tree.search(s + ch) != -1) {
                    s = s + ch;
                    arr.push_back(tree.search(s));
                } else {
                    tree.addnode(s + ch, keycode);
                    s = s + ch;
                    arr.push_back(tree.search(s)); 
                }
        } 
        
        else if(tree.search(s + ch) != -1) {
            s = s + ch;
        } else {
            if(s.length() == 0) {
                s = ch;
            }

            else if(s.length() == 1) {
                for(int i = 0; i < 256; i++) {
                    if(ascii[i] == s)
                        arr.push_back(i); }

                tree.addnode(s + ch, keycode);
                s = ch;
                keycode++;
            } else {
                arr.push_back(tree.search(s));
                tree.addnode(s + ch, keycode);
                s = ch;
                keycode++;
            }	
        }
    } 

    ofstream outFile;
	outFile.open("compout.txt");


    vector<int>::iterator it;


    for ( it=arr.begin() ; it < arr.end(); it++ ) {
        outFile<<*it<<" "; 
    }

	return 0;
} 