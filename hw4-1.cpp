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

p.s. Head: Doubly-Linked-List(NOT using array since NOT sure of Vertices counts)

*/

/*-------------------------DEFINITION------------------------------*/

// represent connected Node with Head
struct Node{
	int id=-1;
	int weight=INT_MAX;
	Node* next_node=nullptr;
	Node* last_node=nullptr;
};

// represent Head
struct Head{
	int id=-1;
	Head* last_head=nullptr;
	Head* next_head=nullptr;
	Node* next_node=nullptr;
};


/*----------------------OTHER FUNCTIONS---------------------------*/

// check if input number is valid or not
bool validNum(int id){
	return(id>=0&&id<=100);
}

// check if vertex is already in G
bool vertexExist(Head* head, int id){
	while(head!=nullptr){
		if(head->id==id)return true;
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
		cout<<currHead->id;
		currNode=currHead->next_node;
		while(currNode!=nullptr){
			cout<<" -> "<<currNode->id<<"("<<currNode->weight<<")";
			currNode=currNode->next_node;
		}
		currHead=currHead->next_head;
		cout<<endl;
	}
	cout<<"===========================\n";
	return;
}

// find given head
Head* findHead(Head* head, int id){
	while(head->id!=id){
		head=head->next_head;
	}
	return head;
}

// free head & its node
void freeHeadAndNode(Head*& head){
	if(head==nullptr)return;
	Node* currNode=head->next_node;
	Node* delNode=nullptr;
	while(currNode!=nullptr){
		delNode=currNode;
		currNode=currNode->next_node;
		delete delNode;
		delNode=nullptr;
	}
	delete head;
	head=nullptr;
	return;
}

// free given node
void freeGivenNode(Head* head, Node*& node){
	if(node->last_node==nullptr){ // means node is first node after head
		head->next_node=node->next_node;
		if(node->next_node!=nullptr){
			(node->next_node)->last_node=nullptr;
		}
	}
	else{
		(node->last_node)->next_node=node->next_node;
		if(node->next_node!=nullptr){
			(node->next_node)->last_node=node->last_node;
		}
	}
	// free the memory
	delete node;
	node=nullptr;
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
	newNode->id=aa;
	if(head==nullptr){
		head=newNode;
		return;
	}
	// insert newNode at head position
	newNode->next_head=head;
	head->last_head=newNode;
	newNode->last_head=nullptr;
	head=newNode;
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
	/*---------- FREE THE HEAD & FOLLOWING NODES ----------*/
	Head* delHead=findHead(head, aa);
	// free delHead linked list node
	Head* next=delHead->next_head;
	Head* prev=delHead->last_head;
	if(prev==nullptr){ // Condition: delete the first head
 		head=next;
		if(head!=nullptr)head->last_head=nullptr;
	}
	else{
		prev->next_head=next;
		if(next!=nullptr)next->last_head=prev;
	}
	freeHeadAndNode(delHead);
	/*----- FREE OTHER CONNECTIONS WITH OTHER NODES -----*/
	Head* recover=head;
	while(head!=nullptr){
		Node* currNode=head->next_node;
		while(currNode!=nullptr){
			if(currNode->id==aa){ // encounter matched edge
				freeGivenNode(head, currNode);
				break; // move to next head
			}
			currNode=currNode->next_node;
		}
		head=head->next_head;
	}
	head=recover;
	return;
}

// add edge func
void addEdge(Head* head, int aa, int bb, int weight){
	if((!vertexExist(head, aa))||(!vertexExist(head, bb))){
		cout<<"add an invalid edge\n";
		return;
	}
	Head* hh=findHead(head, aa); // added edge head
	Node* last=nullptr;
	Node* curr=hh->next_node;
	while(curr!=nullptr){
		// already connected, only update weight
		if(curr->id==bb){
			curr->weight=weight;
			return;
		}
		last=curr;
		curr=curr->next_node;
	}
	// reach nullptr, create a new connection
	// new insert connection
	Node* newNode=new Node();
	newNode->id=bb;
	newNode->weight=weight;
	if(last==nullptr){
		hh->next_node=newNode; // no Node after Head
		newNode->last_node=nullptr; // means reach the Head
	}
	else{
		last->next_node=newNode; // reach the last Node in currHead hh
		newNode->last_node=last;
	}
	return;
}

// del edge func
void deleteEdge(Head* head, int aa, int bb){
	if((!vertexExist(head, aa))||(!vertexExist(head, bb))){
		cout<<"delete an invalid edge\n";
		return;
	}
	Head* hh=findHead(head, aa); // delete edge head
	Node* currNode=hh->next_node;
	// Ideally, we should find the delEdge & return before while loop end
	while(currNode!=nullptr){
		if(currNode->id==bb){ // encounter matched edge
			freeGivenNode(hh, currNode);
			return;
		}
		currNode=currNode->next_node;
	}
	// Not finding the edge
	cout<<"fail to delete edge <"<<aa<<","<<bb<<">\n";
	return;
}

// STRONGLY connect components func
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
			deleteEdge(head, stoi(aa), stoi(bb));
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
	
	graph_implementation();
	
	system("pause");
	return 0;
}
