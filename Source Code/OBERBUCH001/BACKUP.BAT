@echo off
echo ---- Deleting scratch files from \oberbuch ------
del \oberbuch\*.bak
del \oberbuch\*.srt
del \oberbuch\*.tmp
del \oberbuch\diffs
del \oberbuch\errs
del \oberbuch\pt.las
del \oberbuch\voice.out
del \oberbuch\voice.lst
echo ---- Deleting scratch files from \oberbuch\afiles
del \oberbuch\afiles\*.bak
del \oberbuch\afiles\*.srt
del \oberbuch\afiles\*.tmp
del \oberbuch\afiles\pt.las
echo ---- Deleting scratch files from \oberbuch\cfiles
del \oberbuch\cfiles\*.bak
del \oberbuch\cfiles\*.srt
del \oberbuch\cfiles\*.tmp
del \oberbuch\cfiles\pt.las
echo ---- Deleting scratch files from \oberbuch\doc --
del \oberbuch\doc\*.bak
del \oberbuch\doc\*.srt
del \oberbuch\doc\*.tmp
del \oberbuch\doc\pt.las
echo ---- Copying files to B: ------------------------
copy \oberbuch\*.* b:\oberbuch
copy \oberbuch\afiles\*.* b:\oberbuch\afiles
copy \oberbuch\cfiles\*.* b:\oberbuch\cfiles
copy \oberbuch\doc\*.* b:\oberbuch\doc
echo Last backup made at >\oberbuch\lastback.dat
today x >>\oberbuch\lastback.dat
copy \oberbuch\lastback.dat b:\oberbuch
type \oberbuch\lastback.dat
