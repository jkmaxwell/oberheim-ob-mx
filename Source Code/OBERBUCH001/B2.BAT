@echo off
echo ----- copying current files to \oberbuch\former\...
del lastver.dat
echo Most recent version stored to 'former' at >lastver.dat
today x >>lastver.dat
copy \oberbuch\*.* \oberbuch\former
copy \oberbuch\afiles\*.* \oberbuch\former\afiles
copy \oberbuch\cfiles\*.* \oberbuch\former\cfiles
copy \oberbuch\doc\*.* \oberbuch\former\doc
cat lastver.dat
