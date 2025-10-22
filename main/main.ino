#include <Keypad.h>

#define ROW_NUM     4 // four rows
#define COLUMN_NUM  4 // four columns
#define PASSWORD_NUM 4

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM]      = {19, 18, 5, 17}; // GPIO19, GPIO18, GPIO5, GPIO17 connect to the row pins
byte pin_column[COLUMN_NUM] = {16, 4, 0, 2};   // GPIO16, GPIO4, GPIO0, GPIO2 connect to the column pins

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

const int ledPin = 13;

char password[PASSWORD_NUM] = {'2', '4', '6', '8'};
char input[PASSWORD_NUM] = {'-', '-', '-', '-'};
int k = 0;

bool arraysEqual(char arr1[], char arr2[]) {
  for (int i = 0; i < PASSWORD_NUM; i++) {
    if (arr1[i] != arr2[i]) {
      return false;
    }
  }
  return true;
}

void resetPassword(char arr[]) {
  for (int i = 0; i < PASSWORD_NUM; i++) {
    arr[i] = '-';
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    input[k] = key;
    k++;
  }

  if (k >= 4) {
    if (arraysEqual(password, input)) {
      Serial.println("Correct Password!!!");
      for (int i = 0; i < 10; i++) {
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
      }
    }

    k = 0;
    resetPassword(input);
    Serial.println("Try Again");
  }
}