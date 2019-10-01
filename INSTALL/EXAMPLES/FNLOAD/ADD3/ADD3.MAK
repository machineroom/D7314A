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
LINKOPT=-me add3
CONFOPT=
OCONFOPT=
COLLECTOPT=
COPT=
F77OPT=


all: add3.rsc

add3.rsc: add3.cah
	$(COLLECT) add3.cah -t -k -o add3.rsc $(COLLECTOPT)

add3.cah: add3.tah
	$(LINK) add3.tah -ta -o add3.cah $(LINKOPT)

add3.tah: add3.c
	$(CC) add3.c -ta -o add3.tah $(COPT)
