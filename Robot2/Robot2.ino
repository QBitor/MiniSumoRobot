//Arduino PWM  Code
//M1: Direction for Motor1
//M2: Direction for Motor2
//E1: PWM control for Motor1
//E2: PWM control for Motor2
int E1 = 5;   //left   
int M1 = 4;   //left
int E2 = 6;   //right                         
int M2 = 7;   //right                
void setup() 
{ 
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT); 
}
void loop() 
{ 
  int value; 
  for(value = 0 ; value <= 255; value+=5) 
  { 
    digitalWrite(M1,LOW);   
    digitalWrite(M2, LOW);       
    analogWrite(E1, value);   //PWM Speed control 
    analogWrite(E2, value);   //PWM Speed control 
    delay(30); 
  }  
}

void turnLeft(){
    digitalWrite(M1,LOW);   //both motor forward 
    digitalWrite(M2, LOW);    //both motors forward
    analogWrite(E1, value);
    analogWrite(E2, value); 
}


