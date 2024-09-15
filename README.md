# Telegram ChatGPT Bot on ESP32

This project implements a Telegram chatbot running on an ESP32 microcontroller. It allows users to send queries to the ChatGPT API and receive responses. The bot displays responses both in the Telegram chat and on an SPI OLED screen connected to the ESP32.

## Features

- Connects to WiFi and Telegram Bot API
- Interfaces with ChatGPT API for generating responses
- Displays responses on a Telegram chat and an OLED screen
- Includes additional fun commands for playing melodies and displaying images

## Hardware Requirements

- ESP32 development board
- SSD1306 OLED display (128x64 pixels)
- Buzzer (connected to pin 15)

## Software Dependencies

- Arduino core for ESP32
- WiFi library
- HTTPClient library
- SPI library
- Wire library
- Adafruit_GFX library
- Adafruit_SSD1306 library
- WiFiClientSecure library
- UniversalTelegramBot library
- ArduinoJson library

## Setup

1. Install the required libraries in your Arduino IDE.
2. Replace the following placeholders in the code with your actual credentials:
   - `"Wifi name"` with your WiFi SSID
   - `"Wifi Password"` with your WiFi password
   - `"Telegram Bot token"` with your Telegram Bot token
   - `"OpenAi api Key"` with your OpenAI API key
3. Upload the code to your ESP32 board.

## Usage

1. Start a chat with your Telegram bot.
2. Send `/start` to begin interaction with the bot.
3. Send any message to get a response from ChatGPT.
4. Use special commands for additional features:
   - `/Rickroll`: Plays the "Never Gonna Give You Up" melody and displays an image
   - `/Whistle`: Plays a whistle melody and displays an image
   - `/Alfredo`: Plays a custom melody and displays an image

## Notes

- The OLED display is used to show status messages and responses.
- The buzzer is used to play melodies for special commands.
- Ensure all connections are correct and the ESP32 is properly powered.

## Customization

You can modify the code to add more commands, change the melodies, or update the images displayed on the OLED screen.

## Troubleshooting

If you encounter any issues:
- Check your WiFi and API credentials
- Ensure all libraries are correctly installed
- Verify hardware connections

## Contributing

Contributions through pull requests are encouraged. For significant modifications, please start by opening an issue to discuss the changes you'd like to make.

## License

This project is open-source. Please check the individual libraries used for their respective licenses.

## Disclaimer

This project uses third-party APIs. Ensure you comply with their terms of service and usage policies.
