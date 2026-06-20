#include <ch32x035.h>
#include "usb_serial.h"
#include "debug.h"
// send in bcdef
// get abcde as reply


int main(void)
{
    signed char counter = 0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    SystemCoreClockUpdate();

    usbSerial_begin();

	while (!usbSerial_connected())
		;
    while (1)
    {

        if (usbSerial_available())
        {
            unsigned char count = 0;
            unsigned char data[256];
            memset(data, 0, sizeof(data));
            while (usbSerial_available())
            {
                data[count] = usbSerial_read();
                count++;
            }
            for (unsigned short i = 0; i < count - 1; i++)
            {
                data[i]--;
            }
            usbSerial_println_i(counter);

            usbSerial_println_s(" texttest ");

            usbSerial_writeP(data, count);
            usbSerial_flush();
            counter++;
        }

    }
}
