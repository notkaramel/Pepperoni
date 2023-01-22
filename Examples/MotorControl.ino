#define A_1A 1  // Arduino pin tied to A_1A on the Motor Controller
#define A_1B 3  // Arduino pin tied to A_1B on the Motor Controller

#define B_1A 6  // Arduino pin tied to B_1A on the Motor Controller
#define B_1B 5  // Arduino pin tied to B_1B on the Motor Controller

const int delayTime = 5000;
const int speed = 150;
const int stop = 0;

void setup() {
  // put your setup code here, to run once:
  
  // Setup One Side
  pinMode(A_1A, OUTPUT);
  pinMode(A_1B, OUTPUT);

  // Setup Other Side
  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);


}

void forward(){
  analogWrite(A_1A, stop);
  analogWrite(A_1B, speed);

  analogWrite(B_1A, speed);
  analogWrite(B_1B, stop);

  delay(delayTime);
}

void backward(){
  analogWrite(A_1A, speed);
  analogWrite(A_1B, stop);

  analogWrite(B_1A, stop);
  analogWrite(B_1B, speed);

  delay(delayTime);
}

void brake(){
  analogWrite(A_1A, stop);
  analogWrite(A_1B, stop);

  analogWrite(B_1A, stop);
  analogWrite(B_1B, stop);

  delay(delayTime);
}

// REAL BLOW UP danger, do if you like to waste money
void danger(){
  analogWrite(A_1A, speed);
  analogWrite(A_1B, speed);
  delay(delayTime);
}

void loop() {
  // put your main code here, to run repeatedly:
  // forward();
  // brake();
  // backward();
  brake();
}

