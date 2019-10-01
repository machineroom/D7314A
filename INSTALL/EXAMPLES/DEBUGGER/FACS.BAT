REM  PC dumb batch file to build debugger example program: facs.bah

icc /ta /g facs.c /o facs.tax
ilink /ta facs.tax /f cnonconf.lnk /o facs.cah
icollect /t facs.cah /o facs.bah
