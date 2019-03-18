#ifndef COMMON_H_
#define COMMON_H_

// some common macros

// array size
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

// debug_printf 
// note: compiler issues warning on varargs for call with only 1 argument. It can be safely ignored
#include <avr/pgmspace.h>
#if defined(DEBUG)
        #define debug_printf(format, ...) printf_P(PSTR(format), ##__VA_ARGS__)
#else
        #define debug_printf(...)
#endif // DEBUG


// trick linker into pulling ISR from library
//    using TWI interrupt as an example:
//    put PROVIDE_ENTRY(TWI_vect); in ISR function definition
//    put REQUEST_ENTRY(TWI_vect); in application
//       --or-- use -Wl,-u,tag_TWI_vect in link step
#if defined(__ASSEMBLER__)
    #define PROVIDE_SYM(name)   GLOBAL_SYM name
    #define REQUEST_SYM(name)   .global name
    .macro GLOBAL_SYM _name
        .global \_name
    \_name:
    .endm
#else
    #define PROVIDE_SYM(name)   __asm__ __volatile__(".global " #name "\n" #name ":\n"::)
    #define REQUEST_SYM(name)   __asm__ __volatile__(".global " #name "\n"::)
#endif
#define PROVIDE_ENTRY(name)     PROVIDE_SYM(tag_##name)
#define REQUEST_ENTRY(name)     REQUEST_SYM(tag_##name)

// timer prescaler bit values for bits CSn2-CSn0 in TCCRnB register (valid for counters 0 and 1)
#define TIMER_PRS_MASK  (uint8_t)0x07  // prescaler bits mask
#define TIMER_PRS_0     (uint8_t)0x00  // Timer prescaler = 0 (timer stopped)
#define TIMER_PRS_1     (uint8_t)0x01  // Timer prescaler = 1
#define TIMER_PRS_8     (uint8_t)0x02  // Timer prescaler = 8
#define TIMER_PRS_64    (uint8_t)0x03  // Timer prescaler = 64
#define TIMER_PRS_256   (uint8_t)0x04  // Timer prescaler = 256
#define TIMER_PRS_1024  (uint8_t)0x05  // Timer prescaler = 1024
#define TIMER_EXT_FE    (uint8_t)0x06  // Timer on Tn falling edge
#define TIMER_EXT_RE    (uint8_t)0x07  // Timer on Tn rising edge

// timer prescaler bit values for bits CS22-CS20 in TCCR2B register (valid for counter 2)
#define TIMER2_PRS_MASK (uint8_t)0x07  // prescaler bits mask
#define TIMER2_PRS_0    (uint8_t)0x00  // Timer prescaler = 0 (timer stopped)
#define TIMER2_PRS_1    (uint8_t)0x01  // Timer prescaler = 1
#define TIMER2_PRS_8    (uint8_t)0x02  // Timer prescaler = 8
#define TIMER2_PRS_32   (uint8_t)0x03  // Timer prescaler = 32
#define TIMER2_PRS_64   (uint8_t)0x04  // Timer prescaler = 64
#define TIMER2_PRS_128  (uint8_t)0x05  // Timer prescaler = 128
#define TIMER2_PRS_256  (uint8_t)0x06  // Timer prescaler = 256
#define TIMER2_PRS_1024 (uint8_t)0x07  // Timer prescaler = 1024

#endif // COMMON_H_
