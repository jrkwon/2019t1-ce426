    .global main    ; makes “main” accessible from outside this file.
    .text   ; set the following section to flash (RO). used for code.
; Add constants for the program


main                ; must be “main.” the Startup code of CCS
                    ; uses this name.
; Add your code here
; ------------------


loop:
; This super loop is for not having exception
; when code reaches the end of the program
    b loop




