#include <PWM.h>

int pin_out = 9;
int d = 1;
float output = 0.0;
int input = 10;

void setup() {
  //initialize all timers except for 0, to save time keeping functions
  //just because you init the timer doesn't change the default frequency until you call setpinfreq 
  InitTimersSafe(); 

  //sets the frequency for the specified pin
  bool success = SetPinFrequencySafe(pin_out, 20000);
  //success == true if it worked

  // Analog pins as input
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  // Init Serial
  Serial.begin(115200);

  output = map(input, 0, 100, 0, 400);
  analogWrite(pin_out, output);

}// end setup

void send_serial(char type, int analog){
  output = analog*5.0/1023.0;
  if(type == 'i'){
    output = (output - 2.5)/0.185;
  }
  else if(type == 'v'){
    output = output*10.0/110.0;
  }
  Serial.println(String(type) + " :" +  String(output));
  delayMicroseconds(d);
}


void loop() {

  if(Serial.available()) {

    int signal = Serial.read();

    if(signal == 119) {

      //current sensors
      send_serial( 'i', analogRead(A0) );
      send_serial( 'i', analogRead(A2) );
      send_serial( 'i', analogRead(A4) );
      //voltage sensors
      send_serial( 'v', analogRead(A1) );
      send_serial( 'v', analogRead(A3) );
      send_serial( 'v', analogRead(A5) );

    }
  }
}
