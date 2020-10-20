#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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

int string_compare(char str1[], char str2[]){
  int ctr = 0;
  while(str1[ctr] == str2[ctr]){
    if(str1[ctr] == '\0' || str2[ctr] == '\0')
      break;
    ctr++;
  }
  if(str1[ctr] == '\0' && str2[ctr] == '\0')
    return 0;
  else
    return -1;
}

/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char* instr){
  char **token = tokenize(instr); //tokenizes the string
  //created an array containing the first POSSIBLE words
  char *first[] = {"LW", "LD", "SW", "SD", "ADD", "ADDI", "SLLI", "SRLI", "AND", "OR", "XOR"};
  int check_instr;
  char *instru[1];
  char *firstReg[1];
  char *secReg;
 
  int size_first = sizeof first / sizeof *first;

  //-------------------TAKING CARE OF FINDING THE INSTRUCTION----------------------------
  for(int i = 0; i < size_first; i++){ //will iterate through the list and check if it exists
    check_instr = string_compare(token[0], first[i]);
    if(check_instr == 0){ //if found, it equals 0
      instru[0] = first[i];
      break;
    }
  }
  if(check_instr == 0){
    printf("-INSTRUCTION: %s \n", instru[0]);
  }
  else{
    return false;
  }
  //-------------------THE FIRST REGISTER WILL BE THE SECOND TOKEN----------------------
  
  firstReg[0] = token[1];
  printf("-DEST REGISTER: %s \n", firstReg[0]);

  //------------------CHECKING IF INSTR = LW or LD or SW or SW -------------------------
  if(instru[0] == "LW" || instru[0] == "LD" || instru[0] == "SW" || instru[0] =="SD"){
    secReg = strtok(token[2], "("); //still not tokenized
    char *imm = secReg; //the immediate of the second register
    char *secondReg; //actual second register
    
    while(secReg != NULL){
      secondReg = secReg;
      secReg = strtok(NULL, "(");
    }
    
    printf("-IMMEDIATE FOR SECOND REGISTER: %s\n", imm);
    printf("-SECOND REGISTER: %s\n", secondReg);
  } 
  //--------CHECKING IF INSTRUCTION IS   "ADD"  or  "AND"  or   "OR"  or   "XOR"----------------
  char *secondRegExtra[1];
  char *thirdRegExtra[1];
  if(instru[0] == "ADD" || instru[0] == "AND" || instru[0] == "OR" || instru[0] == "XOR"){
    secondRegExtra[0] = token[2];
    printf("-SECOND REGISTER: %s\n", secondRegExtra[0]);
    thirdRegExtra[0] = token[3];
    printf("-THIRD REGISTER: %s\n", thirdRegExtra[0]);
  }
  //-------------------CHECKING IF INSTRUCTION IS   "ADDI"   or   "SLLI"   or   "SRLI" -----------
  char *immediates[1];
  char *secondRegImm[1];
  if(instru[0] == "ADDI" || instru[0]== "SLLI" || instru[0]=="SRLI"){
    secondRegImm[0] = token[2];
    immediates[0] = token[3];
    printf("-SECOND REGISTER %s\n", secondRegImm[0]);
    printf("-IMMEDIATE: %s\n", immediates[0]);
  }
  
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
  printf("----------------------------------------------------------------------\n");
  printf("Hello, this program only takes in instructions with spaces. Not commas.\n");
  printf("----------------------------------------------------------------------\n");
 
  char user_input[INPUT_LIM]; 
  //will ask for user input until they enter ctrl+D
  init_regs(); //DO NOT REMOVE THIS LINE
 
  while(1){
    printf("--->Enter an instruction or use ctrl+D on windows to exit the program\n");
    printf("$ ");
    fgets(user_input,INPUT_LIM,stdin); //get user input
    char *str = user_input;

    //----------------CHECK IF CONTROL D PRESSED -------------------
    if (str[0] == EOF){ //FOR NOW EOF = /n
      break;
    }
    //--------------------------------------------------------------
    
    bool correctlyExec =  interpret(str); //calls interpret function from riscv.c file
    if (correctlyExec == 0){ //if not executed correctly
      printf("--->Sorry. This was not executed correctly.\n");
    }
  }
  printf("\n");  

  return 0;
}
