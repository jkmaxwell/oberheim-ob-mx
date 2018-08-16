@echo off
echo ---- Deleting scratch files from \oberbuch\afiles
del \oberbuch\afiles\*.bak
del \oberbuch\afiles\*.tmp
del \oberbuch\afiles\*.srt
del \oberbuch\afiles\pt.las
echo ---- Deleting scratch files from \oberbuch\cfiles
del \oberbuch\cfiles\*.bak
del \oberbuch\cfiles\*.tmp
del \oberbuch\cfiles\*.srt
del \oberbuch\cfiles\pt.las
echo ---- Deleting scratch files from \oberbuch\doc --
del \oberbuch\doc\*.bak
del \oberbuch\doc\*.tmp
del \oberbuch\doc\*.srt
del \oberbuch\doc\pt.las
echo ---- Deleting scratch files from \oberbuch\obj --
del \oberbuch\obj\*.bak
del \oberbuch\obj\*.tmp
del \oberbuch\obj\*.srt
del \oberbuch\obj\pt.las
echo ---- Deleting scratch files from \oberbuch ------
del \oberbuch\*.bak
del \oberbuch\*.tmp
del \oberbuch\*.srt
del \oberbuch\errs
del \oberbuch\pt.las
hd \oberbuch /c/e/6
