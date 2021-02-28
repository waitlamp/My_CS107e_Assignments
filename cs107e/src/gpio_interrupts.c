#include "assert.h"
#include "bits.h"
#include "gpio_interrupts.h"
#include "gpio.h"
#include "gpio_extra.h"
#include "_gpio_private.h"
#include "interrupts.h"
#include <stddef.h>
#include <stdbool.h>

static bool gpio_interrupts_initialized = false;

// This array stores the handlers for gpio interrupts, one per pin.
// If no handler is registered for a given pin, the fn at that index
// will be NULL
static struct {
    handler_fn_t fn;
    void *aux_data;
} handlers[GPIO_PIN_LAST + 1];

static unsigned int get_next_pin(void) {
    unsigned int bank0_zeroes = count_leading_zeroes(_gpio->eds[0]);
    unsigned int bank1_zeroes = count_leading_zeroes(_gpio->eds[1]);
    if (bank0_zeroes != 32) {
        return 31 - bank0_zeroes;
    } else if (bank1_zeroes != 32) {
        return 63 - bank1_zeroes;
    } else {
        return GPIO_PIN_LAST + 1;
    }
}

// dispatch_gpio_interrupt is registered with top-level interrupts
// module as handler for source INTERRUPTS_GPIO3. This handler is
// thus called for all GPIO interrupts and then performs second-level
// dispatch to the per-pin handlers that have been registered with
// this module (gpio_interrupts)
static void dispatch_gpio_interrupt(unsigned int pc, void *unused) {
    unsigned int next_pin = get_next_pin();
    if (next_pin <= GPIO_PIN_LAST) {
        if (handlers[next_pin].fn) {
            handlers[next_pin].fn(pc, handlers[next_pin].aux_data);
        } else {
            // I would have thought this an error, i.e. event detect
            // enabled for pin but no handler registered. Would such
            // an event infinitely re-raise (no handler to clear?) But....
            // GPIO 35 event detect rising edge on by default has
            // no handler and event clears itself -- mysterious?
            // more investigation needed
        }
    }
}

void gpio_interrupts_init(void) {
    // okay to re-init this module, just re-registers same handler
    interrupts_register_handler(INTERRUPTS_GPIO3, dispatch_gpio_interrupt, NULL);
    gpio_interrupts_initialized = true;
}

void gpio_interrupts_register_handler(unsigned int pin, handler_fn_t fn, void *aux_data) {
    assert(gpio_interrupts_initialized);
    assert(pin <= GPIO_PIN_LAST);
    handlers[pin].fn = fn;
    handlers[pin].aux_data = aux_data;
}
