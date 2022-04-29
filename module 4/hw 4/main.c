// Compile this assignment with: gcc -g -Wall main.c -o main
// Use this file to implement testing for your
// doubly linked list implementation
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_dll.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.



// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){
    dll_t * dll = create_dll();
	printf("Now the DLL has size %d\n",dll->count);
	
	//test empty
	if (dll_empty(dll) == 1) {
		printf("So, the DLL is empty\n");
	} else {
		printf("the DLL is not empty. \n");
	}

	//test push front
	dll_push_front(dll,1);
	printf("Now insert 1 to the list\n");
	dll_push_front(dll,2);
	printf("Now insert 2 to the list\n");
	dll_push_front(dll,3);
	printf("Now insert 3 to the list\n");

	printf("Now the DLL has size %d elements on the list\n",dll->count);

	//test pop front
	dll_pop_front(dll);
	dll_pop_front(dll);
	dll_pop_front(dll);
	printf("Deleted 3 items from the list\n");
	printf("Now the DLL has size %d elements on the list\n",dll->count);

	//test push back
	dll_push_back(dll,1);
	printf("Now insert %d to the list\n", dll_get(dll, 0));
	dll_push_back(dll,2);
	printf("Now insert %d to the list\n", dll_get(dll, 1));
	dll_push_back(dll,3);
	printf("Now insert %d to the list\n", dll_get(dll, 2));
	printf("Now the DLL has size %d elements on the list\n",dll->count);

	printf("Delete %d from the list\n", dll_pop_back(dll));
	printf("Delete %d from the list\n", dll_pop_back(dll));
	printf("Delete %d from the list\n", dll_pop_back(dll));

	printf("Now the DLL has size %d elements on the list\n",dll->count);

	//test insert
	dll_push_back(dll,1);
	dll_push_back(dll,1);
	dll_push_back(dll,1);
	dll_push_back(dll,1);
	dll_push_back(dll,1);
	dll_push_back(dll,1);
	dll_push_back(dll,1);

	dll_insert(dll,2,2);
	printf("After insertion, the 2 position is %d now\n", dll_get(dll, 2));


    return 0;
}
