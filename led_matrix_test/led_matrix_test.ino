#define IIC_SCL  A5
#define IIC_SDA  A4

void IIC_start();
void IIC_send(unsigned char send_data);
void IIC_end();

unsigned char table[3][16] = {
  {0x00, 0xFF, 0x81, 0x81, 0x7E, 0x00, 0x00, 0xFF, 0x88, 0xFF, 0x00, 0x00, 0xF1, 0x91, 0x91, 0x99},
  {0x00, 0xFF, 0x10, 0x10, 0x10, 0xFF, 0x00, 0x00, 0xF1, 0x91, 0x91, 0x99, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0x20, 0x44, 0x42, 0x84, 0x80, 0x84, 0x42, 0x44, 0x20, 0x00, 0x00, 0x00}
};

int data_line = 0;
int delay_count = 0;

void setup() {
  pinMode(IIC_SCL, OUTPUT);
  pinMode(IIC_SDA, OUTPUT);
  digitalWrite(IIC_SCL, LOW);
  digitalWrite(IIC_SDA, LOW);
}

void loop() {
  // Address auto-increment setup
  IIC_start();
  IIC_send(0x40);
  IIC_end();

  // Send display data
  IIC_start();
  IIC_send(0xC0); // starting address
  for (char i = 0; i < 16; i++) {
    IIC_send(table[data_line][i]);
  }

  if (++delay_count >= 10) {
    delay_count = 0;
    data_line++;
    if (data_line >= 3) data_line = 0;
  }

  IIC_end();

  // Set brightness
  IIC_start();
  IIC_send(0x8A);
  IIC_end();

  delay(100);
}

void IIC_start() {
  digitalWrite(IIC_SCL, LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA, HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL, HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA, LOW);
  delayMicroseconds(3);
}

void IIC_send(unsigned char send_data) {
  for (char i = 0; i < 8; i++) {
    digitalWrite(IIC_SCL, LOW);
    delayMicroseconds(3);
    digitalWrite(IIC_SDA, (send_data & 0x01) ? HIGH : LOW);
    delayMicroseconds(3);
    digitalWrite(IIC_SCL, HIGH);
    delayMicroseconds(3);
    send_data >>= 1;
  }
}

void IIC_end() {
  digitalWrite(IIC_SCL, LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA, LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL, HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA, HIGH);
  delayMicroseconds(3);
}
