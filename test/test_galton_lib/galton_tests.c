#include <unity.h>
#include "galton_lib.h"
#include "test_utils.h"
#include <string.h>
#include <stdio.h>

void setUp(void){
test_utils_init();
}

void tearDown(void){
  galton_deinit();
}
void testImport(){
  #ifdef GALTON
  TEST_ASSERT_TRUE(1);
  #else
  TEST_ASSERT_TRUE(0);
  #endif
}

galton_algorithm current_algo = BY_POS;

void testInitWith0(){
  galton_init(0, &all_0s, current_algo);
  TEST_ASSERT_EQUAL_UINT(0,board_levels);
  TEST_ASSERT_EQUAL_UINT(1,board_size);
  TEST_ASSERT_EQUAL_UINT(0,board_number_of_positions);
  char expected_board[] = {0};
  TEST_ASSERT_EQUAL_CHAR_ARRAY(expected_board,board,1);
}

void testInitWith1(){
  galton_init(1, &all_0s, current_algo);
  TEST_ASSERT_EQUAL_UINT(1,board_levels);
  TEST_ASSERT_EQUAL_UINT(1,board_size);
  TEST_ASSERT_EQUAL_UINT(1,board_number_of_positions);
  char expected_board[] = {0};
  TEST_ASSERT_EQUAL_CHAR_ARRAY(expected_board,board,1);
}

void testInitWith3(){
  galton_init(3, &all_0s, current_algo);
  TEST_ASSERT_EQUAL_UINT(3,board_levels);
  TEST_ASSERT_EQUAL_UINT(1,board_size);
  TEST_ASSERT_EQUAL_UINT(6,board_number_of_positions);
  char expected_board[] = {0};
  TEST_ASSERT_EQUAL_CHAR_ARRAY(expected_board,board,1);
}

/**
 * @brief test the init function with 6 levels
 * @note I could not create a test that failed when board
 * was accessed out of its bounds, it is the developers
 * responsabillity to check agains board_size to avoid writing
 * outside its size and generating unexpected behaviour  
 */
void testInitWith6(){
  galton_init(6, &all_0s, current_algo);
  TEST_ASSERT_EQUAL_UINT(6,board_levels);
  TEST_ASSERT_EQUAL_UINT(21,board_number_of_positions);
  TEST_ASSERT_EQUAL_UINT(3,board_size);
  char expected_board[] = {0,0,6};
  board[2] = 6;
  TEST_ASSERT_EQUAL_CHAR_ARRAY(expected_board,board,3);
}

void testGalton_onceLoadsAballAtTheTop(){
  galton_init(1, &all_0s, current_algo);
  galton_once();
  TEST_ASSERT_EQUAL_INT16(1,all_0s_calls);
  char expected_board[] = {1};
  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_board,board,1);
}

void testGalton_oncePropagatesBallToTheLeft(){
  galton_init(2, &all_0s, current_algo);
  galton_once();
  TEST_ASSERT_EQUAL_INT16(1,all_0s_calls);
  char expected_board[] = {1};
  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_board,board,1);
  galton_once();
  TEST_ASSERT_EQUAL_INT16(2,all_0s_calls);
  expected_board[0] = 0b011; //one ball at the top one ball at the left
  TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_board,board,1);
}

void testGalton_once10timesleft(){
  int levels = 10;
  galton_init(levels, &all_0s, current_algo);
  char expected_boards[10][7] = {{1,0,0,0,0,0,0},
                                 {3,0,0,0,0,0,0},
                                 {0xb,0,0,0,0,0,0},
                                 {0x4b,0,0,0,0,0,0},
                                 {0x4b,0x4,0,0,0,0,0},
                                 {0x4b,0x84,0,0,0,0,0},
                                 {0x4b,0x84,0x20,0,0,0,0},
                                 {0x4b,0x84,0x20,0x10,0,0,0},
                                 {0x4b,0x84,0x20,0x10,0x10,0,0},
                                 {0x4b,0x84,0x20,0x10,0x10,0x20,0}};
  char expected_board[7];
  char format[] = "failed at %i";
  char buffer[100] = {0};
  for (int i=0; i<levels; i++){
    galton_once();
    memcpy(expected_board,expected_boards[i],7);
    TEST_ASSERT_EQUAL_INT16(1+i,all_0s_calls);
    sprintf(buffer,format,i);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expected_board,board,7,buffer);
  }
}

void testGalton_once10timesright(){
  int levels = 10;
  galton_init(levels, &all_1s, current_algo);
  char expected_boards[10][7] = {{1,0,0,0,0,0,0},
                                 {5,0,0,0,0,0,0},
                                 {0x25,0,0,0,0,0,0},
                                 {0x25,0x2,0,0,0,0,0},
                                 {0x25,0x42,0,0,0,0,0},
                                 {0x25,0x42,0x10,0,0,0,0},
                                 {0x25,0x42,0x10,0x8,0,0,0},
                                 {0x25,0x42,0x10,0x8,0x8,0,0},
                                 {0x25,0x42,0x10,0x8,0x8,0x10,0},
                                 {0x25,0x42,0x10,0x8,0x8,0x10,0x40}};
  char expected_board[7];
  char format[] = "failed at %i";
  char buffer[100] = {0};
  for (int i=0; i<levels; i++){
    galton_once();
    memcpy(expected_board,expected_boards[i],7);
    TEST_ASSERT_EQUAL_INT16(1+i,all_1s_calls);
    sprintf(buffer,format,i);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expected_board,board,7,buffer);
  }
}

void testGalton_once10times_left_right(){
  int levels = 10;
  galton_init(levels, &all_10101010, current_algo);
  char expected_boards[10][7] = { {0x1,  0x0,  0x0, 0x0, 0x0, 0x0, 0x0,},
                                  {0x5,  0x0,  0x0, 0x0, 0x0, 0x0, 0x0,},
                                  {0x15, 0x0,  0x0, 0x0, 0x0, 0x0, 0x0,},
                                  {0x15, 0x1,  0x0, 0x0, 0x0, 0x0, 0x0,},
                                  {0x15, 0x11, 0x0, 0x0, 0x0, 0x0, 0x0,},
                                  {0x15, 0x11, 0x4, 0x0, 0x0, 0x0, 0x0,},
                                  {0x15, 0x11, 0x4, 0x1, 0x0, 0x0, 0x0,},
                                  {0x15, 0x11, 0x4, 0x1, 0x1, 0x0, 0x0,},
                                  {0x15, 0x11, 0x4, 0x1, 0x1, 0x1, 0x0,},
                                  {0x15, 0x11, 0x4, 0x1, 0x1, 0x1, 0x4,},};
  char expected_board[7];
  char format[] = "failed at %i";
  char buffer[100] = {0};
  for (int i=0; i<levels; i++){
    galton_once();
    memcpy(expected_board,expected_boards[i],7);
    TEST_ASSERT_EQUAL_INT16(1+i,all_1s_calls);
    sprintf(buffer,format,i);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expected_board,board,7,buffer);
  }
}

void testGalton_once10times_right_left(){
  int levels = 10;
  galton_init(levels, &all_55, current_algo);
  char expected_boards[10][7] = {{0x1,  0x0,  0x0, 0x0,  0x0, 0x0, 0x0,},
                                 {0x3,  0x0,  0x0, 0x0,  0x0, 0x0, 0x0,},
                                 {0x13, 0x0,  0x0, 0x0,  0x0, 0x0, 0x0,},
                                 {0x93, 0x0,  0x0, 0x0,  0x0, 0x0, 0x0,},
                                 {0x93, 0x10, 0x0, 0x0,  0x0, 0x0, 0x0,},
                                 {0x93, 0x10, 0x2, 0x0,  0x0, 0x0, 0x0,},
                                 {0x93, 0x10, 0x2, 0x1,  0x0, 0x0, 0x0,},
                                 {0x93, 0x10, 0x2, 0x81, 0x0, 0x0, 0x0,},
                                 {0x93, 0x10, 0x2, 0x81, 0x0, 0x1, 0x0,},
                                 {0x93, 0x10, 0x2, 0x81, 0x0, 0x1, 0x2,}};
  char expected_board[7];
  char format[] = "failed at %i";
  char buffer[100] = {0};
  for (int i=0; i<levels; i++){
    galton_once();
    memcpy(expected_board,expected_boards[i],7);
    TEST_ASSERT_EQUAL_INT16(1+i,all_1s_calls);
    sprintf(buffer,format,i);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expected_board,board,7,buffer);
  }
}

void testGalton_1ballAtLeftContainer(){
  int levels = 1;
  galton_init(levels, &all_0s, current_algo);
  for (int i=0; i<levels+1; i++){
    galton_once();
    TEST_ASSERT_EQUAL_INT16(1+i,all_0s_calls);
  }
  TEST_ASSERT_EQUAL_INT(1,containers[0]);
}

void testGalton_2ballAtLeftContainer(){
  int levels = 1;
  galton_init(levels, &all_0s, current_algo);
  for (int i=0; i<levels+2; i++){
    galton_once();
    TEST_ASSERT_EQUAL_INT16(1+i,all_0s_calls);
  }
  TEST_ASSERT_EQUAL_INT(2,containers[0]);
}

void testGalton_1ballAtRightContainer(){
  int levels = 1;
  galton_init(levels, &all_1s, current_algo);
  for (int i=0; i<levels+1; i++){
    galton_once();
    TEST_ASSERT_EQUAL_INT16(1+i,all_1s_calls);
  }
  TEST_ASSERT_EQUAL_INT(1,containers[1]);
}

void testGalton_2ballAtRightContainer(){
  int levels = 1;
  galton_init(levels, &all_1s, current_algo);
  for (int i=0; i<levels+2; i++){
    galton_once();
    TEST_ASSERT_EQUAL_INT16(1+i,all_1s_calls);
  }
  TEST_ASSERT_EQUAL_INT(2,containers[1]);
}

void testGalton_5ballAtLeftContainer_3_levels(){
  int levels = 3;
  galton_init(levels, &all_0s, current_algo);
  for (int i=0; i<levels+5; i++){
    galton_once();
    TEST_ASSERT_EQUAL_INT16(1+i,all_0s_calls);
  }
  TEST_ASSERT_EQUAL_INT(5,containers[0]);
}

void testGalton_5ballAtRightContainer_3_levels(){
  int levels = 3;
  galton_init(levels, &all_1s, current_algo);
  for (int i=0; i<levels+5; i++){
    galton_once();
    TEST_ASSERT_EQUAL_INT16(1+i,all_1s_calls);
  }
  TEST_ASSERT_EQUAL_INT(5,containers[levels]);
}

void run_the_tests(){
  RUN_TEST(testImport);
  RUN_TEST(testInitWith0);
  RUN_TEST(testInitWith1);
  RUN_TEST(testInitWith3);
  RUN_TEST(testInitWith6);
  RUN_TEST(testGalton_onceLoadsAballAtTheTop);
  RUN_TEST(testGalton_oncePropagatesBallToTheLeft);
  RUN_TEST(testGalton_once10timesleft);
  RUN_TEST(testGalton_once10timesright);
  RUN_TEST(testGalton_once10times_left_right);
  RUN_TEST(testGalton_once10times_right_left);
  RUN_TEST(testGalton_1ballAtLeftContainer);
  RUN_TEST(testGalton_2ballAtLeftContainer);
  RUN_TEST(testGalton_1ballAtRightContainer);
  RUN_TEST(testGalton_2ballAtRightContainer);
  RUN_TEST(testGalton_5ballAtLeftContainer_3_levels);
  RUN_TEST(testGalton_5ballAtRightContainer_3_levels);
}

int main( int argc, char **argv){

  UNITY_BEGIN();
  run_the_tests();
  UNITY_END();
  }