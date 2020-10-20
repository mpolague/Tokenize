#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

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

  //HISTORY CALLS
  char *temp = str;
  List *strings;
  strings = init_history(); //initialize list
  int num_words = count_words(str);

  for (int i = 0; i <num_words;i++){ //loop to add nodes up to the number of words
    add_history(strings,temp);
    temp = word_terminator(temp); //word_start and word_terminator to get the start of a word each
    temp = word_start(temp); //time it loops and sends it to add_history
  }
  
  history_UI(strings,str); //UI for printing and finding strings in history list
  free_history(strings);
}
