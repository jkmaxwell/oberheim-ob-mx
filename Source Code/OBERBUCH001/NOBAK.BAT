@echo off
echo ----- deleting *.bak and pt.las files
echo ----- from \oberbuch
del \oberbuch\*.bak
del \oberbuch\pt.las
del \oberbuch\afiles\*.bak
del \oberbuch\afiles\pt.las
del \oberbuch\cfiles\*.bak
del \oberbuch\cfiles\pt.las
del \oberbuch\doc\*.bak
del \oberbuch\doc\pt.las
del \oberbuch\obj\*.bak
del \oberbuch\obj\pt.las
del \oberbuch\tests\*.bak
del \oberbuch\tests\pt.las
hd \oberbuch /c/e/6
