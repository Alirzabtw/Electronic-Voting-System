#ifndef INCLUDE_H
#define INCLUDE_H

// include.h
#define _XTAL_FREQ 40000000  // Define your system operating frequency

#include <xc.h>
#include <stdint.h>

// Define ports and pins
#define SEG_A PORTHbits.RH0
#define SEG_B PORTHbits.RH1
#define SEG_C PORTHbits.RH2
#define SEG_D PORTHbits.RH3
#define SEG_E PORTEbits.RE3
#define SEG_F PORTEbits.RE4
#define SEG_G PORTEbits.RE5
#define SEG_DP PORTHbits.RH7

// Define the pins for each digit
#define DIGIT1 LATJbits.LATJ0
#define DIGIT2 LATJbits.LATJ1
#define DIGIT3 LATJbits.LATJ2
#define DIGIT4 LATJbits.LATJ3

#define RS LATCbits.LATC0
#define EN LATCbits.LATC1
#define LCD_PORT LATD

void BusyWait3Seconds(void);
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_init(void);
void lcd_clear(void);
void lcd_setcursor(unsigned char row, unsigned char col);
void lcd_writestring(const char *str);
void adc_init(void);
uint16_t adc_read(uint8_t channel);
void int_to_str(int num, char *str);
int str_to_int(const char *str);
void blinker(void);
void update_votes(char candidate_name[], char votes[][3]);
int get_candidate_index(char candidate_name[]);
void display_nothing(void);
void display_digit(int digit, int value);
void display_number(int number);
int find_highest_votes(char votes[][3]);

#endif
