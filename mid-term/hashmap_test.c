// Note: This is not an exhaustive test suite, but gives you the idea
//       of some tests you might want to create.
//
// Compile this assignment with: gcc -g -Wall hashmap_test.c -o hashmap_test
//
// Run with: ./hashmap_test
//
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_hashmap.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.


// A sample collection of tests for your program
// You can add as many unit tests as you like
// We will be adding our own to test your program.


// Tests creation and deletion of the hashmap
// Ideally does not cause any segfaults, and this
// is considered passing.
int unitTest1(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(12);    
    hashmap_delete(test);
    passed = 1;
    return passed;
}

// Tests has_key for a missing key
int unitTest2(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(12);
    
    if(hashmap_hasKey(test, "cow")==0){
      passed = 1;
    }
    
    hashmap_delete(test);
    return passed;
}


// Tests insert and has_key
int unitTest3(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(12);
    hashmap_insert(test,"cow","A common farm animal.");
    
    if(hashmap_hasKey(test, "cow")==1) {
      passed = 1;
    }
    
    hashmap_delete(test);
    return passed;
}

// Tests insert and has_key and remove key
int unitTest4(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(12);
    hashmap_insert(test,"cow","A common farm animal.");
    hashmap_removeKey(test, "cow");
    
    if(hashmap_hasKey(test, "cow")==0) {
      passed = 1;
    }
    
    hashmap_delete(test);

    return passed;
}

// Tests update_key
int unitTest5(int status) {
    int passed = 0;
    hashmap_t* test = hashmap_create(12);
    hashmap_insert(test,"cow","A common farm animal.");
    hashmap_update(test, "cow", "A common farm animal in Ohio.");
    
    if(hashmap_hasKey(test, "cow")==1) {
      passed = 1;
    }
    
    hashmap_delete(test);
    return passed;
}

// Tests hashmap_hasKey & hashmap_getValue 
int unitTest6(int status) {
	int passed = 0;
	hashmap_t* test = hashmap_create(12);
	hashmap_insert(test, "good", "mean");
	char* c = (char*)malloc(sizeof(char) * 5);
	strcpy(c, "mean");
	char* v = hashmap_getValue(test, "good");
	if (strcmp(c, v) == 0) {
		passed = 1;
	}
	hashmap_delete(test);
	free(c);
	return passed;
}

// Tests hashmap functions overall
int unitTest7(int status) {
	int passed = 0;
	hashmap_t* test = hashmap_create(12);
	hashmap_insert(test, "a", "A");
	hashmap_insert(test, "b", "B");
	hashmap_insert(test, "c", "C");
	hashmap_insert(test, "d", "D");
	hashmap_insert(test, "e", "E");
	hashmap_insert(test, "f", "F");
	hashmap_insert(test, "g", "G");
	hashmap_insert(test, "h", "H");
	hashmap_printKeys(test);
	hashmap_removeKey(test, "a");
	if (hashmap_hasKey(test, "a") != 1) {
		passed = 1;
	}
	hashmap_delete(test);
	return passed;
}

// Tests hashmap functions overall
int unitTest8(int status) {
	int passed = 0;
	hashmap_t* test = hashmap_create(12);
	hashmap_insert(test, "a", "A");
	hashmap_insert(test, "b", "B");
	hashmap_insert(test, "c", "C");
	hashmap_insert(test, "d", "D");
	hashmap_insert(test, "e", "E");
	hashmap_insert(test, "f", "F");
	hashmap_insert(test, "g", "G");
	hashmap_insert(test, "h", "H");
	hashmap_delete(test);
	hashmap_t* test2 = hashmap_create(12);
	hashmap_insert(test2, "d", "dd");
	if (hashmap_hasKey(test2, "a") == -9999
		|| hashmap_hasKey(test2, "a") == 0 ) {
		passed = 1;
	}
	hashmap_delete(test2);
	return passed;
}

// Tests hashmap functions overall
int unitTest9(int status) {
	int passed = 0;
	hashmap_t* test = hashmap_create(12);
	hashmap_insert(test, "a", "A");
	hashmap_insert(test, "a", "B");
	hashmap_insert(test, "a", "C");
	hashmap_insert(test, "a", "D");
	hashmap_insert(test, "e", "E");
	hashmap_insert(test, "f", "F");
	hashmap_insert(test, "g", "G");
	hashmap_insert(test, "h", "H");
	char* a_value = hashmap_getValue(test, "a");
	if (strcmp("A", a_value) == 0) {
		passed = 1;
	}
	hashmap_delete(test);
	return passed;
}

int (*unitTests[])(int)={
	 unitTest1,
	 unitTest2,
	 unitTest3,
	 unitTest4,
	 unitTest5,
	 unitTest6,
	 unitTest7,
	 unitTest8,
	 unitTest9,
    NULL
};


// ====================================================
// ================== Program Entry ===================
// ====================================================
int main() {
    unsigned int testsPassed = 0;
    // List of Unit Tests to test your data structure
    int counter =0;
    while(unitTests[counter]!=NULL){
	printf("========unitTest %d========\n", counter);
        if(1==unitTests[counter](1)){
		printf("passed test\n");
		testsPassed++;	
	}else{
		printf("failed test, missing functionality, or incorrect test\n");
	}
        counter++;
    }

    printf("%d of %d tests passed\n", testsPassed, counter);

    return 0;
}
