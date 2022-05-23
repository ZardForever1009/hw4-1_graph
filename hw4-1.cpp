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

// Dijkstra record vertices stats
struct DijNode{
	int id=-1;
	int dis=INT_MAX; // source to current vertex minimum cost
	bool visited=false; // defualt mark all vertex as unvisited vertex
	int last_vertex=-1; // allow trace back for route
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
		if(st[i]==push_id)return; // already push before
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

// stack empty check
bool empty(int* st, int v_count){
	for(int i=v_count-1;i>=0;i--){
		if(st[i]!=-1){
			return false; // still exist some vertices
		}
	}
	return true;
}

// DFS 
void DFS(Head* head, Head* currHead, Node* currNode, Node* visited, int* st, int v_count){
	if(visitedAlready(visited, currHead->id, v_count)){
		// Head(visited) -> nullptr
		if(currNode==nullptr){
			push(st, v_count, currHead->id);
			return;
		}
		// Head(visited) -> node
		if(currNode->last_node==nullptr){
			return;
		}
	}
	markVisited(visited, currHead->id, v_count);
	if(currNode==nullptr){
		push(st, v_count, currHead->id);
		return;
	}
	if(visitedAlready(visited, currNode->id, v_count)){
		push(st, v_count, currHead->id);
		DFS(head, currHead, currNode->next_node, visited, st, v_count);
		return;
	}
	else{
		Head* newHead=findHead(head, currNode->id);
		DFS(head, newHead, newHead->next_node, visited, st, v_count);
		DFS(head, currHead, currNode->next_node, visited, st, v_count);
		return;
	}
}

// check if a graph contains a negative edge (FOR Dijkstra's algorithm)
bool negativeEdgeExist(Head* head){
	while(head!=nullptr){
		Node* currNode=head->next_node;
		while(currNode!=nullptr){
			if(currNode->weight<0)return true; // exist a negative edge
			currNode=currNode->next_node;
		}
		head=head->next_head;
	}
	return false;
}

//  assign node id value to arr
void initializeArr(Head* head, DijNode* arr){
	int idx=0;
	while(head!=nullptr){
		arr[idx].id=head->id;
		head=head->next_head;
		idx++;
	}
	return;
}

// get dis of given vertex_id in arr
int getDis(int id, DijNode* arr, int v_count){
	for(int i=0;i<v_count;i++){
		if(arr[i].id==id)return arr[i].dis;
	}
	return -1;//default value
}

// update dis & last_vertex of given id's vertex
void update(int id, DijNode* arr, int v_count, int new_dis, int last_vertex){
	for(int i=0;i<v_count;i++){
		if(arr[i].id==id){
			arr[i].dis=new_dis;
			arr[i].last_vertex=last_vertex;
		}
	}
	return;
}

// mark given vertex as visited
void setVisited(int id, DijNode* arr, int v_count){
	for(int i=0;i<v_count;i++){
		if(arr[i].id==id)arr[i].visited=true;
	}
	return;
}

// find the vertex which is unvisited and smallest path
int findMinDis(DijNode* arr, int v_count){
	int MinDis=INT_MAX;
	int MinDisID=0;
	for(int i=0;i<v_count;i++){
		if(arr[i].visited==false){ // unvisited
			if(arr[i].dis<MinDis){ // smaller vertex discovered
				MinDis=arr[i].dis;
				MinDisID=arr[i].id;
			}
			else if(arr[i].dis==MinDis){ // equal vertex (COMPARE THE ID SIZE)
				if(arr[i].id<MinDisID){
					MinDisID=arr[i].id;
				}
				else;
			}
			else;
		}
		else;
	}
	return MinDisID;
}

// check if all vertices visited in arr
bool arrAllVisited(DijNode* arr, int v_count){
	for(int i=0;i<v_count;i++){
		if(!arr[i].visited)return false;
	}
	return true;
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
	int v_count=verticesCount(head); // vertex count
	Node* visited=visitedArray(head, v_count); // record vertex visited or not
	int* st=new int[v_count]; // -1 means nothing, 0~100 means vertex id
	int* GTst=new int[v_count];
	for(int i=0;i<v_count;i++){
		st[i]=-1; // initializtion
		GTst[i]=-1;
	}
	// DFS for graph
	while(head!=nullptr){
		DFS(origin_head, head, head->next_node, visited, st, v_count);
		head=head->next_head;
	}
	// reset all vertices to non-visited
	head=origin_head;
	for(int i=0;i<v_count;i++){
		visited[i].weight=0;
	}
	Head* GTHead=transposeGraph(head); // transpose graph 
	// DFS for transpose graph
	int SCC_count=0; // record result
	while(!empty(st, v_count)){
		int pop_id=pop(st, v_count);
		// only when non-visited, we do DFS, or we keep pop()
		if(!visitedAlready(visited, pop_id, v_count)){
			Head* currHead=findHead(GTHead, pop_id);
			DFS(GTHead, currHead, currHead->next_node, visited, GTst, v_count);
			SCC_count++;
		}
	}
	cout<<"connected components: "<<SCC_count<<endl;
	return;
}

// Dijsktra solver
int DijkstraSolver(int v_id, Node* currNode, DijNode* arr, int v_count){
	while(currNode!=nullptr){
		int new_dis=getDis(v_id, arr, v_count)+currNode->weight;
		/* cout<<"currNode: "<<currNode->id<<"/"<<"NEW DIS: "<<new_dis<<endl;  */
		// Smaller path discover, update data
		if(new_dis<getDis(currNode->id, arr, v_count)){
			// new_dis becomes the path pass the vertex of v_id
			// last_vertex becomes the vertex of v_id
			update(currNode->id, arr, v_count, new_dis, v_id);
			/* cout<<"UPDATE: "<<getDis(currNode->id, arr, v_count)<<endl; */
		}
		else; // No better path, so no update
		currNode=currNode->next_node;
	}
	setVisited(v_id, arr, v_count); // update vertex to visited
	int new_v_id=findMinDis(arr, v_count);
	return new_v_id;
}

// Dijkstra func
void Dijkstra(Head* head, int aa, int bb){
	if((!vertexExist(head, aa))||(!vertexExist(head, bb))){
		cout<<"an invalid vertex\n";
		return;
	}
	if(negativeEdgeExist(head)){
		cout<<"G contains a negative edge\n";
		return;
	}
	int v_count=verticesCount(head); // vertex count
	DijNode* arr=new DijNode[v_count];
	initializeArr(head, arr);
	// set the source dis as 0
	for(int i=0;i<v_count;i++){
		if(arr[i].id==aa){
			arr[i].dis=0;
			break;
		}
	}
	
	// start with source vertex's neighboring vertices
	Node* currNode=findHead(head, aa)->next_node;
	int new_v_id=DijkstraSolver(aa, currNode, arr, v_count);
	while(!arrAllVisited(arr, v_count)){
		currNode=findHead(head, new_v_id)->next_node;
		new_v_id=DijkstraSolver(new_v_id, currNode, arr, v_count);
		/* cout<<"ID: "<<new_v_id<<endl;
			cout<<"==========================\n";
			for(int i=0;i<v_count;i++){
			cout<<arr[i].id<<": "<<arr[i].dis<<endl;
		}
		cout<<"==========================\n"; */
	}
	
	for(int i=0;i<v_count;i++){
		cout<<arr[i].id<<": "<<arr[i].dis<<endl;
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
