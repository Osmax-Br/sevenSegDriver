#include <Arduino.h>
int STCP_pin = 27 ; //latch
int SHCP_pin = 14 ; //clock
int DS_pin = 12 ;
int dec_digits   [11] {1,79,18,6,76,36,32,15,0,4,127};
int seg_parts[4] = {17,5,18,19};  
int next_seg = 0;
int next_seg_time = 0;
int temp_num = 0;



void segment_driver(int number){
int first_digit = (number/1000)%10 ;                 //,second_digit,third_digit,fourth_digit = 0;
int second_digit = (number / 100)%10 ;
int third_digit = (number / 10)%10 ;
int fourth_digit = number % 10 ;


if(number < 1000){
  first_digit = 10;
  if(number < 100){
    second_digit = 10;
    if(number < 10){
      third_digit = 10;
    }
  }
}


if(next_seg == 0){
  digitalWrite(seg_parts[0],1);
  digitalWrite(seg_parts[1],0);
  digitalWrite(seg_parts[2],0);
  digitalWrite(seg_parts[3],0);

  digitalWrite(STCP_pin,LOW);
  shiftOut(DS_pin,   SHCP_pin, LSBFIRST,dec_digits[first_digit]);
  digitalWrite(STCP_pin, HIGH);
  if(next_seg_time + 5 < millis()){
  next_seg_time = millis();
  next_seg = 1;
  }
}

else if(next_seg == 1){

  digitalWrite(seg_parts[0],0);
  digitalWrite(seg_parts[1],1);
  digitalWrite(seg_parts[2],0);
  digitalWrite(seg_parts[3],0);

  digitalWrite(STCP_pin,LOW);
  shiftOut(DS_pin,   SHCP_pin, LSBFIRST,dec_digits[second_digit]);
  digitalWrite(STCP_pin, HIGH);
  if(next_seg_time + 5 < millis()){
  next_seg_time = millis();
  next_seg = 2;
  }
}

 

else if(next_seg == 2){
  digitalWrite(seg_parts[0],0);
  digitalWrite(seg_parts[1],0);
  digitalWrite(seg_parts[2],1);
  digitalWrite(seg_parts[3],0);

  digitalWrite(STCP_pin,LOW);
  shiftOut(DS_pin,   SHCP_pin, LSBFIRST,dec_digits[third_digit]);
  digitalWrite(STCP_pin, HIGH);
    if(next_seg_time + 5 < millis()){
  next_seg_time = millis();
  next_seg = 3;
  }
}





else if(next_seg == 3){
  digitalWrite(seg_parts[0],0);
  digitalWrite(seg_parts[1],0);
  digitalWrite(seg_parts[2],0);
  digitalWrite(seg_parts[3],1);

  digitalWrite(STCP_pin,LOW);
  shiftOut(DS_pin,   SHCP_pin, LSBFIRST,dec_digits[fourth_digit]);
  digitalWrite(STCP_pin, HIGH);
   if(next_seg_time + 5 < millis()){
  next_seg_time = millis();
  next_seg = 0;
  }
}

}


void setup(){
  pinMode(SHCP_pin,OUTPUT);
  pinMode(STCP_pin,OUTPUT);
  pinMode(DS_pin,OUTPUT);
  pinMode(seg_parts[0],OUTPUT);
  pinMode(seg_parts[1],OUTPUT);
  pinMode(seg_parts[2],OUTPUT);
  pinMode(seg_parts[3],OUTPUT);

}


void loop(){

for(int i = 0 ; i<10000 ;){
segment_driver(i);
if(temp_num + 30 < millis()){
i++;
temp_num = millis();
}

}


}