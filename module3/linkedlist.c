// Modify this file
// compile with: gcc linkedlist.c -o linkedlist

#include <stdio.h>
#include <stdlib.h> // contains the functions free/malloc

// TODO: Create your node_t type here
typedef struct node{
	int win_data;
	int year;
	struct node* next;
}node_t;

// TODO: Write your functions here
// There should be 1.) create_list 2.) print_list 3.) free_list
// You may create as many helper functions as you like.
node_t* create_list() {
	node_t* head2018 = (node_t*)malloc(sizeof(node_t));
	node_t* node2017 = (node_t*)malloc(sizeof(node_t));
	node_t* node2016 = (node_t*)malloc(sizeof(node_t));
	node_t* node2015 = (node_t*)malloc(sizeof(node_t));
	node_t* node2014 = (node_t*)malloc(sizeof(node_t));
	
	head2018->year = 2018;
	node2017->year = 2017;
	node2016->year = 2016;
	node2015->year = 2015;
	node2014->year = 2014;

	head2018->win_data = 108;
	node2017->win_data = 93;
	node2016->win_data = 93;
	node2015->win_data = 78;
	node2014->win_data = 71;

	head2018->next = node2017;
	node2017->next = node2016;
	node2016->next = node2015;
	node2015->next = node2014;
	node2014->next = NULL;

	return head2018;	
}

void print_list(node_t* head) {
	node_t* itr = head;
	while(itr != NULL) {
		printf("%d, %d wins\n", itr->year, itr->win_data);
		itr = itr->next;
	}
}

void free_list(node_t* head) {
	node_t* itr = head;
	while(itr != NULL) {
		free(itr);
		itr = itr->next;
	}
}

int main(){
	// TODO: Implement me!  
	node_t* head = NULL;
	head = create_list();
	print_list(head);
	free_list(head);
    return 0;
}
