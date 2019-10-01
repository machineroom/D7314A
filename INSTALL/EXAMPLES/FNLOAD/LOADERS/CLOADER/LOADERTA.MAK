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

cloader.cfb: cloader.cfs cloader.cah 
	$(CONFIG) cloader.cfs -o cloader.cfb $(CONFOPT)

cloader.cah: cloader.lnk cloader.tah 
	$(LINK) -f cloader.lnk -ta -h -mo cloader.dah -o cloader.cah -y $(LINKOPT)

cloader.tah: cloader.c 
	$(CC) cloader.c -ta -p cloader.mah -o cloader.tah $(COPT)
