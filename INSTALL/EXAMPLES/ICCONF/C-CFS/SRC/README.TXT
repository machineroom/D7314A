(c) Copyright INMOS Ltd 1990, 1991, 1992. All Rights Reserved.

INMOS ANSI C Toolset ICCONF Examples
====================================

This directory contains the configuration programs which are supplied
as part of the INMOS ANSI C Toolset to provide examples for the icconf
configuration tool.

(It is assumed in the example configurations that they will use an IMS
B008 or compatible evaluation board, therefore there are also supplied
files which can be used with the INMOS Module Motherboard Software to
setup an IMS B008 or compatible board for use with these examples.)

For each example configuration program there are supplied files which
can be used for building the example. For all hosts there is a generic
make file that can be used with a UNIX style make utility and if there
is no make utility available as standard for the host then batch files
are also supplied.

The supplied make files are constructed so that they can be used from
any host with a UNIX style make utility without modification. This is
achieved by specifying to the make utility the switch character for the
host which will then be used by the tools called from the make file.

The following is a list of example command lines for calling the make
utility for each of the currently supported hosts:

    PC   : make S=/ -f <makefile>
    Sun3 : make S=- -f <makefile>
    Sun4 : make S=- -f <makefile>
    VAX  : make S=/ -f <makefile>

Note that the -f option is used to specify the name of the make file to
be used by the make utility and the S=<character> option specifies the
switch character (<character>) for the host.

There are supplied two sets of make and batch files for building either
boot from link or boot from ROM versions of the examples.

For each of the hosts supported by this toolset the following list
specifies the directories which contain the boot from link and boot
from ROM versions of the make and batch files and the directory which
contains the hardware files (which are relative to this directory):

i) PC Toolset

    * Generic hardware files : ..\..\hw-cfs\*.cfs
    * Boot from ROM make files : ..\mkf\btr\*.mkf
    * Boot from link make files : ..\mkf\btl\*.mkf
    * Boot from ROM batch files : ..\bat\btr\*.bat
    * Boot from link batch files : ..\bat\btl\*.bat

ii) Sun3/Sun4 Toolsets

    * Generic hardware files : ../../hw-cfs/*.cfs
    * Boot from ROM make files : ../mkf/btr/*.mkf
    * Boot from link make files : ../mkf/btl/*.mkf

iii) VAX Toolset

    * Generic hardware files : [--.hw-cfs]*.cfs
    * Boot from ROM make files : [-.mkf.btr]*.mkf
    * Boot from link make files : [-.mkf.btl]*.mkf
    * Boot from ROM batch files : [-.com.btr]*.com
    * Boot from link batch files : [-.com.btl]*.com

IMPORTANT: the directory which contains the hardware files should be
added to the front of the ISEARCH search path.

1 Jun 1992
