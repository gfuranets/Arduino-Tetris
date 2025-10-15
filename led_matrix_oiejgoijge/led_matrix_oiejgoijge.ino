// define output ports A4 and A5
#define IIC_SCL  A5
#define IIC_SDA  A4

/* 
A4 - SDA
A5 - SCL
VCC - 5V
GND - GND 
*/

void IIC_start();
void IIC_send(unsigned char send_data);
void IIC_end();

// 8x16 matrix LED information
unsigned char matrix[16] = {0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00};

void setup() {
  pinMode(IIC_SCL,OUTPUT);
  pinMode(IIC_SDA,OUTPUT);
  digitalWrite(IIC_SCL,LOW);
  digitalWrite(IIC_SDA,LOW);

  // pins for game button input
  // rotate ccw, eotate cw, move l, move r, drop
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);

  matrix[15] |= (1 << 3);
  matrix[15] |= (1 << 4);
  matrix[14] |= (1 << 3);
  matrix[14] |= (1 << 4);
}

void loop() 
{
    /**************set the address plus 1***************/
    IIC_start();
    IIC_send(0x40);// set the address plus 1 automatically
    IIC_end();
    /************end the process of address plus 1 *****************/
    /************set the data display*****************/ 
    IIC_start();
    IIC_send(0xc0);// set the initial address as 0

    for (char i = 0; i < 16; i++) {
      IIC_send(matrix[i]);
    }


    IIC_end();
    /************end the data display*****************/
    /*************set the brightness display***************/ 
    IIC_start();
    IIC_send(0x8A);// set the brightness display
    IIC_end(); 
    /*************end the brightness display***************/ 
}
/*----------------------------------------------------------------*/

void IIC_start()
{
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
  
void IIC_end()
{
  digitalWrite(IIC_SCL,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,HIGH);
  delayMicroseconds(3);
}