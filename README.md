# ESP32-Wi-Fi-HTTP-Client
Overview

This project demonstrates how to connect an ESP32 to a Wi-Fi network and communicate with a remote server using HTTP requests.

The application automatically connects to a wireless network, monitors connection events, retrieves network configuration information, and sends data to a server through HTTP POST requests.

Features
Wi-Fi station mode connection
Automatic reconnection on network loss
Network information display
HTTP client implementation
HTTP POST request support
FreeRTOS task management
ESP-IDF development framework
Hardware Requirements
ESP32 Development Board
USB Cable
Wi-Fi Access Point
Software Requirements
ESP-IDF
Visual Studio Code 
ESP32 Toolchain


Working Principle
Initialize the network stack.
Connect to the configured Wi-Fi network.
Wait until an IP address is assigned.
Display network configuration.
Initialize the HTTP client.
Send data to a remote server using an HTTP POST request.
Process server responses.


Technologies Used
C Programming Language
ESP-IDF
FreeRTOS
Wi-Fi Driver
TCP/IP Stack
HTTP Client API
