@echo off
echo ----- copying current files to \oberbuch\oldver\...
echo Most recent version stored to 'oldver' at >lastver.dat
today x >>lastver.dat
copy \oberbuch\*.* \oberbuch\oldver
copy \oberbuch\afiles\*.* \oberbuch\oldver\afiles
copy \oberbuch\cfiles\*.* \oberbuch\oldver\cfiles
copy \oberbuch\doc\*.* \oberbuch\oldver\doc
