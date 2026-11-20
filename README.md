# DoorScan AI

An automated doorway attendance, access alert, and assessment prototype combining an Arduino Uno, HC-SR04 ultrasonic sensor, LED indicators, browser-based webcam face recognition, Web Serial communication, and cloud logging.

## Key Features

* **Proximity Trigger (`150–250 cm`):** HC-SR04 ultrasonic sensor detects approaching individuals and sends `STUDENT\_DETECTED` over serial at `9600` baud.
* **Live Distance \& Face Recognition:** Browser interface (`index.html`) displays live distance readings and runs webcam face registration/recognition.
* **Visual Hardware Feedback:** Activates the **Green LED** (`WELCOME`) for registered users and blinks the **Red LED** (`ALERT`) for unregistered faces.
* **Cloud Logging \& Resilience:** Syncs attendance/quiz records to Google Sheets via a Google Apps Script `doPost(e)` webhook with offline queue support, alongside automated assessment and alert workflows.

## Hardware \& Pinout

* **Microcontroller:** Arduino Uno (`9600` baud)
* **HC-SR04 Ultrasonic Sensor:**

  * `VCC` $\\rightarrow$ `5V`
  * `GND` $\\rightarrow$ `GND`
  * `TRIG` $\\rightarrow$ Pin `9`
  * `ECHO` $\\rightarrow$ Pin `10`
* **Red LED (Unregistered Alert):** Pin `7` (with `100Ω` resistor)
* **Green LED (Registered Welcome):** Pin `6` (with `100Ω` resistor)
* **Camera:** Webcam connected to the host computer

## Repository Structure

* `index.html` — Frontend UI, live distance display, Web Serial integration, face scan workflow, and sync logic
* `doorscan\_arduino.ino` — Arduino sketch for HC-SR04 distance measurement, `STUDENT\_DETECTED` triggers, and Red/Green LED control
* `google\_sheets\_webhook.js` — Google Apps Script `doPost(e)` webhook handler for appending records to Google Sheets
* `README.md` — Project documentation and setup guide

## Setup \& Usage

1. **Flash the Arduino:**

   * Open `doorscan\_arduino.ino` in the Arduino IDE.
   * Select your Arduino Uno board and COM port, then click **Upload**.
   * Close the Arduino Serial Monitor so the COM port is free for the browser.
2. **Set Up Google Sheets Webhook:**

   * Open your target Google Sheet $\\rightarrow$ **Extensions** $\\rightarrow$ **Apps Script**.
   * Paste the code from `google\_sheets\_webhook.js`, save, and click **Deploy** $\\rightarrow$ **New deployment** (**Web app**, Execute as: **Me**, Who has access: **Anyone**).
   * Copy the deployed Web App URL into `index.html`.
3. **Run the Web Interface:**

   * Open `index.html` in **Google Chrome** or **Microsoft Edge**.
   * Click **Connect Arduino (USB)**, select the Arduino COM port, and wait \~2 seconds for board reset.
   * Enter the `150–250 cm` detection zone (or use the manual scan trigger) to test registered and unregistered face flows.

## Demo Video

* **Demo Video (2–3 mins):** https://drive.google.com/file/d/1Lab0rVG1mcvbeX42xRIurQj1QoDeqZZB/view?usp=sharing

## Team

* Jishnu Deshpande
* Nihar S
* Sathwik R
* Jeevan D

