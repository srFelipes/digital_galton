#include <Arduino.h>
#include "spi2shiftRegister.h"
#include "galton.h"

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
  for (int k=0;k<5000;k++){
    
    init=micros();
    result=galton_onceV2();
    refreshGaltonBoard(serialized_galton_board);
    end=micros();
    Serial.print("iteration = ");
    Serial.print(k);
    Serial.print(" | Time = ");
    Serial.print(end-init);
    Serial.print(" microseconds. | result = ");
    Serial.println(result);
    delay(1000);
  }


}

void loop() {
 

}