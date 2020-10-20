#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

#define INPUT_LIM 50  //limit on how many characters a user can input

int main(){

  //TOKENIZER CALLS
  char user_input[INPUT_LIM]; 
  printf("$ ");
  fgets(user_input,INPUT_LIM,stdin); //get user input
  char *str = user_input;

  char **token = tokenize(str);  
  print_tokens(token); 
  free_tokens(token); 
  printf("\n");  
}
