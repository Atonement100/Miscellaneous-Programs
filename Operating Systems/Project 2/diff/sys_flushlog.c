#include "syslib.h"

int sys_flushlog(unsigned flags, endpoint_t proc_ep){
	message m;

	return(_kernel_call(SYS_FLUSHLOG, &m));
}

int sys_updatetracking(unsigned flags, endpoint_t proc_ep, int target_endpt, int target_pid, int new_tracking_state){
	message m;

	m.m2_i1 = target_endpt;
	m.m2_i2 = new_tracking_state;
	m.m2_i3 = flags;
	m.m2_l1 = target_pid;

	return(_kernel_call(SYS_UPDATETRACKING, &m));
}

int sys_retrievelog(message *m_ptr){
	return(_kernel_call(SYS_RETRIEVELOG, m_ptr));
}
