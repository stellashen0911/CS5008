// =================== Support Code =================
// Graph.
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they 
//      should be removed from your final version)
// ==================================================
//
// Name : Minjie Shen
// Homework 9 for CS5008

#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "my_dll.h"
#include <stdlib.h>
#include <assert.h>
// Create a graph data structure
typedef struct graph{
    int numNodes;
    int numEdges;
    dll_t* nodes;     //an array of nodes storing all of our nodes.
} graph_t;

typedef struct graph_node{
    int data;
    dll_t* inNeighbors;
    dll_t* outNeighbors;
} graph_node_t;

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
// Returns NULL if we cannot allocate memory.
graph_t* create_graph(){
    // Modify the body of this function as needed.
    graph_t* myGraph=(graph_t*)malloc(sizeof(graph_t));
    myGraph->nodes = create_dll();
    myGraph->numEdges = 0;
    myGraph->numNodes = 0;
    return myGraph;
}

// Returns the node pointer if the node exists.
// Returns NULL if the node doesn't exist or the graph is NULL
graph_node_t* find_node( graph_t * g, int value){
	if (g == NULL) return NULL;
	node_t* ptr = g->nodes->head;
	if (ptr == NULL) return NULL;
	while (ptr != NULL) {
		graph_node_t* graph_node = ptr->data;
		if (graph_node->data == value) {
			return graph_node;
		} else {
			ptr = ptr->next;
		}
	}
    return NULL;
}

// Creates a graph node
// Note: This relies on your dll implementation.
graph_node_t * create_graph_node(int value){
    graph_node_t * graph_node = (graph_node_t*)malloc(sizeof(graph_node_t));
    if ( graph_node == NULL ) return NULL;
    graph_node->data = value;
    graph_node->inNeighbors = create_dll();
    graph_node->outNeighbors = create_dll();
    return graph_node;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node already exists )
// Returns -1 if the graph is NULL.
int graph_add_node(graph_t* g, int value){
    if ( g == NULL ) return -1;
    if (find_node(g, value) != NULL) return 0;
    graph_node_t* newNode = create_graph_node(value);
    if ( newNode == NULL ) return 0;
    assert(g->nodes);
    dll_push_back(g->nodes, newNode);
    g->numNodes++;
    return 1;
}

//Returns -1 if failure or t is null
//Returns 1 if success
int delete_node(dll_t* t, int value) {
	if (t == NULL) return -1;
	node_t* ptr = t->head;
	while (ptr != NULL) {
		graph_node_t* curr = ptr->data;
		if (curr->data == value) {
			//this ptr is the node we want to delete
			if (dll_size(t) == 1) {
				dll_pop_front(t);
			} else if (ptr == t->head) {
				t->head = ptr->next;
			} else if (ptr == t->tail) {
				t->tail->previous->next = NULL;
			} else {
				ptr->previous->next = ptr->next;
				ptr->next->previous = ptr->previous;
			}
			return 1;
		}
		ptr = ptr->next;
	}
	return -1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node doesn't exist )
// Returns -1 if the graph is NULL.
int graph_remove_node(graph_t* g, int value){
	if (g == NULL) return -1;
	if (find_node(g, value) == NULL) return 0;
	node_t* ptr = g->nodes->head;
	while (ptr != NULL) {
		graph_node_t* currNode = ptr->data;
		if (currNode->data == value) { // we find the node that we want to delete
			// we need to delete ourself from the inneighbors of this current Node
			dll_t* inNeighbor = currNode->inNeighbors;
			dll_t* outNeighbor = currNode->outNeighbors;
			if (inNeighbor != NULL && dll_size(inNeighbor) >= 1) {
				node_t* inHead = inNeighbor->head;
				while (inHead != NULL) {
					graph_node_t* in = inHead->data;
					delete_node(in->outNeighbors, value);
					inHead = inHead->next;
				}
			}
			if (outNeighbor != NULL && dll_size(outNeighbor) >= 1) {
				node_t* outHead = outNeighbor->head;
				while (outHead != NULL) {
					graph_node_t* out = outHead->data;
					delete_node(out->inNeighbors, value);
					outHead = outHead->next;
				}
			}
			int edges = dll_size(inNeighbor) + dll_size(outNeighbor);
			node_t* headptr = g->nodes->head;
			node_t* tailptr = g->nodes->tail;
			graph_node_t* headgraph = headptr->data;
			graph_node_t* tailgraph = tailptr->data;
			if (currNode->data == headgraph->data) {
				dll_pop_front(g->nodes);
			} else if (currNode->data == tailgraph->data) {
				dll_pop_back(g->nodes);
			} else {
				node_t* pre = ptr->previous;
				node_t* after = ptr->next;
				pre->next = after;
				after->previous = pre;
			}
		//	free_dll(inNeighbor);
		//	free_dll(outNeighbor);
			free(currNode);
			free(ptr);
			g->numNodes--;
			g->numEdges -= edges;
			return 1;
		} else {
			ptr = ptr->next;
		}
	}
    return -1;
}

//Returns 1 if t find val
//returns 0 if t does not find val or fail
int DLL_find(dll_t* t, int val) {
	if (t == NULL) return 0;
	node_t* ptr = t->head;
	while (ptr != NULL) {
		graph_node_t* curr = ptr->data;
		if (curr->data == val) {
			return 1;
		}
		ptr = ptr->next;
	}
	return 0;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge already exists )
// Returns -1 if the graph is NULL.
int graph_add_edge(graph_t * g, int source, int destination){
    if (g == NULL) return -1;
	if (find_node(g, source) == NULL || find_node(g, destination) == NULL) {
		return 0;
	}
	//find the two source node and the destination node
	node_t* sourceNode = g->nodes->head;
	node_t* destNode = g->nodes->head;

	node_t* SourceNode = NULL;
	node_t* DestNode = NULL;

	while (sourceNode != NULL && destNode != NULL) {
		graph_node_t* SGN = sourceNode->data;
		graph_node_t* DGN = destNode->data;
		if (SGN->data == source) {
			SourceNode = sourceNode;
		}
		if (DGN->data == destination) {
			DestNode = destNode;
		}
		sourceNode = sourceNode->next;
		destNode = destNode->next;
	}
	
	//we need to add the source node into the destination node's inNeighbors list
	//and add the destination node into the source node's outNeighbors list
	if (SourceNode == NULL || DestNode == NULL) return 0;
	graph_node_t* source_t = SourceNode->data;
	graph_node_t* dest_t = DestNode->data;
	dll_t* sourceOut = source_t->outNeighbors;
	dll_t* destIn = dest_t->inNeighbors;
	//if the edge already exist, break out
	if (DLL_find(sourceOut, dest_t->data) == 1) return 0;
	if (DLL_find(destIn, source_t->data) == 1) return 0;
	//if the edge does not exist yet, add the node to the list
	if (dll_push_back(sourceOut, dest_t) == 1 &&
		dll_push_back(destIn, source_t) == 1) {
		g->numEdges = g->numEdges + 1;
		return 1;
	}
	return 0;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge doesn't exists )
// Returns -1 if the graph is NULL.
int graph_remove_edge(graph_t * g, int source, int destination){
	if (g == NULL) return -1;
	if (find_node(g, source) == NULL || find_node(g, destination) == NULL) {
		return 0;
	}
	//find the two source node and the destination node
	node_t* sourceNode = g->nodes->head;
	node_t* destNode = g->nodes->head;

	node_t* SourceNode = NULL;
	node_t* DestNode = NULL;

	while (sourceNode != NULL && destNode != NULL) {
		graph_node_t* SGN = sourceNode->data;
		graph_node_t* DGN = destNode->data;
		if (SGN->data == source) {
			SourceNode = sourceNode;
		}
		if (DGN->data == destination) {
			DestNode = destNode;
		}
		sourceNode = sourceNode->next;
		destNode = destNode->next;
	}
	
	if (SourceNode == NULL || DestNode == NULL) return 0;
	graph_node_t* source_graph = SourceNode->data;
	graph_node_t* dest_graph = DestNode->data;
	int dest_val = dest_graph->data;
	int source_val = source_graph->data;
	if (delete_node(source_graph->outNeighbors, dest_val) == 1
	&& delete_node(dest_graph->inNeighbors, source_val) == 1) {
		g->numEdges -= 1;
		return 1;
	}
    return 0;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist )
// Returns -1 if the graph is NULL.
int contains_edge( graph_t * g, int source, int destination){
	if (g == NULL) return -1;
	if (find_node(g, source) == NULL || find_node(g, destination) == NULL) {
		return 0;
	}
	//find the two source node and the destination node
	node_t* sourceNode = g->nodes->head;
	node_t* destNode = g->nodes->head;

	node_t* SourceNode = NULL;
	node_t* DestNode = NULL;

	while (sourceNode != NULL && destNode != NULL) {
		graph_node_t* SGN = sourceNode->data;
		graph_node_t* DGN = destNode->data;
		if (SGN->data == source) {
			SourceNode = sourceNode;
		}
		if (DGN->data == destination) {
			DestNode = destNode;
		}
		sourceNode = sourceNode->next;
		destNode = destNode->next;
	}
	
	//åto see if there is an edge between source and destination,
	// we need to check whether ths source is in the inNeighbors list of the destination node
	// and the destination num is in the outNeighbors of the source node
	if (SourceNode == NULL || DestNode == NULL) return 0;
	graph_node_t* source_t = SourceNode->data;
	graph_node_t* dest_t = DestNode->data;
	dll_t* sourceOut = source_t->outNeighbors;
	dll_t* destIn = dest_t->inNeighbors;
	//if the edge already exist, break out
	if (DLL_find(sourceOut, dest_t->data) == 1 && 
		DLL_find(destIn, source_t->data) == 1) {
		return 1;
	}
    return 0;
}

// Returns dll_t* of all the in neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getInNeighbors( graph_t * g, int value ){
   	if (g == NULL) return NULL;
	if (find_node(g, value) == NULL) {
		return NULL;
	}
	node_t* ptr = g->nodes->head;
	while (ptr != NULL) {
		graph_node_t* curr = ptr->data;
		if (curr->data == value) {
			dll_t* inNeighbor = curr->inNeighbors;
			return inNeighbor;
		}
		ptr = ptr->next;
	}
	return NULL;
}

// Returns the number of in neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumInNeighbors( graph_t * g, int value){
   	if (g == NULL) return -1;
	if (find_node(g, value) == NULL) {
		return -1;
	}
	node_t* ptr = g->nodes->head;
	while (ptr != NULL) {
		graph_node_t* curr = ptr->data;
		if (curr->data == value) {
			dll_t* inNeighbor = curr->inNeighbors;
			int size = dll_size(inNeighbor);
			return size;
		}
		ptr = ptr->next;
	}
	return -1;

}

// Returns dll_t* of all the out neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getOutNeighbors( graph_t * g, int value ){
    if (g == NULL) return NULL;
	if (find_node(g, value) == NULL) {
		return NULL;
	}
	node_t* ptr = g->nodes->head;
	while (ptr != NULL) {
		graph_node_t* curr = ptr->data;
		if (curr->data == value) {
			dll_t* outNeighbor = curr->outNeighbors;
			return outNeighbor;
		}
		ptr = ptr->next;
	}
	return NULL;
}

// Returns the number of out neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumOutNeighbors( graph_t * g, int value){
    if (g == NULL) return -1;
	if (find_node(g, value) == NULL) {
		return -1;
	}
	node_t* ptr = g->nodes->head;
	while (ptr != NULL) {
		graph_node_t* curr = ptr->data;
		if (curr->data == value) {
			dll_t* outNeighbor = curr->outNeighbors;
			int size = dll_size(outNeighbor);
			return size;
		}
		ptr = ptr->next;
	}
	return -1;
}

// Returns the number of nodes in the graph
// Returns -1 if the graph is NULL.
int graph_num_nodes(graph_t* g){
    if (g == NULL) return -1;
	return g->numNodes;
}

// Returns the number of edges in the graph,
// Returns -1 on if the graph is NULL
int graph_num_edges(graph_t* g){
	if (g == NULL) return -1;
    return g->numEdges;
}

//Returns 1 if t find val
//returns 0 if t does not find val or fail
int recursively_find(dll_t* t, int val) {
	if (t == NULL) return 0;
	if (dll_size(t) == -1) return 0;
	node_t* ptr = t->head;
	while (ptr != NULL) {
		graph_node_t* curr = ptr->data;
		if (curr->data == val) {
			return 1;
		} else {
			if (curr->outNeighbors == NULL) return 0;
			dll_t* out = curr->outNeighbors;
			if(recursively_find(out, val) == 1) {
				return 1;
			}
		}
		ptr = ptr->next;
	}
	return 0;
}

//Returns 1 if reachable
//Returns 0 if not reachable.
//Returns -1 if the graph is NULL or if either of the nodes doesn't exist.
int is_reachable(graph_t * g, int source, int dest){
	if (g == NULL) return -1;
	if (find_node(g, source) == NULL || find_node(g, dest) == NULL) return 0;
	node_t* ptr = g->nodes->head;
	while (ptr != NULL) {
		graph_node_t* curr = ptr->data;
		if (curr->data == source) {
			//we find the source node, see if the dest is in the outNeighbors recursicely
			if (curr->outNeighbors == NULL) return 0;
			dll_t* outNeighbor = curr->outNeighbors;
			if (recursively_find(outNeighbor, dest) == 1) {
				return 1;
			}
		}
		ptr = ptr->next;
	}
    return 0;
}

//return 1 if the node has cycle in the path
//return 0 if the node does not have cycle or is not valid
int has_cycle_dll(node_t* node, dll_t* visited) {
	if (node == NULL) return 0;
	if (visited == NULL) return 0;
	graph_node_t* curr = node->data;
	//if the current node is already visited
	if (DLL_find(visited, curr->data) == 1) {
		return 1;
	} else {
		//if the current node has not been visited, we add the current node to the visited dll
		dll_push_front(visited, curr);
		dll_t* out = curr->outNeighbors;
		node_t* ptr = out->head;
		while (ptr != NULL) {
			if (has_cycle_dll(ptr, visited) == 1) {
				return 1;
			}
			ptr = ptr->next;
		}
	}
	return 0;
}



//Returns 1 if the graph has a cycle.
//Returns 0 if the graph doesn't have a cycle.
//Returns -1 if the graph is NULL or if either of the nodes doesn't exist.
int has_cycle(graph_t * g){
	if (g == NULL) return -1;
	//if the graph only have nodes but without any edge, or the graph has no nodes
	//there is no cycle
	if (graph_num_nodes(g) == 0 || graph_num_edges(g) == 0) return 0;
	//create a empty dll to store all the visited nodes
	node_t* ptr = g->nodes->head;
	while (ptr != NULL) {
		dll_t* visited = create_dll();
		if (has_cycle_dll(ptr, visited) == 1) {
			free_dll(visited);
			return 1;
		}
		ptr = ptr->next;
		free_dll(visited);
	}
	return 0;
}


void print_helper(node_t* node, int target) {
	if (node == NULL) return;
	graph_node_t* curr = node->data;
	if (curr->data == target) {
		printf("%d\n", curr->data);
		return;
	}
	printf("%d ", curr->data);
	dll_t* outNeighbor = curr->outNeighbors;
	node_t* nextPtr = outNeighbor->head;
	while (nextPtr != NULL) {
		graph_node_t* nextGraph = nextPtr->data;
		dll_t* outGraph = nextGraph->outNeighbors;
		if (recursively_find(outGraph, target) == 1 || nextGraph->data == target) {
			print_helper(nextPtr, target);
			break;
		} else {
			nextPtr = nextPtr->next;
		}
	}
}


//Prints all the nodes from source to destination ( including the source and destination),
//i.e. print_path(1,5) => 1 2 3 4 5
//otherwise it prints "path does not exit" or if source or dest nodes do not exist or if the graph is NULL.
void print_path(graph_t * g, int source, int dest){
	if (g == NULL || find_node(g, source) == NULL || find_node(g, dest) == NULL) { 
		printf("Path does not exist\n");
		return;
	}
	if (is_reachable(g, source, dest) != 1) {
		printf("Path does not exist\n");
		return;
	}
	node_t* ptr = g->nodes->head;
	while (ptr != NULL) {
		graph_node_t* curr = ptr->data;
		if (curr->data == source) {
			print_helper(ptr, dest);
		}
		ptr = ptr->next;
	}
}			

// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the program terminates.
// Make sure you free all the dll's too.
void free_graph(graph_t* g) {
	if (g == NULL) return;
	free_dll(g->nodes); 
	free(g);
	return;
}

		
#endif
