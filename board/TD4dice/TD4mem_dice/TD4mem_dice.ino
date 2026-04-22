// A: [A3:A0] (PC3:PC0)
// D: [D7:D2 + D9:D8] (PB1:PB0 + PD7:PD2)

uint8_t mem[] = {
  // dice (OUT[2:0], IN0=start, IN1=stop (push=0)
  // IN: no=0x3, Start=0x2, Stop=0x1
  0x20, 0x0d, 0xe4, 0xf0, 0x90, 0x20, 0x0e, 0xe0, 0x10, 0x01, 0x40, 0x0a, 0xe4, 0x50, 0xf4, 0xf0
  /*
  0x0 IN A
  0x1 ADD A, 13
  0x2 JNC 0x4    ; any pressed -> start
  0x3 JMP 0x0
  0x4 OUT B
  0x5 IN A
  0x6 ADD A, 14
  0x7 JNC 0x0    ; Stop pressed -> stop (initial)
  0x8 MOV A, B   ; A <- B
  0x9 ADD A, 1
  0xa MOV B, A   ; B++
  0xb ADD A, 10
  0xc JNC 0x4    ; B<6 -> loop
  0xd MOV B, 0
  0xe JMP 0x4    ; B=6 -> B=0
  0xf JMP 0x0
  */
};

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
