icc lowhigh.c /o lowhigh.tco /ta /g /wt
ilink lowhigh.tco /o lowhigh.lku /f cstartup.lnk /ta
icc hostmult.c /o hostmult.tco /ta /g /wt
ilink hostmult.tco /o hostmult.lku /f cstartrd.lnk /ta
icconf lowhigh1.cfs /ro /rs 256k /p Root
icollect lowhigh1.cfb
ieprom lowhigh1.epr
