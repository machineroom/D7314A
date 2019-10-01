icc hostpass.c /o hostpass.tco /ta /g /wt
ilink hostpass.tco /o hostpass.lku /f cstartup.lnk /ta
icc multpass.c /o multpass.tco /ta /g /wt
ilink multpass.tco /o multpass.lku /f cstartrd.lnk /ta
icc multpass.c /o multpass.t2h /t2 /g /wt
ilink multpass.t2h /o multpass.c2h /f cstartrd.lnk /t2
icconf ringt2.cfs /ro /rs 256k /p RootRing
icollect ringt2.cfb
ieprom ringt2.epr
