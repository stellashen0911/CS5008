// ==================================================
// Name: Minjie Shen
// Homework 4 for CS5008 Doublely Linked List
// Program: It construct a doublely linkedlist to store integer data.

#ifndef MYDLL_H
#define MYDLL_H
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node {
	void* data;
	struct node* next;
  	struct node* previous;
} node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL {
	int count;		// count keeps track of how many items are in the DLL.
	node_t* head;		// head points to the first node in our DLL.
    node_t * tail;          //tail points to the last node in our DLL.
} dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t* create_dll(){
	// Modify the body of this function as needed.
	dll_t* myDLL = (dll_t*)malloc(sizeof(dll_t));
	if(myDLL == NULL) {
		return NULL;
	}
	myDLL->head = NULL;
	myDLL->tail = NULL;
	myDLL->count = 0;
	return myDLL;
}

// DLL Empty
// Check if the DLL is empty
// Returns -1 if the dll is NULL.
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
int dll_empty(dll_t* l){
	if(l == NULL) {
		return -1;
	}
	if(l->count == 0) {
		return 1;
	} else {
		return 0;
	}	
	return -1;
}

// push a new item to the front of the DLL ( before the first node in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t* l, void* item){
	if(l == NULL) {
		return -1;
	}
	node_t* new_front_node = (node_t*)malloc(sizeof(node_t));
	if(new_front_node == NULL) {
		return 0;
	}
	new_front_node->data = item;
	if(l->count == 0) {
		new_front_node->previous = NULL;
		new_front_node->next = NULL;
		l->head = new_front_node;
		l->tail = new_front_node;
	} else {
		new_front_node->next = l->head;
		l->head->previous = new_front_node;
		new_front_node->previous = NULL;
		l->head = new_front_node;
	}
	l->count++;
	return 1;
}

// push a new item to the end of the DLL (after the last node in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t* l, void* item){
	if(l == NULL) {
		return -1;
	}
	node_t* new_last = (node_t*)malloc(sizeof(node_t));
	
	if(new_last == NULL) {
		return 0;
	}
	new_last->data = item;
	if(l->count == 0) {
		new_last->next = NULL;
		new_last->previous = NULL;
		l->head = new_last;
		l->tail = new_last;
	} else {
		new_last->previous = l->tail;
		l->tail->next = new_last;
		new_last->next = NULL;
		l->tail = new_last;
	}
	l->count++;
	return 1; 
}

// Returns the first item in the DLL and also removes it from the list.
// Returns -1 if the DLL is NULL. 
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
int dll_pop_front(dll_t* t){
	if(t == NULL) {
		return -1;
	}
	if(t->count == 0 || t->head == NULL) {
		return 0;
	}
	//record the current front node
	node_t* node_pop = t->head;
	node_t* new_head = node_pop->next;
	if (new_head == NULL) {
		t->head = NULL;
		t->tail = NULL;
		t->count--;
		free(node_pop);
		return 1;
	} else {
		//set the head node to be the next of the front node
		t->head = new_head;
		//set the new head node previous to be NULL
		t->head->previous = NULL;
		//free the original head node
		free(node_pop);
		t->count--;
		return 1;
	}	
	return -1;
}


// Returns the last item in the DLL, and also removes it from the list.
// Returns a -1 if the DLL is NULL. 
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
int dll_pop_back(dll_t* t){
	if(t == NULL) {
		return -1;
	}
	if(t->count == 0 || t->tail == NULL) {
		return 0;
	}

	//record the tail node (to be deleted)
	node_t* last_node = t->tail;
	node_t* new_tail = last_node->previous;
	if (new_tail == NULL) {
		t->head = NULL;
		t->tail = NULL;
		t->count--;
		free(last_node);
		return 1;
	}else {
		//set the new tail node to be the previous of the original tail
		t->tail = new_tail;
		//set the new tail node next to be NULL
		t->tail->next = NULL;
		free(last_node);
		t->count = t->count - 1;
		return 1;
	}
	return -1;
}

// Inserts a new node before the node at the specified position.
// Returns -1 if the list is NULL
// Returns 1 on success
// Retruns 0 on failure:
//  * we couldn't allocate memory for the new node
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent as calling push_back).
int dll_insert(dll_t* l, int pos, void* item){
	if(l == NULL) {
		return -1;
	}
	node_t* insert_node = (node_t*)malloc(sizeof(node_t));

	if(insert_node == NULL || pos < 0 || pos > l->count) {
		return 0;
	}
	
	//if position is 0, this is equivalent to insert at front
	if (pos == 0) {
		if (dll_push_front(l, item) == 1) {
			return 1;
		}
	}
	//if position is the size of the linkedlist, this is equivalent to push back
	if(pos == l->count) {
		if (dll_push_back(l, item) == 1) {
			return 1;
		}
	}
	//the new node data is item
	insert_node->data = item;
	//use an iterator to move to the position
	node_t* itr = l->head;
	int count = 1;
	while(count != pos) {
		itr = itr->next;
		count++;
	}
	insert_node->next = itr->next;
	itr->next->previous = insert_node;
	insert_node->previous = itr;
	itr->next = insert_node;

	l->count++;
	return 1;
}

// Returns the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the list is NULL
//  (does not remove the item)
// Returns 0 on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Assume no negative numbers in the list or the number zero.
void* dll_get(dll_t* l, int pos){
	if(l == NULL) {
		return NULL;
	}
	if(pos < 0 || pos >= l->count) {
		return NULL;
	}
	int count = 0;
	node_t* itr = l->head;
	while(count != pos) {
		itr = itr->next;
		count++;
	}
	return itr->data; // Note: This line is a 'filler' so the code compiles.
}

// Removes the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the list is NULL
// Returns 0 on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Assume no negative numbers in the list or the number zero.
int dll_remove(dll_t* l, int pos){
	if(l == NULL) {
		return -1;
	}
	if(pos < 0 || pos >= l->count) {
		return 0;
	}
	if(pos == 0) {
		if (dll_pop_front(l) != -1) {
			return 1;
		}
	}
	if(pos == l->count - 1) {
		if (dll_pop_back(l) != -1) {
			return 1;
		}
	}
	node_t* itr = l->head;
	int count = 0;
	while (count != pos) {
		itr = itr->next;
		count++;
	}
	itr->previous->next = itr->next;
	itr->next->previous = itr->previous;
	free(itr);
	l->count--;
	return 1;
}

// DLL Size
// Returns -1 if the DLL is NULL.
// Queries the current size of a DLL
int dll_size(dll_t* t){
	if (t == NULL) {
		return -1; 
	}
	return t->count;
}

// Free DLL
// Removes a DLL and all of its elements from memory.
// This should be called before the proram terminates.
void free_dll(dll_t* t){
	if (t == NULL) {
		return;
	}
	int size = dll_size(t);
	if (size == 0) {
		free(t);
		return;
	}
	node_t* itr = t->head;
	while(itr != NULL) {
		node_t* temp = itr;
		itr = itr->next;
		free(temp);
	}
	free(t);
	return;
}


#endif
