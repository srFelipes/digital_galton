#include "galton_lib.h"
#include <stdlib.h>

#include <stdbool.h>

#include <stdio.h>


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

bool isBallAtByteAndIndex(int index, int current_byte){
    return ((board[current_byte]>>(index&7))&1);
}

void galton_once()
{
    char random_seed[1];
    random_seed[0] = 0;
    givenRandom(random_seed,1);
    for (int current_level = board_levels-1; current_level > 0; current_level--)
    {
        int min_pos = ((current_level-1)*current_level) >> 1;
        for (int pos_in_the_level = 0; pos_in_the_level < current_level ; pos_in_the_level++ )
        {   
            int pos = min_pos+pos_in_the_level;
            int index = pos & 7; //the LSB of pos
            int current_byte = pos >> 3; // pos divided by 8
            if (isBallAtByteAndIndex(index,current_byte)){
                int new_pos = pos + current_level;
                index = new_pos & 7; //the LSB of pos
                current_byte = new_pos >> 3; // pos divided by 8
                board[current_byte] |= 1<<index;
            }
        }
    }
    board[0] |= 1;
}