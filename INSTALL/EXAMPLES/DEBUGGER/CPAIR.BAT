REM  PC dumb batch file to build debugger example program: cpair.btl

icc master.c /ta /g
icc mult.c /ta /g
ilink master.tco /ta /f cstartup.lnk
ilink mult.tco /ta /f cstartrd.lnk
icconf /g /nv cpair.cfs /w
icollect cpair.cfb
