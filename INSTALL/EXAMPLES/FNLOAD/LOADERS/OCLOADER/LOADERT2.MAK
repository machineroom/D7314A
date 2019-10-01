LIBRARIAN=ilibr
OCCAM=oc
LINK=ilink
CONFIG=icconf
OCONFIG=occonf
COLLECT=icollect
CC=icc
FORTRAN=if77
DELETE=rm
LIBOPT=
OCCOPT=
LINKOPT=
CONFOPT=-nv
OCONFOPT=
COLLECTOPT=
COPT=
F77OPT=

#
# Used 'imakef ocloader.btl -y -d -c -ni -m' to generate this makefile's
# commands; note the 'nv' option added to CONFOPT above
#

##### IMAKEF CUT #####

ocloader.btl: ocloader.cfb 
	$(COLLECT) ocloader.cfb -p ocloader.map -o ocloader.btl $(COLLECTOPT)

ocloader.cfb: ocloader.cfs ocloader.c2h 
	$(CONFIG) ocloader.cfs -o ocloader.cfb $(CONFOPT)

ocloader.c2h: ocloader.lnk ocloader.t2h 
	$(LINK) -f ocloader.lnk -t2 -h -mo ocloader.d2h -o ocloader.c2h -y $(LINKOPT)

ocloader.t2h: ocloader.c 
	$(CC) ocloader.c -t2 -p ocloader.m2h -o ocloader.t2h $(COPT)

