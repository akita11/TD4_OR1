// A: [A3:A0] (PC3:PC0)
// D: [D7:D2 + D9:D8] (PB1:PB0 + PD7:PD2)

uint8_t mem[] = {
  //0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f 
//0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
  // blink (count up)
  0x70, 0x90, 0x51, 0xf1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // OUT blink (MOV B,0 / OUT B / ADD B,1 / JMP 1)

void setup() {
#define ADDR_PINMODE INPUT
//#define ADDR_PINMODE INPUT_PULLUP
  pinMode(A3, ADDR_PINMODE);
  pinMode(A2, ADDR_PINMODE);
  pinMode(A1, ADDR_PINMODE);
  pinMode(A0, ADDR_PINMODE);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

uint8_t data = 0x00, data0 = 0x00;

void loop() {
  uint8_t addr;
  addr = (digitalRead(A3) << 3) | (digitalRead(A2) << 2) | (digitalRead(A1) << 1) | (digitalRead(A0));
  data = mem[addr];
  //Serial.print(addr, HEX); Serial.print(' '); Serial.println(data, HEX);
  if (data != data0){
    if (data & 0x01) digitalWrite(8, 1); else digitalWrite(8, 0);
    if (data & 0x02) digitalWrite(9, 1); else digitalWrite(9, 0);
    if (data & 0x04) digitalWrite(2, 1); else digitalWrite(2, 0);
    if (data & 0x08) digitalWrite(3, 1); else digitalWrite(3, 0);
    if (data & 0x10) digitalWrite(4, 1); else digitalWrite(4, 0);
    if (data & 0x20) digitalWrite(5, 1); else digitalWrite(5, 0);
    if (data & 0x40) digitalWrite(6, 1); else digitalWrite(6, 0);
    if (data & 0x80) digitalWrite(7, 1); else digitalWrite(7, 0);
    data0 = data;
  }
}
