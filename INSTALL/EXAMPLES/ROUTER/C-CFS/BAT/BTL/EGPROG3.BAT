icc filter.c /o filter.tco /ta /g /wt
ilink filter.tco /o filter.lku /f cstartrd.lnk /ta
icc generate.c /o generate.tco /ta /g /wt
ilink generate.tco /o generate.lku /f cstartrd.lnk /ta
icc monitor.c /o monitor.tco /ta /g /wt
ilink monitor.tco /o monitor.lku /f cstartup.lnk /ta
icc result.c /o result.tco /ta /g /wt
ilink result.tco /o result.lku /f cstartrd.lnk /ta
icconf egprog3.cfs
icollect egprog3.cfb
