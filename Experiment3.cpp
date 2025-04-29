/*
AIM: Beginning with an empty binary search tree,
Construct binary search tree by inserting the values in the order given. 
After constructing a binary tree -
	i. Insert new node 
	ii. Find number of nodes in longest path from root
	iii.Minimum data value found in the tree
	iv. Change a tree so that the roles of the left and right pointers are swapped at every node
	v. Search a value 

INPUT: The set of values
OUTPUT: Various operations result.

*/

#include<iostream>
using namespace std;

typedef struct node
{
   struct node *LChild;
   int data;
   struct node *RChild;
}NODE;

class BST
{
	NODE *root;	//root node address
	int count;	//no. of comparisions
	int lh,rh;	//left height and right height
	public:
		//Constructor to initialize the attributes of class
	BST()
	{
		root=NULL;
		count=0;
		lh=rh=0;
	}
	
	//Function to return root address
	NODE* getroot()
	{
		return root;
	}

	
	//i. Insert new node
	void addNode(int key)
	{
		NODE *newNode,*previous,*cur;

		newNode=new NODE;
		newNode->data=key;
		newNode->LChild=newNode->RChild=NULL;

		if(root==NULL)	// If root is NULL then add the value as root node of tree
			root=newNode;
		else //Otherwise traverse the tree to add node at proper place
		{
			cur=root;//Current pointer to search a proper node 

			while(cur)//traverse till proper node found
			{
				previous=cur;	//'previous' follows 'cur' pointer
				if(cur->data == key)	//data of current node and the 'key' are same
				{ 
					cout<<"\nDuplicate Node!";
					return ;
				}
				if(cur->data > key)	//if new value 'key' is smaller than current node data
					cur=cur->LChild;	// traverse to the left to get correct node
				else
					cur=cur->RChild;	//else traverse tp the right
			}
			//the proper node is pointed by pointer 'previous' where insertion is possible

			if(key <previous->data)		//if key is smaller than data of 'previous'
				previous->LChild=newNode;//insert new node as left child of 'previous'
			else
				previous->RChild=newNode;//insert new node as right child of 'previous'
		}
		return;
	}
	
	//INORDER Traversal of tree
	void displayIN(NODE *T)
	{
		if(T)
		{
			displayIN(T->LChild);
			cout<<" "<<T->data;
			displayIN(T->RChild);
		}
	}
	
	//ii. Find number of nodes in longest path from root - Hight Of tree
	int height(NODE *T)
	{

		if(T==NULL)
		{
			return 0;
		}
		if(T->LChild ==NULL && T->RChild==NULL)	//if leaf node then retrun height '0'
		{
			return 0;
		}
		lh=height(T->LChild);	//travel left recursively
		rh=height(T->RChild);	//travel right recursively
		
		if(lh>rh)		//For every node see left height is greater than right 
		{
			return lh+1;		//return left height 
		}
		else
		{
			return rh+1;		//return left height
		}
	}
	
	//iii.Minimum data value found in the tree
	void minimumDataValue(NODE *T)
	{
		NODE *previous,*t;
		int top=-1;
		t=T;
		if (t==NULL)
			cout<<"\nTree Empty";
		else
		{
			while(t)//Traversal of tree to left till last node
			{
				previous=t;//'previous' follows 't'
				t=t->LChild;//Goto left
			}
			cout<<"Minimum data value found is:: "<<previous->data;
		}
	}
	
	//iv.Change a tree so that the roles of the left and right pointers are swapped at every node
	void Mirror(NODE *t)
	{
		//This algorithm prints the mirror image of the BST.
		//The pointer ‘t’ points to the ‘root’ node of a BST.
		//The algorithm is recursive and terminates when t reaches to NULL link of leaf node.
		NODE *previous;// temporary pointer for exchanging the address of left child and right child link
		if(t) // call recursively till pointer ‘t’ points to NULL
		{
			previous=t->LChild; // hold the address of left child
			t->LChild=t->RChild; // replace left child address with right child address
			t->RChild=previous; // replace right child address with left child address
			Mirror(t->LChild); // call recursive for left subtree of the BST
			Mirror(t->RChild); // call recursive for right subtree of the BST
		}
	}
	
	//v. Search a value, Logic is same as insert node in BST
	
	void searchNode(int key)
	{
		NODE *previous,*cur;
		count=0;//initialize count to zero for every new search
		if(root==NULL)
			cout<<"\nTree Empty!!";
		else
		{
			cur=root;
			while(cur)
			{
				count++;
				
				if(cur->data == key)
				{
					cout<<"\nNode Found after "<<count<<" comparisions";;
					return ;
				}
				if(key<cur->data)
					cur=cur->LChild;
				else
					cur=cur->RChild;
			}
		}
		cout<<"\nNode value not found after "<<count<<" comparisions";
		return;
	}
	
};


int main(void)
{
   BST B;
   int val,cho,n;
   cho=0;
   while(cho != 7)
   {
     
	cout<<"\n1-ADD NODE";
	cout<<"\n2-DISPLAY NODE INORDER";
	cout<<"\n3-NO. OF NODES IN THE LONGEST PATH FROM ROOT";
	cout<<"\n4-MINIMUM DATA VALUE IN THE TREE";
	cout<<"\n5-MIRROR IMAGE";
	cout<<"\n6-SEARCH NODE IN NODE";
     	cout<<"\n7-EXIT";

     	cout<<"\nEnter ur choice:";
     	cin>>cho;
     switch(cho)
     {
       case 1:
		cout<<"\nEnte any value to added in tree:";
		cin>>val;
		B.addNode(val);
		break;
       case 2:
		B.displayIN(B.getroot());
		break;
       case 3:
		n=B.height(B.getroot());
		cout<<"\nNo. of nodes in the longest path are:"<<n+1;
		break;
       case 4:
		B.minimumDataValue(B.getroot());
		break;
       case 5:
		cout<<"\nThe mirror image of tree"<<endl;
		B.Mirror(B.getroot());
		break;
	case 6:
	    	cout<<"\nEnte any value to be searched in tree:";
		cin>>val;
		B.searchNode(val);
		break;
	case 7:
		cout<<"\nProgram Exits!!";
		break;
       default:
		cout<<"\nWrong choice!";
     }
    }   
   return 0;
}