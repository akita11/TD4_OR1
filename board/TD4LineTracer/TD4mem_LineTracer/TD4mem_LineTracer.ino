// A: [A3:A0] (PC3:PC0)
// D: [D7:D2 + D9:D8] (PB1:PB0 + PD7:PD2)

uint8_t mem[] = {
  // line trace
  0x20, 0x08, 0xe8, 0x20, 0x06, 0xed, 0xb0, 0xf0, 0x20, 0x0e, 0xef, 0xb2, 0xf0, 0xb1, 0xf0, 0xb3
  /*
  IN1=Left/ IN3=right (0=white)
  0         0    =0    -> go strait
  1         0    =2    -> turn left
  0         1    =8    -> turn right
  1         1    =10   -> stop
  
  0x0 IN A
  0x1 ADD A, 8
  0x2 JLC 0x8    ; IN=0 or 2 -> jmp to 0x8
  0x3 IN A
  0x4 ADD A, 6
  0x5 JNC 0xd    ; IN=8 -> jmp to turn right
  0x6 OUT 0x0    ; IN=5 -> stop
  0x7 JMP 0x0
  0x8 IN A
  0x9 ADD A, 14
  0xa JNC 0xf    ; IN=0 -> jmp to go straight
  0xb OUT 0x2    ; turn left
  0xc JMP 0x0
  0xd OUT 0x01   ; turn right
  0xe JMP 0x0
  0xf OUT 0x3    ; go straight
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
