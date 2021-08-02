#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial


char auth[] = "ent8Ke0s5mndBknW2verPku5Rai02P-F";

const char* NAME;
const char* ID;


String Event_Name = "fingerprint";

String Key = "41Ycg0FJDuQD_rr9IQY4FxeR5yYgaSWqtgli0jSZcN";

// Replace with your unique IFTTT URL resource
String resource = "/trigger/" + Event_Name + "/with/key/" + Key;

// Maker Webhooks IFTTT
const char* server = "maker.ifttt.com";

// Replace with your SSID and Password
char* ssid     = "Forcabarca";
const char* password = "bidariniwas";

const int buzzer = D4;
SoftwareSerial mySerial(13, 15);//Fingerprint sensor TX attached to D7 (GPIO13), RX - to D8 (GPIO15) of Nodemcu board

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t id;

void setup()
{
  Blynk.begin(auth, ssid, password);
  pinMode(buzzer, OUTPUT);
  Serial.begin(115200);
  delay(100);
  // For Yun/Leo/Micro/Zero/...

  Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) {
      delay(1);
    }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  //  Serial.println("Waiting for valid finger...");

  Serial.print("Connecting to: ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(".");

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect, going back to sleep");
  }

  Serial.print("WiFi connected in: ");
  Serial.print(millis());
  Serial.print(", IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()                     // run over and over again
{
  Blynk.run();

  getFingerprintIDez();
  if (finger.fingerID == 1) {

    //    Serial.print("!!--");
    Serial.println(finger.fingerID);
    NAME = "Bishal";
    ID = "1";
    if (finger.confidence >= 60) {
      Serial.println(NAME); Serial.print("Attendace is Marked. ");
      delay(1000);
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
      Blynk.notify("Attendance Sucessfully Register for Bishal.");
      makeIFTTTRequest();


    }

  }

  if (finger.fingerID == 2 ) {
    Serial.print("");
    Serial.println(finger.fingerID);
    //    digitalWrite(2, LOW);
    NAME = "Shrawan";
    ID = "2";
    if (finger.confidence >= 60) {
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      delay(1000);
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
      Blynk.notify("Attendance Sucessfully Register for Shrawan.");
      makeIFTTTRequest();
    }
  }
  if (finger.fingerID == 3 ) {
    //    Serial.print("!!--");
    Serial.println(finger.fingerID);
    //    digitalWrite(2, LOW);
    NAME = "Abhishek";
    ID = "3";
    if (finger.confidence >= 60) {
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      delay(1000);
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
      Blynk.notify("Attendance Sucessfully Register for Abhishek");
      makeIFTTTRequest();

    }
  }
  if (finger.fingerID == 4 ) {
    //    Serial.print("!!--");
    Serial.println(finger.fingerID);
    //    digitalWrite(2, LOW);
    NAME = "Neerajan";
    ID = "4";
    if (finger.confidence >= 60) {
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      delay(1000);
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
      Blynk.notify("Attendance Sucessfully Register  for Neerajan");
      makeIFTTTRequest();

    }
  }
  if (finger.fingerID == 5 ) {
    //    Serial.print("!!--");
    Serial.println(finger.fingerID);
    //    digitalWrite(2, LOW);
    NAME = "Monkey D. Luffy";
    ID = "5";
    if (finger.confidence >= 60) {
      Serial.print("Attendace Marked for "); Serial.println(NAME);
      delay(1000);
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
      Blynk.notify("Attendance Sucessfully Register of Monkey.D Luffy.");
      makeIFTTTRequest();

    }else{
      digitalWrite(buzzer, HIGH);
      delay(2000);
      digitalWrite(buzzer, LOW);
      delay(2000);
    }
  }
  finger.fingerID = 0;
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
//      delay(1000);
//      digitalWrite(buzzer, HIGH);
//      delay(2000);
//      digitalWrite(buzzer, LOW);
//      delay(2000);

      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      delay(1000);
      digitalWrite(buzzer, HIGH);
      delay(2000);
      digitalWrite(buzzer, LOW);
      delay(2000);
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      delay(1000);
      digitalWrite(buzzer, HIGH);
      delay(2000);
      digitalWrite(buzzer, LOW);
      delay(2000);
      return p;
    default:
      Serial.println("Unknown error");
      delay(1000);
      digitalWrite(buzzer, HIGH);
      delay(2000);
      digitalWrite(buzzer, LOW);
      delay(2000);
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      delay(1000);
      digitalWrite(buzzer, HIGH);
      delay(2000);
      digitalWrite(buzzer, LOW);
      delay(2000);
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      delay(1000);
      digitalWrite(buzzer, HIGH);
      delay(2000);
      digitalWrite(buzzer, LOW);
      delay(2000);
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      delay(1000);
      digitalWrite(buzzer, HIGH);
      delay(2000);
      digitalWrite(buzzer, LOW);
      delay(2000);
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      delay(1000);
      digitalWrite(buzzer, HIGH);
      delay(2000);
      digitalWrite(buzzer, LOW);
      delay(2000);
      return p;
    default:
      Serial.println("Unknown error");
      delay(1000);
      digitalWrite(buzzer, HIGH);
      delay(2000);
      digitalWrite(buzzer, LOW);
      delay(2000);
      return p;
  }

  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}

// Make an HTTP request to the IFTTT web service
void makeIFTTTRequest() {
  Serial.print("Connecting to ");
  Serial.print(server);

  WiFiClient client;
  int retries = 5;
  while (!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if (!!!client.connected()) {
    Serial.println("Failed to connect...");
  }

  Serial.print("Request resource: ");
  Serial.println(resource);


  String jsonObject = String("{\"value1\":\"") + NAME + "\",\"value2\":\"" + ID
                      + "\"}";

  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server);
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);

  int timeout = 5 * 10; // 5 seconds
  while (!!!client.available() && (timeout-- > 0)) {
    delay(100);
  }
  if (!!!client.available()) {
    Serial.println("No response...");
  }
  while (client.available()) {
    Serial.write(client.read());
  }

  Serial.println("\n Scanner Ready to go.....");
  client.stop();
}
