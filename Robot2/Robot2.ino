//US defintions
#include <Ultrasonic.h>
#define TRIGGER_PIN  6
#define ECHO_PIN     7
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

//MOTOR definitions
int E1 = 11;   //left motor PWM   
int M1 = 6;   //left motor 
int E2 = 9;   //right motor PWM                   
int M2 = 4;   //right motor

//SERVO definitions
#include <Servo.h> //include servo libs
Servo Servo; //create servo object to control a servo 
int Servo_Pin = 9; //connected to digital out

//FRONT PUSH definitions
int frontPush_Pin = 10;

//POWER PUSH definitions
int powerPush_Pin = 8;

//LINE defintions 
int leftFrontLine_Pin = 0; //connected to analog in 0
int rightFrontLine_Pin = 1; //connected to analog in 0

int frontLine_Led = 13;
int leftFrontLine_Value;
int rightFrontLine_Value;
int frontLine_Value;

//GLOBAL definitions
//arena official diameter mini category: 77 cm
float trigDist = 38.5f;
boolean trigToken;
float t1, t2, t3;
float maxTime;
boolean noBreak;

void setup(){
	Serial.begin(9600);

	//startup delay
	Serial.println("Welcome to Neothug");
	Serial.println("Starting in 5 seconds...");
	delay(5000);
	  
	pinMode(M1, OUTPUT);   
	pinMode(M2, OUTPUT); 
	AttachServo();
}

void SensorsReport(){
	US();
	Serial.print("Left frontLine Sensor: ");
	Serial.println(analogRead(leftFrontLine_Pin));
	Serial.print("Right frontLine Sensor: ");
	Serial.println(analogRead(rightFrontLine_Pin));
	Serial.print("FrontPush state: ");
	FrontPush();
	Serial.print("PowerPush state: ");
	PowerPush();  
}

void loop(){
	TestMotors();
}

void TestMotors(){ 
int value; 
	for(value = 0 ; value <= 255; value+=5){ 
		digitalWrite(M1,LOW);   
		digitalWrite(M2, LOW);       
		analogWrite(E1, value);   //PWM Speed control -> other PIN
		analogWrite(E2, value);   //PWM Speed control 
		delay(30); 
	}  
}

void real_loop(){  
	//FrontLine true when white, false when black in real conditions
	SensorsReport();

	//main code

	//get current values
	if(!trigToken){
		t1 = US();
		delay(5);
		t2 = US();
		delay(5);
		t3 = US();
		delay(5);
	}

	if(!FrontLine()){
		if ((t1 < trigDist && t2 < trigDist && t3 < trigDist) || trigToken){ 
			trigToken = false; 
			maxTime = millis() + 3500.0f;
			while(!FrontLine() && millis() < maxTime){
				Forward();
			}
		}
		else{
			while(!FrontLine() && US() > trigDist){
				RotateCW();
			}
			Stop();
			if (US() < trigDist){
				trigToken = true;
			}
		}
	}

	if(FrontLine()){
	Stop();
	AvoidBorder();
	}
}


float US(){
	//US
	float cmMsec, inMsec;
	long microsec = ultrasonic.timing();

	cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
	Serial.print("MS: ");
	Serial.print(microsec);
	Serial.print(", Distance (cm): ");
	Serial.println(cmMsec);
	return cmMsec;
}

boolean PowerPush(){
	if (digitalRead(powerPush_Pin) == LOW) {
		Serial.print("Button is LOW");
		return false;
	}
	else{
		Serial.print("Button is HIGH");
		return true;
	}
}
	
boolean FrontPush(){
	if (digitalRead(frontPush_Pin) == LOW) {
		Serial.print("Button is LOW");
		return false;
	}
	else{
		Serial.print("Button is HIGH");
		return true;
	}	
}  
  
boolean FrontLine(){
	//frontLine get data
	leftFrontLine_Value = analogRead(leftFrontLine_Pin);
	rightFrontLine_Value = analogRead(rightFrontLine_Pin);
	 
	if(leftFrontLine_Value < 52 || rightFrontLine_Value < 52){
			return true;
		}
		else{
			return false;
		}
}

void AttachServo(){
	Servo.attach(Servo_Pin);  //attaches the servo on pin to the servo object  
}

void Stop(){
    digitalWrite(M1,LOW);
    digitalWrite(M2, LOW);
    analogWrite(E1, 0);
    analogWrite(E2, 0);
}

void Backward(){
    digitalWrite(M1,HIGH);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 230);
    analogWrite(E2, 230);
}

void Forward(){
    digitalWrite(M1,LOW);
    digitalWrite(M2, LOW);
    analogWrite(E1, 250);
    analogWrite(E2, 250);
}

void RotateCW(){
    digitalWrite(M1,LOW);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 77);
    analogWrite(E2, 177);
}

void RotateCCW(){
    digitalWrite(M1,HIGH);
    digitalWrite(M2, LOW);    
    analogWrite(E1, 177);
    analogWrite(E2, 77);
}

void RotateCWSlow(){

}

void RotateCCWSlow(){

}

void RotateCWavg(){
	digitalWrite(M1,LOW);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 77);
    analogWrite(E2, 177);
}

void AvoidBorder(){
	Stop();
	delay(75);
	RotateCWavg();
	delay(275);
	Stop();
	delay(75);
	Forward();
	delay(350);
	Stop();
	delay(75);
}

//not used 
void EvasiveManeuver(){
	//when facing enemy for too long
	Stop();
	delay(75);
	RotateCW();
	delay(700);
	Stop();
	delay(75);
	noBreak = false;
}	




