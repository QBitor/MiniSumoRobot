//Arduino PWM  Code
//M1: Direction for Motor1
//M2: Direction for Motor2
//E1: PWM control for Motor1
//E2: PWM control for Motor2
int E1 = 5;   //left motor PWM   
int M1 = 4;   //left motor 
int E2 = 3;   //right motor PWM                   
int M2 = 2;   //right motor

void setup() 
{ 
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT); 
}

void loop(){
  testMotors();
}

void testMotors() 
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
    digitalWrite(M1,HIGH);
    digitalWrite(M2, LOW);    
    analogWrite(E1, 177);
    analogWrite(E2, 77);
}

void turnRight(){
    digitalWrite(M1,LOW);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 77);
    analogWrite(E2, 177);
    
}

void stop(){
    digitalWrite(M1,LOW);
    digitalWrite(M2, LOW);
    analogWrite(E1, 0);
    analogWrite(E2, 0);
}






