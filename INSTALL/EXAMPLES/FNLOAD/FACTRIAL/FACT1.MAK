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
LINKOPT=-me c_fnload_stage1 -f clibs.lnk 
CONFOPT=
OCONFOPT=
COLLECTOPT=
COPT=
F77OPT=


all: fact1.rsc

fact1.rsc: fact1.cah
	$(COLLECT) fact1.cah -t -k -o fact1.rsc $(COLLECTOPT)

fact1.cah: fact1.tah fact2.tah fact3.tah
	$(LINK) fact1.tah fact2.tah fact3.tah -ta -o fact1.cah $(LINKOPT)

fact1.tah: fact1.c
	$(CC) fact1.c -ta -o fact1.tah $(COPT)

fact2.tah: fact2.c
	$(CC) fact2.c -ta -o fact2.tah $(COPT)

fact3.tah: fact3.c
	$(CC) fact3.c -ta -o fact3.tah $(COPT) -ks
