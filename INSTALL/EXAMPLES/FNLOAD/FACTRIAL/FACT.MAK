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


all: fact.bah

fact.bah: fact.cah
	$(COLLECT) fact.cah -t  -o fact.bah $(COLLECTOPT)

fact.cah: fact.lnk fact.tah 
	$(LINK) -f fact.lnk -ta -h -o fact.cah $(LINKOPT)

fact.tah: fact.c
	$(CC) fact.c -ta -o fact.tah $(COPT)
