@echo off
echo Most recent version stored to 'previous' at >lastver.dat
today x >>lastver.dat
echo ----- copying current files to \oberbuch\previous\...
copy \oberbuch\*.* \oberbuch\previous
copy \oberbuch\afiles\*.* \oberbuch\previous\afiles
copy \oberbuch\cfiles\*.* \oberbuch\previous\cfiles
copy \oberbuch\doc\*.* \oberbuch\previous\doc
