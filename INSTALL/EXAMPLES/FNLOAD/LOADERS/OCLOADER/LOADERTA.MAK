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

ocloader.cfb: ocloader.cfs ocloader.cah 
	$(CONFIG) ocloader.cfs -o ocloader.cfb $(CONFOPT)

ocloader.cah: ocloader.lnk ocloader.tah 
	$(LINK) -f ocloader.lnk -ta -h -mo ocloader.dah -o ocloader.cah -y $(LINKOPT)

ocloader.tah: ocloader.c 
	$(CC) ocloader.c -ta -p ocloader.mah -o ocloader.tah $(COPT)

