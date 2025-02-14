# EMV - SMART CARD - READER

This project implements a smart card reader using **C++ and Arduino NANO|UNO**, specifically designed for reading EMV (Europay, Mastercard, and Visa) cards.  It allows interaction with EMV chip cards, enabling reading of card data and potentially performing other EMV-related transactions.

## Introduction

This project provides a foundation for reading data from EMV smart cards using an Arduino microcontroller. It handles the low-level communication protocols required to interact with the card and retrieve information stored on the chip. This can be used for various applications, such as:

* Access control systems
* Point-of-sale (POS) systems
* Personal identification systems

## Features

* Arduino compatibility.
* EMV card reading capabilities.
* Support for ISO 7816 communication protocol.
* Basic data retrieval from the card (e.g., PAN, expiry date).

## Hardware Requirements

* Arduino microcontroller ( Uno, Nano ).

## Software Requirements

* [Nodepp-arduino](https://github.com/NodeppOficial/nodepp-arduino) installed
* [Nodepp](https://github.com/NodeppOficial/nodepp) installed
* Arduino IDE.

## Installation | Arduino

1. Clone this repository: `git clone https://github.com/YOUR_USERNAME/EMV-SMART-CARD-READER.git`.
2. Copy the `example/emv_reader.ino` in the `root`, and open the project in the Arduino IDE.
3. Install [Nodepp-arduino](https://docs.arduino.cc/libraries/nodepp) through the Arduino IDE Library Manager.

## Installation | PC

1. Clone this repository: `git clone https://github.com/YOUR_USERNAME/EMV-SMART-CARD-READER.git`.
2. Copy the `example/emv_reader.cpp` in the `root` as `main.cpp`.
3. Install [Nodepp](https://github.com/NodeppOficial/nodepp) in your PC.
4. Compile it using `g++ -o main main.cpp ; ./main ?DEVICE=ttyUSBX`.

## Usage

1. Upload the emv-reader code to your Arduino board.
2. Compile and run the emv-reader code in your PC
2. Insert an EMV card into the reader.
3. The program will attempt to read | write APDU commands.

## Arduino PINOUTS

* PIN 2 | OUTPUT => VCC Smart Card Pin
* PIN 6 | OUTPUT => RST Smart Card Pin
* PIN 3 | OUTPUT => CLK Smart Card Pin
* PIN 4 | INPUT  => IO  Smart Card Pin
* PIN 5 | OUTPUT => IO  Smart Card Pin

## APDU REFERENCES

* AID  List:   [https://en.wikipedia.org/wiki/EMV]()
* TLV  List:   [https://www.eftlab.com/knowledge-base/complete-list-of-emv-nfc-tags]()
* APDU List:   [https://gist.github.com/hemantvallabh/d24d71a933e7319727cd3daa50ad9f2c]()
* APDU Status: [https://www.eftlab.com/knowledge-base/complete-list-of-apdu-responses]()
