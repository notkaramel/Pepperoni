// Black Line Follower 
int IR1=9;      //Right sensor
int IR2=10;     //Left sensor

void setup() {
  // put your setup code here, to run once:
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);

  // Setup the serial monitor
  Serial.begin(9600);
}
void loop() 
{
  // int rightVal = analogRead(IR1);
  int rightVal = digitalRead(IR1);
  
  // int leftVal = analogRead(IR2);
  int rightVal = digitalRead(IR2);
  // Serial.print("RIGHT: ");
  // Serial.println(rightVal);
  
  // Delay 500msec between every IR scan 
  delay(500);
}
