@echo off
echo ----- copying current files to \oberbuch\previous\...
del lastver.dat
echo Most recent version stored to 'previous' at >lastver.dat
today x >>lastver.dat
copy \oberbuch\*.* \oberbuch\previous
copy \oberbuch\afiles\*.* \oberbuch\previous\afiles
copy \oberbuch\cfiles\*.* \oberbuch\previous\cfiles
copy \oberbuch\doc\*.* \oberbuch\previous\doc
cat lastver.dat
