// lcd.c
#include "include.h"
#include "lcd.h"

void lcd_command(unsigned char cmd) {
    RS = 0;  // Command mode
    RW = 0;  // Write mode
    
    LCD_PORT = (LCD_PORT & 0x0F) | (cmd & 0xF0);  // Send higher nibble
    EN = 1;
    __delay_ms(2);
    EN = 0;
    
    LCD_PORT = (LCD_PORT & 0x0F) | ((cmd << 4) & 0xF0);  // Send lower nibble
    EN = 1;
    __delay_ms(2);
    EN = 0;
    
    __delay_ms(2);  // Additional delay for processing
}

void lcd_data(unsigned char data) {
    RS = 1;  // Data mode
    RW = 0;  // Write mode
    
    LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);  // Send higher nibble
    EN = 1;
    __delay_ms(2);
    EN = 0;
    
    LCD_PORT = (LCD_PORT & 0x0F) | ((data << 4) & 0xF0);  // Send lower nibble
    EN = 1;
    __delay_ms(2);
    EN = 0;
    
    __delay_ms(2);  // Additional delay for processing
}

void lcd_init() {
    TRISD = 0x00;  // Set PORTD as output
    TRISH = 0xF0; // Set PORTH as output for 7-segment  
    TRISE = 0x00; // Set PORTE as output for 7-segment 
    TRISCbits.TRISC0 = 0;  // Set RC0 as output (RS)
    TRISCbits.TRISC1 = 0;  // Set RC1 as output (EN)
    TRISEbits.TRISE1 = 1;   // Set RE1 as input
  
    TRISBbits.TRISB7 = 1;   // Set RB7 as input 
    
    LATH = 0x00;   // Initially turn off all segments
    TRISA = 0xff;

    // Set digit pins as outputs
    TRISJ = 0xF0;  // Set lower nibble of PORTJ as output for digits
    LATJ = 0xF0;   // Initially turn off all digits
    
    __delay_ms(20);  // Wait for more than 15 ms after VDD rises to 4.5V

    lcd_command(0x02);  // Initialize in 4-bit mode
    __delay_ms(5);  // Wait for more than 4.1 ms
    
    lcd_command(0x28);  // Function set: 4-bit, 2 line, 5x7 dots
    __delay_ms(5);  // Wait for more than 4.1 ms
    
    lcd_command(0x0C);  // Display on, cursor off
    __delay_ms(5);  // Wait for more than 4.1 ms
    
    lcd_command(0x06);  // Entry mode set: increment cursor
    __delay_ms(5);  // Wait for more than 4.1 ms
    
    lcd_command(0x01);  // Clear display
    __delay_ms(5);  // Wait for more than 1.53 ms
}

void lcd_clear(void) {
    lcd_command(0x01); // Clear display command
    __delay_ms(2); // Clear command delay
}

void lcd_setcursor(unsigned char row, unsigned char col) {
    unsigned char address;
    switch (row) {
        case 1: address = 0x80 + (col - 1); break; // Line 1 address
        case 2: address = 0xC0 + (col - 1); break; // Line 2 address
        default: address = 0x80 + (col - 1); break; // Default to line 1
    }
    lcd_command(address);
}

void lcd_writestring(const char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}
