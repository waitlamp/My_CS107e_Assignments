#ifndef GPIO_EXTRA_H
#define GPIO_EXTRA_H

#include <stdbool.h>

/*
 * Functions for controlling extra features of
 * Raspberry Pi GPIO: event detection and pull state.
 *
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 *         Philip Levis <pal@cs.stanford.edu>
 *         Julie Zelenski <zelenski@cs.stanford.edu>
 *
 * Last edited: Feb 2018
 */

enum gpio_event {
    GPIO_DETECT_RISING_EDGE = 0,
    GPIO_DETECT_FALLING_EDGE,
    GPIO_DETECT_HIGH_LEVEL,
    GPIO_DETECT_LOW_LEVEL,
    GPIO_DETECT_ASYNC_RISING_EDGE,
    GPIO_DETECT_ASYNC_FALLING_EDGE,
};

/*
 * `gpio_enable_event_detection`
 *
 * Enables detection of GPIO `event` for GPIO pin number `pin`.
 *
 * @param pin       GPIO pin number to configure
 * @param event     which event to enable, see gpio_event enumeration
 *
 * If `pin` or `event` is invalid, does nothing.
 */
void gpio_enable_event_detection(unsigned int pin, unsigned int event);

/*
 * `gpio_disable_event_detection`
 *
 * Disables detection of GPIO `event` for GPIO pin number `pin`.
 *
 * @param pin       GPIO pin number to configure
 * @param event     which event to disable, see gpio_event enumeration
 *
 * If `pin` or `event` is invalid, does nothing.
 */
void gpio_disable_event_detection(unsigned int pin, unsigned int event);

/*
 * `gpio_get_event_detection`
 *
 * Gets the state of detection of GPIO `event` for GPIO pin number `pin`.
 * Returns true if event detection is enabled for `event`, false if disabled.
 *
 * @param pin       GPIO pin number to query
 * @param event     which event, see gpio_event enumeration
 * @return          true if enabled, false otherwise
 *
 * If `pin` or `event` is invalid, returns false.
 */
bool gpio_get_event_detection(unsigned int pin, unsigned int event);

/*
 * `gpio_disable_all_event_detection`
 *
 * Disables detection of all GPIO events for GPIO pin number `pin`.
 *
 * @param pin       GPIO pin number to disable detection of all events
 *
 * If `pin` is invalid, does nothing.
 */
void gpio_disable_all_event_detection(unsigned int pin);

/*
 * `gpio_check_event`
 *
 * Returns the event status for GPIO pin number `pin`.
 * The event status is true if an event has been detected for `pin`
 * and the event has not been cleared, status is false otherwise.
 *
 * @param pin       GPIO pin number to check
 * @return          true if event detected, false otherwise
 *
 * If `pin` is invalid, returns false.
 */
bool gpio_check_event(unsigned int pin);

/*
 * `gpio_clear_event`
 *
 * Clears the event status for GPIO pin number `pin`. Note that if the
 * event detected is high or low level and the level is still high or low,
 * clearing the event makes no change in event status.  The event
 * status remains true as long as the high or low level is in effect.
 *
 * @param pin       GPIO pin number to clear
 *
 * If `pin` is invalid, does nothing.
 */
void gpio_clear_event(unsigned int pin);

/*
 * `gpio_check_and_clear_event`
 *
 * Returns the event status for GPIO pin number `pin` and clears the
 * event status.
 *
 * @param pin       GPIO pin number to check and clear
 * @return          true if event detected and cleared, false otherwise
 *
 * If `pin` is invalid, does nothing and returns false.
 */
bool gpio_check_and_clear_event(unsigned int pin);

/*
 * The functions below control the pull state of a GPIO pin via its
 * internal resistor. Setting the pull state is useful for when you
 * have an input pin that would otherwise be floating. A pin configured
 * to pull-up defaults to 1. If configured to pull-down defaults to 0.
 * The Broadcom manual says pull state of a pin cannot be queried,
 * so you have to remember what state you have configured. The manual
 * is also unclear about when the pull state is reset (may not be on
 * restart, but is after power down?). Best to reset yourself to be
 * sure.
 */

/*
 * `gpio_set_pullup`
 *
 * Set pull state of GPIO pin number `pin` to pull-up.
 *
 * @param pin       GPIO pin number to configure as pull-up
 *
 * If `pin` is invalid, does nothing.
 */
void gpio_set_pullup(unsigned int pin);

/*
 *
 * `gpio_set_pulldown`
 *
 * Set pull state of GPIO pin number `pin` to pull-down.
 *
 * @param pin       GPIO pin number to configure as pull-down
 *
 * If `pin` is invalid, does nothing.
 */
void gpio_set_pulldown(unsigned int pin);

/*
 * `gpio_set_pullnone`
 *
 * Disables any pull state of GPIO pin number `pin` (will float).
 *
 * @param pin       GPIO pin number to disable pull state
 *
 * If `pin` is invalid, does nothing.
 */
void gpio_set_pullnone(unsigned int pin);

#endif
