/* DUMP_SP PROC                                                       */
/* The following proc when evoked displays the contents of the stack. */
/* To run the proc, include the file and type:                        */ 
/*                                                                    */
/*                        dump_sp(X) <enter>                          */
/*                                                                    */
/* Where X equals the initial value of the stack pointer prior to any */
/* stack operations.                                                  */

/* Define the variables used in the proc */
define proc DUMP_SP = do
define byte save_wsr = wsr
define word sp_int = %0
define word addr
define word xdat
define word odd1
define word odd2
define byte first_time = 1h
define byte last_time = 0h
define word xlength = (sp_int - sp)/2h

/* Turn off the PAGING pseudovariable, and set the WSR to 0. */ 
paging = false
wsr = 0h
write ''

/* Check for improper (odd) stack value. */
odd1 = sp_int mod 2h
odd2 = sp mod 2h
if (odd1 or odd2) then write &
  '  ERROR - Odd stack value is invalid.'
  write ''
  paging = true
  wsr = save_wsr
  return
  endif
  
/* Check if stack is empty. */
if sp_int == sp then write &
  '  No entries in stack.'
  wsr = save_wsr
  paging = true
  write ''
  return
  endif
  
/* Check if initial stack value entered as an argument in the proc is */
/* less than the current stack value.                                 */
if sp_int < sp then write &
  '  ERROR - Stack grows into lower memory; therefore, the argument input'
  write &
  '          to the proc (which is the initial stack value) must be greater'
  write &
  '          than the current stack value.'  
  write ''
  paging = true
  wsr = save_wsr
  return 
  endif
   
/* For large stacks which may scroll off the screen, show the keys used to */
/* control screen scroll and proc quit.                                    */
if ((sp_int - sp) > 14t) then 
  write ''
  write ' "s" Key = Scroll'
  write ' "q" Key = Quit'
  write ''
   /********* NOTE: The following count value may cause too long of a delay*/
   /*               for slow host computers (ie: XT's). This value can     */
   /*               be adjusted as necessary to decrease the time that     */
   /*               the above scroll message remains on the screen.        */
  count 950h
   end /* count */
  endif

/* Set up the stack headings. */
if base == decimal then
  write using &
  ('25C,"--------STACK--------" ')
  write using &
  ('25C,"| Address |  Data   |" ')  
  write using &
  ('25C,"---------------------" '); endif

if base == binary then
  write using &
  ('15C,"-------------------STACK-------------------" ')
  write using &
  ('15C,"|     Address        |        Data        |" ')
  write using &
  ('15C,"-------------------------------------------" '); endif

if base == hex then
  write using &
  ('26C,"-------STACK-------" ')
  write using &
  ('26C,"| Address|  Data  |" ')
  write using &
  ('26C,"-------------------" '); endif

/* Get the value of the stack at each location, and print it out in a */
/* display window on the screen.                                      */
do
    repeat
     if not first_time then
               
        addr = sp_int 
        xdat = word sp_int

        if sp == sp_int then last_time = 1h; endif

        if last_time then

          if (base == binary) then
          write using &
          ('9C,"SP => |  ",0,"  |  ",0,"  |" ') addr, xdat ;endif

          if (base == hex) then
          write using &
          ('20C,"SP => |  ",0,"  |  ",0,"  |" ') addr, xdat ;endif

          if (base == decimal) then
          write using &
          ('19C,"SP => |  ",5,"  |  ",5,"  |" ') addr, xdat ;endif

        else

          if (base == binary) then
          write using &
          ('15C,"|  ",0,"  |  ",0,"  |" ') addr, xdat ;endif

          if (base == hex) then
          write using &
          ('26C,"|  ",0,"  |  ",0,"  |" ') addr, xdat ;endif

          if (base == decimal) then
          write using &
          ('25C,"|  ",5,"  |  ",5,"  |" ') addr, xdat ;endif

        endif /* not last time */

        if base == decimal then
        write using &
        ('25C,"---------------------" '); endif

        if base == binary then
        write using &
        ('15C,"-------------------------------------------" '); endif

        if base == hex then
        write using &
        ('26C,"-------------------" '); endif

     endif /* not first_time */
             
     first_time = 0
     sp_int = sp_int - 2h
        
/* This section of code implements SCROLL and QUIT functions, to stop the */
/* screen to view deep stacks, or to quit the proc prior to displaying the*/
/* the complete stack.                                                    */
     define char scroll_off = dci
     if ((scroll_off == 's')or(scroll_off == 'S')) then do 
        repeat
          define char scroll_on = ci
          if ((scroll_on == 'q')or(scroll_on == 'Q')) then
            wsr = save_wsr
            paging = true
            write ''
            return
            endif
          until ((scroll_on == 's')or(scroll_on == 'S'))
        end  /* repeat */
        end /* do */
     end /* if */
     if ((scroll_off == 'q')or(scroll_off == 'Q')) then
        wsr = save_wsr
        paging = true
        write ''
        return
	endif
	        
    until ((sp_int - sp + 2h) == 0h)
    end /* big repeat loop */

end /* big do loop */

/* For deep stacks, greater than ten entries, print the number of entries to */
/* the screen.                                                               */
if xlength > 10t then
write ''
write using ('" Stack is ",T,0," WORD(s) deep." ') xlength
write ''
endif

wsr = save_wsr
paging = true
end /* dump_sp */
