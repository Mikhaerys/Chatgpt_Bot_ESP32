#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

#include "display.h"
#include "music.h"

#define BOTtoken "Telegram Bot token"

const char* ssid = "Wifi name";
const char* password = "Wifi Password";
const char* chatgpt_token = "OpenAi api Key";

// response and question variables
String chatgpt_Q;
String chatgpt_A;
uint16_t dataStart = 0;
uint16_t dataEnd = 0;

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOTtoken, secured_client);
String chat_id;

const unsigned long botRequestDelay = 1000;
unsigned long lastTimeBotRan;


void setup() {

  Serial.begin(115200);
  startDisplay();
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  while (!Serial);

  // wait for WiFi connection
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  displayText("Conectado");
  delay(1000);
  displayText("Abra el chat para enviar un mensaje");
}


void loop() {
  if (millis() - lastTimeBotRan  > botRequestDelay) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    Serial.println(numNewMessages);
    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }

  delay(5000);
}


void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++) {
    chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;
    // Here you can put if statements so that something happens according to the text sent.
     
    if(text == "/start"){
      displayText("Good morning, ask me whatever you want");
      bot.sendMessage(chat_id, "Good morning, ask me whatever you want", "");
    }
    else if (text == "/Rickroll"){
      showImage(epd_bitmap_Rick);
      playMelody(melody1);
    }
    else if (text == "/Whistle"){
      showImage(epd_bitmap_josh_hutcherson_whistle);
      playMelody(melody2);
    }
    else if (text == "/Alfredo"){
      showImage(epd_bitmap_Alfredo);
      playMelody(melody3);
    }
    else{
      chatgpt_Q = text;
      displayText("Waiting for Response");
      ChatGPT();
      bot.sendMessage(chat_id, chatgpt_A, "");
    }
  }
}


void ChatGPT() {
  HTTPClient https;

  Serial.print("[HTTPS] begin...\n");
  if (https.begin("https://api.openai.com/v1/chat/completions")) {  // HTTPS

    https.addHeader("Content-Type", "application/json");
    String token_key = String("Bearer ") + chatgpt_token;
    https.addHeader("Authorization", token_key);

    String payload = String("{\"model\": \"gpt-3.5-turbo\", \"messages\": [{\"role\": \"user\", \"content\": \"") + chatgpt_Q + String(" \"}], \"temperature\": 0.7, \"max_tokens\": 40}");  //Instead of TEXT as Payload, can be JSON as Paylaod

    Serial.print("[HTTPS] GET...\n");

    // Send Request
    int httpCode = https.POST(payload);
    payload = "";

    // Get the answer
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
      String payload = https.getString();
      dataStart = payload.indexOf("\"content\": \"") + 12;
      dataEnd = payload.indexOf("\"", dataStart);
      chatgpt_A = payload.substring(dataStart, dataEnd);
      Serial.print(chatgpt_A);
      displayText(chatgpt_A);
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\n");
  }
}