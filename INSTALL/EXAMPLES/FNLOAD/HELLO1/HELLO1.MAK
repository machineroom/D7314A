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


all: hello1.rsc

hello1.rsc: hello1.cah
	$(COLLECT) hello1.cah -t -k -o hello1.rsc $(COLLECTOPT)

hello1.cah: hello1.tah hello2.tah hello3.tah
	$(LINK) hello1.tah hello2.tah hello3.tah -ta -o hello1.cah $(LINKOPT)

hello1.tah: hello1.c
	$(CC) hello1.c -ta -o hello1.tah $(COPT)

hello2.tah: hello2.c
	$(CC) hello2.c -ta -o hello2.tah $(COPT)

hello3.tah: hello3.c
	$(CC) hello3.c -ta -o hello3.tah $(COPT)
