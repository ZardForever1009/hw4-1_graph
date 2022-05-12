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

// represent Head
struct Head_Node{
	int vertex_num=-1;
	Head_Node* next_head=nullptr;
};

// represent conected Node with Head
struct Node{
	int vertex_num=-1;
	int weight=INT_MAX;
	Node* next_node=nullptr;
};

// check if input number is valid or not
bool validNum(int num){
	return(num>=0&&num<=100);
}

// add vertex func
void addVertex(int node){
	if(!validNum(node)){
		cout<<"add an invalid vertex\n";
		return;
	}
	
}

// del vertex func
void deleteVertex(int node){
	if(!validNum(node)){
		cout<<"delete an invalid vertex\n";
		return;
	}
	
}

// add edge func
void addEdge(int from_node, int to_node, int edge){
	
}

// del edge func
void deleteEdge(int from_node, int to_node){
	
}

// connect components func
void connectedComponents(void){
	
}

// Dijkstra func
void Dijkstra(int from_node, int to_node){
	
}

// BellmanFord func
void BellmanFord(int from_node, int to_node){
	
}

// combine all func together
void graph_implementation(){
	string action, a_node, b_node, weight;
	while(cin>>action){
		if(action=="addVertex"){
			cin>>a_node;
			addVertex(stoi(a_node));
		}
		else if(action=="deleteVertex"){
			cin>>a_node;
			deleteVertex(stoi(a_node));
		}
		else if(action=="addEdge"){
			cin>>a_node;
			cin>>b_node;
			cin>>weight;
			
		}
		else if(action=="deleteEdge"){
			cin>>a_node;
			cin>>b_node;
			
		}
		else if(action=="connectedComponents"){
			
		}
		else if(action=="Dijkstra"){
			cin>>a_node;
			cin>>b_node;
			
		}
		else if(action=="BellmanFord"){
			cin>>a_node;
			cin>>b_node;
			
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
