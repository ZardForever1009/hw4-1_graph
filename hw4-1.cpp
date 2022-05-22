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

// find how many vertices exist
int verticesCount(Head* head){
	int count=0;
	while(head!=nullptr){
		count++;
		head=head->next_head;
	}
	return count;
}

// build array to store visited or not
Node* visitedArray(Head* head, int v_count){
	Node* result=new Node[v_count];
	for(int i=0;i<v_count;i++){
		result[i].id=head->id;
		result[i].weight=0; // set 0 as not visited before
		head=head->next_head;
	}
	return result;
}

// return to check if a vertex is visted or not
bool visitedAlready(Node* visited, int id, int v_count){
	for(int i=0;i<v_count;i++){
		if(visited[i].id==id){
			return visited[i].weight;
		}
	}
	return false; // prevent something wrong
}

// marked a given vertices as visited
void markVisited(Node* visited, int id, int v_count){
	for(int i=0;i<v_count;i++){
		if(visited[i].id==id){
			visited[i].weight=1; // set 1 as visited already
			return;
		}
	}
}

// stack push function
void push(int* st, int v_count, int push_id){
	for(int i=0;i<v_count;i++){
		if(st[i]==-1){ // means empty, then insert push_id
			st[i]=push_id;
			return;
		}
	}
}

// stack pop function
int pop(int* st, int v_count){
	for(int i=v_count-1;i>=0;i--){
		if(st[i]!=-1){
			int result=st[i];
			st[i]=-1; // reset to empty
			return result;
		}
	}
}

// DFS 
void DFS(Head* head, Head* currHead, Node* currNode, Node* visited, int* st, int v_count){
	
	cout<<currHead->id<<"/";
	if(currNode!=nullptr)cout<<currNode->id;
	else cout<<"nullptr";
	if(visitedAlready(visited, currHead->id, v_count))cout<<"CONNECT\n";
	else cout<<"NONO\n";
	for(int i=0;i<v_count;i++){
		cout<<st[i]<<"| ";
	}
	cout<<endl;
	for(int i=0;i<v_count;i++){
		cout<<visited[i].weight<<"| ";
	}
	cout<<"\n==================="<<endl;
	
	
	// check if Head already visited
	if(visitedAlready(visited, currHead->id, v_count)){
		push(st, v_count, currHead->id);
		return;
	}
	// reach a empty node
	if(currNode==nullptr){
		markVisited(visited, currHead->id, v_count);
		push(st, v_count, currHead->id);
		return;
	}
	if(currNode->next_node==nullptr){
		markVisited(visited, currHead->id, v_count);
	}
	// the currNode is already visited with its head
	if(visitedAlready(visited, currNode->id, v_count)){
		DFS(head, currHead, currNode->next_node, visited, st, v_count);
		return;
	}
	// Not traversing yet
	else{
		Head* newHead=findHead(head, currNode->id);
		DFS(head, newHead, newHead->next_node, visited, st, v_count);
		DFS(head, currHead, currNode->next_node, visited, st, v_count);
		return;
	}
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

// return transpose of given graph (FOR connectedComponents function)
Head* transposeGraph(Head* head){
	Head* result=nullptr;
	Head* recover=head;
	Node* currNode=nullptr;
	// build all vertices
	while(head!=nullptr){
		addVertex(result, head->id);
		head=head->next_head;
	}
	head=recover;
	// add all vertex
	while(head!=nullptr){
		currNode=head->next_node;
		while(currNode!=nullptr){
			addEdge(result, currNode->id, head->id, currNode->weight);
			currNode=currNode->next_node;
		}
		head=head->next_head;
	}
	return result;
}

// STRONGLY connect components func
void connectedComponents(Head* head){
	Head* origin_head=head;
	int v_count=verticesCount(head);
	Node* visited=visitedArray(head, v_count);
	int* st=new int[v_count]; // -1 means nothing, 0~100 means vertex id
	for(int i=0;i<v_count;i++){
		st[i]=-1; // initializtion
	}	
	while(head!=nullptr){
		DFS(origin_head, head, head->next_node, visited, st, v_count);
		head=head->next_head;
	}
	
	
	for(int i=0;i<v_count;i++){
		cout<<st[i]<<"| ";
	}
	cout<<endl;
	for(int i=0;i<v_count;i++){
		cout<<visited[i].weight<<"| ";
	}
	cout<<endl;
	
	
	Head* GTHead=transposeGraph(head);
	
	return;
}

// Dijkstra func
void Dijkstra(Head* head, int aa, int bb){
	if((!vertexExist(head, aa))||(!vertexExist(head, bb))){
		cout<<"an invalid vertex\n";
		return;
	}
	
	return;
}

// BellmanFord func
void BellmanFord(Head* head, int aa, int bb){
	if((!vertexExist(head, aa))||(!vertexExist(head, bb))){
		cout<<"an invalid vertex\n";
		return;
	}
	
	return;
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
			connectedComponents(head);
		}
		else if(action=="Dijkstra"){
			cin>>aa;
			cin>>bb;
			Dijkstra(head, stoi(aa), stoi(bb));
		}
		else if(action=="BellmanFord"){
			cin>>aa;
			cin>>bb;
			BellmanFord(head, stoi(aa), stoi(bb));
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
