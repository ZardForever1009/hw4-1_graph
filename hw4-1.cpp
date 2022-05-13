// hw4-1: Graph implementation
// environment: Notepad++ 8.2.1(64bits X64)
// C++ type: C++ 14
// g++ type: g++ version 6.3.0
#include <iostream>
#include <string>

#define INT_MAX 2147483647 // means no connection between Head_Node && Node

using namespace std;

/*
	<< Adjacency List Implemntation >>

Head / Node1 / Node2 / Node3 ......  
A  ->   a   ->  b   ->  nullptr
B  -> nullptr
C  ->   b   ->  nullptr

*/

/*-------------------------DEFINITION------------------------------*/

// represent conected Node with Head
struct Node{
	int num=-1;
	int weight=INT_MAX;
	Node* next_node=nullptr;
};

// represent Head
struct Head{
	int num=-1;
	Head* next_head=nullptr;
	Node* next_node=nullptr;
};


/*----------------------OTHER FUNCTIONS---------------------------*/

// check if input number is valid or not
bool validNum(int num){
	return(num>=0&&num<=100);
}

// check if vertex is already in G
bool vertexExist(Head* head, int num){
	while(head!=nullptr){
		if(head->num==num)return true;
		head=head->next_head;
	}
	return false;
}

// print out all connections
void printAdjList(Head* head){
	if(head==nullptr){
		cout<<"Empty adjacency list\n";
		return;
	}
	Head* currHead=head;
	Node* currNode=nullptr;
	cout<<"===========================\n";
	while(currHead!=nullptr){
		cout<<currHead->num;
		currNode=currHead->next_node;
		while(currNode!=nullptr){
			cout<<" -> "<<currNode->num<<"("<<currNode->weight<<")";
			currNode=currNode->next_node;
		}
		currHead=currHead->next_head;
		cout<<endl;
	}
	cout<<"===========================\n";
	return;
}

// find given head
void findHead(Head*& head, int num){
	while(head->num!=num){
		head=head->next_head;
	}
	return;
}

/*----------------------ACTION FUNCTION---------------------------*/

// add vertex func
void addVertex(Head*& head, int aa){
	if(!validNum(aa)){
		cout<<"add an invalid vertex\n";
		return;
	}
	if(vertexExist(head, aa)){
		cout<<"vertex "<<aa<<" is already in G\n";
		return;
	}
	Head* newNode=new Head();
	newNode->num=aa;
	if(head==nullptr){
		head=newNode;
		return;
	}
	Head* recover=head;
	while(head->next_head!=nullptr){
		head=head->next_head;
	}
	head->next_head=newNode;
	head=recover;
	return;
}

// del vertex func
void deleteVertex(Head*& head, int aa){
	if(!validNum(aa)){
		cout<<"delete an invalid vertex\n";
		return;
	}
	if(!vertexExist(head, aa)){
		cout<<"vertex "<<aa<<" isn't in G\n";
		return;
	}
	
}

// add edge func
void addEdge(Head*& head, int aa, int bb, int weight){
	if((!vertexExist(head, aa))||(!vertexExist(head, bb))){
		cout<<"add an invalid edge\n";
		return;
	}
	Head* recover=head;
	findHead(head, aa); // add edge head
	Node* last=nullptr;
	Node* curr=head->next_node;
	while(curr!=nullptr){
		// already connected, only update weight
		if(curr->num==bb){
			curr->weight=weight;
			head=recover;
			return;
		}
		last=curr;
		curr=curr->next_node;
	}
	// reach nullptr, create a new connection
	// new insert connection
	Node* newNode=new Node();
	newNode->num=bb;
	newNode->weight=weight;
	if(last==nullptr)head->next_node=newNode;
	else last->next_node=newNode;
	head=recover;
	return;
}

// del edge func
void deleteEdge(int aa, int bb){
	
}

// connect components func
void connectedComponents(void){
	
}

// Dijkstra func
void Dijkstra(int aa, int bb){
	
}

// BellmanFord func
void BellmanFord(int aa, int bb){
	
}

// combine all func together
void graph_implementation(){
	Head* head=nullptr;
	string action, aa, bb, weight;
	while(cin>>action){
		if(action=="addVertex"){
			cin>>aa;
			addVertex(head, stoi(aa));
		}
		else if(action=="deleteVertex"){
			cin>>aa;
			deleteVertex(head, stoi(aa));
		}
		else if(action=="addEdge"){
			cin>>aa;
			cin>>bb;
			cin>>weight;
			addEdge(head, stoi(aa), stoi(bb), stoi(weight));
		}
		else if(action=="deleteEdge"){
			cin>>aa;
			cin>>bb;
			
		}
		else if(action=="connectedComponents"){
			
		}
		else if(action=="Dijkstra"){
			cin>>aa;
			cin>>bb;
			
		}
		else if(action=="BellmanFord"){
			cin>>aa;
			cin>>bb;
			
		}
		else if(action=="Print"){
			printAdjList(head); // print out list
		}
		else{
			cout<<"Error: No corresponding function"<<endl; 
		}
	}
	return;
}

int main(){
	
	/* Node* aa=new Node();
	Node* bb=aa;
	Node* cc=new Node();
	cc->num=20;
	
	cout<<aa->next_node<<endl;
	cout<<bb->next_node<<endl;
	bb->next_node=cc;
	cout<<aa->next_node->num<<endl;
	cout<<bb->next_node->num<<endl; */
	
	graph_implementation();
	
	system("pause");
	return 0;
}
