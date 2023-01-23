// Digital pins -> Motors
const int A_1A = 6; // Motor A_1A
const int A_1B = 9; // Motor A_1B
const int B_1A = 5; // Motor B_1A
const int B_1B = 3; // Motor B_1B

const int IR1 = 13;     // InfraRed sensor
const int IR2 = 2;      // InfraRed sensor 2
const int echoPin = 11; // Ultrasonic sensor echo
const int trigPin = 12; // Ultrasonic sensor trigger

const int delayTime = 151;
const int speed = 150;
const int stop = 0;

// Serial monitor: 9600 
void setup()
{
    Serial.begin(9600);

    // IR sensors
    pinMode(IR1, INPUT);
    pinMode(IR2, INPUT);

    // Motors
    pinMode(A_1A, OUTPUT);
    pinMode(A_1B, OUTPUT);
    pinMode(B_1A, OUTPUT);
    pinMode(B_1B, OUTPUT);
    // Ultrasonic sensor
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    Serial.println("Setup complete");
}

void rightForward()     // Right wheel go forward
{
    analogWrite(B_1A, speed);
    analogWrite(B_1B, stop);
}

void rightBackward()    // Right wheel go backward
{
    analogWrite(B_1A, stop);
    analogWrite(B_1B, speed);
}

void leftForward()      // Left wheel go forward
{
    analogWrite(A_1A, stop);
    analogWrite(A_1B, speed);
}

void leftBackward()     // Left wheel go backward
{
    analogWrite(A_1A, speed);
    analogWrite(A_1B, stop);
}

void forward()         // Both wheels go forward
{
    leftForward();
    rightForward();
}

void turnLeft(int delayTime)    // Turn left for a certain amount of time
{

    leftBackward();
    rightForward();

    delay(delayTime);
}

void turnRight(int delayTime)   // Turn right for a certain amount of time
{
    leftForward();
    rightBackward();

    delay(delayTime);
}

bool detectObstacle(long distance)  // Detect obstacle
{
    if (distance <= 18)
    {
        return true;
    }
    return false;
}

void avoidObstacle()   // Avoid obstacle with a left curve
{
    // Turn about 45 degrees left
    turnLeft(delayTime);

    // Left motor forward more
    analogWrite(A_1A, speed * 1.5);
    analogWrite(A_1B, stop);

    // Right motor forward less
    analogWrite(B_1A, speed * 0.5);
    analogWrite(B_1B, stop);

    delay(1500);

    // Turn about 45 degrees right
    turnRight(1000);

    forward();

    // Turn 90 degrees right

    // // Left motor forward more
    // analogWrite(A_1A, speed * 1.5);
    // analogWrite(A_1B, stop);

    // // Right motor forward less
    // analogWrite(B_1A, speed * 0.5);
    // analogWrite(B_1B, stop);

    // delay(delayTime);
}

void brake(int timeDelay)  // Brake for a certain amount of time
{
    analogWrite(A_1A, stop);
    analogWrite(A_1B, stop);

    analogWrite(B_1A, stop);
    analogWrite(B_1B, stop);
    delay(timeDelay);
}

void go()
{
    // on the while path,
    if (digitalRead(IR1) == 1 && digitalRead(IR2) == 1)
    {
        forward();
        delay(delayTime);
    }

    // Left sensor sees black, make a left turn
    else if (digitalRead(IR1) == 0 && digitalRead(IR2) == 1)
    {
        brake(delayTime);
        turnLeft(500);
    }
    // Right sensor sees black, make a right turn
    else if (digitalRead(IR2) == 0)
    {
        brake(delayTime);
        turnRight(500);
    }
    // else
    // {
    //     brake();
    // }
}

void loop()
{

    Serial.print("IR1: ");
    Serial.print(digitalRead(IR1));
    Serial.print("\tIR2: ");
    Serial.println(digitalRead(IR2));

    // delay(delayTime);
    // turnLeft(500);

    long duration;
    long distance;

    // Clear the trigPin by setting it LOW:
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);

    // Trigger the sensor by setting the trigPin high for 10 microseconds:
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
    duration = pulseIn(echoPin, HIGH);
    // Calculate the distance:
    distance = duration * 0.034 / 2;

    // Print the distance on the Serial Monitor (Ctrl+Shift+M):
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print("\tDuration: ");
    Serial.println(duration);

    if (detectObstacle(distance)) {
        avoidObstacle();
    }

    go();
}
