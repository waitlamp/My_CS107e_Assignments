---
released: true
permalink: /labs/lab7/
title: 'Lab 7: Raspberry Pi, Interrupted'
toc: true
readings: |
  [Prelab](/labs/lab7/#prelab-preparation) to prep before lab.
---
{% comment %}
Task list to copy/paste when creating PR for this lab:

__Before releasing lab7:__
- [ ] Review writeup/code/checkin questions (instructor)
- [ ] Walk through (SL)
- [ ] Followup on issues from previous quarter postmortem (issue #)

__To prep for lab7:__
- [ ] Ensure monitor/cable per pair avail in lab

{% endcomment %}

*Lab written by Philip Levis, updated by Pat Hanrahan and Julie Zelenski*

## Goals

The goal of this lab is to get you started with interrupts in preparation for
your final assignment.

During this lab you will:

- Review the support code for interrupts on the Pi,
- Write code to handle button presses using GPIO event interrupts, and
- Brainstorm possibilities for achieving world domination with your awesome bare-metal Raspberry Pi final project.

## Prelab preparation
To prepare for lab, do the following: 

- Pull the latest version of the `cs107e.github.io` courseware repository.
- Clone the lab repository `https://github.com/cs107e/lab7`.
- Browse our [project gallery](/project_gallery/) to gather ideas and inspiration from the projects of our past students.
- Extra supplies needed in lab this week:
    - __HDMI cable and display__
    - __parts kit__ (breadboard, button, jumper)


## Lab exercises

### Interrupts

#### 1) Review interrupt assembly

In the first lecture on interrupts, we went over the low-level mechanisms. The `interrupts` module is used to configure interrupts and manage interrupt handlers at the system level. The module interface is documented in `interrupts.h` and its implementation is split into the files `interrupts.c` (C code) and `interrupts_asm.s` (assembly). These source files are available in the directory `$CS107E/src`.

Start by reviewing the assembly in `interrupts_asm.s`. The first two functions, `interrupts_global_disable` and `interrupts_global_enable`,
do as they indicate: they flip the interrupts enabled bit in the CPSR
(current processor state register). This register is so important and
special that it has its own instructions to read and write it, `msr` and
`mrs`.

Next, the file defines `_RPI_INTERRUPT_VECTOR_BASE`, which specifies
the address where the interrupt vector table should go. On the Raspberry
Pi, this is address 0 -- one reason why null pointer errors are so dangerous!

Next, the file defines `_vectors`, which are the assembly instructions
that the processor will jump to on different interrupts. For us, almost
all of them indicate some kind of fatal error we can't recover from,
so the instruction is `ldr pc, abort_addr`. If these interrupts trigger,
we put the data stored at `abort_addr` into the program counter. For
general interrupts, though, index 6 in the table, we'll instead load
the value at `interrupt_addr` into the program counter.

Both `interrupt_addr` and `abort_addr` are defined just below the table.
They hold the address of the `interrupt_asm` and `abort_asm` functions.
By putting these into `.word` values right after the table, they'll
store absolute addresses and can be copied with the table. This means
that when we copy the table to `_RPI_INTERRUPT_VECTOR_BASE`, code will
still jump to the right address and call these functions. Note that
`_vectors_end` is *after* these two `.word` values, so they are copied
with the table. Look over the function `interrupts_init` of `interrupts.c` to see how the vectors are copied to the proper location.

`abort_asm` resets the stack pointer to use a separate stack (so it
won't corrupt our current stack) then jumps to `pi_abort`, which
does not return.

Let's now dig into `interrupts_asm`. This is the critical sequence of assembly needed to safely transition in and out of interrupt mode. Carefully trace this sequence and challenge each other to understand what instruction is doing and why. At the point it calls the C function `interrupt_dispatch`, things proceed pretty normally until it's time for the one jam-packed final instruction need to resume supervisor mode. 

Here are some questions to confirm your understanding of the low-level mechanisms. Ask us for clarification on anything you find confusing.

+ When installing the vector table, `interrupts_init` copies eight
instructions plus two additional words of data. What are those
additional words and why is it essential that they are copied along
with the table? The existing code copies the information using an
explicit loop. This could instead be a single call to `memcpy`. What
would be the correct arguments to `memcpy` to do the equivalent copy
task?
 
+ How does the private helper `vector_table_is_installed` verify that
initialization was successful? Find where this helper is used. What
client oversight is it attempting to defend against?

+ What piece of state needs to change to globally enable/disable
interrupts?

+ The supervisor stack is located at `0x8000000` and configured as one
of the first instructions executed in `_start`. Where is the interrupt
stack located and when it is configured?  A different approach would
be to configure the interrupt stack at program start along with the
supervisor stack, but doing so then would require temporarily changing
to interrupt mode -- why is that switch needed?

You're ready for a check-in question [^1]

#### 2) Review interrupt dispatch

In our second lecture on interrupts, we looked at dispatch support in the `interrupts` and `gpio_interrupts` modules. These modules maintain a table of handlers (function pointers), each handler is registered to a particular event and stored in the table under the event index. When an event occurs, the dispatch accesses the event index in the table and invokes the registered handler. In the top-level `interrupts` module, the interrupt source number is the index into the table of handlers. In the `gpio_interrupts` module, the GPIO pin number is used as the index. 

Both modules make use of neat performance trick for quickly identifying the index of the event that triggered the interrupt. The needed process is to scan the bits in the interrupt registers to find the bit that is set and. This scan is performed by the function `count_leading_zeroes` declared in `bits.h`. The obvious way to implement this function is in C. You could perhaps iterate over each bit, or do some fancy bit twiddling, say use Kernighan's algorithm and combine it with a lookup table. This might take anywhere from 8-100 cycles.

A better way to implement it is in assembly. ARM has a
[`clz` instruction](http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0802a/Cihjgjed.html)
that can perform the needed operation in a single operation. Look into the source code for `bits_asm.s` to see how it is used here.  This use of assembly cuts the time it takes to find a pending interrupt from 100 to 3 cycles, a 33x improvement. Given this code runs on every interrupt, this is an excellent performance improvement: it's why instructions like `clz` exist. Neat!

+ How is a function "registered" as a handler for an interrupt source?
Can there be multiple handlers registered to the same source? What
happens if no handler has been registered to process a handled interrupt?

+ An `aux_data` pointer can be stored stored with a registered handler. That pointer is later passed to as an argument to the handler when invoked. What is the purpose of an `aux_data` pointer?

Confirm your understanding with a check-in question [^2]

#### 3) Set up a button circuit

Now let's get going on using interrupts in a s program. Set up a one-button circuit on your breadboard. Connect one sside of the button to GPIO pin 20 and the other side to ground. Connect your Pi to a HDMI monitor.

![button circuit](images/button-circuit.jpg){: .zoom -w-50}

The button circuit is configured for a default state of high (1) by activating the Pi's internal pull-up resistor on the button GPIO.  When the button is not pressed, the resistor "pulls up" the value to 1.  When the button is pressed, it closes the circuit and connects the pin to ground. The value then reads as 0.

The `main` function in `code/button/button.c` sits in a loop, waiting for a button press and then redrawing the screen. Fill in the implementation of the empty `wait_for_click` function. This version of  `wait_for_click` operates by _polling_. It should:

1. Wait for a falling edge on the button gpio, i.e. watch for the pin state to transition from 1 to 0 (you can read the pin state with `gpio_read`).

2. Increment the `gCount` global variable and announce the event with a `printf("Click!")`

Compile and run the program. Each time you click the button, the message is printed and the screen redraws and shows the incremented count of clicks. This version of the program is always redrawing or waiting for a click, but it's either one or the other. While waiting for a button press, the screen redraw is paused. While redrawing the screen, no button presses are detected. Ideally, we want the program to do both tasks concurrently.

- If you click the button multiple times in quick succession, some of
the presses are missed. You get neither a printed message nor a screen
redraw and these clicks are not included in the count. Why does that happen? 

You'll note that redrawing the screen is quite slow. If we speed
that up, it would cause us to miss fewer events, but we still have to spin waiting for a press and still can miss events. Interrupts will solve this problem.

#### 4) Write a button handler

You are now going to rework the program to detect button presses via
interrupts.

Remove the call to `wait_for_click` from the loop in `main`. Compile and re-run. The program now repeatedly redraws the screen.  If you click the button, nothing happens, as the program is not reading the state of the GPIO pin, it's 100% occupied with drawing.

To handle button press via interrupt, you need to make several edits to the program:

- Enable detection of falling edge events on the GPIO pin connected as button input. The function you need is `gpio_enable_event_detection`. The gpio event functions are documented in the header file [gpio_extra.h](/header#gpio_extra).
- Add a handler function to process the event.
    - The handler function must be defined to match the required prototype:
        
        `void my_function(unsigned int pc, void *aux_data)`
    - The handler must clear the event. Check the header file [gpio_extra.h](/header#gpio_extra) to find the function used to do this.
    - Use the `aux_data` parameter to pass a message string to the handler. The handler should cast the received pointer to  `char *` to and use `printf` to output the message.
- Edit the `main` function to configure and enable interrupts. There are several things you need to do and the order in which you do them is important.
    - Initialize both `interrupts` module and the `gpio_interrupts` module.
    - Register your handler with the `gpio_interrupts` module. Pass the string "YOUR-NAME-HERE is an interrupt ninja" as the `aux_data` pointer when registering your handler. The handler will print this message.
    - Turn on global interrupts. 

Think carefully about each of these changes, revisiting the lecture notes if
you need to.  Talk this over with your tablemates and ensure that you
understand what each step does and why it's necessary.

Compile and run the program. If you have done everything correctly, the program continuously redraws as before, but now whenever you click the button, it prints a message to congratulate your prowess with interrupts and the click count increments.  You get the best of both worlds: your long-running computation can be written as a simple loop, yet the system is immediately responsive to input.

1. Describe the sequence of steps to configure and enable interrupts. What is the consequence of skipping a step or doing the steps out of order?

1. What happens if the handler does not clear the event before returning?

You're ready for these check-in questions [^3] [^4]

#### 5) Coordinate between main and interrupt

You want to change the program to now redraw once in response to a button click rather than continuously update. This requires that the interrupt and main code share state.

Edit the code within the loop in `main` to only call `redraw` if the count of clicks `gCount` has changed since the last redraw. Save the count used at last redraw and compare that saved value to `gCount` to determine when a redraw is necessary.

The count is being stored in the global variable `gCount`. The handler increments it and the `main` reads the value and compares to saved count.  `gCount` is not currently declared `volatile`. Should it be? Why or why not?  Can the compiler tell, by looking at only this file, how control flows between main and the interrupt handler? Will the compiler generate different code if `volatile` than without it? Will the program behave differently? Test it both ways and find out!

- What changes if `gCount` variable is not declared `volatile`? [^5]

#### 6) Use a ring buffer queue

Watch carefully as the program executes and you'll note that every click is detected and counted, but the count of redraw iterations is not one-to-one with those updates. Multiple clicks can occur before the `main` loop gets around to next checking the value of `gCount`.

To track all updates and process each one by one, we can use a queue to communicate between the interrupt handler and `main`. The handler will enqueue each update to the queue and `main` will dequeue each update. Because the queue stores every individual update posted by the interrupt handler, we can be sure that we never miss one.

How to rework the code:

- Review the [ringbuffer.h](header#ringbuffer) header file and [ringbuffer.c](https://github.com/cs107e/cs107e.github.io/blob/master/cs107e/src/ringbuffer.c) source for documentation on the ring buffer queue. This ADT maintains a queue of integer values implemented as a ring buffer.
- In the `main` function, declare a variable of type `rb_t *rb` and initialize with a call to `rb_new`.  Use the  `rb` pointer as the `aux_data` pointer when registering the handler.
- Edit your handler to now cast the `aux_data` parameter to type `rb_t *`.  In the handler, enqueue the updated value of count to the ring buffer by calling `rb_enqueue`.
- Edit `main` to use `rb_dequeue` to retrieve each update from the queue. This replaces the previous code that compared `gCount` to the saved value to detect a change in click count.

Make the above changes and rebuild and run the program. It should now redraw the screen once for each button press in one-to-one correspondence, including patiently processing a backlog of redraws from a sequences of fast presses. 

When you're done, take a moment to verify your understanding:

1. Why is the significance of the return value from `rb_dequeue`? Why is it essential to pay attention to that return value?
1. Why might you want the handler to enqueue and return instead of doing
   the actual task (e.g. redraw) directly in the handler?
1. With this change, is it now necessary for `gCount` to be declared `volatile`? Does the ring buffer need to be declared `volatile`?  Why or why not?

You're ready for the final check-in question [^6]

### Project brainstorm and team speed-dating

Visit our [project gallery](https://cs107e.github.io/project_gallery/) to see a sampling of projects from our past students. We are __so so proud__ of the creations of our past students -- impressive, inventive, and fun! You'll get started in earnest on the project next week, but we set aside a little time in this week's lab for a group discussion to preview the general guidelines and kindle your creativity about possible directions you could take in your project. If you have questions about the project arrangements or are curious about any of our past projects, please ask us for more info, we love to talk about the neat work we've seen our students do. If you have ideas already fomenting, share with the group to find synergy and connect with possible teammates. Project teams are most typically pairs, although occasionally we have allowed solo or trios by special request.

### Bonus speed exercise
In past quarters, we have used some of the time in lab7 do some explorations in performance optimization. We don't have time for it this quarter, but we linked the [materials](speed) if you want to check it out for fun.

## Check in with TA 

Before leaving the lab, check in with a TA and discuss any challenges to answering the questions in the lab. If you do not feel confident about your responses, please ask us about it too!

[^1]: Why is 4 subtracted from the `lr`?

[^2]: How is a function "registered" as a handler for an interrupt source? Can there be multiple handlers registered to the same source? What happens if an event is generated on a source for which no handler s been registered?

[^3]: What initialization must happen before registering a handler with the gpio_interrupts module? What happens if you attempt to register a handler without the proper initialization?

[^4]: What happens if an interrupt handler does not clear the event before returning?

[^5]: What is the consequence of not declaring the `gCount` variable as `volatile`?

[^6]: Why might you want the handler to enqueue an update and return instead of doing the actual task (e.g. redraw) directly in the handler?
