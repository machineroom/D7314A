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


all: stack1.rsc

stack1.rsc: stack1.cah
	$(COLLECT) stack1.cah -t -k -o stack1.rsc $(COLLECTOPT)

stack1.cah: stack1.tah stack2.tah stack3.tah
	$(LINK) stack1.tah stack2.tah stack3.tah -ta -o stack1.cah $(LINKOPT)

stack1.tah: stack1.c
	$(CC) stack1.c -ta -o stack1.tah $(COPT)

stack2.tah: stack2.c
	$(CC) stack2.c -ta -o stack2.tah $(COPT)

stack3.tah: stack3.c
	$(CC) stack3.c -ta -o stack3.tah $(COPT) -ks
