// Implement your cycle count tool here.
// Name: Minjie Shen
// CS5008 Lab: Estimating Execution
//
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include <ctype.h>

// this is the function to check how many cycles the str will be count;
// since ADDQ, ADDB all count as ADD, we just need to compare the first three characthers,
// if the first three charecters are the same as ADD, we return the cycle number 1.

void print_frequency(int* arr) {
	for (int i = 0; i < 9; i++) {
		if (arr[i] == 0) {
			continue;
		}
		if (i == 0) {
			printf("ADD %d\n", arr[i]);
		}
		if (i == 1) {
			printf("SUB %d\n", arr[i]);
		}
		if (i == 2) {
			printf("MOV %d\n", arr[i]);
		}
		if (i == 3) {
			printf("PUSH %d\n", arr[i]);
		}
		if (i == 4) {
			printf("POP %d\n", arr[i]);
		}
		if (i == 5) {
			printf("RET %d\n", arr[i]);
		}
		if (i == 6) {
			printf("MUL %d\n", arr[i]);
		}
		if (i == 7) {
			printf("LEA %d\n", arr[i]);
		}
		if (i == 8) {
			printf("DIV %d\n", arr[i]);
		}
	}
}



void count_frequency(char str[], int* arr) {
	char a[] = "add";
	char s[] = "sub";
	char m[] = "mul";
	char m2[] = "imul";
	char d[] = "div";
	char d2[] = "idiv";
	char mo[] = "mov";
	char l[] = "lea";
	char pu[] = "push";
	char po[] = "pop";
	char re[] = "ret";
	if (strncmp(str, a, 3) == 0) {
		arr[0]++;
	}
	if (strncmp(str, s, 3) == 0) {
		arr[1]++;
	}
	if (strncmp(str, mo, 3) == 0) {
		arr[2]++;
	}
 	if (strncmp(str, pu, 3) == 0) {
		arr[3]++;
	}
	if (strncmp(str, po, 3) == 0) {
		arr[4]++;
	}
    if (strncmp(str, re, 3) == 0) {
		arr[5]++;
	}	
	if (strncmp(str, m, 3) == 0 ||
	    strncmp(str, m2, 3) == 0) {
		arr[6]++;
	}	
	if (strncmp(str, l, 3) == 0) {
		arr[7]++;
	}
	if (strncmp(str, d, 3) == 0 ||
		strncmp(str, d2, 3) == 0) {
		arr[8]++;
	}
}


int string_to_cycles(char str[]) {
	if (strlen(str) < 3) {
		return 0;
	}
	char a[] = "add";
	char s[] = "sub";
	char m[] = "mul";
	char m2[] = "imul";
	char d[] = "div";
	char d2[] = "idiv";
	char mo[] = "mov";
	char l[] = "lea";
	char pu[] = "push";
	char po[] = "pop";
	char re[] = "ret";
	if (strncmp(str, a, 3) == 0 ||
	    strncmp(str, s, 3) == 0 ||
	    strncmp(str, mo, 3) == 0 ||
 	    strncmp(str, pu, 3) == 0 ||
	    strncmp(str, po, 3) == 0 ||
	    strncmp(str, re, 3) == 0) {
		return 1;
	}	
	if (strncmp(str, m, 3) == 0 ||
	    strncmp(str, m2, 3) == 0 ||
	    strncmp(str, l, 3) == 0) {
		return 3;
	}
	if (strncmp(str, d, 3) == 0) {
		return 24;
	}
	return 0;
}

int parse_instructions(char instruct[], int* cycle, int* arr) {
	*cycle = string_to_cycles(instruct);
	count_frequency(instruct, arr);
	return 1;
}

int main(int argc, char** argv){
	assert(argc == 2);

	char* file_name = argv[1];
	FILE* input_file = fopen(file_name, "r");
	if (input_file == NULL) {
		return 1;
	}

	int total_cycles = 0;
	int num_of_instructions = 0;
	int cycle_num;
	int arr[9];
	for (int i = 0; i < 9; i++) {
		arr[i] = 0;//set all frequency to 0 at first
	}

	char instructions[20];
	while (fscanf(input_file, "%s", instructions) == 1) {
		parse_instructions(instructions, &cycle_num, arr);
		if (cycle_num != 0) {
			num_of_instructions++;
		}
		total_cycles += cycle_num;
	}
	
	print_frequency(arr);
	printf("\n");
	printf("Total Instructions = %d\n", num_of_instructions);
	printf("Total Cycles = %d\n", total_cycles);

	return 0;
}

