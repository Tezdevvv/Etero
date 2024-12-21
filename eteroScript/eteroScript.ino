#include <SoftwareSerial.h>

SoftwareSerial btSerial(11, 12); // RX | TX

char moveFB = 'M'; // Default: Stabil
char moveRL = 'N'; // Default: Netral

void setup() {
  btSerial.begin(38400);
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  Serial.println("Mobil RC siap digunakan.");
}

void loop() {
  if (btSerial.available() > 0) {
    String command = btSerial.readStringUntil('\n');
    if (command.length() >= 2) {
      moveFB = command[0];
      moveRL = command[1];
    }
    Serial.print("Diterima: ");
    Serial.println(command);
  }
  
    // Logika gerakan kombinasi
  if (moveFB == 'B') {
    if (moveRL == 'L') {
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
    } else if (moveRL == 'R') {
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
    } else {
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
    }
  } else if (moveFB == 'F') {
    if (moveRL == 'L') {
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
    } else if (moveRL == 'R') {
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
    } else {
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
    }
  } else if (moveFB == 'M') {
    if (moveRL == 'L') {
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
    } else if (moveRL == 'R') {
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
    } else {
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
    }
  }
}

void compass() {
  
}
