#include <galton.h>


void print_galton_trays(void){
    for (int i=0;i<BOARD_SIZE;i++){
        for (int j=0;j<BOARD_SIZE;j++){
            Serial.print("galton_board_trays[");
            Serial.print(i);
            Serial.print("][");
            Serial.print(j);
            Serial.print("] = ");
            Serial.println(galton_board_trays[i][j]);
        }        
    }
}

