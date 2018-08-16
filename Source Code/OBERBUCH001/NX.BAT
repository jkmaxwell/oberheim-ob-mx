@echo off
echo Making new VOICE.OUT in Intel-standard format
del afiles\*.bak
del afiles\*.tmp
del afiles\*.srt
del afiles\pt.las
del cfiles\*.bak
del cfiles\*.tmp
del cfiles\*.srt
del cfiles\pt.las
del obj\*.bak
del obj\*.lst
del obj\*.r15
del obj\*.tmp
del obj\*.srt
del obj\pt.las
del *.bak
del *.tmp
del *.lst
del *.srt
del voice.out
del errs
del pt.las
nmake /s /f makehex >errs
br errs
