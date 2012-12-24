#include <Wire.h>
#include <inttypes.h>

#define MCP23017_ADDRESS 0x20

// registers
#define MCP23017_IODIRA 0x00
#define MCP23017_IPOLA 0x02
#define MCP23017_GPINTENA 0x04
#define MCP23017_DEFVALA 0x06
#define MCP23017_INTCONA 0x08
#define MCP23017_IOCONA 0x0A
#define MCP23017_GPPUA 0x0C
#define MCP23017_INTFA 0x0E
#define MCP23017_INTCAPA 0x10
#define MCP23017_GPIOA 0x12
#define MCP23017_OLATA 0x14


#define MCP23017_IODIRB 0x01
#define MCP23017_IPOLB 0x03
#define MCP23017_GPINTENB 0x05
#define MCP23017_DEFVALB 0x07
#define MCP23017_INTCONB 0x09
#define MCP23017_IOCONB 0x0B
#define MCP23017_GPPUB 0x0D
#define MCP23017_INTFB 0x0F
#define MCP23017_INTCAPB 0x11
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATB 0x15

#define MCP_ADDR0 0x20
#define MCP_ADDR1 0x21

void
setup(){
  Serial.begin(11500);

  Wire.begin();

  // reset and set up all pull ups
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  delay(50);
  digitalWrite(4, HIGH);
  Wire.beginTransmission(MCP_ADDR0);
  Wire.write(MCP23017_GPPUA);
  Wire.write(0xFF);
  Wire.write(0xFF);
  Wire.endTransmission();
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  delay(50);
  digitalWrite(5, HIGH);
  Wire.beginTransmission(MCP_ADDR1);
  Wire.write(MCP23017_GPPUA);
  Wire.write(0xFF);
  Wire.write(0xFF);
  Wire.endTransmission();

  Keyboard.begin();
}

int counter=0;

int enter=0;

void
loop(){
  uint8_t values[26];
  // clear array
  for(int i=0;i<26;i++)
    values[i]=0;
  // scan all pins
  for(int p=0;p<25;p++){
    // set all as inputs
    Wire.beginTransmission(MCP_ADDR0);
    Wire.write(MCP23017_IODIRA);
    Wire.write(0xFF);
    Wire.write(0xFF);
    Wire.endTransmission();
    Wire.beginTransmission(MCP_ADDR1);
    Wire.write(MCP23017_IODIRA);
    Wire.write(0xFF);
    Wire.write(0xFF);
    Wire.endTransmission();
    // set current pin as output
    if(p<8){
      Wire.beginTransmission(MCP_ADDR0);
      Wire.write(MCP23017_IODIRA);
      Wire.write(~(1<<p));
      Wire.endTransmission();
    }else if(p<16){
      Wire.beginTransmission(MCP_ADDR0);
      Wire.write(MCP23017_IODIRB);
      Wire.write(~(1<<(p-8)));
      Wire.endTransmission();
    }else if(p<24){
      Wire.beginTransmission(MCP_ADDR1);
      Wire.write(MCP23017_IODIRA);
      Wire.write(~(1<<(p-16)));
      Wire.endTransmission();
    }else{
      Wire.beginTransmission(MCP_ADDR1);
      Wire.write(MCP23017_IODIRB);
      Wire.write(~(1<<(p-24)));
      Wire.endTransmission();
    }
    // read all gpio
    uint32_t gpio=0;
    if(p<16){
      Wire.beginTransmission(MCP_ADDR0);
      Wire.write(MCP23017_GPIOA);
      Wire.endTransmission();
      Wire.requestFrom(MCP_ADDR0, 2);
      gpio=Wire.read();
      gpio=gpio|((uint32_t)Wire.read()<<8);
    }
    Wire.beginTransmission(MCP_ADDR1);
    Wire.write(MCP23017_GPIOA);
    Wire.endTransmission();
    Wire.requestFrom(MCP_ADDR1, 2);
    gpio=gpio|((uint32_t)Wire.read()<<16);
    gpio=gpio|((uint32_t)Wire.read()<<24);
    // look for key presses
    for(int i=p+1;i<26;i++){
      if(~gpio&(1L<<i)){
        values[i]=1;
        values[p]=1;
      }
    }
  }
if(values[7]&&values[15]){
  Keyboard.press(KEY_RETURN);
}else{
  Keyboard.release(KEY_RETURN);
}
  // Print results
  Serial.print(counter++);
  Serial.print(": ");
  for(int i=0;i<26;i++){
    if(values[i]){
      if(i<10)
        Serial.print(' ');
      Serial.print(i);
    } else
      Serial.print(" .");
    Serial.print(' ');
  }
  Serial.println("");
}
