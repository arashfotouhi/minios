/*
Bare metal BeagleBone Black example for turning on led USR0.
*/

.equ CM_PER_GPIO1_CLKCTRL, 0x44e000AC
.equ GPIO1_OE, 0x4804C134
.equ GPIO1_SETDATAOUT, 0x4804C194

.equ TIMER_1MS_TIER, 0x44E3101C
.equ INTERRUPT_CONTROLLER, 0x48200000

_start:
    mrs r0, cpsr
    bic r0, r0, #0x1F @ clear mode bits
    orr r0, r0, #0x13 @ set SVC mode
    orr r0, r0, #0xC0 @ disable FIQ and IRQ
    msr cpsr, r0

    /* set clock for GPIO1, TRM 8.1.12.1.29 */
    ldr r0, =CM_PER_GPIO1_CLKCTRL
    ldr r1, =0x40002
    str r1, [r0]

    /* set pin 21 for output, led USR0, TRM 25.3.4.3 */
    ldr r0, =GPIO1_OE
    ldr r1, [r0]
    bic r1, r1, #(1<<21)
    str r1, [r0]

    /* logical 1 turns on the led, TRM 25.3.4.2.2.2 */
    ldr r0, =GPIO1_SETDATAOUT
    ldr r1, =(1<<21)
    str r1, [r0]

    /* enable match interrupt */
    ldr r0, =TIMER_1MS_TIER
    ldr r1, =0x1
    str r1, [r0]

    /* set match value register */
    ldr r0, =TIMER_1MS_TMAR
    ldr r1, =#5000
    str r1, [r0]

    

.loop: b .loop
