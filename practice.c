/**
 * @file practic..c
 * @brief Implementation file for practice-related functions and logic.
 *
 * This file contains the main code for demonstrating and testing various C programming concepts,
 * including function definitions, data structures, and algorithm implementations.
 * It serves as a practice ground for experimenting with C syntax and features.
 *
 * @author Suvrat Ramasubramanian
 * @date [Date]
*/

#include "practice.h"

char* getWrongAnswers(int N, char* C) {
  // Write your code here
  
  char *answers = (char*)malloc((N+1)*sizeof(char));
  
  for (int i =0; i<N; i++){
    printf("Original character at index %d : %c\n", i, C[i]);
    answers[i] = (C[i] == 'A') ? 'B': 'A';
    printf("Changed character at index %d : %c\n", i, answers[i]);
  }
  
  return answers;
}


int main(){

  int N = 3;
  char C[] = "ABA";
  
  char* wrongAnswers = getWrongAnswers(N, C);
  
  printf("Wrong Answers: %s\n", wrongAnswers);
  
  return 0;
}

