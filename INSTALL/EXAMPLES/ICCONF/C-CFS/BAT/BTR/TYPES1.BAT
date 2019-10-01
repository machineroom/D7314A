icc types.c /o types.tco /ta /g /wt
ilink types.tco /o types.lku /f cstartup.lnk /ta
icconf types1.cfs /ro /rs 256k /p Root
icollect types1.cfb
ieprom types1.epr
