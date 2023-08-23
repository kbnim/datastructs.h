#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

void print(char* str, ...);

int main(void) {
    char a[] = "hi %d %s\n";
    int b = 1;
    char c[] = "kdgl";
    print("hello %d and %s\n", b);
    return 0;
}

bool check_

void print(char* str, ...) {
    va_list arguments;
    va_start(arguments, str);

    bool formatting_start = false;
    int index = 0;
    
    while (*str != '\0') {
        
        if (!formatting_start) {
            switch (*str) {
                case '%':
                    formatting_start = true;
                    break;
                default:
                    putchar(*str);
                    break;
            }
        } else {
            // todo
            switch (*str) {
                case 'd':
                case 'i':
                    break;
                
                case 'f':
                    break;
                
                case 'c':
                    break;
                
                case 's':
                    break;
                
                case 'p':
                    break;
                
                case 'x':
                case 'X':
                    break;
                
                case 'o':
                    break;

                case 'u':
                    break;
            }
        }

        str++;
        index++;
    }

    va_end(arguments);
}