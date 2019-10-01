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
CONFOPT=
OCONFOPT=
COLLECTOPT=
COPT=
F77OPT=


all: simplest.bah

simplest.bah: simplest.cah 
	$(COLLECT) simplest.cah -t  -o simplest.bah $(COLLECTOPT)

simplest.cah: simplest.lnk simplest.tah 
	$(LINK) -f simplest.lnk -ta -h -o simplest.cah $(LINKOPT)

simplest.tah: simplest.c 
	$(CC) simplest.c -ta -o simplest.tah $(COPT)
