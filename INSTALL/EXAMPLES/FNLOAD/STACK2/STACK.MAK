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


all: stack.bah

stack.bah: stack.cah
	$(COLLECT) stack.cah -t  -o stack.bah $(COLLECTOPT)

stack.cah: stack.lnk stack.tah 
	$(LINK) -f stack.lnk -ta -h -o stack.cah $(LINKOPT)

stack.tah: stack.c
	$(CC) stack.c -ta -o stack.tah $(COPT)
