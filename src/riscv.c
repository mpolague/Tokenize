#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file
#define INPUT_LIM 50 //limit on how many characters a user can input

int64_t* r; // Array of 32 64-bit registers

void init_regs();
bool interpret(char* instr);
void write_read_demo();

/**
 * Initialize register array for usage.
 * Malloc space for each 64-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	r = malloc(reg_amount * sizeof(int64_t)); // 32 * 8 bytes
	for(int i = 0; i < 32; i++){
		r[i] = 0;
	}
}



/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char* instr){
  //tokenize then interpret
  char **token = tokenize(instr); //tokenizes the string
  //created an array containing the first word
  char *first[] = {"LW", "LD", "SW", "SD", "ADD", "ADDI", "SLLI", "SRLI", "AND", "OR", "XOR"};
  //char *firstOfToken[] = *token[0];
  print_tokens(token);
  
  //bool checkEqual = true;
  //for(int i = 0; i < 3; i++){
  //  if(token[0][i] != 0){
  //    if(token[i] != first[i]){
  //	printf("Token[0][i] is %c and first[i] is %c", token[i], first[i]);
  //	checkEqual = false;
  //	break;
  //   }      
  //}
  //}
  printf("IT ISSSS: %d", checkEqual);
 
  
  return true;
}


/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
void write_read_demo(){
	int64_t data_to_write = 0xFFF; // equal to 4095
	int64_t address = 0x98; // equal to 152
	char* mem_file = "mem.txt";
	
	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int64_t write = write_address(data_to_write, address, mem_file);
	if(write == (int64_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int64_t read = read_address(address, mem_file);
	
	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}


/** 
 * Your code goes in the main
 * 
 */
int main(){
  // Do not write any code between init_regs
  init_regs(); // DO NOT REMOVE THIS LINE
	
  // Below is a sample program to a write-read. Overwrite this with your own code.
  write_read_demo();
	
  //TOKENIZER CALLS
  char user_input[INPUT_LIM]; 
  printf("$ ");
  //will ask for user input until
  init_regs(); //DO NOT REMOVE THIS LINE
 
  while(1){
    fgets(user_input,INPUT_LIM,stdin); //get user input
    char *str = user_input;
    if (str == '/n'){ //FOR NOW EOF = /n
      break;
    }
    bool correctlyExec =  interpret(str); //calls interpret function from riscv.c file
  }
  
  //char **token = tokenize(str);  
  //print_tokens(token); 
  //free_tokens(token); 
  printf("\n");  

  return 0;
}
