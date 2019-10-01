icc hellop.c /o hellop.tco /ta /g /wt
ilink hellop.tco /o hellop.lku /f cstartup.lnk /ta
icc worldp.c /o worldp.tco /ta /g /wt
ilink worldp.tco /o worldp.lku /f cstartup.lnk /ta
icc hostmult.c /o hostmult.tco /ta /g /wt
ilink hostmult.tco /o hostmult.lku /f cstartrd.lnk /ta
icconf hello2.cfs /ro /rs 256k /p Root
icollect hello2.cfb
ieprom hello2.epr
