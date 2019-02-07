    .global main    ; makes “main” accessible from outside this file.

    .data

var1    .word 0x22000008

    .text   ; set the following section to flash (RO). used for code.


; Add constants for the program
SYSCTL_RCGCGPIO_R   .field  0x400FE608

main                ; must be “main.” the Startup code of CCS
                    ; uses this name.
; Add your code here
; ------------------

    LDR  R0, SYSCTL_RCGCGPIO_R
    LDR  R1,[R0]      ; read previous value
    ORR  R1,R1,#0x20  ; set bit 5
    STR  R1,[R0]      ; update



loop:
; This super loop is for not having exception
; when code reaches the end of the program
    b loop
