    ldr r0, FSEL1   // set GPIO 10 as input
    mov r1, #0
    str r1, [r0]

    ldr r0, FSEL2   // set GPIO 20 as output
    mov r1, #1
    str r1, [r0]

    mov r2, #(1<<10)    // bit 10
    mov r3, #(1<<20)    // bit 20

wait:
    ldr r0, LEV0
    ldr r1, [r0]    // read GPIO 10
    tst r1, r2
    bne  wait       // if button not pressed, keep waiting

    ldr r0, SET0    // set GPIO 20 high
    str r3, [r0]

FSEL1: .word 0x20200004
FSEL2: .word 0x20200008
 SET0: .word 0x2020001C
 LEV0: .word 0x20200034
