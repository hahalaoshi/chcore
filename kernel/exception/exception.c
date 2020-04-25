/*
 * Copyright (c) 2020 Institute of Parallel And Distributed Systems (IPADS),
 * Shanghai Jiao Tong University (SJTU) OS-Lab-2020 (i.e., ChCore) is licensed
 * under the Mulan PSL v1. You can use this software according to the terms and
 * conditions of the Mulan PSL v1. You may obtain a copy of Mulan PSL v1 at:
 *   http://license.coscl.org.cn/MulanPSL
 *   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE. See the
 * Mulan PSL v1 for more details.
 */

#include "exception.h"
#include "esr.h"
#include <common/kprint.h>
#include <lib/types.h>
#include <common/util.h>
#include <exception/irq.h>
#include <exception/pgfault.h>
#include <sched/sched.h>

void exception_init_per_cpu(void)
{
	/**
	 * Lab3: Your code here
	 * Setup the exception vector with the asm function written in exception.S
	 */
	set_exception_vector();
	// enable_irq();
	// disable_irq();
}

void exception_init(void)
{
	exception_init_per_cpu();
}

void handle_entry_c(int type, u64 esr, u64 address)
{
	/* ec: exception class */
	u32 esr_ec = GET_ESR_EL1_EC(esr);
	// kinfo("interupt = %d\n", type);
	// kinfo("esr = %d\n", esr_ec);
	kdebug(
	    "Interrupt type: %d, ESR: 0x%lx, Fault address: 0x%lx, EC 0b%b\n",
	    type, esr, address, esr_ec);
	/* Dispatch exception according to EC */
	switch (esr_ec) {
	/*
	 * Lab3: Your code here
	 * Handle exceptions as required in the lab document. Checking exception codes in
	 * esr.h may help.
	 */
	case ESR_EL1_EC_DABT_LEL:
		// kinfo("hello\n");
		do_page_fault(esr, address);
		break;
	case ESR_EL1_EC_DABT_CEL:
		// kinfo("hello1\n");
		do_page_fault(esr, address);
		break;
	default:
		kdebug("Unsupported Exception ESR %lx\n", esr);
		kinfo(UNKNOWN);
		sys_exit(-ESUPPORT);
		break;
	}
}
