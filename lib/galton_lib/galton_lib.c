#include "galton_lib.h"
#include <stdlib.h>

#include <stdbool.h>

#include <stdio.h>


static RandomFunction_t givenRandom = NULL;

unsigned int board_levels;
int board_size;
unsigned int board_number_of_positions;
char *board = NULL;
unsigned long *containers = NULL;

unsigned int levels;
int size;
unsigned int number_of_positions;
char internal_board[1];

void (*galton_once)();

unsigned char *board_as_positions;

#define NO_BALL 0xff

void galton_init(unsigned int number_of_levels, RandomFunction_t rand_func, galton_algorithm algorithm)
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
    board = (char *)calloc(board_size, sizeof(char));
    containers = (long *)calloc((board_levels+1), sizeof(long));
    board_as_positions = (unsigned char *)calloc((board_levels+1), sizeof(char));
    for (int i = 0; i < board_levels+1; i++)
    {
        board_as_positions[i] = NO_BALL;
    }
    if (algorithm == BY_POS){
        galton_once = galton_by_pos;
    }
    else if (algorithm == BY_TRAJ){
        galton_once = galton_by_traj;

    }
}

void galton_deinit()
{
    free(board);
}

bool bitAt(int pos, char* buffer){
    int current_byte = pos>>3;
    int index = pos&7;
    return ((buffer[current_byte]>>(index))&1);
}

int min_pos_f(int current_level){
    return ((current_level-1)*current_level) >> 1;
}

void galton_by_pos()
{   
    char random_run[3]; /*array to keep random bits |0: left | 1: right|*/
    givenRandom(random_run,10);
    int last_level_min_pos =  min_pos_f(board_levels);
    
    for (int current_pos = last_level_min_pos;
         current_pos < last_level_min_pos + board_levels; 
         current_pos++ ){
        if (bitAt(current_pos,board)){
            containers[current_pos - last_level_min_pos + bitAt(board_levels,random_run)] += 1;
        }
    }

    for (int current_level = board_levels-1; current_level > 0; current_level--)
    {
        int min_pos = min_pos_f(current_level);
        for (int pos_in_the_level = 0; pos_in_the_level < current_level ; pos_in_the_level++ )
        {   
            int pos = min_pos+pos_in_the_level;
            if (bitAt(pos,board)){ //ball at pos
                int new_pos;
                if (bitAt(current_level, random_run)){ //
                    new_pos = pos + current_level + 1;
                }
                else{
                    new_pos = pos + current_level;
                }
                int index = new_pos & 7; //the LSB of pos
                int current_byte = new_pos >> 3; // pos divided by 8
                board[current_byte] |= 1<<index;
            }
        }
    }
    board[0] |= 1;
}

void set_to_board(int current_level, int current_pos){
    int min_pos = min_pos_f(current_level+1);
    int new_pos =  min_pos + current_pos;
    int index = new_pos & 7; //the LSB of pos
    int current_byte = new_pos >> 3; // pos divided by 8
    board[current_byte] |= 1<<index;
}


void galton_by_traj(){
    char random_run[3]; /*array to keep random bits |0: left | 1: right|*/
    givenRandom(random_run,10);

    if (board_as_positions[board_levels-1] != NO_BALL){
        containers[board_as_positions[board_levels-1]
                   +bitAt(board_levels -1, random_run)] += 1;
    }

    for (int current_level = board_levels-2; current_level > -1; current_level--){
        if (board_as_positions[current_level] != NO_BALL){
            board_as_positions[current_level+1] = board_as_positions[current_level] + bitAt(current_level+1, random_run);
            set_to_board(current_level+1,board_as_positions[current_level+1]);
        }
    }
    
    board_as_positions[0] = 0;
    board[0] |= 1;
}