#include <SPI.h>
#include <LoRa.h>
#include <U8x8lib.h>

#define NSS_PIN 10
#define RST_PIN 9
#define DIO0_PIN 2
#define BUZZER_PIN 3

U8X8_SSD1306_128X64_NONAME_HW_I2C oled(U8X8_PIN_NONE);

unsigned long lastPacketTime = 0;
const unsigned long maxSilentTime = 10000;
void(* resetFunc) (void) = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  oled.begin();
  oled.setFont(u8x8_font_chroma48medium8_r);
  oled.clear();
  oled.drawString(0, 1, "LoRa Receiver");

  LoRa.setPins(NSS_PIN, RST_PIN, DIO0_PIN);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa Init Failed!");
    oled.drawString(0, 3, "LoRa Init Failed");
    while (1);
  }

  Serial.println("LoRa Ready");
  oled.drawString(0, 3, "LoRa Ready");
  delay(1000);
  oled.clear();
  lastPacketTime = millis();
}

void loop() {
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    String received = LoRa.readStringUntil('\n');

    // Split message on ":" → expect 7 parts
    int parts[6]; float temp = 0, humid = 0;
    int p1 = received.indexOf(':');
    int p2 = received.indexOf(':', p1 + 1);
    int p3 = received.indexOf(':', p2 + 1);
    int p4 = received.indexOf(':', p3 + 1);
    int p5 = received.indexOf(':', p4 + 1);
    int p6 = received.indexOf(':', p5 + 1);

    if (p1 > 0 && p6 > p5) {
      int packetNum = received.substring(1, p1).toInt();
      int gas = received.substring(p1 + 1, p2).toInt();
      temp = received.substring(p2 + 1, p3).toFloat();
      humid = received.substring(p3 + 1, p4).toFloat();
      int ax = received.substring(p4 + 1, p5).toInt();
      int ay = received.substring(p5 + 1, p6).toInt();
      int az = received.substring(p6 + 1).toInt();

      // Serial Output
      Serial.print("Packet #"); Serial.print(packetNum);
      Serial.print(" | Gas: "); Serial.print(gas);
      Serial.print(" | Temp: "); Serial.print(temp);
      Serial.print("C | Humid: "); Serial.print(humid);
      Serial.print("% | Accel: ");
      Serial.print(ax); Serial.print(", ");
      Serial.print(ay); Serial.print(", ");
      Serial.println(az);

      // OLED Output
      oled.clear();
      oled.setCursor(0, 1);
      oled.print("Pkt: "); oled.print(packetNum);
      oled.setCursor(0, 2);
      oled.print("Gas: "); oled.print(gas);
      oled.setCursor(0, 3);
      oled.print("Tmp: "); oled.print(temp, 1);

      // Buzzer
      digitalWrite(BUZZER_PIN, gas > 400 ? HIGH : LOW);
      lastPacketTime = millis();
    } else {
      Serial.println("Corrupted packet: " + received);
    }
  }

  if (millis() - lastPacketTime > maxSilentTime) {
    Serial.println("No packets for 10s. Restarting...");
    oled.clear();
    oled.drawString(0, 4, "Restarting...");
    delay(1000);
    resetFunc();
  }
}