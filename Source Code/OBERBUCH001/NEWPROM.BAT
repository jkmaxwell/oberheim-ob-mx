@echo off
call clean
md \oberbuch\%1
md \oberbuch\%1\afiles
md \oberbuch\%1\cfiles
md \oberbuch\%1\doc
echo ----- copying current files to \oberbuch\%1\...
echo Most recent version stored to '%1' at >lastver.dat
today x >>lastver.dat
copy \oberbuch\*.* \oberbuch\%1
copy \oberbuch\afiles\*.* \oberbuch\%1\afiles
copy \oberbuch\cfiles\*.* \oberbuch\%1\cfiles
copy \oberbuch\doc\*.* \oberbuch\%1\doc
