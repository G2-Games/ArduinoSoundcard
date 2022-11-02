int output1 = 2;
int output2 = 3;
int output3 = 4;
int output4 = 5;


int freq;
float finaldelay = (1248000/freq)/16;

#define NOP __asm__ __volatile__ ("nop\n\t")
#define HI_NIBBLE(b) (((b) >> 4) & 0x0F)
#define LO_NIBBLE(b) ((b) & 0x0F)

byte hival;
byte loval;

float volume = 15;
byte vol;

float x = 0;
int y = 0;

const byte outPins = 4;
byte pins[] = {2, 3, 4, 5};
float sinfunct[16];

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output4, OUTPUT);
  for (int i = 0; i <= 15; i++) { // Pre-generate the waveform to avoid processing in loop
    volume = cos(x) * 7.999 + 7.999;
    sinfunct[i] = volume;
    x = x + (PI / 8);
    if ( x >= TWO_PI ) { x = 0; };
  }
  Serial.begin(2000000);
  freq = (900000/44100)*6;
}

void setup1() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop1() {
  rp2040.fifo.pop();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}

void loop() {
  if (Serial.available() > 0) {
    vol = Serial.read() >> 4;
    rp2040.fifo.push_nb(1);
  }
  digitalWrite(2, bitRead(vol, 0));
  digitalWrite(3, bitRead(vol, 1));
  digitalWrite(4, bitRead(vol, 2));
  digitalWrite(5, bitRead(vol, 3));
  for(int i = 0; i < freq; i++){
    NOP;
  }
}