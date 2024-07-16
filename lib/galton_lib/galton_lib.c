#include "galton_lib.h"
#include <stdlib.h>

#include <stdbool.h>

static RandomFunction_t givenRandom = NULL;

unsigned int board_levels;
int board_size;
unsigned int board_number_of_positions;
char *board = NULL;

unsigned int levels;
int size;
unsigned int number_of_positions;
char internal_board[1];

void galton_init(unsigned int number_of_levels, RandomFunction_t rand_func)
{
    givenRandom = rand_func;
    board_number_of_positions = (number_of_levels * (number_of_levels + 1)) >> 1;
    board_size = number_of_positions >> 3;
    board_levels = number_of_levels;
    board_size = 1;
    if (number_of_levels > 3)
    {
        board_size += board_number_of_positions >> 3;
    }
    board = (char *)malloc(board_size * sizeof(char));
    for (int i = 0; i < board_size; i++)
    {
        board[i] = 0;
    }
}

void galton_deinit()
{
    free(board);
}

void galton_once()
{
    char random_seed[1];
    if (board[0] == 0)
    {
        board[0] = 1;
    }
    else
    {
        board[0] = 0b11;
    }
    // random_seed[0] = 0;
    // givenRandom(random_seed,1);
    // bool ball;
    // int current_byte;
    // int current_bit;
    // int current_level = board_levels;
    // for (int current_level=board_levels-1; current_level>=0; current_level--){
    //     for (int current_pos=current_level+1; current_pos>=0; current_level--){
    //         current_bit =
    //         ball = (board[current_byte]>>current_bit)&1;
    //     }
    // }
    // for (int i = number_of_positions-1; i>=0; i--){
    //     current_byte = (i>>3);
    //     current_bit = i&0xff;
    //     ball = (board[current_byte]>>current_bit)&1;
    //     if (ball){
    //     }
    // }
}