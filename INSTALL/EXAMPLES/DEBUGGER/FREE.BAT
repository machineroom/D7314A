REM  PC dumb batch file to build debugger example program: free.bah

icc /ta /g free.c /o free.tax
ilink /ta free.tax /f cnonconf.lnk /o free.cah
icollect /t free.cah /o free.bah
