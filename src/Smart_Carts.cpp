#include<ESP8266WiFi.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include<SPI.h>
#include<MFRC522.h>

#define SS_PIN D5
#define RST_PIN D6

LiquidCrystal_I2C lcd(0x27, 16, 2);

const char *SSID = "TT_IOT";
const char *PASSWORD = "ttiot2019";

char input[10];
int count = 0;
int a;
int p1 = 0, p2 = 0, p3 = 0, p4 = 0, p5 = 0;
int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0;
double total = 0;
int count_prod = 0;
int status = 0;
int out = 0;

MFRC522 mfrc522(SS_PIN, RST_PIN);
String ID_TAG;
WiFiServer server(80);

void readRFID(byte *buffer, byte bufferSize) {
    ID_TAG = "";
    for(byte i = 0;i<bufferSize; i++) {
        ID_TAG = ID_TAG+String(buffer[i], HEX);
        }
}

void setup() {
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();
    Wire.begin(D2, D1);
    
    lcd.init();   
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print (" Smart Cart");
    lcd.setCursor(0, 1);
    lcd.print("Luck Project");
    Serial.print("Connecting to: ");
    Serial.println(SSID);
    WiFi.begin(SSID, PASSWORD);

    while(WiFi.status() !=WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("Connected WIFI");
    Serial.println("IP address:");
    Serial.println(WiFi.localIP());
    server.begin();
    delay(2000);
    lcd.clear();
    lcd.print("Happy Shopping");
    lcd.setCursor(0, 1);
    lcd.print("Happy Enjoy");
    server.begin();
    delay(2000);
    lcd.clear();
    lcd.print("Item = 0");
    lcd.setCursor(0, 1);
    lcd.print("Total = Rp.0");

}

void send() {
  WiFiClient client = server.available();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");  
  client.println("Refresh: 5");  
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");  
  client.println("<title>e-Cart Lucky Project </title></head><style type=\"text/css\">");     
  client.println("table{border-collapse: collapse;}th {background-color:rgb(0, 248, 62) ;color: white;}table,td {border: 4px solid black;font-size: x-large;");     
  client.println("text-align:center;border-style: groove;border-color: rgb(0, 4, 255);}</style><body><center>");     
  client.println("<h1>Smart Shopping Cart Lucky Project </h1><br><br><table style=\"width: 1200px;height: 450px;\">");
  client.println("<tr><th>ITEMS</th><th>QUANTITY</th><th>COST</th></tr>");
  client.println("<tr><td>Gula pasir (1kg)</td><td>"+String(p1)+"</td><td>"+String(c1)+"</td></tr>");     
  client.println("<tr><td>Terigu (1kg)</td><td>"+String(p2)+"</td><td>"+String(c2)+"</td></tr>");
  client.println("<tr><td>Minyak (1L)</td><td>"+String(p3)+"</td><td>"+String(c3)+"</td></tr>");  
  client.println("<tr><td>Wafer Tanggo (1Pcs)</td><td>"+String(p4)+"</td><td>"+String(c4)+"</td></tr>");
  client.println("<tr><th>Grand Total</th><th>"+String(count_prod)+"</th><th>"+String(total)+"</th></tr>");     
  client.println("</table><br><input type=\"button\" name=\"Bayar\" value=\"Bayar\" style=\"width: 200px;height: 50px\"></center></body></html>");
  client.println("<meta http-equiv=\"refresh\" content=\"2\">");
  delay(5000);

  lcd.clear();
  lcd.print("Item = ");
  lcd.print(count_prod);
  lcd.setCursor(0, 1);
  lcd.print("Total = Rp.");
  lcd.print(total);
    }

void loop() {
    if(!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        return;
    }
    readRFID(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.print("UID RFID :");
    Serial.println(ID_TAG);

    if (ID_TAG== "e745ba15") {
    lcd.setCursor(0, 0);
    lcd.print("Rice 1Kg           ");
    lcd.setCursor(0, 1);
    lcd.print("Rp.14.000,-        ");
    p1++;
    total = total + 14000;
    count_prod++;
    c1=p1*14000;
    send();
    }

    else if (ID_TAG== "d6e3f9a2") {
    lcd.setCursor(0, 0);
    lcd.print("Sugar 1Kg           ");
    lcd.setCursor(0, 1);
    lcd.print("Rp.12.000,-         ");
    p2++;
    total = total + 12000;
    count_prod++;
    c2=p2*12000;
    send();
    }
    
    else if (ID_TAG== "f8a1b4c7") {
    lcd.setCursor(0, 0);
    lcd.print("Flavour 1Kg         ");
    lcd.setCursor(0, 1);
    lcd.print("Rp.15.000,-         ");
    p3++;
    total = total + 15000;
    count_prod++;
    c3=p3*15000;
    send();
    }

    else if (ID_TAG== "c9d2e5b3") {
    lcd.setCursor(0, 0);
    lcd.print("Sunlight 500mL      ");
    lcd.setCursor(0, 1);
    lcd.print("Rp.10.000,-         ");
    p4++;
    total = total + 10000;
    count_prod++;
    c4=p4*10000;
    send();
    }

    else if (ID_TAG== "b1e4a6f8") {
    lcd.setCursor(0, 0);
    lcd.print("Frying Oil 1L       ");
    lcd.setCursor(0, 1);
    lcd.print("Rp.18.000,-         ");
    p5++;
    total = total + 18000;
    count_prod++;
    c5=p5*18000;
    send();
    }
}