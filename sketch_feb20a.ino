#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
#define BUZZER 2

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ====== ADD YOUR REAL UIDs HERE ======
String uidSunny = "97 13 B4 51";
String uidRahul = "11 22 33 44";
String uidAmit  = "62 63 BA 5C";

// ====== Attendance Status ======
bool sunnyMarked = false;
bool rahulMarked = false;
bool amitMarked  = false;

int totalPresent = 0;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.init();
  lcd.backlight();
  pinMode(BUZZER, OUTPUT);

  showMainScreen();
}

void loop() {

  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  String content = "";

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content += String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    content += String(mfrc522.uid.uidByte[i], HEX);
  }

  content.toUpperCase();
  content.trim();

  lcd.clear();

  // ====== SUNNY ======
  if (content == uidSunny) {
    if (!sunnyMarked) {
      sunnyMarked = true;
      totalPresent++;
      lcd.setCursor(0,0);
      lcd.print("Welcome Sunny");
      beep();
    } else {
      lcd.setCursor(0,0);
      lcd.print("Already Marked");
    }
  }

  // ====== RAHUL ======
  else if (content == uidRahul) {
    if (!rahulMarked) {
      rahulMarked = true;
      totalPresent++;
      lcd.setCursor(0,0);
      lcd.print("Welcome Rahul");
      beep();
    } else {
      lcd.setCursor(0,0);
      lcd.print("Already Marked");
    }
  }

  // ====== AMIT ======
  else if (content == uidAmit) {
    if (!amitMarked) {
      amitMarked = true;
      totalPresent++;
      lcd.setCursor(0,0);
      lcd.print("Welcome Amit");
      beep();
    } else {
      lcd.setCursor(0,0);
      lcd.print("Already Marked");
    }
  }

  // ====== UNKNOWN CARD ======
  else {
    lcd.setCursor(0,0);
    lcd.print("Access Denied");
  }

  // Always show total on second line
  lcd.setCursor(0,1);
  lcd.print("Present: ");
  lcd.print(totalPresent);

  delay(2000);
  showMainScreen();

  mfrc522.PICC_HaltA();
}

void showMainScreen() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Scan Your Card");
  lcd.setCursor(0,1);
  lcd.print("Present: ");
  lcd.print(totalPresent);
}

void beep() {
  digitalWrite(BUZZER, HIGH);
  delay(200);
  digitalWrite(BUZZER, LOW);
}