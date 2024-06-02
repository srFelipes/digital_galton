#include <unity.h>
#include "galton_lib.h"
#include "test_utils.h"

void setUp(void){

}

void tearDown(void){

}
void testImport(){
  #ifdef GALTON
  TEST_ASSERT_TRUE(1);
  #else
  TEST_ASSERT_TRUE(0);
  #endif
}

void testInitWith0(){
  galton_init(0,&all_0s);
  TEST_ASSERT_EQUAL_UINT(0,board_levels);
  TEST_ASSERT_EQUAL_UINT(1,board_size);
  TEST_ASSERT_EQUAL_UINT(0,board_number_of_positions);
  char expected_board[] = {0};
  TEST_ASSERT_EQUAL_CHAR_ARRAY(expected_board,board,1);
}

void testInitWith1(){
  galton_init(1,&all_0s);
  TEST_ASSERT_EQUAL_UINT(1,board_levels);
  TEST_ASSERT_EQUAL_UINT(1,board_size);
  TEST_ASSERT_EQUAL_UINT(1,board_number_of_positions);
  char expected_board[] = {0};
  TEST_ASSERT_EQUAL_CHAR_ARRAY(expected_board,board,1);
}

void testInitWith3(){
  galton_init(3,&all_0s);
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
  galton_init(6,&all_0s);
  TEST_ASSERT_EQUAL_UINT(6,board_levels);
  TEST_ASSERT_EQUAL_UINT(21,board_number_of_positions);
  TEST_ASSERT_EQUAL_UINT(3,board_size);
  char expected_board[] = {0,0,6};
  board[2] = 6;
  TEST_ASSERT_EQUAL_CHAR_ARRAY(expected_board,board,3);
}

int main( int argc, char **argv){

    UNITY_BEGIN();
    RUN_TEST(testImport);
    RUN_TEST(testInitWith0);
    RUN_TEST(testInitWith1);
    RUN_TEST(testInitWith3);
    RUN_TEST(testInitWith6);
    UNITY_END();
  }