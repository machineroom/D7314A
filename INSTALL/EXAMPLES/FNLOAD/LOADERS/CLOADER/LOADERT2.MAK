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
# Used 'imakef cloader.btl -y -d -c -ni -m' to generate this makefile's
# commands; note the 'nv' option added to CONFOPT above
#

##### IMAKEF CUT #####

cloader.btl: cloader.cfb 
	$(COLLECT) cloader.cfb -p cloader.map -o cloader.btl $(COLLECTOPT)

cloader.cfb: cloader.cfs cloader.c2h 
	$(CONFIG) cloader.cfs -o cloader.cfb $(CONFOPT)

cloader.c2h: cloader.lnk cloader.t2h 
	$(LINK) -f cloader.lnk -t2 -h -mo cloader.d2h -o cloader.c2h -y $(LINKOPT)

cloader.t2h: cloader.c 
	$(CC) cloader.c -t2 -p cloader.m2h -o cloader.t2h $(COPT)

