# VenodeMCU-ESP8266: IoT Vending Machine with NodeMCU ESP8266

An IoT vending machine project that integrates **NodeMCU ESP8266** with a Laravel backend, using RFID, servo, and LCD components. The system processes transactions by validating RFID cards registered in the database and checks if they have sufficient balance. The NodeMCU communicates with the Laravel API, and transaction data is displayed via a web interface.

## Tech & Tools

![PlatformIO](https://img.shields.io/badge/platformio-FF7F00?style=for-the-badge&logo=platformio&logoColor=white)
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![RFID](https://img.shields.io/badge/RFID-00FF00?style=for-the-badge)
![LCD](https://img.shields.io/badge/LCD-0000FF?style=for-the-badge)
![Servo](https://img.shields.io/badge/Servo-FF4500?style=for-the-badge)

## System Overview

### Key Features
- **RFID Validation**: Verifies the RFID card's balance and credentials from the Laravel API.
- **Servo Motor Control**: Controls the vending machine's servo motor for dispensing items.
- **LCD Display**: Displays transaction details and status.
- **API Integration**: Communicates with the Laravel backend API for card validation and transaction processing.
  
### Backend Repository
The Laravel API backend is available here:  
[VenodeMCU-Laravel](https://github.com/sfmuazam/VenodeMCU-Laravel)

### Hardware Components
- **NodeMCU ESP8266**
- **RFID Reader**
- **Servo Motor**
- **LCD Screen**

## Installation

### Prerequisites
- Install **PlatformIO** in your IDE (e.g., VSCode)
- NodeMCU ESP8266 board
- Laravel backend (set up from the [VenodeMCU-Laravel](https://github.com/sfmuazam/VenodeMCU-Laravel) repository)

### Steps

1. **Clone the Repository**
    ```bash
    git clone https://github.com/sfmuazam/VenodeMCU-ESP8266.git
    cd VenodeMCU-ESP8266
    ```

2. **Install PlatformIO Dependencies**
    PlatformIO will handle dependencies automatically when you build the project.

3. **Update Wi-Fi Credentials and API URL**
    Open the `main.cpp` file and adjust the following lines:
    ```cpp
    const char *ssid = "YOUR_WIFI";         // Your WiFi SSID
    const char *password = "*********";     // Your WiFi Password

    api_url = "http://your-backend-url/api/transaksi";  // Laravel API endpoint
    ```
    - Replace `"YOUR_WIFI"` and `"*********"` with your actual Wi-Fi SSID and password.
    - Set the `api_url` to your Laravel API endpoint for processing transactions.

4. **Build and Upload Code**
    Use PlatformIO to build and upload the code to your **NodeMCU ESP8266**.

5. **Set Up the Hardware**
    Connect the **RFID reader**, **Servo motor**, and **LCD** to the NodeMCU according to your circuit design.

6. **Run the System**
    Once the hardware is set up and the code is uploaded, the system will begin validating RFID cards and displaying transaction information on the LCD.
