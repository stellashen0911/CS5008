//Name : Minjie Shen
//Homework 8 BST

// Include our header file for our my_bst.c
#include "my_bst.h"

// Include any other libraries needed
#include <stdio.h>
#include <stdlib.h>

// Creates a BST
// Returns a pointer to a newly created BST.
// The BST should be initialized with data on the heap.
// The BST fields should also be initialized to default values(i.e. size=0).
bst_t* bst_create(){
    bst_t* myBST= (bst_t*)malloc(sizeof(bst_t)); 
	myBST->root = NULL;
	myBST->size = 0;
    return myBST;
}

// BST Empty
// Check if the BST is empty
// Returns 1 if true (The BST is completely empty)
// Returns 0 if false (the BST has at least one element)
int bst_empty(bst_t* t){
	if (t == NULL) {
		return 1;
	}
	if (t->size == 0) {
		return 1;
	}
    return 0;
}

//helper method to add a new item to the original non-NULL bst recursively
//if successfully add the new node, return 1
//else return 0 to indicate fail
int bst_add_helper(bstnode_t* root, int item) {
	if(root == NULL) return 0; //we deal with this situation in the parent function
	if (item <= root->data) {
		// the item should be on the left side of the root
		if (root->leftChild == NULL) {
			//if the root does not have a left node, the item is the new node
			root->leftChild = (bstnode_t*)malloc(sizeof(bstnode_t));
			root->leftChild->data = item;
			root->leftChild->leftChild = NULL;
			root->leftChild->rightChild = NULL;
			return 1;
		} else {
			//recursively find the right position on the left sub tree
			if (bst_add_helper(root->leftChild, item) == 1) {
				return 1;
			}
		}
	} else { //if the item value is greater than root->data, it should be on the right side of the bst
		if (root->rightChild == NULL) {
			root->rightChild = (bstnode_t*)malloc(sizeof(bstnode_t));
			root->rightChild->data = item;
			root->rightChild->leftChild = NULL;
			root->rightChild->rightChild = NULL;
			return 1;
		} else {
			if (bst_add_helper(root->rightChild, item) == 1) {
				return 1;
			}
		}
	}
	return 0;
}

// Adds a new node containng item to the BST
// The item is added in the correct position in the BST.
//  - If the data is less than or equal to the current node we traverse left
//  - otherwise we traverse right.
// The bst_function returns '1' upon success
//  - bst_add should increment the 'size' of our BST.
// Returns a -1 if the operation fails.
//      (i.e. the memory allocation for a new node failed).
// Your implementation should should run in O(log(n)) time.
//  - A recursive imlementation is suggested.
int bst_add(bst_t* t, int item){
    if (t == NULL) return -1; //if the BST is null, return fail
	if (t->root == NULL && t->size != 0) return -1; //if the bst is not valid, return fail
	if (bst_empty(t)) {
		//if the bst is empty, we set the root as the item we need to create
		t->root = (bstnode_t*)malloc(sizeof(bstnode_t));
		//we initialize the bst root node as a bstnode_t*
		t->root->data = item;
		t->root->leftChild = NULL;
		t->root->rightChild = NULL;
		t->size = t->size + 1;
		return 1;
	} else {
		//if the bst does not have empty root, we add the item recursively 
		if (bst_add_helper(t->root, item) == 1) {
			t->size = t->size + 1;
			return 1;
		} else {
			return 0;
		}
	}
	return 0;
}

//helper function for bst_print, print the bst in ascending order,
//which is the in-order traversal of the bst
void bst_print_in_order(bstnode_t* root) {
	if (root == NULL) return;
	bst_print_in_order(root->leftChild);
	printf("%d ", root->data);
	bst_print_in_order(root->rightChild);
	return;
}

//helper function for bst_print, print the bst in descending order
void bst_print_descending(bstnode_t* root) {
	if (root == NULL) return;
	bst_print_descending(root->rightChild);
	printf("%d ", root->data);
	bst_print_descending(root->leftChild);
	return;
}


// Prints the tree in ascending order if order = 0, otherwise prints in descending order.
// A BST that is NULL should print "(NULL)"
// It should run in O(n) time.
void bst_print(bst_t *t, int order){
    if(NULL == t){
        printf("(NULL)");
    }else{
		if (t->root == NULL) {
			printf("(NULL)");
		} else {
			if (order == 0) {
				bst_print_in_order(t->root);
				return;
			} else {
				bst_print_descending(t->root);
				return;
			}
		}
    }
}

//Helper function to find the sum of the bst
int bst_sum_helper(bstnode_t* root) {
	if (root == NULL) return 0;
	int sum = 0;
	sum += bst_sum_helper(root->leftChild);
	sum += bst_sum_helper(root->rightChild);
	sum += root->data;
	return sum;
}

// Returns the sum of all the nodes in the bst. 
// A BST that is NULL exits the program.
// It should run in O(n) time.
int bst_sum(bst_t *t){
	if (t == NULL) exit(0);
	return bst_sum_helper(t->root);
}

//Helper function to find the target value in the bst
int bst_find_helper(bstnode_t* root, int value) {
	if (root == NULL) return 0; 
	if (root->data == value) return 1; 
	if (value < root->data) {
		return bst_find_helper(root->leftChild, value);
	} else {
		return bst_find_helper(root->rightChild, value);
	}
	return 0;
}

// Returns 1 if value is found in the tree, 0 otherwise. 
// For NULL tree -- exit the program. 
// It should run in O(log(n)) time.
int bst_find(bst_t * t, int value){
	if (t == NULL) exit(0);
	return bst_find_helper(t->root, value);
}

// Returns the size of the BST
// A BST that is NULL exits the program.
// (i.e. A NULL BST cannot return the size)
unsigned int bst_size(bst_t* t){
    if (t == NULL) exit(0);
	return t->size;
}


//Helper function to free all the node in the bst
void bstnode_free(bstnode_t* root) {
	if (root == NULL) return;
	bstnode_free(root->leftChild); //recursively free the left sub tree of the root
	bstnode_free(root->rightChild); //recursively free the right sub tree of the root
	free(root); //free the root node
}

// Free BST
// Removes a BST and ALL of its elements from memory.
// This should be called before the proram terminates.
void bst_free(bst_t* t){
	if (t == NULL) return;
	bstnode_free(t->root);
	free(t);
}

