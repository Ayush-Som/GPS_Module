#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define F_CPU 8000000UL  // Assuming your ATmega32 is running at 8MHz
#define BAUD 9600
#define UBRR_VAL ((F_CPU / (16UL * BAUD)) - 1)

// Function to initialize USART communication
void USART_Init(unsigned int ubrr) {
    UBRRH = (unsigned char)(ubrr >> 8);
    UBRRL = (unsigned char)ubrr;
    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

// Function to transmit data over USART
void USART_Transmit(unsigned char data) {
    while (!(UCSRA & (1 << UDRE)));
    UDR = data;
}

// Function to receive data over USART
unsigned char USART_Receive() {
    while (!(UCSRA & (1 << RXC)));
    return UDR;
}

// Function to initialize the GPS module
void GPS_Init() {
    // You might need to configure any specific settings for the GPS module here
}

// Function to read a line from GPS module
void GPS_ReadLine(char* buffer, int buffer_size) {
    int i = 0;
    while (i < buffer_size - 1) {
        char received = USART_Receive();
        if (received == '\r' || received == '\n') {
            if (i == 0) continue; // Skip leading newline characters
            break; // End of line
        }
        buffer[i++] = received;
    }
    buffer[i] = '\0'; // Null-terminate the string
}

// Function to parse GPS data and calculate speed and distance
void Calculate_Speed_Distance() {
    char buffer[128]; // Adjust the buffer size as needed
    GPS_ReadLine(buffer, sizeof(buffer));
    
    // Parse NMEA sentence and extract GPS data
    // Implement parsing logic based on NMEA sentence format
    
    // Calculate speed and distance based on parsed GPS data
    
    // Transmit the calculated values using USART_Transmit
}

int main() {
    USART_Init(UBRR_VAL);
    GPS_Init();
    
    while (1) {
        Calculate_Speed_Distance();
        _delay_ms(1000); // Delay for 1 second
    }
    
    return 0;
}
