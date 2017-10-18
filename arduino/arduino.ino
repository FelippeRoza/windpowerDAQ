int d = 1;

void setup() {

  // All pins to input
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  // Init Serial
  Serial.begin(115200);

}// end setup

void send_serial(char type, int analog){
  Serial.print(type);
  Serial.println(analog);
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
