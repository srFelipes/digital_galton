#include <unity.h>
#include "galton_lib.h"

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
int main( int argc, char **argv){

    UNITY_BEGIN();
    RUN_TEST(testImport);
    UNITY_END();
  }