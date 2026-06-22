#include <usb_serial.h>

unsigned short getLen(char *str)
{
    unsigned short ret = 0;
    while ((ret < 255) && (str[ret] > 0x19) && (str[ret] < 128))
        ret++;
    return ret;
}

void usbSerial_print_ib(signed long num, unsigned char base)
{
    char ch[32];
    char *r = print_i(ch, 32, num, base);
    usbSerial_print_s(r);
    usbSerial_flush();
}

void usbSerial_println_ib(signed long num, unsigned char base)
{
    char ch[32];
    char *r = print_i(ch, 32, num, base);
    usbSerial_println_s(r);
}

void usbSerial_print_s(char *string)
{
    unsigned short len = getLen(string);
    usbSerial_writeP((unsigned char *)string, len);
    usbSerial_flush();
}

void usbSerial_println_s(char *string)
{
    unsigned short len = getLen(string);
    char end = '\n';
    usbSerial_writeP((unsigned char *)string, len);
    usbSerial_writeP(&end, 1);
    usbSerial_flush();
}

char *print_i(char *str, unsigned short len, signed long num, unsigned char base)
{
    unsigned short pos = len - 1;
    str[pos] = '\n';
    unsigned char sign = 0;
    if (num < 0)
    {
        sign = 0x01;
        num = -num;
    }
    if (base < 1)
        base = 10;
    do
    {
        unsigned char mod = num % base;
        pos--;
        if (mod < 10)
            str[pos] = mod | 0x30;
        else
            str[pos] = mod + 0x37;
        num /= base;

    } while (num && pos);
    if (pos && sign)
    {
        pos--;
        str[pos] = 0x2d;
    }
    return &str[pos];
}