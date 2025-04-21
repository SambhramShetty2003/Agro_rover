/*// LEFT sensor(LSP) on digitalPin 2
// Right sensor(RSP) on digitalPin 3

// Left Motor connected to 4,5 digitalPins
// Right Motor connected to 10,9 digitalPins
int LMP =8;
int LMN =9;
int RMP=6;
int RMN=7;

void setup() {
  // put your setup code here, to run once:
  pinMode(LMP, OUTPUT);
  pinMode(LMN, OUTPUT);
  pinMode(RMP, OUTPUT);
  pinMode(RMN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    String Direction = Serial.readString();
    if(Direction == "F")
    {
      //Move Forward 
      digitalWrite(LMP, HIGH);
      digitalWrite(LMN, LOW);
      digialtWrite(RMP, LOW);
      digitalWrite(RMN, HIGH);

    }
    else if (Direction == "B")
    {
      //Move backward
      digitalWrite(LMP, LOW);
      digitalWrite(LMN, HIGH);
      digialtWrite(RMP, HIGH);
      digitalWrite(RMN, LOW);

    }

    else if (Direction == "L")
    {
      //Move backward
      digitalWrite(LMP, LOW);
      digitalWrite(LMN, HIGH);
      digialtWrite(RMP, LOW);
      digitalWrite(RMN, HIGH);

    }

    else if (Direction == "R")
    {
      // Left turn
      //Move backward
      digitalWrite(LMP, HIGH);
      digitalWrite(LMN, LOW);
      digialtWrite(RMP, HIGH);
      digitalWrite(RMN, LOW);

    }

    else if (Direction == "S")
    {
      //Stop
      digitalWrite(LMP, LOW);
      digitalWrite(LMN, LOW);
      digialtWrite(RMP, LOW);
      digitalWrite(RMN, LOW);

    }

  }

}
*/




// LEFT sensor(LSP) on digitalPin 2
// Right sensor(RSP) on digitalPin 3

// Motor 1 is the left motor
// Motor 2 is the right motor

// Motor 1 pins
int M1P = 13; // Positive terminal
int M1N = 12; // Negative terminal
int M1PWM = 11; // PWM Pin

// Motor 2 pins
int M2P = 9;  // Positive terminal
int M2N = 8;  // Negative terminal
int M2PWM = 10; // PWM Pin

// Motor 3 pins
int M3P = 2;  // Positive terminal
int M3N = 4;  // Negative terminal
int M3PWM = 3; // PWM Pin

void setup() {
  // Set up motor pins
  pinMode(M1P, OUTPUT);
  pinMode(M1N, OUTPUT);
  pinMode(M1PWM, OUTPUT); // PWM Pin

  pinMode(M2P, OUTPUT);
  pinMode(M2N, OUTPUT);
  pinMode(M2PWM, OUTPUT); // PWM Pin

  // Set up motor pins
  pinMode(M3P, OUTPUT);
  pinMode(M3N, OUTPUT);
  pinMode(M3PWM, OUTPUT); // PWM Pin
  
  // Set full speed for both motors (255 is maximum for PWM)
  analogWrite(M1PWM, 255);
  analogWrite(M2PWM, 255);
  analogWrite(M3PWM, 255);
  
  Serial.begin(9600);
}

void loop() {
  // Check if data is available from Serial
  if (Serial.available()) {
    String Direction = Serial.readString();

    // Move Forward
    if (Direction == "F") {
      digitalWrite(M1P, HIGH);
      digitalWrite(M1N, LOW);
      digitalWrite(M2P, HIGH);
      digitalWrite(M2N, LOW);
    }
    
    // Move Backward
    else if (Direction == "B") {
      digitalWrite(M1P, LOW);
      digitalWrite(M1N, HIGH);
      digitalWrite(M2P, LOW);
      digitalWrite(M2N, HIGH);
    }
    
    // Turn Left
    else if (Direction == "L") {
      digitalWrite(M1P, LOW);
      digitalWrite(M1N, HIGH);
      digitalWrite(M2P, HIGH);
      digitalWrite(M2N, LOW);
    }
    
    // Turn Right
    else if (Direction == "R") {
      digitalWrite(M1P, HIGH);
      digitalWrite(M1N, LOW);
      digitalWrite(M2P, LOW);
      digitalWrite(M2N, HIGH);
    }
    
    // Stop
    else if (Direction == "S") {
      digitalWrite(M1P, LOW);
      digitalWrite(M1N, LOW);
      digitalWrite(M2P, LOW);
      digitalWrite(M2N, LOW);
    }
    
    // Move Upward pulley
    else if (Direction == "U") {
      digitalWrite(M3P, HIGH);
      digitalWrite(M3N, LOW);
    }

    // Move Stop pulley
    else if (Direction == "T") {
      digitalWrite(M3P, LOW);
      digitalWrite(M3N, LOW);
    }

    // Move DOWNward pulley
    else if (Direction == "D") {
      digitalWrite(M3P, LOW);
      digitalWrite(M3N, HIGH);
    }
  }
}
