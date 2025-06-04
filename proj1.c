// proj1.c
#include "include.h"
#include "lcd.h"

void BusyWait3Seconds(void) {
    for (unsigned long i = 0; i < 20000; i++) {
        for (unsigned long j = 0; j < 50; j++) {
            // Busy-wait loop
            __asm__("nop");
        }
    }
}

void adc_init(void) {
    // Set ADC voltage reference and result format
    ADCON1bits.VCFG0 = 0; // Use VDD as reference voltage
    ADCON1bits.VCFG1 = 0; // Use VSS as reference voltage
    ADCON2bits.ADFM = 1; // Right justify result

    // Select ADC conversion clock
    ADCON2bits.ACQT = 0b111; // Acquisition Time: 20 TAD
    ADCON2bits.ADCS = 0b110; // ADC Conversion Clock: FOSC/64
    ADCON2bits.ADCS2 = 1; // (Set FOSC/64)

    // Select ADC channel
    ADCON0bits.CHS = 0; // Select AN0 as the ADC channel

    // Turn on ADC module
    ADCON0bits.ADON = 1; // Enable ADC module
}

// Function to read ADC value
uint16_t adc_read(uint8_t channel) {
    // Select ADC channel
    ADCON0bits.CHS = channel;

    // Start ADC conversion
    ADCON0bits.GO = 1;

    // Wait for conversion to complete
    while (ADCON0bits.GO);

    // Read ADC result
    return ((uint16_t)ADRESH << 8) | ADRESL;
}

void int_to_str(int num, char *str) {
    int i = 0;
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    while (num != 0) {
        str[i++] = (num % 10) + '0';
        num = num / 10;
    }
    str[i] = '\0';

    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

int str_to_int(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    // Handle leading whitespaces
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
        i++;
    }

    // Handle optional sign
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    // Convert characters to integer
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result * sign;
}

void blinker() {
    lcd_setcursor(2, 2);
    lcd_writestring(" ");
    __delay_ms(250);
    lcd_setcursor(2, 2);
    lcd_writestring(">");
    __delay_ms(250);
}

void update_votes(char candidate_name[], char votes[][3]) {
    if (strcmp(candidate_name, "Poe") == 0) {
        votes[0][1]++;
        if (votes[0][1] > '9') {
            votes[0][0]++;
            votes[0][1] = '0';
        }
    } else if (strcmp(candidate_name, "Galib") == 0) {
        votes[1][1]++;
        if (votes[1][1] > '9') {
            votes[1][0]++;
            votes[1][1] = '0';
        }
    } else if (strcmp(candidate_name, "Selimi") == 0) {
        votes[2][1]++;
        if (votes[2][1] > '9') {
            votes[2][0]++;
            votes[2][1] = '0';
        }
    } else if (strcmp(candidate_name, "Nesimi") == 0) {
        votes[3][1]++;
        if (votes[3][1] > '9') {
            votes[3][0]++;
            votes[3][1] = '0';
        }
    } else if (strcmp(candidate_name, "Hatayi") == 0) {
        votes[4][1]++;
        if (votes[4][1] > '9') {
            votes[4][0]++;
            votes[4][1] = '0';
        }
    } else if (strcmp(candidate_name, "Zweig") == 0) {
        votes[5][1]++;
        if (votes[5][1] > '9') {
            votes[5][0]++;
            votes[5][1] = '0';
        }
    } else if (strcmp(candidate_name, "Nabi") == 0) {
        votes[6][1]++;
        if (votes[6][1] > '9') {
            votes[6][0]++;
            votes[6][1] = '0';
        }
    } else if (strcmp(candidate_name, "Austen") == 0) {
        votes[7][1]++;
        if (votes[7][1] > '9') {
            votes[7][0]++;
            votes[7][1] = '0';
        }
    }
}

int get_candidate_index(char candidate_name[]) {
    if (strcmp(candidate_name, "Poe") == 0) {
        return 0;
    } else if (strcmp(candidate_name, "Galib") == 0) {
        return 1;
    } else if (strcmp(candidate_name, "Selimi") == 0) {
        return 2;
    } else if (strcmp(candidate_name, "Nesimi") == 0) {
        return 3;
    } else if (strcmp(candidate_name, "Hatayi") == 0) {
        return 4;
    } else if (strcmp(candidate_name, "Zweig") == 0) {
        return 5;
    } else if (strcmp(candidate_name, "Nabi") == 0) {
        return 6;
    } else if (strcmp(candidate_name, "Austen") == 0) {
        return 7;
    } else {
        return -1; // Invalid candidate
    }
}

void display_nothing() {
    SEG_A = 1;  // Turn off segment A
    SEG_B = 1;  // Turn off segment B
    SEG_C = 1;  // Turn off segment C
    SEG_D = 1;  // Turn off segment D
    SEG_E = 1;  // Turn off segment E
    SEG_F = 1;  // Turn off segment F
    SEG_G = 0;  // Turn off segment G
    SEG_DP = 1; // Turn off decimal point (if present)
}

void display_digit(int digit, int value) {
    // Turn off all digits
    DIGIT1 = 1;
    DIGIT2 = 1;
    DIGIT3 = 1;
    DIGIT4 = 1;
    
    // Turn off all segments initially
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 1;
    SEG_DP = 1;

    // Set the segments based on the given value
    switch (value) {
        case 1:
            SEG_B = 0;
            SEG_C = 0;
            break;
        case 2:
            SEG_A = 0;
            SEG_B = 0;
            SEG_G = 0;
            SEG_E = 0;
            SEG_D = 0;
            break;
        case 3:
            SEG_A = 0;
            SEG_B = 0;
            SEG_G = 0;
            SEG_C = 0;
            SEG_D = 0;
            break;
        case 4:
            SEG_F = 0;
            SEG_G = 0;
            SEG_B = 0;
            SEG_C = 0;
            break;
        case 5:
            SEG_A = 0;
            SEG_F = 0;
            SEG_G = 0;
            SEG_C = 0;
            SEG_D = 0;
            break;
        case 6:
            SEG_A = 0;
            SEG_F = 0;
            SEG_G = 0;
            SEG_E = 0;
            SEG_D = 0;
            SEG_C = 0;
            break;
        case 7:
            SEG_A = 0;
            SEG_B = 0;
            SEG_C = 0;
            break;
        case 8:
            SEG_A = 0;
            SEG_B = 0;
            SEG_C = 0;
            SEG_D = 0;
            SEG_E = 0;
            SEG_F = 0;
            SEG_G = 0;
            break;
        case 9:
            SEG_A = 0;
            SEG_B = 0;
            SEG_C = 0;
            SEG_D = 0;
            SEG_F = 0;
            SEG_G = 0;
            break;
        case 0:
            SEG_A = 0;
            SEG_B = 0;
            SEG_C = 0;
            SEG_D = 0;
            SEG_E = 0;
            SEG_F = 0;
            SEG_G = 1;
        default:
            break;
    }
    
    // Turn on the specified digit
    if (digit == 1) {
        DIGIT1 = 0;
    } else if (digit == 2) {
        DIGIT2 = 0;
    } else if (digit == 3) {
        DIGIT3 = 0;
    } else if (digit == 4) {
        DIGIT4 = 0;
    }
}

void display_number(int number) {
    // Break the number into individual digits
    int tens = (number % 100) / 10;
    int ones = number % 10;

    // Display each digit on the 7-segment display
    for (int i = 0; i < 50; i++) { // Loop to refresh the display
        display_digit(3, tens);
        __delay_ms(5);
        display_digit(4, ones);
        __delay_ms(5);
    }
}

int find_highest_votes(char votes[][3]) {
    int max_votes = 0;
    for (int i = 0; i < 8; i++) {
        int candidate_votes = str_to_int(votes[i]);
        if (candidate_votes > max_votes) {
            max_votes = candidate_votes;
        }
    }
    return max_votes;
}

void main() { 
    char str[3] = "00";
    int counter = 0;
    int digit_selection = 0; // 0 for first digit, 1 for second digit
    int toggle_done = 0; // flag to ensure single toggle per button press
    int number_of_voters = 0;
    int stop_votes = 0;
    char time_str[16] = "  Time left :"; // Ensure space for 2 digits and null terminator
    char sec_str[3]; // Need space for 2 digits and null terminator
    char candidate_id[3];
    char votes[8][3] = {"00", "00", "00", "00", "00", "00", "00", "00"}; // Votes for each candidate
    char *candidate_name;
    int seconds = 90;
    lcd_setcursor(1, 1); // Set cursor for candidate info on the first row
    votes[0][0] = '0'; // Set initial votes for Poe
    votes[0][1] = '0';
    lcd_init();
    adc_init();
    lcd_clear();
    lcd_setcursor(1, 1);
    lcd_writestring(" #Electro Vote# ");
    lcd_setcursor(2, 1);
    lcd_writestring(" ############## ");
    
    display_nothing();
    
    while (1) {
        // Read the ADC to allow scrolling
        uint16_t adc_value = adc_read(0);
        
        if (PORTEbits.RE1 == 0) {
            while (PORTEbits.RE1 == 0); // Debounce button press
            str[0] = '0';
            str[1] = '0';
            BusyWait3Seconds();
            lcd_clear();
            lcd_setcursor(1, 1);
            lcd_writestring(" #Enter Voters# ");
            lcd_setcursor(2, 2);
            lcd_writestring(str);
        }

        if (PORTBbits.RB6 == 0) {
            while (PORTBbits.RB6 == 0); // Debounce button press
            if (digit_selection == 0) {
                if (str[0] >= '0' && str[0] < '9') {
                    str[0]++;
                } else if (str[0] == '9') {
                    str[0] = '0';
                }
            } else if (digit_selection == 1) {
                if (str[1] >= '0' && str[1] < '9') {
                    str[1]++;
                } else if (str[1] == '9') {
                    str[1] = '0';
                }
            }

            lcd_setcursor(2, 2);
            lcd_writestring(str);
        }
        stop_votes = str_to_int(str);
        
        if (PORTBbits.RB7 == 0) {
            while (PORTBbits.RB7 == 0); // Debounce button press
            digit_selection = digit_selection + 1; // Toggle between 0 and 1
        }

        if (digit_selection >= 2) {
            digit_selection++;
            lcd_clear();
            
            while (seconds >= 0) {
                uint16_t adc_value = adc_read(0);
                if (stop_votes > 0) {
                    // Determine candidate based on ADC value
                    if (adc_value >= 0 && adc_value <= 127) {
                        candidate_name = "Poe";
                        lcd_setcursor(2, 1);
                        lcd_writestring(" >18 Poe    :");
                    } else if (adc_value >= 128 && adc_value <= 255) {
                        candidate_name = "Galib";
                        lcd_setcursor(2, 1);
                        lcd_writestring(" >64 Galib  :");
                    } else if (adc_value >= 256 && adc_value <= 383) {
                        candidate_name = "Selimi";
                        lcd_setcursor(2, 1);
                        lcd_writestring(" >34 Selimi :");
                    } else if (adc_value >= 384 && adc_value <= 511) {
                        candidate_name = "Nesimi";
                        lcd_setcursor(2, 1);
                        lcd_writestring(" >23 Nesimi :");
                    } else if (adc_value >= 512 && adc_value <= 639) {
                        candidate_name = "Hatayi";
                        lcd_setcursor(2, 1);
                        lcd_writestring(" >33 Hatayi :");
                    } else if (adc_value >= 640 && adc_value <= 767) {
                        candidate_name = "Zweig";
                        lcd_setcursor(2, 1);
                        lcd_writestring(" >67 Zweig  :");
                    } else if (adc_value >= 768 && adc_value <= 895) {
                        candidate_name = "Nabi";
                        lcd_setcursor(2, 1);
                        lcd_writestring(" >63 Nabi   :");
                    } else if (adc_value >= 896 && adc_value <= 1023) {
                        candidate_name = "Austen";
                        lcd_setcursor(2, 1);
                        lcd_writestring(" >99 Austen :");
                    }

                    if (seconds < 10) {
                        // Add leading zero for single-digit seconds
                        sec_str[0] = '0';
                        sec_str[1] = '0' + seconds;
                        sec_str[2] = '\0'; // Null-terminate the string
                    } else {
                        // Convert two-digit seconds to string
                        int_to_str(seconds, sec_str);
                    }

                    // Copy second string to time string at the correct position
                    time_str[13] = sec_str[0];
                    time_str[14] = sec_str[1];
                    seconds--;
    
                    lcd_setcursor(1, 1);
                    lcd_writestring(time_str); // Write the formatted time string to the LCD
    
                    if (PORTBbits.RB7 == 0) {
                        stop_votes--;
                        update_votes(candidate_name, votes);
                    }
                    int candidate_index = get_candidate_index(candidate_name);
                    if (candidate_index >= 0) {
                        lcd_setcursor(2, 14);
                        lcd_writestring(votes[candidate_index]);
                    }
                    blinker();
                    
                    int highest_votes = find_highest_votes(votes);
                    display_number(highest_votes);
                }
            }

            // Display the most voted candidate's number of votes on the 4-digit 7-segment display
            while (1); // Infinite loop to stop further execution
        }
    }
}
