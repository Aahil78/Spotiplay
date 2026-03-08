#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <SpotifyEsp32.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#include <Adafruit_NeoPixel.h>

//////////////// WIFI //////////////////

const char* ssid = "YOUR_WIFI"; //Wi-Fi Name
const char* password = "YOUR_PASS"; //Wi-Fi Password

//////////////// SPOTIFY //////////////////

//Obtain all from Spotify Developer Dashboard
#define CLIENT_ID "YOUR_CLIENT_ID"
#define CLIENT_SECRET "YOUR_CLIENT_SECRET"
#define REFRESH_TOKEN "YOUR_REFRESH_TOKEN"

SpotifyEsp32 spotify(CLIENT_ID, CLIENT_SECRET, REFRESH_TOKEN);

//////////////// DISPLAY //////////////////

#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

//////////////// LED STRIP //////////////////

#define LED_PIN 18
#define LED_COUNT 10

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

//////////////// Switches //////////////////

#define BTN_VOL_UP 1
#define BTN_VOL_DOWN 2
#define BTN_PREV 3
#define BTN_PLAY 4
#define BTN_NEXT 5

//////////////// VARIABLES //////////////////

String trackName = "";
String artistName = "";
String albumArt = "";

int duration_ms = 0;
int progress_ms = 0;
bool isPlaying = false;

unsigned long lastUpdate = 0;

//////////////// FUNCTIONS //////////////////

void connectWiFi()
{
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
}

//////////////// DRAW TEXT //////////////////

void drawTrack()
{
  tft.fillScreen(ILI9341_BLACK);

  tft.setTextColor(ILI9341_WHITE);

  tft.setTextSize(2);
  tft.setCursor(10, 20);
  tft.println(trackName);

  tft.setTextSize(2);
  tft.setCursor(10, 50);
  tft.println(artistName);
}

//////////////// TIME FORMAT //////////////////

String formatTime(int ms)
{
  int total = ms / 1000;
  int minutes = total / 60;
  int seconds = total % 60;

  char buffer[10];
  sprintf(buffer, "%d:%02d", minutes, seconds);

  return String(buffer);
}

void drawTime()
{
  tft.fillRect(0, 200, 320, 40, ILI9341_BLACK);

  tft.setCursor(10, 210);
  tft.setTextSize(2);

  String current = formatTime(progress_ms);
  String total = formatTime(duration_ms);

  tft.print(current + "/" + total);
}

//////////////// LED AMBIENT //////////////////

void setAmbientColor(uint8_t r, uint8_t g, uint8_t b)
{
  for (int i = 0; i < LED_COUNT; i++)
  {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }

  strip.show();
}

//////////////// COVER COLOR //////////////////

void updateColorFromCover()
{
  // simplified random color placeholder
  uint8_t r = random(80,255);
  uint8_t g = random(80,255);
  uint8_t b = random(80,255);

  setAmbientColor(r,g,b);
}

//////////////// SPOTIFY UPDATE //////////////////

void updateSpotify()
{
  CurrentlyPlaying currentlyPlaying;

  if (spotify.getCurrentlyPlaying(currentlyPlaying))
  {
    trackName = currentlyPlaying.trackName;
    artistName = currentlyPlaying.artistName;
    albumArt = currentlyPlaying.albumArt;

    duration_ms = currentlyPlaying.durationMs;
    progress_ms = currentlyPlaying.progressMs;
    isPlaying = currentlyPlaying.isPlaying;

    drawTrack();
    drawTime();

    updateColorFromCover();
  }
}

//////////////// BUTTON HANDLER //////////////////

void handleButtons()
{
  if (!digitalRead(BTN_PLAY))
  {
    spotify.togglePlay();
    delay(300);
  }

  if (!digitalRead(BTN_NEXT))
  {
    spotify.nextTrack();
    delay(300);
  }

  if (!digitalRead(BTN_PREV))
  {
    spotify.previousTrack();
    delay(300);
  }

  if (!digitalRead(BTN_VOL_UP))
  {
    spotify.volumeUp();
    delay(200);
  }

  if (!digitalRead(BTN_VOL_DOWN))
  {
    spotify.volumeDown();
    delay(200);
  }
}

//////////////// SETUP //////////////////

void setup()
{
  Serial.begin(115200);

  pinMode(BTN_VOL_UP, INPUT_PULLUP);
  pinMode(BTN_VOL_DOWN, INPUT_PULLUP);
  pinMode(BTN_PREV, INPUT_PULLUP);
  pinMode(BTN_PLAY, INPUT_PULLUP);
  pinMode(BTN_NEXT, INPUT_PULLUP);

  tft.begin();
  tft.setRotation(1);

  strip.begin();
  strip.show();

  connectWiFi();

  spotify.begin();
}

//////////////// LOOP //////////////////

void loop()
{
  handleButtons();

  if (millis() - lastUpdate > 2000)
  {
    updateSpotify();
    lastUpdate = millis();
  }

  if (isPlaying)
  {
    progress_ms += 1000;
    drawTime();
  }

  delay(1000);
}
