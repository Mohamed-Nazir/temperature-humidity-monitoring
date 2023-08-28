#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 15
#define DHTTYPE DHT11
// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "HUAWEI Y6"
#define WIFI_PASSWORD "0606nazir"

// Insert Firebase project API Key
#define API_KEY "AIzaSyBL_BvSVsZO6krMQSEm1G7d9BOvMrn3pM8"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://esp-firebase-app-default-rtdb.europe-west1.firebasedatabase.app/"

#define USER_EMAIL "felixndao@esp.sn"
#define USER_PASSWORD "passer"
// Define Firebase Data object
FirebaseData fbdo;
DHT dht(DHTPIN, DHTTYPE);
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
String uid;
int temperature, humidity;
void setup()
{
    Serial.begin(115200);
    dht.begin();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    /* Assign the api key (required) */
    config.api_key = API_KEY;

    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    /* Assign the RTDB URL (required) */
    config.database_url = DATABASE_URL;

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    Serial.println("Getting User UID");
    while ((auth.token.uid) == "")
    {
        Serial.print('.');
        delay(1000);
    }
    Serial.print("Get user UID");
    uid = auth.token.uid.c_str();
    Serial.print("User UID: ");
    Serial.println(uid);
}

void loop()
{
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    if (Firebase.ready() && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0))
    {
        sendDataPrevMillis = millis();
        // Write an Int number on the database path test/int
        if (Firebase.RTDB.setInt(&fbdo, "/bd/temperature", temperature))
        {
            Serial.println("Données transmises avec succés !");
            Serial.println("Température (° C): " + temperature);
            Serial.println("PATH: " + fbdo.dataPath());
            Serial.println("TYPE: " + fbdo.dataType());
        }
        else
        {
            Serial.println("Données non transmises");
            Serial.println("RAISON: " + fbdo.errorReason());
        }

        // Write an Float number on the database path test/float
        if (Firebase.RTDB.setInt(&fbdo, "/bd/humidity", humidity))
        {
            Serial.println("Données transmises avec succés !");
            Serial.println("Humidity (%): " + humidity);
            Serial.println("PATH: " + fbdo.dataPath());
            Serial.println("TYPE: " + fbdo.dataType());
        }
        else
        {
            Serial.println("Données non transmises");
            Serial.println("RAISON: " + fbdo.errorReason());
        }
        count++;
        // Firebase.RTDB.setInt(&fbdo, "/bd/numberOfEnrg", +count);
    }
}
