#include <Arduino.h>
#include "spi2shiftRegister.h"
const unsigned long N_BEANS = 100000;
const unsigned long N_BYTES = N_BEANS / 32;
const int LEVELS = 10;
unsigned long current_beans = 0;


unsigned long timer;
long thisRandom1;
long thisRandom2;
boolean bo = false;
byte board[] = {0, 0, 0, 0, 0, 0, 0};

//iterate galton variables
unsigned long columns[11]; //here the beans are kept
unsigned long rand1;
unsigned long rand2;
unsigned long rand3;
byte index[2];
byte delta;



unsigned long time2;
unsigned long time1 ;

//fast rand bin variables
unsigned long rand32 ;
byte counter;
void setup() {
  Serial.begin(115200);
  init_IO();
  init_SPI();
  randomSeed(analogRead(0));
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);
  //  board[2]=_BV(0)41
  rand32 = random();
  counter = 0;
  board[0] |= _BV(0);
// 
//  refreshGaltonBoard(board);
// delay(800);
//  for (int p = 0; p < 9; p++) {
//    iterateGalton1();
//    refreshGaltonBoard(board);
//    delay(800);
//  }
  //  while (true) {
  //    board[0] |= _BV(0);
  //    iterateGalton1();
  //    refreshGaltonBoard(board);
  //    current_beans++;
  //    Serial.println(current_beans);
  //    if (current_beans == N_BEANS) {
  //      Serial.print(columns[0]);
  //      Serial.print(" ");
  //      Serial.print(columns[1]);
  //      Serial.print(" ");
  //      Serial.print(columns[2]);
  //      Serial.print(" ");
  //      Serial.print(columns[3]);
  //      Serial.print(" ");
  //      Serial.print(columns[4]);
  //      Serial.print(" ");
  //      Serial.print(columns[5]);
  //      Serial.print(" ");
  //      Serial.print(columns[6]);
  //      Serial.print(" ");
  //      Serial.print(columns[7]);
  //      Serial.print(" ");
  //      Serial.print(columns[8]);
  //      Serial.print(" ");
  //      Serial.print(columns[9]);
  //      Serial.print(" ");
  //      Serial.println(columns[10]);
  //      Serial.print("------ ------ ");
  //      break;
  //    }
  //  }

}

void loop() {
  // put your main code here, to run repeatedly:
    board[0] |= _BV(0);
    iterateGalton1();
    refreshGaltonBoard(board);
//      delay(30);
  //    Serial.println("next iteration");

}
void iterateGalton1(void) {
  //generate random numbers

  index[0] = 6;
  index[1] = 6;

  //calculate the last row
  //keep the balls at the colums
  for (int j = 9; j >= 0; j--) {
    if (isBeanAtIndex(index[0], index[1])) {
      board[index[0]] &= ~_BV(index[1]); //clearAtIndex
      if (fastRandBin()) { //right
        columns[j + 1]++;
      }
      else { //left
        columns[j]++;
      }
    }
    if (index[1] == 0) {
      index[0]--;
      index[1] = 7;
    }
    else {
      index[1]--;
    }
  }


  for (int i = 8; i >= 0; i--) {

    for (int j = i; j >= 0; j--) {
      if (isBeanAtIndex(index[0], index[1])) {
        //there is ball in the space
        //        Serial.print("ballHere");
        board[index[0]] &= ~_BV(index[1]); //clearAtIndex

        if (fastRandBin()) { //right
          delta = (index[1] + i + 2);

          board[(delta >> 3) + index[0]] |= _BV(delta & B111);
        }
        else { //left
          delta = (index[1] + i + 1);

          board[(delta >> 3) + index[0]] |= _BV(delta & B111);
        }
      }
      if (index[1] == 0) {
        index[0]--;
        index[1] = 7;
      }
      else {
        index[1]--;
      }
    }
  }
}
boolean isBeanAtIndex(byte idx0, byte idx1) {
  //  Serial.print("idx0 =");
  //  Serial.print(idx0);
  //  Serial.print(" idx1 =");
  //  Serial.print(idx1);
  //  Serial.print(" ball = ");
  //  Serial.println((1 & (board[idx0] >> idx1)));
  //
  return  (1 & (board[idx0] >> idx1));
}

boolean fastRandBin(void) {

  if (counter > 31) {
    counter = 0;
    rand32 = random();
  }
  counter++;
  return (1 & (rand32 >> (counter - 1)));

}
//boolean fastRandTray(void) {
//  int toReturn;
//  
//  if (counter > 31) {
//    counter = 10;
//    rand32 = random();
//    toReturn=rand32&(_BV(10)-1);
//  }
//  else if (counter>21){
//    bitsLeft=31-counter;
//    toReturn=rand32&(_BV(bitsLeft)-1);
//    toReturn=toReturn<<(bitsLeft);
//    rand32 = random();
//    toReturn
//    
//  }
//  else{
//    
//  }
//  counter++;
//  return (1 & (rand32 >> (counter - 1)));
//
//}
//
//void gatltonTray(){
//  unsigned int tray
//}
