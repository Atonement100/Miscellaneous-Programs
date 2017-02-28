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
	patch /usr/src/servers/vfs/main.c -i diff/ussv_main.diff
	patch /usr/src/lib/libsys/Makefile -i diff/usll_Makefile.diff
	cp diff/sys_flushlog.c /usr/src/lib/libsys/sys_flushlog.c
	patch /usr/src/kernel/system.h -i diff/usk_system.diff
	patch /usr/src/kernel/system/do_exit.c -i diff/usks_doexit.diff
	patch /usr/src/kernel/system/do_fork.c -i diff/usks_dofork.diff
	cp diff/do_logging.c /usr/src/kernel/system/do_logging.c
	patch /usr/src/kernel/system/Makefile.inc -i diff/usks_makefile.diff
	patch /usr/src/kernel/system.c -i diff/usk_systemc.diff
	patch /usr/src/kernel/proc.h -i diff/usk_proc.diff
	patch /usr/src/kernel/proc.c -i diff/usk_procc.diff
	patch /usr/src/kernel/glo.h -i diff/usk_glo.diff
	patch /usr/src/include/minix/com.h -i diff/usim_com.diff
	patch /usr/src/commands/service/parse.c -i diff/uscs_parse.diff
	patch /usr/src/kernel/proto.h -i diff/usk_proto.diff
	patch /usr/src/servers/pm/mproc.h -i diff/ussp_mproc.diff
	patch /usr/src/include/minix/syslib.h -i diff/usim_syslib.diff
	patch /usr/src/servers/pm/main.c -i diff/ussp_main.diff
	cp manual/* /usr/man/man2/
	cd /usr/src && $(MAKE) build
