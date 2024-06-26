/********************************
  Driving shift registers using
  an AVR chip's hardwarre SPI
*       *
  http://jumptuck.com
*       *
********************************/


//d10 es el galton
//d9 es el display


#define SHIFT_REGISTER DDRB
#define SHIFT_PORT PORTB
#define DATA (1<<PB3)   //MOSI (SI)
#define LATCH (1<<PB2)    //SS   (RCK)
#define LATCH_COLUMNS (1<<PB1)  //SS display
#define CLOCK (1<<PB5)    //SCK  (SCK)

void init_IO(void) {
  //Setup IO
  SHIFT_REGISTER |= (DATA | LATCH | CLOCK | LATCH_COLUMNS); //Set control pins as outputs
  SHIFT_PORT &= ~(DATA | LATCH | CLOCK);    //Set control pins low
}

void init_SPI(void) {
  //Setup SPI
  SPCR = (1 << SPE) | (1 << MSTR); //Start SPI as Master
}

void spi_send(unsigned char byte) {
  SPDR = byte;      //Shift in some data
  while (!(SPSR & (1 << SPIF))); //Wait for SPI process to finish
}

int limit = 7;

void refreshGaltonBoard(byte board[]) {
  //Pull LATCH low (Important: this is necessary to start the SPI transfer!)
  SHIFT_PORT &= ~LATCH;
  for (int i = 1; i <= limit; i++) {
    spi_send(board[7-i]);
  }

  //Toggle latch to copy data to the storage register
  SHIFT_PORT |= LATCH;
  SHIFT_PORT &= ~LATCH;

}

int limit_display = 11;
void refreshColumns(byte results[]){
  SHIFT_PORT &= ~LATCH_COLUMNS;
  for (int i = 1; i <= limit_display; i++){
    spi_send(results[limit_display-i]);
  }
  //Toggle latch to copy data to the storage register
  SHIFT_PORT |= LATCH_COLUMNS;
  SHIFT_PORT &= ~LATCH_COLUMNS;
}