// define output ports A4 and A5
#define IIC_SCL  A5
#define IIC_SDA  A4

#include "Tetris.h"
#include "Tetromino.h"

/* 
A4 - SDA
A5 - SCL
VCC - 5V
GND - GND 
*/

unsigned int last_time = 0;

void IIC_start();
void IIC_send(unsigned char send_data);
void IIC_end();

char figs[7] = {'b', 'd', 't', 'j', 'l', 'z', 's'};

// 8x16 matrix LED information
unsigned char matrix[16] = {0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00};

Tetris* tetris = new Tetris;
char initial = 'a';
Tetromino* tetromino = new Tetromino(initial);

void setup() {
  pinMode(IIC_SCL,OUTPUT);
  pinMode(IIC_SDA,OUTPUT);
  digitalWrite(IIC_SCL,LOW);
  digitalWrite(IIC_SDA,LOW);

  // pins for game button input
  // rotate ccw, rotate cw, move l, move r, drop
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  // pinMode(11, INPUT_PULLUP);
}

void loop() {
    // get user input for tetromino movement
    bool left = !digitalRead(6);
    bool right = !digitalRead(7);
    bool rccw = !digitalRead(8);
    bool rcw = !digitalRead(9);
    bool drop = !digitalRead(10);
    // bool flip = !digitalRead(11);

    // update tetromino state one a second
    if (millis() - last_time >= 1000) {
      // main function code
      if (tetromino -> connects(tetris -> grid)) {
        delete tetromino;
        tetromino = new Tetromino();
      }


      if (left) tetromino -> move(tetris -> grid, 'r');
      if (right) tetromino -> move(tetris -> grid, 'l');
      if (drop) tetromino -> move(tetris -> grid, 'x');
      if (rcw) tetromino -> rotateClockwise();
      if (rccw) tetromino -> rotateCounterClockwise();



      tetromino -> update(tetris -> grid);
      
      last_time = millis();
    }

    // update the grid
    tetris -> update();

    for (int i = 0; i < 16; i++) {
      for (int j = 0; j < 8l j++) {
        // check whether grid and matrix states are different
        if ((tetris -> grid[i][j] && (matrix[i] & (1 << j)) != 0) ||
            !tetris -> grid[i][j] && ((matrix[i] >> j) & 0x01)) {
              // flip a bit if there is unmatching between grid and matrix
              matrix[i] ^= (1 << j);
            }
      }
    }

    IIC_start();
    IIC_send(0x40);// set the address plus 1 automatically
    IIC_end();

    IIC_start();
    IIC_send(0xc0); // set the initial address as 0

    for (char i = 0; i < 16; i++) {
      IIC_send(matrix[i]);
    }

    IIC_end();

    IIC_start();
    IIC_send(0x8A); // set the brightness display
    IIC_end(); 
}
/*----------------------------------------------------------------*/

void IIC_start() {
  digitalWrite(IIC_SCL,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,LOW);
  delayMicroseconds(3);
}

void IIC_send(unsigned char send_data) {
  for (char i = 0; i < 8; i++) {
    digitalWrite(IIC_SCL,LOW);
    delayMicroseconds(3); 

    // activate a LED light if a bit is 1
    if(send_data & 0x01) digitalWrite(IIC_SDA,HIGH);
    else digitalWrite(IIC_SDA,LOW);

    delayMicroseconds(3);
    digitalWrite(IIC_SCL,HIGH); 
    delayMicroseconds(3);

    // got to next pixel
    send_data = send_data >> 1;
  }
}
  
void IIC_end() {
  digitalWrite(IIC_SCL,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,HIGH);
  delayMicroseconds(3);

  delete tetromino;
  delete tetris;
}