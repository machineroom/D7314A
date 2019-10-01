icc proc1.c /o proc1.tco /ta /g /wt
ilink proc1.tco /o proc1.lku /f cstartup.lnk /ta
icc proc2.c /o proc2.tco /ta /g /wt
ilink proc2.tco /o proc2.lku /f cstartrd.lnk /ta
icconf egprog2.cfs
icollect egprog2.cfb
