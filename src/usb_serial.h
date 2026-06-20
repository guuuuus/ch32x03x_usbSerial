#ifndef ch32v30x_usbserial_h
#define ch32v30x_usbserial_h
#include <ch32x035.h>
#include <ch32x035_usb.h>
#include <ch32x035_pwr.h>
#include <ch32x035_usbfs_device.h>
void usbSerial_begin();
unsigned char usbSerial_read();
unsigned char usbSerial_available();
void usbSerial_writeP(void *p, unsigned short len);
#define usbSerial_writeB(x) usbSerial_writeP(&x, 1)

void usbSerial_flush();
unsigned char usbSerial_connected();

//print stuff
// int
void usbSerial_print_ib(signed long num, unsigned char base);
void usbSerial_println_ib(signed long num, unsigned char base);
// int base 10
#define usbSerial_print_i(n) usbSerial_print_ib (n, 10)
#define usbSerial_println_i(n) usbSerial_println_ib(n, 10)

// string
void usbSerial_print_s(char *string);
void usbSerial_println_s(char *string);

// unsinged
#define usbSerial_print_u(x) usbSerial_print_i((signed long)x)
#define usbSerial_println_u(x) usbSerial_println_i((signed long)x)
#define usbSerial_print_ub(x, y) usbSerial_print_ib((signed long)x, y)
#define usbSerial_println_ub(x, y) usbSerial_println_ib((signed long)x, y)

char *print_i(char *str, unsigned short len, signed long num, unsigned char base);



#endif