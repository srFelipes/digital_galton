#include <Arduino.h>
const int BOARD_SIZE=10;
const int QTY_OF_PLACES=BOARD_SIZE*(BOARD_SIZE+1)/2;
const unsigned long BOARD_SHIFT_MASK=_BV(BOARD_SIZE)-1;
const int SERIAL_BYTES=7;    // the formula por calulating this should be the floor of  (BOARD_SIZE+1)*BOARD_SIZE/2/8



unsigned long resto =0;
unsigned long random_container =0;

int resto_size=0;
int random_size=0;
unsigned int to_return;

unsigned int galton_results[BOARD_SIZE+1];


unsigned int efi_rand(void){
    //this function returns an unsigned int with BOARD_SIZE random bits
    //this is the trayectory that a grain follows    
    if (resto_size>=BOARD_SIZE){
        //there are enough leftover bits to use
        to_return=resto&BOARD_SHIFT_MASK;
        resto_size-=BOARD_SIZE;
        resto=resto>>BOARD_SIZE;
    }
    else if (random_size>=BOARD_SIZE){
        //there are bits left in the random container
        to_return=random_container&BOARD_SHIFT_MASK;
        random_size-=BOARD_SIZE;
        random_container=random_container>>BOARD_SIZE;
    }
    else{
        //save the leftover
        resto=(resto<<random_size)|random_container;
        resto_size+=random_size;
        random_container=random();
        random_size=31;




        if (resto_size>=BOARD_SIZE){
            //there are enough leftover bits to use
            to_return=resto&BOARD_SHIFT_MASK;
            resto_size-=BOARD_SIZE;
            resto=resto>>BOARD_SIZE;
        }
        else{
            //the newly created random must be used
            to_return=random_container&BOARD_SHIFT_MASK;
            random_size-=BOARD_SIZE;
            random_container=random_container>>BOARD_SIZE;

        }
    }
    
    return to_return;
}

void prob_to_tray(int prob, int *tray){
    //this function returns an array with the positions of of the trayectory in the galton board

    tray[0]=0;
    for (int i=1;i<BOARD_SIZE+1;i++){
        tray[i]=tray[i-1]+i+((prob>>(i-1))&1);
    }
}

int galton_board_trays[BOARD_SIZE][BOARD_SIZE+1];
byte serialized_galton_board[SERIAL_BYTES];


void init_tray_matrix(void){    
    //set all the values to 0
    for (int i=0;i<BOARD_SIZE;i++){
        for (int j=0;j<BOARD_SIZE;j++){
            galton_board_trays[i][j]=0;
        }        
    }
}



void clear_board(void){
    for (int i=0;i<SERIAL_BYTES;i++){
        serialized_galton_board[i]&=0;
    }
}

void copy_tray(int new_tray[],int column){
    for (int i=0;i<BOARD_SIZE+1;i++){
        galton_board_trays[column][i]=new_tray[i];
    }
}

int column=0;
int new_prob;
int new_tray[BOARD_SIZE+1];
int counter=0;
int byte_number;
int bit_number;
boolean first_values_fuse=false;


void galton_onceV2(void){
    clear_board();

    column=counter;

    //add a new trayectory array to galton_board_trays
    new_prob=efi_rand();
    prob_to_tray(new_prob,new_tray);
    copy_tray(new_tray,counter);

    for (int row=0;row<BOARD_SIZE;row++){
        
        //set the new value 
        byte_number=galton_board_trays[column][row]>>3;
        bit_number=B111&(galton_board_trays[column][row]);
        serialized_galton_board[byte_number]|=_BV(bit_number);
        
        if (column==0){
            column=BOARD_SIZE-1;
        }
        else{
            column--;
        }
    }
    counter++;
    if (counter==BOARD_SIZE){
            counter=0;
            if (!first_values_fuse){
                first_values_fuse=true;
            }
    }
    if (first_values_fuse){
        to_return=(galton_board_trays[counter][BOARD_SIZE]-QTY_OF_PLACES);
        galton_results[to_return]++;
    }
    
    
}
void print_galton_trays(void){
    for (int i=0;i<BOARD_SIZE;i++){
        for (int j=0;j<BOARD_SIZE+1;j++){
            Serial.print("galton_board_trays[");
            Serial.print(i);
            Serial.print("][");
            Serial.print(j);
            Serial.print("] = ");
            Serial.println(galton_board_trays[i][j]);
        }        
    }
}

