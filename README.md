# Spotiplay
A spotify display with RGB Backlight, 2.8" Touchscreen, and media keys. I made this because I have always wanted to have a mini spotify "dashboard" as it was really cool to have and it's a nice Quality of Life improvement.

## How it works:
Basicslly, it uses Wi-Fi and a Spotify API Key to see what you are playing, fetch the cover art and metadata, and control your music. It fetches the metadata of the current song youu are playing and displays it on the screen, then if any key is pressed, it will see that a key is pressed and performs the corresponding action via API. 

## Code:
The code is written in Arduino IDE, it can be found in the `Code` folder. 

## CAD:
The CAD was made for this in OnShape. Models can be found in the `3D Models` folder.
[CAD Link](https://cad.onshape.com/documents/b8106d655d1fdcd5106cc52a/w/5e26d62ee724bca1cb348ddc/e/785bae49cdaf2f3d98875e78?renderMode=0&uiState=69adb7d1b4e6ea33d7a65cff)

## Pin Connections:

Connect these pins to your components.

| Function   | GPIO |
| ---------- | ---- |
| TFT CS     | 10   |
| TFT DC     | 9    |
| TFT RST    | 8    |
| TFT MOSI   | 11   |
| TFT SCLK   | 12   |
| LED Strip  | 18   |
| Vol +      | 1    |
| Vol -      | 2    |
| Rewind     | 3    |
| Play/Pause | 4    |
| Next       | 5    |

<img width="1190" height="845" alt="SCH_Schematic1_1-P1_2026-03-09" src="https://github.com/user-attachments/assets/6693b37b-8191-4881-ba39-19514da81683" />

## Images:

<img width="410" height="467" alt="image" src="https://github.com/user-attachments/assets/3b7d17cf-7d1c-471a-9ecb-5aa2ed4df781" />
<img width="652" height="410" alt="image" src="https://github.com/user-attachments/assets/e5e6347b-38a8-4219-a147-8cf835910cfd" />
<img width="366" height="531" alt="image" src="https://github.com/user-attachments/assets/fe051f42-70df-487d-9bd3-f6c01836c8c0" />
<img width="412" height="487" alt="image" src="https://github.com/user-attachments/assets/373580cf-1a70-4613-acc2-300115167d61" />
