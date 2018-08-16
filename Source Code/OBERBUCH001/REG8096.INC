;+;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;+;	File:		REG8096.INC
;+;	Purpose:	include file containing 8096 register definitions
;+;	Original:		1989-08-01	Archimedes Software
;+;	Revision:	3	1993-12-06	D.N. Lynx Crowe
;+;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;+ ----------------------------------------------------------------------------
;+	8096 c compiler working registers
;+
;+	WARNING:  Don't move these !!!
;+
;+	The C Compiler expects them to be here, at 0x001A.
;+ ----------------------------------------------------------------------------

ir_base			define	01AH			; register base address

r8				define	(ir_base)		; BYTE, WORD
r9				define	(ir_base+1)		; BYTE

r0				define	(ir_base+2)		; BYTE, WORD, DWORD
r1				define	(ir_base+3)		; BYTE
r2				define	(ir_base+4)		; BYTE, WORD
r3				define	(ir_base+5)		; BYTE
r4				define	(ir_base+6)		; BYTE, WORD, DWORD
r5				define	(ir_base+7)		; BYTE
r6				define	(ir_base+8)		; BYTE, WORD
r7				define	(ir_base+9)		; BYTE

R8				define  (ir_base)		; BYTE, WORD
R9				define  (ir_base+1)		; BYTE

R0				define  (ir_base+2)		; BYTE, WORD, DWORD
R1				define  (ir_base+3)		; BYTE
R2				define  (ir_base+4)		; BYTE, WORD
R3				define  (ir_base+5)		; BYTE
R4				define  (ir_base+6)		; BYTE, WORD, DWORD
R5				define  (ir_base+7)		; BYTE
R6				define  (ir_base+8)		; BYTE, WORD
R7				define  (ir_base+9)		; BYTE

; ----------------------------------------------------------------------------
;	special function registers  (Fixed hardware addresses)
; ----------------------------------------------------------------------------

sp				define  18h
SP				define  18h
stackpointer	define	18h

zero            define  00h
ZERO            define  00h

ad_result		define  02h
ad_result_lo	define	02h
ad_result_hi	define	03h
ad_command		define	02h

hsi_mode		define	03h
hsi_time		define	04h
hsi_status		define	06h

hso_time		define	04h
hso_command     define  06h

sbuf			define	07h
sbuf_rx			define	07h
sbuf_tx			define	07h

int_mask		define	08h
int_pending		define	09h

watchdog		define	0ah

timer1			define	0ah
ioc2			define	0bh
timer2			define	0ch

baud_rate		define	0eh

io_port0		define	0eh
io_port1		define	0fh
io_port2		define	10h

sp_stat			define	11h
sp_con			define	11h

int_pend1		define	12h
int_mask1		define	13h
wsr				define	14h

ios0			define	15h
ios1			define	16h

ioc0			define	15h
ioc1			define	16h

pwm_control		define	17h
ios2			define	17h

AD_RESULT       define  02h
AD_RESULT_LO    define  02h
AD_RESULT_HI    define  03h
AD_COMMAND      define  02h

HSI_MODE        define  03h
HSI_TIME        define  04h
HSI_STATUS      define  06h

HSO_TIME        define  04h
HSO_COMMAND     define  06h

SBUF            define  07h
SBUF_RX         define  07h
SBUF_TX         define  07h

INT_MASK        define  08h
INT_PENDING     define  09h

WATCHDOG        define  0ah

TIMER1          define  0ah
IOC2            define  0bh
TIMER2          define  0ch

BAUD_RATE       define  0eh

IO_PORT0        define  0eh
IO_PORT1        define  0fh
IO_PORT2        define  10h

SP_STAT         define  11h
SP_CON          define  11h

INT_PEND1       define  12h
INT_MASK1       define  13h
WSR             define  14h

IOS0            define  15h
IOS1            define  16h

IOC0            define  15h
IOC1            define  16h

PWM_CONTROL     define  17h
IOS2            define  17h

; The End
