/*+ **** ICE196KD debug macros for the OB-MX voice card ***** */
/*+ Version 94 -- 1994-06-10 -- D.N. Lynx Crowe */

/* Note that these definitions depend on these defines in i196kb.mac:	*/

/*		def		= 'define'												*/
/*		lit		= 'literally'											*/

/* This file defines:													*/

/*+	adr		= 'address'													*/
/*+	dsp		= 'dump_sp(0F800H)'											*/
/*+	dstk	= 'word sp to 0F7FEH'										*/
/*+	gofer	= 'go from 2080H forever'									*/
/*+	len		= 'length'													*/
/*+	lipc0	= 'cls;byte .ipc_fifo len 200H'								*/
/*+	lipc1	= 'cls;byte .ipc_fifo+200H len 200H'						*/
/*+	lipc2	= 'cls;byte .ipc_fifo+400H len 200H'						*/
/*+	lipc3	= 'cls;byte .ipc_fifo+600H len 200H'						*/
/*+	mc		= 'word 8000H to 0FCFEH = 0'
/*+	ns		= 'namescope ='												*/
/*+	nsh		= 'namescope = :hdw'										*/
/*+	nsyn    = 'word .calref=0'											*/
/*+	pa		= 'print cycles all'										*/
/*+	pn		= 'print cycles newest 30'									*/
/*+	rboth	= 'reset chip; go from 2080H forever'						*/
/*+	rerun	= 'halt ; print clear ; go from 2080H forever'				*/
/*+	restart	= 'halt ; print clear ; reset chip ; go from 2080H forever'	*/
/*+	syn     = 'word .calref=1'											*/

/*	cdac		-- clear dac cv table									*/
/*	cipc		-- clear ipc input fifo									*/
/*	cregs		-- dump the C regs										*/
/*	ddac		-- dump dac cv table									*/
/*	dflg		-- display miscellaneous flags							*/
/*	dipc		-- dump ipc input fifo									*/
/*	dtemp		-- dump C TEMPs											*/
/*	dts			-- display tuning status								*/
/*	dta			-- display voice A tunings								*/
/*	dtb			-- display voice B tunings								*/

/*	dvm(vb)		-- display voice miscellaneous variables				*/
/*	 dvma		-- display voice misc. variables for voice A			*/
/*	 dvmb		-- display voice misc. variables for voice B			*/
/*	 dvms		-- display voice misc. variables for both voices		*/

/*	sym(v)		-- evaluate v as a symbol								*/

/*	dcur(vb)	-- dump curval[] table									*/
/*	dout(vb)	-- dump outval[] table									*/

/*	dpv(vb)		-- display VCO pitch values								*/
/*	 dpvs		-- display VCO pitch values for both voices				*/

/*	dpvf(vb)	-- display VCF pitch values								*/
/*	 dpvfs		-- display VCF pitch values for both voices				*/

/*	dvo(vb)		-- display voice offset values							*/
/*	 dvos		-- display voice offset values for both voices			*/

/*	dtl(l) 		-- display tuning log									*/

/*	dtea		-- display voice A tuning errors						*/
/*	dteb		-- display voice B tuning errors						*/

/*	dxoa		-- display VCO tuning xy values for voice A				*/
/*	dxob		-- display VCO tuning xy values for voice B				*/

/*	dhsi		-- display HSI variables								*/

/* ************************************************* */
/* reset the chip and load the code and debug macros */
/* ************************************************* */

reset chip
write 'Chip reset.'

write 'Loading voice.out ...'
load voice.out

write 'Loading sp.prc ... '
include sp.prc nolist

lpath=obj
source=true

/* ****************************************************************** */

write 'Loading defines ... '

/* ******************************* */
/* ***** 'literally' defines ***** */
/* ******************************* */

def lit adr     = 'address'
def lit dsp     = 'dump_sp(0F800H)'
def lit dstk    = 'word sp to 0F7FEH'
def lit gofer   = 'go from 2080H forever'
def lit len     = 'length'
def lit lipc0   = 'cls;byte .ipc_fifo length 200H'
def lit lipc1   = 'cls;byte .ipc_fifo+200H length 200H'
def lit lipc2   = 'cls;byte .ipc_fifo+400H length 200H'
def lit lipc3   = 'cls;byte .ipc_fifo+600H length 200H'
def lit mc		= 'word 8000H to 0FCFEH = 0'
def lit ns      = 'namescope ='
def lit nsh     = 'namescope = :hdw'
def lit nsyn    = 'word .calref=0'
def lit pa      = 'print cycles all'
def lit pn      = 'print cycles newest 40t'
def lit rboth   = 'reset chip; go from 2080H forever'
def lit rerun   = 'halt ; print clear ; go from 2080H forever'
def lit restart = 'halt ; print clear ; reset chip ; go from 2080H forever'
def lit syn     = 'word .calref=1'

/* ************************************************************ */
/* ***** debug variables:  WARNING -- These often change. ***** */
/*																*/
/* variables marked with <-- must be carefully checked and      */
/* updated whenever voice.h or voice.inc change.                */
/* ************************************************************ */

def word v_len   = 1558t		/*+ voice_size		<-- */

def word vco_off = 34t			/*+ voice_vcos		<-- */
def word vco_len = 24t			/*+ vco_size		<-- */

def word vcf_off = 82t			/*+ voice_vcfs		<-- */
def word vcf_len = 8t			/*+ vcf_size		<-- */

def word lfo_off = 98t			/*+ voice_lfos		<-- */
def word lfo_len = 24t			/*+ lfo_size		<-- */

def word env_off = 170t			/*+ voice_envs		<-- */
def word env_len = 42t			/*+ env_size		<-- */

def word mod_off = 338t			/*+ voice_mods		<-- */
def word mod_len = 16t			/*+ mod_size		<-- */

def word dst_off = 722t			/*+ voice_dstptr	<-- */

def word cur_off = 854t			/*+ voice_curval	<-- */

def word out_off = 1078t		/*+ voice_outval	<-- */

def word tt_off  = 1302t		/*+ voice_tunetab	<-- */

def word pp_note  = 2*3t		/*+ offset to VT_PP_NOTE in {cur|out}val[] */
def word pp_pwhl  = 2*5t		/*+ offset to VT_PP_PITCHWHL in {cur|out}val[] */
def word lfo_out  = 2*13t		/*+ offset to VT_PP_LFO1 in {cur|out}val[] */
def word vt_port1 = 2*24t		/*+ offset to VT_VCO1_PORT in {cur|out}val[] */
def word vt_port2 = 2*33t		/*+ offset to VT_VCO2_PORT in {cur|out}val[] */
def word frq_mm   = 2*42t		/*+ offset to VT_MM_FREQ in {cur|out}val[] */
def word frq_ob   = 2*50t		/*+ offset to VT_OB_FREQ in {cur|out}val[] */
def word lfo_cur  = 2*55t		/*+ offset to VT_LFO1_DELAY in {cur|out}val[] */
def word vt_vsens = 2*74t		/*+ offset to VT_ENV1_VEL_SENS in {cur|out}val[] */
def word adj_vco1 = 2*105t		/*+ offset to VT_VCO1_ADJUST in {cur|out}val[] */
def word adj_vco2 = 2*106t		/*+ offset to VT_VCO2_ADJUST in {cur|out}val[] */
def word adj_mm   = 2*107t		/*+ offset to VT_MM_ADJUST in {cur|out}val[] */
def word adj_ob   = 2*108t		/*+ offset to VT_OB_ADJUST in {cur|out}val[] */
def word pch_vco1 =	2*109t		/*+ offset to VT_VCO1_CNOTE in {cur|out}val[] */
def word pch_vco2 =	2*110t		/*+ offset to VT_VCO2_CNOTE in {cur|out}val[] */
def word vt_trans = 2*111t		/*+ offset to VT_TRANSPOSE in {cur|out}val[] */

def word env_coff = 2*8t		/*+ ENV parameter length in {cur|out}val[] */
def word lfo_coff = 2*4t		/*+ LFO parameter length in {cur|out}val[] */
def word vco_coff = 2*9t		/*+ VCO parameter length in {cur|out}val[] */

/* ****************************************************************** */

write 'Loading debug procs ...'

/* ************************************* */
/*+ **** cdac -- clear dac cv table **** */
/* ************************************* */

if listem then
write '   cdac'
endif

def proc cdac = nosource do
word .cvtable length 16t = 0
word .cvtable+32t length 16t = 0
word .cvtable+64t length 16t = 0
word .cvtable+96t length 16t = 0
write using ('"***** cvtable[0..64] cleared to 0 *****"')
end

/* *************************************** */
/*+ **** cipc -- clear ipc input fifo **** */
/* *************************************** */

if listem then
write '   cipc'
endif

def proc cipc = nosource do
word .ipc_stat = 0
word .ipc_addr = 0
word .ipc_byte1 = 0
word .ipc_byte2 = 0
word .if_start = 0
word .if_end = 0
byte .ipc_fifo len 200H = 0
byte .ipc_fifo+200H len 200H = 0
byte .ipc_fifo+400H len 200H = 0
byte .ipc_fifo+600H len 200H = 0
write 'IPC input FIFO cleared'
end

/* ************************************ */
/*+ **** cregs -- dump the C regs  **** */
/* ************************************ */

if listem then
write '   cregs'
endif

def proc cregs = nosource do
def word ir_base = 0001AH
write 'C WORD registers:'
write using ('"R8 = ",>')
word ir_base
write using ('"R0 = ",>')
word ir_base+2t
write using ('"R2 = ",>')
word ir_base+4t
write using ('"R4 = ",>')
word ir_base+6t
write using ('"R6 = ",>')
word ir_base+8t
write 'C DWORD registers:'
write using ('"R0 = ",>')
dword ir_base+2t
write using ('"R4 = ",>')
dword ir_base+6t
end

/* ************************************ */
/*+ **** ddac -- dump dac cv table **** */
/* ************************************ */

if listem then
write '   ddac'
endif

def proc ddac = nosource do
write using ('"***** cvtable[0..64] *****"')
write using ('" 0..9  ",>')
word .cvtable len 10t
write using ('"10..19 ",>')
word .cvtable+20t len 10t
write using ('"20..29 ",>')
word .cvtable+40t len 10t
write using ('"30..39 ",>')
word .cvtable+60t len 10t
write using ('"40..49 ",>')
word .cvtable+80t len 10t
write using ('"50..59 ",>')
word .cvtable+100t len 10t
write using ('"60..63 ",>')
word .cvtable+120t len 4t
end

/* ********************************************** */
/*+ **** dflg -- display miscellaneous flags **** */
/* ********************************************** */

if listem then
write '   dflg'
endif

def proc dflg = nosource do
write using ('"WORD intune     = ",>')
word .intune
write using ('"WORD diagmode   = ",>')
word .diagmode
write using ('"WORD stwat_flag = ",>')
word .stwat_flag
write using ('"WORD noenv      = ",>')
word .noenv
write using ('"WORD nolfo      = ",>')
word .nolfo
write using ('"WORD nomod      = ",>')
word .nomod
write using ('"WORD bflag      = ",>')
word .bflag
write using ('"WORD sflag      = ",>')
word .sflag
end

/* ************************************** */
/*+ **** dipc -- dump ipc input fifo **** */
/* ************************************** */

if listem then
write '   dipc'
endif

def proc dipc = nosource do
write using ('"WORD ipc_stat  = ",>')
word .ipc_stat
write using ('"WORD ipc_addr  = ",>')
word .ipc_addr
write using ('"WORD ipc_byte1 = ",>')
word .ipc_byte1
write using ('"WORD ipc_byte2 = ",>')
word .ipc_byte2
write using ('"WORD if_start  = ",>')
adr .if_start
write using ('"WORD if_end    = ",>')
adr .if_end
write using ('"ipc_fifo[0..127]:"')
byte .ipc_fifo len 128t
end

/* ******************************* */
/*+ **** dtemp - dump C TEMPs **** */
/* ******************************* */

if listem then
write '   dtemp'
endif

def proc dtemp = nosource do
write 'C TEMP area as BYTEs:'
byte 234t len 10t
byte 244t len 10t
write 'C TEMP area as WORDs:'
word 234t len 10t
end

/* *************************************** */
/*+ **** dts -- display tuning status **** */
/* *************************************** */

if listem then
write '   dts'
endif

def proc dts = nosource do
def word oldbase = base
write using ('"BYTE VA.tuning = ",>')
base = binary
byte .v+5t
write using ('"BYTE VB.tuning = ",>')
byte .v+v_len+5t
base = hex
write ''
write using ('"WORD tunemax   = ",>')
word .tunemax
write using ('"WORD tunetry   = ",>')
word .tunetry
write using ('"WORD retune    = ",>')
word .retune
write ''
write using ('"WORD a_v1_tcnt = ",>')
word .a_v1_tcnt
write using ('"WORD a_v2_tcnt = ",>')
word .a_v2_tcnt
write using ('"WORD a_mm_tcnt = ",>')
word .a_mm_tcnt
write using ('"WORD a_ob_tcnt = ",>')
word .a_ob_tcnt
write ''
write using ('"WORD b_v1_tcnt = ",>')
word .b_v1_tcnt
write using ('"WORD b_v2_tcnt = ",>')
word .b_v2_tcnt
write using ('"WORD b_mm_tcnt = ",>')
word .b_mm_tcnt
write using ('"WORD b_ob_tcnt = ",>')
word .b_ob_tcnt
write ''
write using ('"WORD snapadr   = ",>')
word .snapadr
write using ('"WORD snapcnt   = ",>')
word .snapcnt
base = oldbase
end

/* *********************************************************** */
/*+ **** dvm(vb) -- display voice miscellaneous variables **** */
/* *********************************************************** */

if listem then
write '   dvm'
endif

def proc dvm = nosource do
def word v_base = .v+(%0*v_len)
write using ('"BYTE vtrig    = ",>')
byte v_base+0t
write using ('"BYTE vgate    = ",>')
byte v_base+1t
write using ('"BYTE legato   = ",>')
byte v_base+2t
write using ('"BYTE port     = ",>')
byte v_base+3t
write using ('"BYTE pedal    = ",>')
byte v_base+4t
write using ('"BYTE tuning   = ",>')
byte v_base+5t
write using ('"WORD m_level  = ",>')
word v_base+6t
write using ('"WORD p_level  = ",>')
word v_base+8t
write using ('"WORD m_pan    = ",>')
word v_base+10t
write using ('"WORD p_pan    = ",>')
word v_base+12t
write using ('"WORD v_pan    = ",>')
word v_base+14t
write using ('"WORD vel      = ",>')
word v_base+16t
write using ('"WORD note     = ",>')
word v_base+18t
write using ('"WORD note1    = ",>')
word v_base+20t
write using ('"WORD note2    = ",>')
word v_base+22t
write using ('"INT  trans    = ",>')
word v_base+24t
write using ('"INT  offset   = ",>')
word v_base+26t
write using ('"INT  pwsens   = ",>')
word v_base+28t
write using ('"WORD note_ons = ",>')
word v_base+30t
end

if listem then
write '   dvma, dvmb, dvms'		/*+ */
endif

def lit dvma = 'cls;dvm(0)'
def lit dvmb = 'cls;dvm(1)'
def lit dvms = 'cls;dvm(0);write ''-----------------------------'';dvm(1)'

/* ******************************************* */
/*+ **** sym(v) -- evaluate v as a symbol **** */
/* ******************************************* */

if listem then
write '   sym(v)'
endif

def proc sym = nosource do
eval %0 symbol
end

/* ****************************************** */
/*+ **** dcur(vb) -- dump curval[] table **** */
/* ****************************************** */

if listem then
write '   dcur(vb)'
endif

def proc dcur = nosource do
def word cur_base = .v+(%0*v_len)+cur_off
write using ('"[  0..9  ]  ",>')
word cur_base len 10t
write using ('"[ 10..19 ]  ",>')
word cur_base+20t len 10t
write using ('"[ 20..29 ]  ",>')
word cur_base+40t len 10t
write using ('"[ 30..39 ]  ",>')
word cur_base+60t len 10t
write using ('"[ 40..49 ]  ",>')
word cur_base+80t len 10t
write using ('"[ 50..59 ]  ",>')
word cur_base+100t len 10t
write using ('"[ 60..69 ]  ",>')
word cur_base+120t len 10t
write using ('"[ 70..79 ]  ",>')
word cur_base+140t len 10t
write using ('"[ 80..89 ]  ",>')
word cur_base+160t len 10t
write using ('"[ 90..99 ]  ",>')
word cur_base+180t len 10t
write using ('"[100..109]  ",>')
word cur_base+200t len 10t
write using ('"[110..111]  ",>')
word cur_base+220t len 2t
end

/* ****************************************** */
/*+ **** dout(vb) -- dump outval[] table **** */
/* ****************************************** */

if listem then
write '   dout(vb)'
endif

def proc dout = nosource do
def word out_base = .v+(%0*v_len)+out_off
write using ('"[  0..9  ]  ",>')
word out_base len 10t
write using ('"[ 10..19 ]  ",>')
word out_base+20t len 10t
write using ('"[ 20..29 ]  ",>')
word out_base+40t len 10t
write using ('"[ 30..39 ]  ",>')
word out_base+60t len 10t
write using ('"[ 40..49 ]  ",>')
word out_base+80t len 10t
write using ('"[ 50..59 ]  ",>')
word out_base+100t len 10t
write using ('"[ 60..69 ]  ",>')
word out_base+120t len 10t
write using ('"[ 70..79 ]  ",>')
word out_base+140t len 10t
write using ('"[ 80..89 ]  ",>')
word out_base+160t len 10t
write using ('"[ 90..99 ]  ",>')
word out_base+180t len 10t
write using ('"[100..109]  ",>')
word out_base+200t len 10t
write using ('"[110..111]  ",>')
word out_base+220t len 2t
end

/* ***************************************** */
/*+ **** dpv(vb) - display pitch values **** */
/* ***************************************** */

if listem then
write '   dpv(vb)'
endif

def proc dpv = nosource do
def word v_base = .v+(%0*v_len)
def word vco_base = v_base+vco_off
def word cur_base = v_base+cur_off
def word out_base = v_base+out_off
if v_base == .v then
write using ('"VA   WORD note      = ",>')
else
write using ('"VB   WORD note      = ",>')
endif
word v_base+18t
write using ('"     WORD offset    = ",>')
word v_base+26t
write using ('"outval[PP_NOTE]     = ",>')
word out_base+pp_note
write using ('"outval[PP_PITCHWHL] = ",>')
word out_base+pp_pwhl
write using ('"outval[TRANSPOSE]   = ",>')
word out_base+vt_trans
write using ('"VCO1 BYTE pitch     = ",>')
byte vco_base
write using ('"VCO1 BYTE fine      = ",>')
byte vco_base+1t
if v_base == .v then
write using ('"     INT  a_v1_off  = ",>')
word .a_v1_off
else
write using ('"     INT  b_v1_off  = ",>')
word .b_v1_off
endif
write using ('"outval[VCO1_ADJUST] = ",>')
word out_base+adj_vco1
write using ('"curval[VCO1_CNOTE]  = ",>')
word cur_base+pch_vco1
write using ('"outval[VCO1_CNOTE]  = ",>')
word out_base+pch_vco1
write using ('"cvtable[VCO1_PITCH] = ",>')
if v_base == .v then
word .cvtable+(2t*32t)
else
word .cvtable+(2t*34t)
endif
vco_base = .v+(%0*v_len)+vco_len+vco_off
write using ('"VCO2 BYTE pitch     = ",>')
byte vco_base
write using ('"VCO2 BYTE fine      = ",>')
byte vco_base+1t
if v_base == .v then
write using ('"     INT  a_v2_off  = ",>')
word .a_v2_off
else
write using ('"     INT  b_v2_off  = ",>')
word .b_v2_off
endif
write using ('"outval[VCO2_ADJUST] = ",>')
word out_base+adj_vco2
write using ('"curval[VCO2_CNOTE]  = ",>')
word cur_base+pch_vco2
write using ('"outval[VCO2_CNOTE]  = ",>')
word out_base+pch_vco2
write using ('"cvtable[VCO2_PITCH] = ",>')
if v_base == .v then
word .cvtable+(2t*36t)
else
word .cvtable+(2t*38t)
endif
end

if listem then
write '   dpvs'		/*+ */
endif

def lit dpvs = 'cls;dpv(0);dpv(1)'

/* ********************************************** */
/*+ **** dpvf(vb) - display VCF pitch values **** */
/* ********************************************** */

if listem then
write '   dpvf(vb)'
endif

def proc dpvf = nosource do
def word v_base = .v+(%0*v_len)
def word vcf_base = v_base+vcf_off
def word cur_base = v_base+cur_off
def word out_base = v_base+out_off
write using ('"Voice WORD note     = ",>')
word v_base+18t
write using ('"      WORD offset   = ",>')
word v_base+26t
write using ('"outval[PP_NOTE]     = ",>')
word out_base+pp_note
write using ('"outval[PP_PITCHWHL] = ",>')
word out_base+pp_pwhl
write using ('"outval[TRANSPOSE]   = ",>')
word out_base+vt_trans
write using ('"MM    BYTE freq     = ",>')
byte vcf_base+3t
if v_base == .v then
write using ('"      INT  a_mm_off = ",>')
word .a_mm_off
else
write using ('"      INT  b_mm_off = ",>')
word .b_mm_off
endif
write using ('"outval[MM_ADJUST]   = ",>')
word out_base+adj_mm
write using ('"curval[MM_FREQ]     = ",>')
word cur_base+frq_mm
write using ('"outval[MM_FREQ]     = ",>')
word out_base+frq_mm
write using ('"cvtable[MM_FREQ]    = ",>')
if v_base == .v then
word .cvtable+(2t*40t)
else
word .cvtable+(2t*42t)
endif
vcf_base = .v+(%0*v_len)+vcf_len+vcf_off
write using ('"OB    BYTE freq     = ",>')
byte vcf_base+3t
if v_base == .v then
write using ('"      INT  a_ob_off = ",>')
word .a_ob_off
else
write using ('"      INT  b_ob_off = ",>')
word .b_ob_off
endif
write using ('"outval[OB_ADJUST]   = ",>')
word out_base+adj_ob
write using ('"curval[OB_FREQ]     = ",>')
word cur_base+frq_ob
write using ('"outval[OB_FREQ]     = ",>')
word out_base+frq_ob
write using ('"cvtable[OB_FREQ]    = ",>')
if v_base == .v then
word .cvtable+(2t*44t)
else
word .cvtable+(2t*46t)
endif
end

if listem then
write '   dpvfs'	/*+ */
endif

def lit dpvfs = 'cls;dpvf(0);write ''--------------------'';dpvf(1)'

/* ********************************************** */
/*+ **** dvo(vb) -- dump voice offset values **** */
/* ********************************************** */

if listem then
write '   dvo(vb)'
endif

def proc dvo = nosource do
def word v_base = .v+(%0*v_len)
def word out_base = v_base+out_off
if v_base == .v then
write '------------- VOICE A -------------'
else
write '------------- VOICE B -------------'
endif
write using ('"INT  trans               = ",>')
word v_base+24t
write using ('"INT  offset              = ",>')
word v_base+26t
write using ('"INT  outval[TRANSPOSE]   = ",>')
word out_base+vt_trans
write ''
write using ('"INT  pwsens              = ",>')
word v_base+28t
write using ('"INT  outval[PP_PITCHWHL] = ",>')
word out_base+pp_pwhl
end

if listem then
write '   dvos'		/*+ */
endif

def lit dvos = 'cls;dvo(0);dvo(1)'

/* ************************************** */
/*+ **** dsv -- display scale values **** */
/* ************************************** */

if listem then
write '   dsv'
endif

def proc dsv = nosource do
write using ('"a_v1_scl     = ",>')
word .a_v1_scl
write using ('"A VCO1_SCALE = ",>')
word .cvtable+66t
write ''
write using ('"b_v1_scl     = ",>')
word .b_v1_scl
write using ('"B VCO1_SCALE = ",>')
word .cvtable+70t
write ''
write using ('"a_v2_scl     = ",>')
word .a_v2_scl
write using ('"A VCO2_SCALE = ",>')
word .cvtable+74t
write ''
write using ('"b_v2_scl     = ",>')
word .b_v2_scl
write using ('"B VCO2_SCALE = ",>')
word .cvtable+78t
write ''
write using ('"a_mm_scl     = ",>')
word .a_mm_scl
write using ('"A MM_SCALE   = ",>')
word .cvtable+82t
write ''
write using ('"b_mm_scl     = ",>')
word .b_mm_scl
write using ('"B MM_SCALE   = ",>')
word .cvtable+86t
write ''
write using ('"a_ob_scl     = ",>')
word .a_ob_scl
write using ('"A OB_SCALE   = ",>')
word .cvtable+90t
write ''
write using ('"b_ob_scl     = ",>')
word .b_ob_scl
write using ('"B OB_SCALE   = ",>')
word .cvtable+94t
end

/* ************************************** */
/*+ **** dov -- display offset values **** */
/* ************************************** */

if listem then
write '   dov'
endif

def proc dov = nosource do
write using ('"a_v1_off = ",>')
word .a_v1_off
write using ('"b_v1_off = ",>')
word .b_v1_off
write ''
write using ('"a_v2_off = ",>')
word .a_v2_off
write using ('"b_v2_off = ",>')
word .b_v2_off
write ''
write using ('"a_mm_off = ",>')
word .a_mm_off
write using ('"b_mm_off = ",>')
word .b_mm_off
write ''
write using ('"a_ob_off = ",>')
word .a_ob_off
write using ('"b_ob_off = ",>')
word .b_ob_off
end

/* ***************************************** */
/*+ **** dta -- display voice A tunings **** */
/* ***************************************** */

if listem then
write '   dta'
endif

def proc dta = nosource do
write using ('"BYTE VA.tuning = ",>')
byte .v+5t
write using ('"WORD a_v1_off  = ",>')
word .a_v1_off
write using ('"WORD a_v2_off  = ",>')
word .a_v2_off
write using ('"WORD a_mm_off  = ",>')
word .a_mm_off
write using ('"WORD a_ob_off  = ",>')
word .a_ob_off
write using ('"WORD a_v1_scl  = ",>')
word .a_v1_scl
write using ('"cvtable+v1_scl = ",>')
word .cvtable+66t
write using ('"WORD a_v2_scl  = ",>')
word .a_v2_scl
write using ('"cvtable+v2_scl = ",>')
word .cvtable+74t
write using ('"WORD a_mm_scl  = ",>')
word .a_mm_scl
write using ('"cvtable+mm_scl = ",>')
word .cvtable+82t
write using ('"WORD a_ob_scl  = ",>')
word .a_ob_scl
write using ('"cvtable+ob_scl = ",>')
word .cvtable+90t
end

/* ***************************************** */
/*+ **** dtb -- display voice B tunings **** */
/* ***************************************** */

if listem then
write '   dtb'
endif

def proc dtb = nosource do
write using ('"BYTE VB.tuning = ",>')
byte .v+v_len+5t
write using ('"WORD b_v1_off  = ",>')
word .b_v1_off
write using ('"WORD b_v2_off  = ",>')
word .b_v2_off
write using ('"WORD b_mm_off  = ",>')
word .b_mm_off
write using ('"WORD b_ob_off  = ",>')
word .b_ob_off
write using ('"WORD b_v1_scl  = ",>')
word .b_v1_scl
write using ('"cvtable+v1_scl = ",>')
word .cvtable+70t
write using ('"WORD  b_v2_scl = ",>')
word .b_v2_scl
write using ('"cvtable+v2_scl = ",>')
word .cvtable+78t
write using ('"WORD  b_mm_scl = ",>')
word .b_mm_scl
write using ('"cvtable+mm_scl = ",>')
word .cvtable+86t
write using ('"WORD  b_ob_scl = ",>')
word .b_ob_scl
write using ('"cvtable+ob_scl = ",>')
word .cvtable+94t
end

if listem then
write '   dtl'
endif

/* ***************************************** */
/*+ **** dtl(l) -- display tuning log  ***** */
/* ***************************************** */

def word tl_len = 10t	/* snap entry line length in words */
def word tl_siz = 30t	/* number of snap entries per page */

/* def word tl_len = 8t	snap entry line length in words */
/* def word tl_siz = 16t	number of snap entries per page */

def proc dtl = nosource do
base = hex

def word tl_adr = .snapbuf+(%0*tl_siz*tl_len*2t)

write '         ctl1 ctl2 a_v1 a_v2 a_mm a_ob b_v1 b_v2 b_mm b_ob'

/* write '         phse ttry stat time hcnt flgs last val ' */

/* write '         scnt phse ttry flgs APch AScl Bpch Bscl' */

word tl_adr+( 0t*tl_len*2t) len tl_len
word tl_adr+( 1t*tl_len*2t) len tl_len
word tl_adr+( 2t*tl_len*2t) len tl_len
word tl_adr+( 3t*tl_len*2t) len tl_len
word tl_adr+( 4t*tl_len*2t) len tl_len
word tl_adr+( 5t*tl_len*2t) len tl_len
write ''
word tl_adr+( 6t*tl_len*2t) len tl_len
word tl_adr+( 7t*tl_len*2t) len tl_len
word tl_adr+( 8t*tl_len*2t) len tl_len
word tl_adr+( 9t*tl_len*2t) len tl_len
word tl_adr+(10t*tl_len*2t) len tl_len
word tl_adr+(11t*tl_len*2t) len tl_len
write ''
word tl_adr+(12t*tl_len*2t) len tl_len
word tl_adr+(13t*tl_len*2t) len tl_len
word tl_adr+(14t*tl_len*2t) len tl_len
word tl_adr+(15t*tl_len*2t) len tl_len
word tl_adr+(16t*tl_len*2t) len tl_len
word tl_adr+(17t*tl_len*2t) len tl_len
write ''
word tl_adr+(18t*tl_len*2t) len tl_len
word tl_adr+(19t*tl_len*2t) len tl_len
word tl_adr+(20t*tl_len*2t) len tl_len
word tl_adr+(21t*tl_len*2t) len tl_len
word tl_adr+(22t*tl_len*2t) len tl_len
word tl_adr+(23t*tl_len*2t) len tl_len
write ''
word tl_adr+(24t*tl_len*2t) len tl_len
word tl_adr+(25t*tl_len*2t) len tl_len
word tl_adr+(26t*tl_len*2t) len tl_len
word tl_adr+(27t*tl_len*2t) len tl_len
word tl_adr+(28t*tl_len*2t) len tl_len
word tl_adr+(29t*tl_len*2t) len tl_len
end

if listem then
write '   dtae'
endif

/* ************************************************* */
/*+ **** dtea -- display voice A tuning errors ***** */
/* ************************************************* */

def proc dtea = nosource do
write using ('"WORD a_v1_e2   = ",>')
word .a_v1_e2
write using ('"WORD a_v1_e6   = ",>')
word .a_v1_e6
write ''
write using ('"WORD a_v2_e2   = ",>')
word .a_v2_e2
write using ('"WORD a_v2_e6   = ",>')
word .a_v2_e6
write ''
write using ('"WORD a_mm_e2   = ",>')
word .a_mm_e2
write using ('"WORD a_mm_e6   = ",>')
word .a_mm_e6
write ''
write using ('"WORD a_ob_e2   = ",>')
word .a_ob_e2
write using ('"WORD a_ob_e6   = ",>')
word .a_ob_e6
end

if listem then
write '   dteb'
endif

/* ************************************************* */
/*+ **** dteb -- display voice B tuning errors ***** */
/* ************************************************* */

def proc dteb = nosource do
write using ('"WORD b_v1_e2   = ",>')
word .b_v1_e2
write using ('"WORD b_v1_e6   = ",>')
word .b_v1_e6
write ''
write using ('"WORD b_v2_e2   = ",>')
word .b_v2_e2
write using ('"WORD b_v2_e6   = ",>')
word .b_v2_e6
write ''
write using ('"WORD b_mm_e2   = ",>')
word .b_mm_e2
write using ('"WORD b_mm_e6   = ",>')
word .b_mm_e6
write ''
write using ('"WORD b_ob_e2   = ",>')
word .b_ob_e2
write using ('"WORD b_ob_e6   = ",>')
word .b_ob_e6
end

if listem then
write '   dtes'
endif

def lit dtes = 'dtea;write '' '';dteb'

if listem then
write '   dxoa'
endif

/* ************************************************************ */
/*+ **** dxoa -- display VCO tuning xy values for voice A ***** */
/* ************************************************************ */

def proc dxoa = nosource do
write using ('"a_v1_off  = ",>')
word .a_v1_off
write using ('"a_v1_offy = ",>')
word .a_v1_offy
write ''
write using ('"a_v1_scl  = ",>')
word .a_v1_scl
write using ('"a_v1_scly = ",>')
word .a_v1_scly
write ''
write using ('"a_v2_off  = ",>')
word .a_v2_off
write using ('"a_v2_offy = ",>')
word .a_v2_offy
write ''
write using ('"a_v2_scl  = ",>')
word .a_v2_scl
write using ('"a_v2_scly = ",>')
word .a_v2_scly
end

if listem then
write '   dxob'
endif

/* ************************************************************ */
/*+ **** dxob -- display VCO tuning xy values for voice B ***** */
/* ************************************************************ */

def proc dxob = nosource do
write using ('"b_v1_off  = ",>')
word .b_v1_off
write using ('"b_v1_offy = ",>')
word .b_v1_offy
write ''
write using ('"b_v1_scl  = ",>')
word .b_v1_scl
write using ('"b_v1_scly = ",>')
word .b_v1_scly
write ''
write using ('"b_v2_off  = ",>')
word .b_v2_off
write using ('"b_v2_offy = ",>')
word .b_v2_offy
write ''
write using ('"b_v2_scl  = ",>')
word .b_v2_scl
write using ('"b_v2_scly = ",>')
word .b_v2_scly
end

if listem then
write '   dhsi'
endif

/* ***************************************** */
/*+ **** dhsi -- display HSI variables ***** */
/* ***************************************** */

def proc dhsi = nosource do
write using ('"hsiflags  = ",>')
word .hsiflags
write using ('"hsicount  = ",>')
word .hsicount
write using ('"hsi_isw   = ",>')
word .hsi_isw
write ''
write using ('"hsi0_cnt  = ",>')
byte .hsi0_cnt
write using ('"hsi1_last = ",>')
word .hsi1_last
write using ('"hsi1_val  = ",>')
word .hsi1_val
write ''
write using ('"hsi1_cnt  = ",>')
byte .hsi1_cnt
write using ('"hsi1_last = ",>')
word .hsi1_last
write using ('"hsi1_val  = ",>')
word .hsi1_val
write ''
write using ('"hsi2_cnt  = ",>')
byte .hsi2_cnt
write using ('"hsi2_last = ",>')
word .hsi2_last
write using ('"hsi2_val  = ",>')
word .hsi2_val
write ''
write using ('"hsi3_cnt  = ",>')
byte .hsi3_cnt
write using ('"hsi3_last = ",>')
word .hsi3_last
write using ('"hsi3_val  = ",>')
word .hsi3_val
end

write 'Loading complete.'

/* The End */
