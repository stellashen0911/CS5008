// Compile this assignment with: gcc -Wall main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"


// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.


//// Testing add node
int unitTest1(){
	int result;
	graph_t * graph = create_graph();
    graph_add_node(graph, 1);
    graph_add_node(graph, 3);
    graph_add_node(graph, 2);
	graph_add_node(graph, 4);
	graph_add_node(graph, 5);
	if (graph_num_nodes(graph) == 5) {
		result = 1;
	} else {
		result = 0;
	}
	free_graph(graph);
	return result;
}

// Testing the delete node
int unitTest2(){
	int result;
	graph_t * graph = create_graph();
    graph_add_node(graph, 1);
    graph_add_node(graph, 3);
    graph_add_node(graph, 2);
	graph_add_node(graph, 4);
	graph_add_node(graph, 5);
	graph_remove_node(graph, 3);
	if (graph_num_nodes(graph) == 4) {
		result = 1;
	} else {
		result = 0;
	}
	free_graph(graph);
	return result;
}

// Testing the add edge and is reachable method
int unitTest3(){
	int result;
	graph_t * graph = create_graph();
    graph_add_node(graph, 1);
    graph_add_node(graph, 3);
    graph_add_node(graph, 2);
	graph_add_node(graph, 4);
	graph_add_node(graph, 5);
	if (graph_add_edge(graph, 1, 4)  == 1 &&
		contains_edge(graph, 1, 4) == 1 &&
		is_reachable(graph, 1, 4) == 1) {
		result = 1;
	} else {
		result = 0;
	}
	free_graph(graph);
	return result;
}

// Testing the has cycle method
int unitTest4(){
	int result;
	graph_t * graph = create_graph();
    graph_add_node(graph, 1);
    graph_add_node(graph, 3);
    graph_add_node(graph, 2);
	graph_add_node(graph, 4);
	graph_add_node(graph, 5);
	graph_add_edge(graph, 1, 3);
	graph_add_edge(graph, 3, 4);
	graph_add_edge(graph, 4, 1);
	if (has_cycle(graph) == 1) {
		result = 1;
	} else {
		result = 0;
	}
	free_graph(graph);
	return result;
}
int (*unitTests[])(int) = {
    unitTest1,
	unitTest2,
    unitTest3,
	unitTest4,
    NULL
};


// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){
	unsigned int testsPassed = 0;
    // List of Unit Tests to test your data structure
    int counter = 0;
    while(unitTests[counter] != NULL){
		printf("========unitTest %d========\n",counter);
		if(1 == unitTests[counter](1)){
			printf("passed test\n");
			testsPassed++;	
		}else{
			printf("failed test, missing functionality, or incorrect test\n");
		}
        counter++;
    }
    printf("%d of %d tests passed\n",testsPassed,counter);
    return 0;
}

