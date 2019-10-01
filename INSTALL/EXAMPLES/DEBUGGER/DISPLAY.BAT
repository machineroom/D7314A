REM  PC dumb batch file to build debugger example program: display.bah

icc /ta /g display.c /o display.tax
ilink /ta display.tax /f cnonconf.lnk /o display.cah
icollect /t display.cah /o display.bah
