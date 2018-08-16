@echo off
copy d:\util\fgrep.exe f:\
f:\fgrep -os -f adoc.fgd afiles\CALC.A afiles\DOMODS.A afiles\DOSRC.A >fgd.tmp
f:\fgrep -os -f adoc.fgd afiles\ENV.A afiles\GATE.A >>fgd.tmp
f:\fgrep -os -f adoc.fgd afiles\HDW.A afiles\LFO.A afiles\QPOTS.A >>fgd.tmp
f:\fgrep -os -f adoc.fgd afiles\TUNE.A afiles\VOICEA.A >>fgd.tmp
f:\fgrep -os -f cdoc.fgd cfiles\IPC1.C cfiles\IPC2.C cfiles\MAIN.C >>fgd.tmp
f:\fgrep -os -f cdoc.fgd cfiles\MODS.C cfiles\TABLES1.C cfiles\TABLES2.C >>fgd.tmp
f:\fgrep -os -f cdoc.fgd cfiles\TABLES3.C cfiles\VARS.C >>fgd.tmp
echo ; The End >>fgd.tmp
del f:\fgrep.exe
pt fgd.tmp
