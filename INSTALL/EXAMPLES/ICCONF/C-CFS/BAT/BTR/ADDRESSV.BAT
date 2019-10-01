icc address.c /o address.tco /ta /g /wt
ilink address.tco /o address.lku /f cstartup.lnk /ta
icc hostmult.c /o hostmult.tco /ta /g /wt
ilink hostmult.tco /o hostmult.lku /f cstartrd.lnk /ta
icconf addressv.cfs /ra /rs 256k /p RootPipe
icollect addressv.cfb
ieprom addressv.epr
