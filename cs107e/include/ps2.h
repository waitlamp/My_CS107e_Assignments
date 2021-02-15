#ifndef PS2_H
#define PS2_H

/*
 * Module that communicates with a PS2 device such as a keyboard
 * or mouse.
 * You will implement this interface in assignments 5 and 7.
 *
 * Author: Julie Zelenski <zelenski@cs.stanford.edu>
 *
 * Last edited Feb 2021
 */

#include <stdbool.h>

typedef struct ps2_device ps2_device_t;

/*
 * Initializes a new PS2 device connected to specified clock and data GPIO
 * pins. The clock and data GPIOs are configured to use the internal pull-up
 * resistors which pull these lines to high resting state as required
 * for PS2 protocol. Returns the new PS2 device.
 *
 * To configure a new PS2 device in your code:
 *
 *     ps2_device_t *dev = ps2_new(KEYBOARD_CLK, KEYBOARD_DATA);
 *
 * Notice that this interface is slightly different from the _init exposed by
 * other libpi modules. This _new pattern allows a client to create multiple PS2
 * devices, such as one for a keyboard and another for a mouse. It also means
 * that clients of this module don't need to know the implementation details
 * (like size) of ps2_device_t, since they just keep a pointer.
 *
 * @param clock_gpio    the gpio connected to the clock line of the PS2 device
 * @param data_gpio     the gpio connected to the data line of the PS2 device
 * @return              pointer to new PS2 device or NULL if failed to create
 *
 * Although `ps2_new` configures the requested clock and data GPIOs
 * to use the internal pull-up resistors, it is recommended to choose GPIO
 * pins whose default state is already pull-up. This avoid timing issues
 * due to the device attempting to handshake with the Pi before `ps2_new`
 * has executed.
 */
ps2_device_t *ps2_new(unsigned int clock_gpio, unsigned int data_gpio);


/*
 * Read (blocking) a single scancode from the specifed PS2 device.
 * Bits are read on the falling edge of the clock.
 *
 * Reads 11 bits: 1 start bit, 8 data bits, 1 parity bit, and 1 stop bit
 *
 * Discards and restarts the scancode if:
 *   (lab5) The start bit is incorrect
 *   (assign5) or if parity or stop bit is incorrect
 *
 * Returns the 8 data bits of a well-formed PS2 scancode.
 * Will not return until it reads a complete and valid scancode.
 *
 * @param dev     PS2 device from which to read
 * @return        scan code read from PS2 device
 */
unsigned char ps2_read(ps2_device_t *dev);


/*
 * Write a single command scancode to the specifed PS2 device.
 * You do not need to implement this function unless you are
 * doing the mouse extension.
 *
 * @param dev       PS2 device to which to write
 * @param command   scancode to write
 * @return          true if successful write, false otherwise
 */
bool ps2_write(ps2_device_t *dev, unsigned char command);


/*
 * Changes this PS2 device from default polling behavior to instead configure
 * interrupts for gpio events. After setting device to use interrupts, client must
 * also globally enable interrupts at system level.
 *
 * @param dev       PS2 device to use interrupts
 */
void ps2_use_interrupts(ps2_device_t *dev);


#endif