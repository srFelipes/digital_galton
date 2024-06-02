/**
 * @file galton_lib.h
 * @author Felipe Guajardo (fgerman.mena@gmail.com)
 * @brief Functions and global variables to perform galton board simulations
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef GALTON
#define GALTON

void galton_init(unsigned int number_of_levels, void *rand_func);

/**
 * @brief pointer to a "global" variable, this is the amount
 * of steps the balls go before falling in a container
 * 
 */
extern unsigned int board_levels;

/**
 * @brief The number of positions inside the board, 
 * a ball can be in any of this positions
 * 
 */
extern unsigned int board_number_of_positions;

/**
 * @brief pointer to the board, a char array of board_size bits
 * where each bit is set if there is a peblle in its position 
 * @details the galton board is represented as follows, the numbers in
 * the levels are its corresponding bit in table
 *                   0
 *                  / \
 *                 1   2
 *                / \ / \
 *               3   4   5
 *              / \ / \ / \
 *              6  7   8   9
 * 
 */
extern char* board;

/**
 * @brief the number of bytes of the board 
 * @note always check against this value before writing to board since
 * C allows to write outside the bounds
 * 
 */
extern int board_size;

/**
 * @brief where the balls are collected, its size is board_levels+1
 * 
 */
extern unsigned long containers[];

/**
 * @brief copies board_size bits into output_array containing random bits
 * 
 * @param output_array[] char array where the new bits will be stored 
 * @param n_of_bits the amounts of random bits to be generated
 */
void efi_rand(char output_array[], unsigned int n_of_bits);

/**
 * @brief board is now all 0 and 1 in its first element
 * 
 */
void clear_board();



void galton_once();

#endif