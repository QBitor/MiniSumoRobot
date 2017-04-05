//POWER SWITCH definitions
int powerSwitch_Pin = 12;

//US defintions
#include <Ultrasonic.h>
#define TRIGGER_PIN  9
#define ECHO_PIN     11
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

//MOTOR definitions
int E1 = 5;   //left motor PWM   
int M1 = 4;   //left motor 
int E2 = 3;   //right motor PWM                   
int M2 = 2;   //right motor

//LINE defintions 
int rightFrontLine_Pin = 4; //connected to analog in 0
int frontLine_Led = 13;
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
	pinMode(M1, OUTPUT);   
	pinMode(M2, OUTPUT); 
	while(!PowerPush()){
		Serial.println("Waiting for start switch!");
	}
	Serial.println("Starting in 5 seconds...");
	delay(5000);
}

boolean PowerPush(){
	if (digitalRead(powerSwitch_Pin) == LOW) {
		Serial.print("Button is LOW");
		return true; //robot run
	}
	else{
		Serial.print("Button is HIGH");
		return false;
	}
}

void SensorsReport(){
	US();
	delay(1000);
	Serial.print("Right frontLine Sensor: ");
	Serial.println(analogRead(rightFrontLine_Pin));
	delay(1000);
	Serial.print("PowerPush state: ");
	delay(1000);
	PowerPush();
}

void TestMotors(){ 
	int value; 
	for(value = 0 ; value <= 255; value+=5){ 
		digitalWrite(M1,LOW);   
		digitalWrite(M2, LOW);       
		analogWrite(E1, value);   //PWM Speed control 
		analogWrite(E2, value);   //PWM Speed control 
		delay(30); 
	}  
}

void testloop(){
	//SensorsReport();
	//TestMotors(); 
}

void loop(){
	while(PowerPush()){
		DoSumo();
	}
	Stop();
}

void DoSumo(){  
	//FrontLine true when white, false when black in real conditions

	//main code

	//get current values
	if(!trigToken){
		t1 = US();
		delay(2);
		t2 = US();
		delay(2);
		t3 = US();
		delay(2);
	}
	  
	if(!FrontLine()){
		if ((t1 < trigDist && t2 < trigDist && t3 < trigDist) || trigToken){ 
			trigToken = false; 
			maxTime = millis() + 1500.0f;
			while(!FrontLine() && millis() < maxTime){
			Forward();
			}
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

boolean FrontLine(){
	//frontLine get data
	rightFrontLine_Value = analogRead(rightFrontLine_Pin);
	  
	if(rightFrontLine_Value < 52){
		//return false;
		return true;
	}
	else{
		return true;
	}
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
	analogWrite(E1, 250);
	analogWrite(E2, 250);
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
	analogWrite(E1, 255);
	analogWrite(E2, 255);
}

void RotateCCW(){
	digitalWrite(M1,HIGH);
	digitalWrite(M2, LOW);    
	analogWrite(E1, 255);
	analogWrite(E2, 255);
}

void RotateCWSlow(){

}

void RotateCCWSlow(){

}

void RotateCWavg(){
	digitalWrite(M1,LOW);
	digitalWrite(M2, HIGH);
	analogWrite(E1, 255);
	analogWrite(E2, 255);
}

void AvoidBorder(){
	Stop();
	//delay(25);
	RotateCWavg();
	delay(1250);
	//Stop();
	//delay(25);
	Forward();
	//delay(450);
	//Stop();
	//delay(25);
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




