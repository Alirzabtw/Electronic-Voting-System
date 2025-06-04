#ifndef LCD_H
#define LCD_H


void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_init(void);
void lcd_clear(void);
void lcd_setcursor(unsigned char row, unsigned char col);
void lcd_writestring(const char *str);





#endif
