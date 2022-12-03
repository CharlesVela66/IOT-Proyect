#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
const char* ssid = "Nombre_De_Tu_Red";
const char* password = "Contraseña_De_Tu_Red";
const char* host= "IP_De_Tu_Red"; // Para obtener la IP te vas al command prompt de tu computadora y escribes "ipconfig" (sin comillas) en IPv4 Address veras tu IP
const int port = 80;
const int watchdog = 5000;
unsigned long previousMillis = millis();

#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 5 // D1
#define DHTTYPE DHT11
#define myled D8
#define myled2 D5
#define myled3 D0

DHT dht(DHTPIN, DHTTYPE);

float temp, hume;
String data;

WiFiClient client;
HTTPClient http;

void setup() {
  Serial.begin(115200);

  pinMode(myled, OUTPUT);
  digitalWrite(myled,LOW);
  pinMode(myled2, OUTPUT);
  digitalWrite(myled2,LOW);
  pinMode(myled3, OUTPUT);
  pinMode(myled3, HIGH);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Wifi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(myled, HIGH);

  unsigned long currentMillis = millis();
  
  if ( currentMillis - previousMillis > watchdog ){
    previousMillis = currentMillis;
    if (!client.connect(host, port)){
      Serial.println("Fallo al conectar");
      delay(1000);
      return;
    }

  }
  delay(2000);
  
  dht.begin();
}

void loop() {

  http.begin(client, "http://172.20.10.2/FinalProyect/index.php");

  hume = dht.readHumidity();
  temp = dht.readTemperature();

  if(isnan(hume) || isnan(temp)) {
    Serial.println("Falla en intentar leer el sensor DHT!");
    delay(5000);
    return;
  }

  if (temp > 20.0 || hume > 85.0){
    digitalWrite(myled3, HIGH);
  }
  else {
    digitalWrite(myled3, LOW);
  }

  Serial.println("Temperatura: " + String(temp) + " C" + " Humedad: " + String(hume) + "%");

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > watchdog){
    
    data = "temp=" + String(temp) + "&hume=" + String(hume);
    //Serial.println(data);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST(data);
    Serial.println(httpCode);
    if (httpCode == 200){
      digitalWrite(myled2, HIGH);
    }
    else {
      digitalWrite (myled2, LOW);
    }
    http.end();

  
  delay(10000);
  //delay(300000);
  }
}
