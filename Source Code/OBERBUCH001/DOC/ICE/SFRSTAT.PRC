/* This file defines:		*/

/*		DUMP_PSW			*/
/*		DUMP_FLAGS			*/
/*		DUMP_INT_PENDING	*/
/*		DUMP_IPEND1			*/
/*		DUMP_INT_MASK		*/
/*		DUMP_IMASK1			*/
/*		DUMP_IOC0			*/
/*		DUMP_IOC1			*/
/*		DUMP_IOC2			*/
/*		DUMP_IOS0			*/

		/* DUMP_PSW */
define proc DUMP_PSW = do
define byte save_base = base
define word working_reg = psw
base = hex
write using ('15C,"--------------------PSW------------------------" ')
write using ('21C,"Interrupt Masks (int 00 to 07):" ')
write using ('15C,"Int_mask 00 (Timer Overflow)..................",1') & 
                                                working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"Int_mask 01 (A/D Conversion Complete).........",1') &
		           			working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"Int_mask 02 (HSI Data Available)..............",1') &
					        working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"Int_mask 03 (High Speed Outputs)..............",1') &
				  		working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"Int_mask 04 (HSI.0)...........................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"Int_mask 05 (Software Timer)..................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"Int_mask 06 (Serial Port).....................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"Int_mask 07 (EXTINT)..........................",1') &
						working_reg mod 2h
write using ('20C,"Flags and Global Interrupt Bit:" ')
working_reg = working_reg / 2h 
write using ('15C,"ST (sticky bit)...............................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"I  (global interrupt bit).....................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"X  (PTS enable bit)...........................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"C  (carry flag)...............................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"VT (overflow trap flag).......................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"V  (overflow flag)............................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"N  (negative flag)............................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"Z  (zero flag)................................",1') &
						working_reg mod 2h
base = save_base
end  /* DUMP_PSW */


		/* DUMP_FLAGS */
define proc DUMP_FLAGS = do
define byte save_base = base
define word working_reg = psw
base = hex
working_reg = working_reg / 100000000y
write ''
write using ('20C,"---------------FLAGS--------------" ')
write using ('20C,"ST (sticky bit)..................",1') &
working_reg mod 2h
working_reg = working_reg / 1000y
write using ('20C,"C  (carry).......................",1') &
working_reg mod 2h
working_reg = working_reg / 10y
write using ('20C,"VT (overflow trap)...............",1') &
working_reg mod 2h
working_reg = working_reg / 10y
write using ('20C,"V  (overflow)....................",1') &
working_reg mod 2h
working_reg = working_reg / 10y
write using ('20C,"N  (negative)....................",1') &
working_reg mod 2h
working_reg = working_reg / 10y
write using ('20C,"Z  (zero)........................",1') &
working_reg mod 2h 
write using ('20C,"----------------------------------" ')
write ''
base = save_base
end /* DUMP_FLAGS */



		/* DUMP_INT_PENDING */
define proc DUMP_INT_PENDING = do
define byte save_base = base
define byte save_wsr = wsr
define byte working_reg

wsr = 0h
base = hex

working_reg = int_pending
wsr = save_wsr

write ''
write using ('13C,"-------------------INT_PENDING--------------------" ')
write using ('13C,"BIT            FUNCTION                      VALUE" ')
write using ('13C,"--------------------------------------------------" ')
write using &
('13C,"Int_pending 00 (Timer Overflow)..................",1') & 
                                                working_reg mod 2h
working_reg = working_reg / 2h
write using &
('13C,"Int_pending 01 (A/D Conversion Complete).........",1') &
		           			working_reg mod 2h
working_reg = working_reg / 2h
write using &
('13C,"Int_pending 02 (HSI Data Available)..............",1') &
					        working_reg mod 2h
working_reg = working_reg / 2h
write using &
('13C,"Int_pending 03 (High Speed Outputs)..............",1') &
				  		working_reg mod 2h
working_reg = working_reg / 2h
write using &
('13C,"Int_pending 04 (HSI.0)...........................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using &
('13C,"Int_pending 05 (Software Timer)..................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using &
('13C,"Int_pending 06 (Serial Port).....................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using &
('13C,"Int_pending 07 (EXTINT)..........................",1') &
						working_reg mod 2h
write using ('13C,"--------------------------------------------------" ')
write ''

base = save_base

end /* DUMP_INT_PENDING */



		/* DUMP_IPEND1 */
define proc DUMP_IPEND1 = do
define byte save_base = base
define byte save_wsr = wsr
define byte working_reg

base = hex
wsr = 0h

working_reg = ipend1
wsr = save_wsr

write ''
write using ('16C,"--------------------IPEND1-------------------" ')
write using ('16C,"BIT       FUNCTION                      VALUE" ')
write using ('16C,"---------------------------------------------" ')

write using &
('16C,"Ipend1 00 (TI)..............................",1') & 
                                                working_reg mod 2h
working_reg = working_reg / 2h
write using &
('16C,"Ipend1 01 (RI)..............................",1') &
		           			working_reg mod 2h
working_reg = working_reg / 2h
write using &
('16C,"Ipend1 02 (HSI4)............................",1') &
					        working_reg mod 2h
working_reg = working_reg / 2h
write using &
('16C,"Ipend1 03 (Timer2 Capture)..................",1') &
				  		working_reg mod 2h
working_reg = working_reg / 2h
write using &
('16C,"Ipend1 04 (Timer2 Overflow).................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using &
('16C,"Ipend1 05 (EXTINT)..........................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using &
('16C,"Ipend1 06 (HSI FIFO Full)...................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using &
('16C,"Ipend1 07 (NMI).............................",1') &
						working_reg mod 2h
write using ('16C,"---------------------------------------------" ')
write ''

base = save_base

end /* DUMP_IPEND1 */



		/* DUMP_INT_MASK */
define proc DUMP_INT_MASK = do
define byte save_base = base
define byte save_wsr = wsr
define byte working_reg

base = hex
wsr = 0h

working_reg = int_mask
wsr = save_wsr

write ''
write using ('15C,"-------------------INT_MASK--------------------" ')
write using ('15C,"BIT         FUNCTION                      VALUE" ')
write using ('15C,"-----------------------------------------------" ')

write using ('15C,"Int_mask 00 (Timer Overflow)..................",1') & 
                                                working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"Int_mask 01 (A/D Conversion Complete).........",1') &
		           			working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"Int_mask 02 (HSI Data Available)..............",1') &
					        working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"Int_mask 03 (High Speed Outputs)..............",1') &
				  		working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"Int_mask 04 (HSI.0)...........................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"Int_mask 05 (Software Timer)..................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"Int_mask 06 (Serial Port).....................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using ('15C,"Int_mask 07 (EXTINT)..........................",1') &
						working_reg mod 2h
write using ('15C,"-----------------------------------------------" ')
write ''

base = save_base

end /* DUMP_INT_MASK */



		/* DUMP_IMASK1 */
define proc DUMP_IMASK1 = do
define byte save_base = base
define byte save_wsr = wsr
define byte working_reg

wsr = 0h
base = hex

working_reg = imask1
wsr = save_wsr

write ''
write using ('16C,"--------------------IMASK1-------------------" ')
write using ('16C,"BIT       FUNCTION                      VALUE" ')
write using ('16C,"---------------------------------------------" ')

write using &
('16C,"Imask1 00 (TI)..............................",1') & 
                                                working_reg mod 2h
working_reg = working_reg / 2h
write using &
('16C,"Imask1 01 (RI)..............................",1') &
		           			working_reg mod 2h
working_reg = working_reg / 2h
write using &
('16C,"Imask1 02 (HSI4)............................",1') &
					        working_reg mod 2h
working_reg = working_reg / 2h
write using &
('16C,"Imask1 03 (Timer2 Capture)..................",1') &
				  		working_reg mod 2h
working_reg = working_reg / 2h
write using &
('16C,"Imask1 04 (Timer2 Overflow).................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using &
('16C,"Imask1 05 (EXTINT)..........................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using &
('16C,"Imask1 06 (HSI FIFO Full)...................",1') &
						working_reg mod 2h
working_reg = working_reg / 2h
write using &
('16C,"Imask1 07 (NMI).............................",1') &
						working_reg mod 2h
write using ('16C,"---------------------------------------------" ')
write ''

base = save_base

end /* DUMP_IMASK1 */



		/* DUMP_IOC0 */
define proc DUMP_IOC0 = do
define byte save_base = base
define byte save_wsr = wsr
define byte working_reg

base = hex

wsr = 0Fh
working_reg = ioc0
wsr = save_wsr

write ''
write using &
('12C,"----------------------IOC0------------------------"')

write using &
('12C,"Bit 0 (HSI.0 Input Enable/Disable*)..............",Y,1')&
						working_reg mod 2h

working_reg = working_reg / 10y
write using &
('12C,"Bit 1 (Timer2 Reset Each Write)..................",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 2 (HSI.1 Input Enable/Disable*)..............",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 3 (Timer2 Ext. Reset Enable/Disable*)........",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 4 (HSI.2 Input Enable/Disable*)..............",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 5 (Timer2 Reset Source HSI.0/T2RST*).........",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 6 (HSI.3 Input Enable/Disable*)..............",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 7 (Timer2 Clock Source HSI.1/T2CLK*).........",Y,1')&
						working_reg mod 2h

write using &
('12C,"--------------------------------------------------"')
write ''

base = save_base

end /* DUMP_IOC0 */



		/* DUMP_IOC1 */
define proc DUMP_IOC1 = do
define byte save_base = base
define byte save_wsr = wsr
define byte working_reg

base = hex

wsr = 0Fh
working_reg = ioc1
wsr = save_wsr

write ''
write using &
('12C,"----------------------IOC1------------------------"')

write using &
('12C,"Bit 0 (Select PWM/P2.5*).........................",Y,1')&
						working_reg mod 2h

working_reg = working_reg / 10y
write using &
('12C,"Bit 1 (External Int ACH7 / EXTINT*)..............",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 2 (Timer1 Overflow Int Enable/Disable*)......",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 3 (Timer2 Overflow Int Enable/Disable*)......",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 4 (HSO.4 Output Enable/Disable*).............",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 5 (Select TXD/P2.0*).........................",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 6 (HSO.5 Output Enable/Disable*).............",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 7 (HSI Int FIFO Full / Holding Reg Loaded*)..",Y,1')&
						working_reg mod 2h

write using &
('12C,"--------------------------------------------------"')
write ''

base = save_base

end /* DUMP_IOC1 */



		/* DUMP_IOC2 */
define proc DUMP_IOC2 = do
define byte save_base = base
define byte save_wsr = wsr
define byte working_reg

base = hex

wsr = 0Fh
working_reg = ioc2
wsr = save_wsr

write ''
write using &
('12C,"----------------------IOC2------------------------"')

write using &
('12C,"Bit 0 (Timer2 Fast Increment Enable/Disable*)....",Y,1')&
						working_reg mod 2h

working_reg = working_reg / 10y
write using &
('12C,"Bit 1 (Timer2 Counts Up/Down*)...................",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 2 (PWM Divide By 2 Prescaler On/Off*)........",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 3 (A/D Sample And Hold Enable/Disable*)......",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 4 (A/D Clock Prescale Disable)...............",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 5 (Timer2 Alternate Int at 8000H On/Off*)....",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 6 (Lockable CAM Entry Enable/Disable*).......",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 7 (Clear Entire CAM).........................",Y,1')&
						working_reg mod 2h

write using &
('12C,"--------------------------------------------------"')
write ''

base = save_base

end /* DUMP_IOC2 */



		/* DUMP_IOS0 */
define proc DUMP_IOS0 = do
define byte save_base = base
define byte save_wsr = wsr
define byte working_reg

base = hex

wsr = 00h
working_reg = ios0
wsr = save_wsr

write ''
write using &
('12C,"----------------------IOS0------------------------"')

write using &
('12C,"Bit 0 (HSO.0 Current Status).....................",Y,1')&
						working_reg mod 2h

working_reg = working_reg / 10y
write using &
('12C,"Bit 1 (HSO.1 Current Status).....................",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 2 (HSO.2 Current Status).....................",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 3 (HSO.3 Current Status).....................",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 4 (HSO.4 Current Status).....................",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 5 (HSO.5 Current Status).....................",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 6 (CAM OR Holding Register Is Full)..........",Y,1')&
						working_reg mod 2h

working_reg = working_reg /10y
write using &
('12C,"Bit 7 (HSO Holding Register Is Full).............",Y,1')&
						working_reg mod 2h

write using &
('12C,"--------------------------------------------------"')
write ''

base = save_base

end /* DUMP_IOS0 */

