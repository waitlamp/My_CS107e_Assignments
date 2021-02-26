#ifndef GPIO_INTERRUPTS_H
#define GPIO_INTERRUPTS_H

#include "interrupts.h"

/*
 * Module to configure GPIO interrupts for Raspberry Pi.
 * Because all of the GPIO pins share a small set of GPIO
 * interrupts, you need a level of indirection to be able
 * to handle interrupts for particular pins. This module
 * allows a client to register one handler for each
 * GPIO pin.
 *
 * Author: Philip Levis <pal@cs.stanford.edu>
 *
 * Last update:   May 2020
 */

/*
 * `gpio_interrupts_init`
 *
 * Initialize the GPIO interrupts module. The init function must be
 * called before any calls to other functions in this module.
 * The init function configures gpio interrupts to a clean state.
 * This function registers a handler for GPIO interrupts, which it
 * uses to call handlers on a per-pin basis.
 *
 */
void gpio_interrupts_init(void);

/*
 * `gpio_interrupts_register_handler`
 *
 * Register a handler function to a given GPIO pin. Each pin
 * source can have one handler: further dispatch should be invoked by
 * the handler itself. Whether or not a particular pin will
 * generate interrupts is specified by the events system,
 * defined in `gpio_extra.h`.
 *
 * @param pin       GPIO pin to register handler for
 * @param fn        handler function to call when interrupt generated on pin
 * @param aux_data  client's data pointer to be passed as second argument
 *                  when calling handler function
 *
 * An assert is raised if `pin` is invalid. `aux_data` can be NULL if
 * handler function has no need for auxiliary data. If `fn` is NULL, removes
 * any previously registered handler for pin.
 *
 */
void gpio_interrupts_register_handler(unsigned int pin, handler_fn_t fn, void *aux_data);


#endif
