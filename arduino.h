#ifndef ARDUINO_H
#define ARDUINO_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>
#include <QString>

class arduino {
public:
    arduino();               // Constructor
    ~arduino();              // Destructor

    int connect_arduino();   // Connect to the Arduino device
    int close_arduino();     // Close the Arduino connection
    QByteArray read_from_arduino();  // Read data from Arduino
    int write_to_arduino(QByteArray d); // Write data to Arduino
    int show_message_on_lcd(const QString& message); // Display a message on the LCD screen connected to Arduino
    QString get_arduino_port_name() const {
          return arduino_port_name;  // Return the port name where Arduino is connected
      }
QString code;
private:
    QSerialPort *serial;  // Serial port object for communication
    QByteArray data;      // Data read from Arduino
    QString arduino_port_name;  // Store the port name for the Arduino
    bool arduino_is_available = false;  // Flag to check if Arduino is available

    // These identifiers are specific to Arduino Uno. You can replace them with your device's vendor and product IDs
    static const int arduino_uno_vendor_id = 0x2341;  // Vendor ID for Arduino
    static const int arduino_uno_producy_id = 0x0043; // Product ID for Arduino Uno
};

#endif // ARDUINO_H
