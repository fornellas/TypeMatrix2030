#include "Keyboard.h"

#include <stdlib.h>

void Keyboard::addKeySequence(uint8_t *seq){
  if(NULL==sequence)
    sequence=seq;
}

void Keyboard::playKeySequence(){
  if(NULL==sequence)
    return;
  // skip
  uint8_t p=0;
  while(sequence[p]==0x00)
    p++;
  // process round
  for(uint8_t k=p+1;k<p+sequence[p]+1;k++){
    press(sequence[k]);
    sequence[k]=0x00;
  }
  // last round
  if(!sequence[p+sequence[p]+1]){
    free(sequence);
    sequence=NULL;
  // more rounds
  }else
    sequence[p]=0x00;
}
