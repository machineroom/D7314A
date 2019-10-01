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


all: helloa.rsc hellob.rsc helloc.rsc

helloa.rsc: helloa.cah
	$(COLLECT) helloa.cah -t -k -o helloa.rsc $(COLLECTOPT)

hellob.rsc: hellob.cah
	$(COLLECT) hellob.cah -t -k -o hellob.rsc $(COLLECTOPT)

helloc.rsc: helloc.cah
	$(COLLECT) helloc.cah -t -k -o helloc.rsc $(COLLECTOPT)


helloa.cah: hello1.tah hello2.tah hello3a.tah
	$(LINK) -f helloa.lnk -ta -o helloa.cah $(LINKOPT)

hellob.cah: hello1.tah hello2.tah hello3b.tah
	$(LINK) -f hellob.lnk -ta -o hellob.cah $(LINKOPT)

helloc.cah: hello1.tah hello2.tah hello3c.tah
	$(LINK) -f helloc.lnk -ta -o helloc.cah $(LINKOPT)


hello1.tah: hello1.c
	$(CC) hello1.c -ta -o hello1.tah $(COPT)

hello2.tah: hello2.c
	$(CC) hello2.c -ta -o hello2.tah $(COPT)

hello3a.tah: hello3a.c
	$(CC) hello3a.c -ta -o hello3a.tah $(COPT)

hello3b.tah: hello3b.c
	$(CC) hello3b.c -ta -o hello3b.tah $(COPT)

hello3c.tah: hello3c.c
	$(CC) hello3c.c -ta -o hello3c.tah $(COPT)
