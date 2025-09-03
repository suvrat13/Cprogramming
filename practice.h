/**
 * @file
 * @brief Header file containing function declarations and macro definitions.
 *
 * This header provides the necessary function prototypes and macro declarations
 * required for the corresponding implementation file. It serves as an interface
 * for other modules to interact with the provided functionalities and constants.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 * @brief Function to get wrong answers based on the provided parameters.
 * 
 * @param N An integer representing the number of characters.
 * @param C A character array containing the answers.
 * @return A character pointer to the processed wrong answers.
*/
char* getWrongAnswers(int N, char* C);
