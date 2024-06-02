#include "galton_lib.h"
#include <stdlib.h>

static RandomFunction_t givenRandom = NULL;

unsigned int board_levels;
int board_size;
unsigned int board_number_of_positions;
char* board = NULL;

unsigned int levels;
int size;
unsigned int number_of_positions;
char internal_board[1];

void galton_init(unsigned int number_of_levels, RandomFunction_t rand_func){
    
    givenRandom = rand_func;
    board_number_of_positions = (number_of_levels*(number_of_levels+1))>>1;
    board_size = 1;
    board = (char*)malloc(board_size * sizeof(char));
    board[0] = 0;
    if (number_of_levels > 3){
        board_size += board_number_of_positions>>3;
    }
    board_levels = number_of_levels;
    
}

void galton_deinit(){
    free(board);
}

void galton_once(){
    board[0] = 1;
    char myArray[1] = {0};
    givenRandom(myArray,1);
}