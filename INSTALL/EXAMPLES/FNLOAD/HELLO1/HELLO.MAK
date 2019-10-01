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


all: hello.bah

hello.bah: hello.cah
	$(COLLECT) hello.cah -t  -o hello.bah $(COLLECTOPT)

hello.cah: hello.lnk hello.tah 
	$(LINK) -f hello.lnk -ta -h -o hello.cah $(LINKOPT)

hello.tah: hello.c
	$(CC) hello.c -ta -o hello.tah $(COPT)
