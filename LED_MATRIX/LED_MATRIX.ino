#define NUMROWS 8
#define NUMCOLS 8
/*  ASM diliyle BLINK
      Bu program ATMEGA'nın PIN, DDR ve PORT yazmaçlarını kullanarak
      PIN ayarları yapmayı gösteriyor.
      Kod IOreg adresi tekniğini kullanıyor.

      // Added by RK for Atmega2560 chip (see datashhet page 96)
      PINA  IOreg = 0x00     offset = 0x20
      DDRA  IOreg = 0x01     offset = 0x21  
      PORTA IOreg = 0x02     offset = 0x22

      PINL  IOreg = 0x00     offset = 0x20
      DDRL  IOreg = 0x01     offset = 0x21  
      PORTL IOreg = 0x02     offset = 0x22
      // rk

      PINB  IOreg = 0x03     offset = 0x23
      DDRB  IOreg = 0x04     offset = 0x24  
      PORTB IOreg = 0x05     offset = 0x25
      PINC  IOreg = 0x06     offset = 0x26
      DDRC  IOreg = 0x07     offset = 0x27
      PORTC IOreg = 0x08     offset = 0x28
      PIND  IOreg = 0x09     offset = 0x29
      DDRD  IOreg = 0x0A     offset = 0x2A
      PORTD IOreg = 0x0B     offset = 0x2B
 
      SAYMAÇLAR:  X: r27:r26          Y: r29:r28          ve Z: r31:r30
 */

volatile byte rowdata_mem;
volatile byte coldata_mem;
volatile byte ledata_mem;

// ROW  at port A
// COL  at port B
// LE   at port C

void writeToROWCOL(volatile byte rowdata, volatile byte coldata, volatile byte ledata){
  rowdata_mem=rowdata;
  coldata_mem=coldata;
  ledata_mem=ledata;

  asm (
    "lds r26, (rowdata_mem) \n" //store r26 into memory location of variable a
    "lds r27, (coldata_mem) \n" //store r26 into memory location of variable a
    "lds r28, (ledata_mem) \n" //store r26 into memory location of variable a
    //"sts (count2), r26 \n" //store r26 into memory location of variable a
    "out 0X02, r26 \n"          // PORTD saymacını güncelle (IOreg = 0x0B)
    "out 0x05, r27 \n"          // PORTD saymacını güncelle (IOreg = 0x0B)
    "out 0x08, r28 \n"          // PORTD saymacını güncelle (IOreg = 0x0B)
  );
  
}

void setup() {
  // configure portA, portB, portC as OUTPUT using DDRA DDRB, DDRC adresses above
  asm (
    "ldi r26, 0xff \n" //store r26 into memory location of variable a
    "out 0X01, r26 \n"          // DDRA 
    "out 0x04, r26 \n"          // DDRB 
    "out 0x07, r26 \n"          // DDRC 
  );
    
Serial.begin(57600);
}
void clearMatrix() {
  for(int i = 0; i < NUMROWS; i++) {
    for(int j = 0; j < NUMCOLS; j++) {
      writeToROWCOL(i, j, 0);  // turn off LED at position (i, j)
    }
  }
}

void writeNumberToMatrix(int number) {
    int digits[4];
    
    // We split the number into individual digits
    for(int i = 3; i >= 0; i--) {
        digits[i] = number % 10;
        number /= 10;
    }
    // Now we write each digit to the corresponding LED Matrix
    for(int i=0; i<4; i++) {
    switch(i) {
      case 0:
        // 1. basamak için kodlar
        switch(digits[i]) {
           case 0:
              writeToROWCOL(0b11111110,0b01111110,0b00010001); // row 1
              delay(10);
              writeToROWCOL(0b10000001,0b01000010,0b00010001); // row 2 3 4 5 6 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111110,0b00010001); // row 8
              delay(10);
               
              break;
              
            case 1:
              writeToROWCOL(0b11111100,0b00011100,0b00010001);
              delay(10);  // 5 ms bekleyin
              writeToROWCOL(0b00000011,0b00011000,0b00010001);
              delay(10);
                 // 5 ms daha bekleyin
              break;
            case 2:
              writeToROWCOL(0b11111100,0b01111100,0b00010001); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11110011,0b01100000,0b00010001); // row 3 and 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b00010001); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b00001100,0b00010001); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b00010001); // row 8
              delay(10);
               
              break;
            case 3:
              writeToROWCOL(0b11111100,0b01111100,0b00010001); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11110011,0b01100000,0b00010001); // row 3 and 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b00010001); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01100000,0b00010001); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b00010001); // row 8 
              delay(10);
               
              break;
            case 4:
              writeToROWCOL(0b11110000,0b00110110,0b00010001); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11101111,0b00111110,0b00010001); // row 5
              delay(10);
              writeToROWCOL(0b00011111,0b00110000,0b00010001); // row 6 7 8
              delay(10);
                 
              break;
            // do the same for all digits till 9
            case 5:
              writeToROWCOL(0b11111100,0b01111100,0b00010001); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11110011,0b00001100,0b00010001); // row 3 and 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b00010001); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01100000,0b00010001); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b00010001); // row 8
              delay(10);
               
              break;
            case 6: 
              writeToROWCOL(0b11111100,0b01111100,0b00010001); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11110011,0b00000100,0b00010001); // row 3 and 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b00010001); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01100100,0b00010001); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b00010001); // row 8
              delay(10);
               
              break;
            case 7:
              writeToROWCOL(0b11111100,0b00011111,0b00010001);
              delay(10);  // 5 ms bekleyin
              writeToROWCOL(0b00000011,0b00011000,0b00010001);
              delay(10);
                 // 5 ms daha bekleyin
              break;
            case 8:
              writeToROWCOL(0b11111110,0b01111100,0b00010001); // row 1
              delay(10);
              writeToROWCOL(0b11110001,0b01000100,0b00010001); // row 2 3 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b00010001); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01000100,0b00010001); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b00010001); // row 8
              delay(10);
               
              break;
            case 9:
              writeToROWCOL(0b11111110,0b01111100,0b00010001); // row 1
              delay(10);
              writeToROWCOL(0b11110001,0b01000100,0b00010001); // row 2 3 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b00010001); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01000000,0b00010001); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b00010001); // row 8
              delay(10);
               
              break;
            default:
                break;
        }
        delay(1000);
        clearMatrix();
        break;
      case 1:
        // 2. basamak için kodlar
        switch(digits[i]) {
          case 0:
              writeToROWCOL(0b11111110,0b01111110,0b00100010); // row 1
              delay(10);
              writeToROWCOL(0b10000001,0b01000010,0b00100010); // row 2 3 4 5 6 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111110,0b00100010); // row 8
              delay(10);
               
              break;
            case 1:
              writeToROWCOL(0b11111100,0b00011100,0b00100010);
              delay(10);  // 5 ms bekleyin
              writeToROWCOL(0b00000011,0b00011000,0b00100010);
              delay(10);
                 // 5 ms daha bekleyin
              break;
            case 2:
              writeToROWCOL(0b11111100,0b01111100,0b00100010); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11110011,0b01100000,0b00100010); // row 3 and 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b00100010); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b00001100,0b00100010); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b00100010); // row 8
              delay(10);
               
              break;
            case 3:
              writeToROWCOL(0b11111100,0b01111100,0b00100010); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11110011,0b01100000,0b00100010); // row 3 and 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b00100010); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01100000,0b00100010); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b00100010); // row 8 
              delay(10);
               
              break;
            case 4:
              writeToROWCOL(0b11110000,0b00110110,0b00100010); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11101111,0b00111110,0b00100010); // row 5
              delay(10);
              writeToROWCOL(0b00011111,0b00110000,0b00100010); // row 6 7 8
              delay(10);
                 
              break;
            // do the same for all digits till 9
            case 5:
              writeToROWCOL(0b11111100,0b01111100,0b00100010); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11110011,0b00001100,0b00100010); // row 3 and 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b00100010); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01100000,0b00100010); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b00100010); // row 8
              delay(10);
               
              break;
            case 6: 
              writeToROWCOL(0b11111100,0b01111100,0b00100010); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11110011,0b00000100,0b00100010); // row 3 and 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b00100010); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01100100,0b00100010); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b00100010); // row 8
              delay(10);
               
              break;
            case 7:
              writeToROWCOL(0b11111100,0b00011111,0b00100010);
              delay(10);  // 5 ms bekleyin
              writeToROWCOL(0b00000011,0b00011000,0b00100010);
              delay(10);
                 // 5 ms daha bekleyin
              break;
            case 8:
              writeToROWCOL(0b11111110,0b01111100,0b00100010); // row 1
              delay(10);
              writeToROWCOL(0b11110001,0b01000100,0b00100010); // row 2 3 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b00100010); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01000100,0b00100010); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b00100010); // row 8
              delay(10);
               
              break;
            case 9:
              writeToROWCOL(0b11111110,0b01111100,0b00100010); // row 1
              delay(10);
              writeToROWCOL(0b11110001,0b01000100,0b00100010); // row 2 3 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b00100010); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01000000,0b00100010); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b00100010); // row 8
              delay(10);
               
              break;
            default:
                break;
        }
        delay(1000);
        clearMatrix();
        break;
      case 2:
        // 3. basamak için kodlar
        switch(digits[i]) {
          case 0:
              writeToROWCOL(0b11111110,0b01111110,0b01000100); // row 1
              delay(10);
              writeToROWCOL(0b10000001,0b01000010,0b01000100); // row 2 3 4 5 6 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111110,0b01000100); // row 8
              delay(10);
               
              break;
            case 1:
              writeToROWCOL(0b11111100,0b00011100,0b01000100);
              delay(10);  // 5 ms bekleyin
              writeToROWCOL(0b00000011,0b00011000,0b01000100);
              delay(10);
                 // 5 ms daha bekleyin
              break;
            case 2:
              writeToROWCOL(0b11111100,0b01111100,0b01000100); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11110011,0b01100000,0b01000100); // row 3 and 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b01000100); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b00001100,0b01000100); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b01000100); // row 8
              delay(10);
               
              break;
            case 3:
              writeToROWCOL(0b11111100,0b01111100,0b01000100); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11110011,0b01100000,0b01000100); // row 3 and 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b01000100); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01100000,0b01000100); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b01000100); // row 8 
              delay(10);
               
              break;
            case 4:
              writeToROWCOL(0b11110000,0b00110110,0b01000100); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11101111,0b00111110,0b01000100); // row 5
              delay(10);
              writeToROWCOL(0b00011111,0b00110000,0b01000100); // row 6 7 8
              delay(10);
                 
              break;
            // do the same for all digits till 9
            case 5:
              writeToROWCOL(0b11111100,0b01111100,0b01000100); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11110011,0b00001100,0b01000100); // row 3 and 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b01000100); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01100000,0b01000100); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b01000100); // row 8
              delay(10);
               
              break;
            case 6: 
              writeToROWCOL(0b11111100,0b01111100,0b01000100); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11110011,0b00000100,0b01000100); // row 3 and 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b01000100); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01100100,0b01000100); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b01000100); // row 8
              delay(10);
               
              break;
            case 7:
              writeToROWCOL(0b11111100,0b00011111,0b01000100);
              delay(10);  // 5 ms bekleyin
              writeToROWCOL(0b00000011,0b00011000,0b01000100);
              delay(10);
                 // 5 ms daha bekleyin
              break;
            case 8:
              writeToROWCOL(0b11111110,0b01111100,0b01000100); // row 1
              delay(10);
              writeToROWCOL(0b11110001,0b01000100,0b01000100); // row 2 3 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b01000100); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01000100,0b01000100); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b01000100); // row 8
              delay(10);
               
              break;
            case 9:
              writeToROWCOL(0b11111110,0b01111100,0b01000100); // row 1
              delay(10);
              writeToROWCOL(0b11110001,0b01000100,0b01000100); // row 2 3 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b01000100); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01000000,0b01000100); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b01000100); // row 8
              delay(10);
               
              break;
            default:
                break;
        }
        delay(1000);
        clearMatrix();
        break;
      case 3:
        // 4. basamak için kodlar
        switch(digits[i]) {
          case 0:
              writeToROWCOL(0b11111110,0b01111110,0b10001000); // row 1
              delay(10);
              writeToROWCOL(0b10000001,0b01000010,0b10001000); // row 2 3 4 5 6 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111110,0b10001000); // row 8
              delay(10);
               
              break;
            case 1:
              writeToROWCOL(0b11111100,0b00011100,0b10001000);
              delay(10);  // 5 ms bekleyin
              writeToROWCOL(0b00000011,0b00011000,0b10001000);
              delay(10);
                 // 5 ms daha bekleyin
              break;
            case 2:
              writeToROWCOL(0b11111100,0b01111100,0b10001000); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11110011,0b01100000,0b10001000); // row 3 and 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b10001000); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b00001100,0b10001000); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b10001000); // row 8
              delay(10);
               
              break;
            case 3:
              writeToROWCOL(0b11111100,0b01111100,0b10001000); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11110011,0b01100000,0b10001000); // row 3 and 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b10001000); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01100000,0b10001000); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b10001000); // row 8 
              delay(10);
               
              break;
            case 4:
              writeToROWCOL(0b11110000,0b00110110,0b10001000); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11101111,0b00111110,0b10001000); // row 5
              delay(10);
              writeToROWCOL(0b00011111,0b00110000,0b10001000); // row 6 7 8
              delay(10);
                 
              break;
            // do the same for all digits till 9
            case 5:
              writeToROWCOL(0b11111100,0b01111100,0b10001000); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11110011,0b00001100,0b10001000); // row 3 and 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b10001000); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01100000,0b10001000); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b10001000); // row 8
              delay(10);
               
              break;
            case 6: 
              writeToROWCOL(0b11111100,0b01111100,0b10001000); // row 1 and 2
              delay(10);
              writeToROWCOL(0b11110011,0b00000100,0b10001000); // row 3 and 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b10001000); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01100100,0b10001000); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b10001000); // row 8
              delay(10);
               
              break;
            case 7:
              writeToROWCOL(0b11111100,0b00011111,0b10001000);
              delay(10);  // 5 ms bekleyin
              writeToROWCOL(0b00000011,0b00011000,0b10001000);
              delay(10);
                 // 5 ms daha bekleyin
              break;
            case 8:
              writeToROWCOL(0b11111110,0b01111100,0b10001000); // row 1
              delay(10);
              writeToROWCOL(0b11110001,0b10001000,0b10001000); // row 2 3 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b10001000); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b10001000,0b10001000); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b10001000); // row 8
              delay(10);
               
              break;
            case 9:
              writeToROWCOL(0b11111110,0b01111100,0b10001000); // row 1
              delay(10);
              writeToROWCOL(0b11110001,0b10001000,0b10001000); // row 2 3 4
              delay(10);
              writeToROWCOL(0b11101111,0b01111100,0b10001000); // row 5
              delay(10);
              writeToROWCOL(0b10011111,0b01000000,0b10001000); // row 6 and 7
              delay(10);
              writeToROWCOL(0b01111111,0b01111100,0b10001000); // row 8
              delay(10);
               
              break;
            default:
                break;
        }
        delay(1000);
        clearMatrix();
        break;
    }
  }
}

void loop() {
    if(Serial.available() > 0) {
        String numberString = Serial.readString();
        int number = numberString.toInt();
        
        writeNumberToMatrix(number);
        
        delay(1000); // wait for 1 seconds
           // clear the matrix after displaying the number
    }
}
