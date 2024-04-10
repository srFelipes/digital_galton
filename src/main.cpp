#include <Arduino.h>
#include "spi2shiftRegister.h"
#include "galton.h"
#include "encoder_routines.h"

void setup() {
  Serial.begin(115200);
  init_IO();
  init_SPI();
  randomSeed(15);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);
  unsigned long init;
  unsigned long end;

  delay(3);
  init_tray_matrix();
  clear_board();
  int result;
  Serial.print("the qty is ");
  Serial.println(QTY_OF_PLACES);
  for (int k=0;k<210;k++){
    
    init=micros();
    galton_onceV2();
    refreshGaltonBoard(serialized_galton_board);
    byte_the_result(0);
    refreshColumns(single_byte_results);
    end=micros();
    Serial.print("iteration = ");
    Serial.print(k);
    Serial.print(" | Time = ");
    Serial.print(end-init);
    Serial.print(" microseconds. | result = ");
    Serial.println(result);

    Serial.println("------------------------");
    for (int i=0;i<BOARD_SIZE+1;i++){
      Serial.print(galton_results[i]);
      Serial.print(" | ");
    }
    Serial.println();
    

  }


}

void loop() {
 

}