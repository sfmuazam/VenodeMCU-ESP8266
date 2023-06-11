#include <Arduino.h>
#include <Servo.h> // Library untuk Servo
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define RST_PIN D1
#define SDA_PIN D2

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SDA_PIN, RST_PIN);
Servo myservo; // Inisialisasi objek Servo
const char *ssid = "ARDHANI KOST";
const char *password = "ardhani2813";
String content = "";

void setup()
{
  // myservo.attach(D6); // Pin Servo dihubungkan ke pin D1 pada NodeMCU
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Wire.begin(2, 0);

  myservo.attach(D0);
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting..");
  }
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("");
  lcd.print("Tempelkan Kartu");
  Serial.println("Tempelkan Kartu");
}

void scrollMessage(int row, String message, int delayTime, int totalColumns)
{
  for (int i = 0; i < totalColumns; i++)
  {
    message = " " + message;
  }
  message = message + " ";
  for (int position = 0; position < message.length(); position++)
  {
    lcd.setCursor(0, row);
    lcd.print(message.substring(position, position + totalColumns));
    delay(delayTime);
  }
}

void parseJson(String cts)
{
  WiFiClient client;
  HTTPClient http;
  http.begin(client, "http://192.168.1.12:8080/vendmcu/public/api/transaksi");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST("uid=" + cts);
  delay(100);
  if (httpResponseCode > 0)
  {
    String response = http.getString();
    // Serial.println(response);
    char json[500];
    response.toCharArray(json, 500);
    StaticJsonDocument<200> doc;
    deserializeJson(doc, json);

    const char *status = doc["status"];
    const char *nama = doc["pelanggan"]["nama"];
    int saldo_sebelum = doc["pelanggan"]["saldo"];
    int nilai_transaksi = doc["nilai_transaksi"];
    int saldo_sekarang = doc["sisa_saldo"];

    Serial.println("=============== HASIL PARSING RESPONSE ===============");
    Serial.print("Status Transaksi = ");
    Serial.println(status);
    Serial.print("Nama Pengguna = ");
    Serial.println(nama);
    Serial.print("Saldo Sebelum = ");
    Serial.println(saldo_sebelum);
    Serial.print("Nilai Transaksi = ");
    Serial.println(nilai_transaksi);
    Serial.print("Saldo Sekarang = ");
    Serial.println(saldo_sekarang);
    Serial.println("======================================================");
    lcd.clear();
    
    if (String(status) == "Transaksi Sukses!")
    {
      lcd.print(status);
      myservo.write(180);
      delay(1000);
      myservo.write(90);
      delay(50);
      scrollMessage(1, "Sisa Saldo: " + String(saldo_sekarang), 200, 16);
    }
    else
    {
      scrollMessage(0, status, 200, 16);
      if (String(status) == "Saldo Tidak Cukup!")
      {
        scrollMessage(1, "Sisa Saldo: " + String(saldo_sekarang), 200, 16);
      }
      
    }
    lcd.clear();
  }
  else
  {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
    scrollMessage(0, "Transaksi Gagal", 200, 16);
  }
  delay(1000);
  http.end();
}

void loop()
{
  content = "";
  if (WiFi.status() == WL_CONNECTED)
  {
    if (!mfrc522.PICC_IsNewCardPresent())
    {
      return;
    }

    if (!mfrc522.PICC_ReadCardSerial())
    {
      return;
    }

    Serial.print("UID tag :");

    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }

    content.toUpperCase();

    Serial.println();
    parseJson(content);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tempelkan Kartu");
  }
  else
  {
    Serial.println("Error in WiFi connection");
  }
}
