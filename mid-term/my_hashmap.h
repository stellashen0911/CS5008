// =================== Support Code =================
// Hashmap 
//
// - Implement each of the functions to create a working hashmap.
// - Do not change any of the function declarations
//   - (i.e. hashmap_t* hashmap_create() should not have additional arguments)
// - You should not have any 'printf' statements in your functions other 
//   than functions that explicitly ask for printf output. 
//   - (You may consider using these printf statements to debug,
//     but they should be removed from your final version)
// - You may add any helper functions that you think you need
//   (if any, or otherwise for debugging)
// ==================================================
#ifndef MY_HASHMAP_T
#define MY_HASHMAP_T

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// An entry consisting of a key-value pair.
// This is specifically for a (char*, char*) key-value pair
typedef struct pair {
    char* key;
    char* value;
} pair_t;

// Each node holds a key and a value
typedef struct node {
    pair_t* kv; // key/value pair
    struct node* next;
} node_t;


// Simple hash function that will put a key into a bucket
// You should not modify this
int stringHash(char* myKey, int numberOfBuckets){
    return strlen(myKey) % numberOfBuckets;
}

// This hash function use a char as hash number, and multiply it with a number 37 to produce a bucket number of a hash map.
int stringHashNew(char *myKey, int numberOfBuckets){
	int hash = 0;
	for (int i = 0; i < numberOfBuckets; i++){ 
		hash = 37 * hash + myKey[i];
		hash %= numberOfBuckets;
		if (hash < 0){
			hash += numberOfBuckets;
		}
	}
	return hash;
}

// Create a function prototype to a function that takes
// in a char* and an int.
typedef int(*hashFunctionPointer)(char*, int); 

// Chained implementation of a hashmap
typedef struct hashmap {
    unsigned int buckets;   // i.e. size of the hashmap
    node_t** arrayOfLists;  // An array of linked lists for our buckets
                            // Read another way -- an array of node_t*

    // A function pointer to a hash function
    // The hash_function must take in a 'char*' as a key, and have a
    // second parameter specifying the number of buckets.
    hashFunctionPointer hashFunction;
} hashmap_t;

// Creates a new hashmap
// Allocates memory for a new hashmap.
// Initializes the capacity(i.e. number of buckets)
// The algorithm is:
//  - allocate memory for our hashmap
//  - set the number of buckets
//  - initialize our array of lists for each bucket
//  - setup our hash function to point to our stringHash function
//  - return new map that we have created
hashmap_t* hashmap_create(unsigned int _buckets) {
	hashmap_t* newHashMap = (hashmap_t*)malloc(sizeof(hashmap_t));
	if (newHashMap == NULL) {
		return NULL;
	}

	newHashMap->buckets = _buckets;//set the number of buckets
	newHashMap->arrayOfLists = (node_t**)malloc(sizeof(node_t*) * _buckets);
	//initialize the array of list to null for each bucket
	for (int i = 0; i < _buckets; i++) {
		newHashMap->arrayOfLists[i] = NULL;
	}
	//setup out hash function to point to stringHash function
	newHashMap->hashFunction = stringHash;

    return newHashMap;//return new hash map we created
}

// Frees a hashmap
// Responsibility to free a hashmap that has been previously allocated.
// Must also free all of the chains in the hashmap
// This function should run in O(n) time
void hashmap_delete(hashmap_t* _hashmap) {
    if (_hashmap == NULL) {
		return;
	}
	//free every bucket of the array list
	for (int i = 0; i < _hashmap->buckets; i++) {
		if (_hashmap->arrayOfLists[i] == NULL) {
			free(_hashmap->arrayOfLists[i]);	
		} else {
			node_t* temp = _hashmap->arrayOfLists[i];
			//free every node within the bucket
			while (temp != NULL) {
				node_t* curr = temp;
				temp = temp->next;
				pair_t* temp_pair = curr->kv;
				char* temp_key = temp_pair->key;
				char* temp_value = temp_pair->value;
				free(temp_key);//free the key pointer
				free(temp_value);//free the value pointer
				free(temp_pair);//free the pair pointer
				free(curr);//free the node pointer
			}
		}
	}
	free(_hashmap->arrayOfLists);
	//free the hashmap
	free(_hashmap);
}

// Returns a boolean value if a key has been put into
// the hashmap
//  - Returns a '1' if a key exists already
//  - Returns a '0' if the key does not exist
//  - Returns a '-9999' if the hashmap is NULL
// The algorithm is:
//  - Call the _hashmap's hash function on the key
//  - Search that bucket to see if the key exists.
// This function should run in average-case constant time
int hashmap_hasKey(hashmap_t* _hashmap, char* key) {
	if (_hashmap == NULL) {
		return -9999;
	}
	//find what bucket the key will be landing if in the map
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
	node_t* head = _hashmap->arrayOfLists[bucket];
	//if the bucket is empty, the key is not in the map
	if (head == NULL) {
		return 0;
	} else {
		//if the bucket has chained node, then iterate through the chain to find key
		while (head != NULL) {
			//if we find out the key within the bucket, return 1	
			if (strcmp(head->kv->key, key)==0) {
				return 1;
			}
			head = head->next;
		}
	}
	//after iteration through the bucket, we did not find the key, return 0
	return 0;
}

// Insert a new key/value pair into a hashmap
// The algorithm is:
//  - If a key already exists, do not add it--return
//  - Call the _hashmap's hash function on the key
//  - Store the key/value pair at the end of the buckets chain
//      - You should malloc the key/value in this function
// This function should run in average-case constant time
void hashmap_insert(hashmap_t* _hashmap,char* key,char* value) {
	if(hashmap_hasKey(_hashmap,key)== 1){
	    return;
	}
	pair_t* newpair = (pair_t*)malloc(sizeof(pair_t));
	newpair->key = (char*)malloc(strlen(key) * sizeof(char) + 1);
	newpair->value = (char*)malloc(strlen(value) * sizeof(char) + 1);
	strcpy(newpair->key, key); 
	strcpy(newpair->value, value);
	node_t* newnode = (node_t*)malloc(sizeof(node_t));
	newnode->next = NULL;//append this node to the end of the bucket chain
	newnode->kv = newpair;

	//find which bucket to insert to
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
	node_t* head = _hashmap->arrayOfLists[bucket];
	if (head == NULL) {
		_hashmap->arrayOfLists[bucket] = newnode;
	} else {
		newnode->next = head;
		_hashmap->arrayOfLists[bucket] = newnode;
	}
}

// Return a value from a key 
// Returns NULL if the _hashmap is NULL
// Returns NULL if the key is not found
// The algorithm is:
//  - If the key does not exist, then--return NULL if not found.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and return the value
// This function should run in average-case constant time
char* hashmap_getValue(hashmap_t* _hashmap, char* key) {
	if (_hashmap == NULL) {
		return NULL;
	}
	//if the key does not exist in the map
	if (hashmap_hasKey(_hashmap, key) != 1) {
		return NULL;
	}
	//find which bucket to search
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
	node_t* head = _hashmap->arrayOfLists[bucket];
	if (head == NULL) {
		return NULL;
	} else {
		while (head != NULL) {
			if (strcmp(head->kv->key, key) == 0) {
				return head->kv->value;
			}
			head = head->next;
		}
	}
	return NULL;
}


// Remove a key from a hashmap
// The algorithm is:
//  - Determine if the key exists--return if it does not.
//  - Call the _hashmap's hash function on the key
//  - Search the _hashmap's bucket for the key and then remove it
// This function should run in average-case constant time
void hashmap_removeKey(hashmap_t* _hashmap, char* key) {
	if (_hashmap == NULL) {
		return;
	}
	//if the key does not exist in the map
	if (hashmap_hasKey(_hashmap, key) != 1) {
		return;
	}
	//find which bucket to search
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
	node_t* head = _hashmap->arrayOfLists[bucket];
	if (head == NULL) {
		return;
	} else {	
		node_t* pre = NULL; //set pre node as NULL when head is on the first position
		while (head != NULL) {
			if (strcmp(head->kv->key, key) == 0) {
				if (pre != NULL) {
					pre->next = head->next;
				} else {
					_hashmap->arrayOfLists[bucket] = head->next;
				}
				free(head->kv->key);
				free(head->kv->value);
				free(head->kv);
				free(head);
				return;
			} else {
				pre = head;
				head = head->next;
			}
		}
	}
	return;
}

// Update a key with a new Value
// The algorithm is:
//  - Returns immediately if the key does not exist
//  - Call the _hashmap's hash function on the key
//  - Updates the value of the key to the new value
// This function should run in average-case constant time
void hashmap_update(hashmap_t* _hashmap, char* key, char* newValue) {
	if (_hashmap == NULL) {
		return;
	}
	//if the key does not exist in the map
	if (hashmap_hasKey(_hashmap, key) != 1) {
		return;
	}
	//find which bucket to search
	unsigned int bucket = _hashmap->hashFunction(key, _hashmap->buckets);
	node_t* head = _hashmap->arrayOfLists[bucket];
	if (head == NULL) {
		return;
	} else {
		while (head != NULL) {
			if (strcmp(head->kv->key, key) == 0) {
				pair_t* curr_pair = head->kv;
				//first delete the original value
				free(head->kv->value);
				head->kv->value = (char*)malloc(strlen(newValue) * sizeof(char) + 1);
				strcpy(head->kv->value, newValue); 
				return;
			} 
			head = head->next;
		}
	}
	return;

}

// Prints all of the keys in a hashmap
// The algorithm is:
//  - Iterate through every bucket and print out the keys
// This function should run in O(n) time
void hashmap_printKeys(hashmap_t* _hashmap){
    if (_hashmap == NULL) {
		return;
	}
	//free every bucket of the array list
	for (int i = 0; i < _hashmap->buckets; i++) {
		printf("Bucket #%d\n", i);
		if (_hashmap->arrayOfLists[i] == NULL) {
			//if the bucket is empty, just keep going to the next bucket
			printf("this bucket is empty\n");
		} else {
			node_t* temp = _hashmap->arrayOfLists[i];
			//print every keys in every node of the bucket
			while (temp != NULL) {
				node_t* curr = temp;
				temp = temp->next;
				printf("\tKey:%s\tValue:%s\n", curr->kv->key, curr->kv->value);
			}
		}
	}
	return;
}

#endif
