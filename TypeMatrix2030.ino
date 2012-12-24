#include <Wire.h>
#include "TypeMatrix.h"

TypeMatrix *tm;

void
setup(){
  Serial.begin(11500);
  tm=new TypeMatrix();
}

void
loop(){
  tm->scanAll();
}
