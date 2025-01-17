void setup() {
 int i;
 int y;
 Serial.begin(9600);
 delay(1000);
 Serial.print("HELLO THERE\n");
 // wait for Serial to finish setting up
 for (i=8;i<=12;i++) {
 pinMode(i,OUTPUT);
 }
 pinMode(A0,INPUT);
 for (i=0;i<32;i+=1) {
 PORTB=i;
 y=analogRead(A0);
//  Serial.print(i);
//  Serial.print('\t');
 Serial.print(y);
 Serial.print('\n');
 }
}

void loop() {
}