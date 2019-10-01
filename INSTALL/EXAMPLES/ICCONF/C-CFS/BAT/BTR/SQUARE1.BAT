icc hostpass.c /o hostpass.tco /ta /g /wt
ilink hostpass.tco /o hostpass.lku /f cstartup.lnk /ta
icc multpass.c /o multpass.tco /ta /g /wt
ilink multpass.tco /o multpass.lku /f cstartrd.lnk /ta
icconf square1.cfs /ro /rs 256k /p Root
icollect square1.cfb
ieprom square1.epr
