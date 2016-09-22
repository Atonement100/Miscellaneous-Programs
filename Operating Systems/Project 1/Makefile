test: 
	patch /usr/src/include/unistd.h -i diff/usi_unistd.diff
	patch /usr/src/include/minix/callnr.h -i diff/usim_callnr.diff
	cp diff/logprocs.c /usr/src/lib/libc/sys-minix/logprocs.c
	patch /usr/src/lib/libc/sys-minix/Makefile.inc -i diff/uslls_makefile.diff
	cp diff/do_logprocs.c /usr/src/servers/pm/do_logprocs.c
	patch /usr/src/servers/pm/forkexit.c -i diff/ussp_forkexit.diff
	patch /usr/src/servers/pm/glo.h -i diff/ussp_glo.diff
	patch /usr/src/servers/pm/Makefile -i diff/ussp_Makefile.diff
	patch /usr/src/servers/pm/proto.h -i diff/ussp_proto.diff
	patch /usr/src/servers/pm/table.c -i diff/ussp_table.diff
	patch /usr/src/servers/pm/type.h -i diff/ussp_type.diff
	cp manual/* /usr/man/man2/
	cd /usr/src/releasetools && $(MAKE) hdboot
	cd /usr/src && $(MAKE) build
