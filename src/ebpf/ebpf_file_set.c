/*
 * Copyright 2017, Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *
 *     * Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * ebpf_file_set.c -- A set of ebpf files
 */

#include <stdlib.h>
#include <string.h>

#include "ebpf_file_set.h"

const char *ebpf_trace_h_file =		"trace.h";
const char *ebpf_head_file =		"trace_head.c";

const char *ebpf_0_str_file =		"template_0_str.c";

const char *ebpf_1_str_sl_file =	"template_1_str-sl.c";
const char *ebpf_2_str_sl_file =	"template_2_str-sl.c";
const char *ebpf_3_str_sl_file =	"template_3_str-sl.c";

const char *ebpf_2_str_ml_file =	"template_2_str-ml.c";
const char *ebpf_3_str_ml_file =	"template_3_str-ml.c";

const char *ebpf_1_str_const_file =	"template_1_str-const.c";
const char *ebpf_2_str_const_file =	"template_2_str-const.c";
const char *ebpf_3_str_const_file =	"template_3_str-const.c";

const char *ebpf_1_str_full_file =	"template_1_str-full.c";
const char *ebpf_2_str_full_file =	"template_2_str-full.c";
const char *ebpf_3_str_full_file =	"template_3_str-full.c";

const char *ebpf_fork_file =		"template_fork.c";
const char *ebpf_exit_file =		"template_exit.c";

const char *ebpf_tracepoints_file =	"template_tracepoints.c";

const char *ebpf_const_string_mode =	"macro_const_string_mode.c";
const char *ebpf_full_string_mode =	"macro_full_string_mode.c";

const char *ebpf_pid_own_file =		"macro_pid_own.c";
const char *ebpf_pid_ff_disabled_file = "macro_pid_ff_disabled.c";
const char *ebpf_pid_ff_full_file =	"macro_pid_ff_full.c";


const char *ebpf_file_table[4][4] = {
	{
		"template_0_str.c",
		"template_0_str.c",
		"template_0_str.c",
		"template_0_str.c",
	},
	{
		"template_1_str-sl.c",
		"template_1_str-sl.c",
		"template_1_str-const.c",
		"template_1_str-full.c",
	},
	{
		"template_2_str-sl.c",
		"template_2_str-ml.c",
		"template_2_str-const.c",
		"template_2_str-full.c",
	},
	{
		"template_3_str-sl.c",
		"template_3_str-ml.c",
		"template_3_str-const.c",
		"template_3_str-full.c",
	}
};

/*
 * ebpf_load_file -- return strndup() from embedded body of a 'virtual' file
 */
char *
ebpf_load_file(const char *const fn)
{
	if (fn == NULL)
		return NULL;

	/* fallback to embedded ones */
	if (strcmp(ebpf_trace_h_file, fn) == 0)
		return BINARY_FILE_CONTENT(trace_h);

	if (strcmp(ebpf_head_file, fn) == 0)
		return BINARY_FILE_CONTENT(trace_head_c);

	if (strcmp(ebpf_0_str_file, fn) == 0)
		return BINARY_FILE_CONTENT(template_0_str_c);

	if (strcmp(ebpf_1_str_sl_file, fn) == 0)
		return BINARY_FILE_CONTENT(template_1_str_sl_c);

	if (strcmp(ebpf_1_str_const_file, fn) == 0)
		return BINARY_FILE_CONTENT(template_1_str_const_c);

	if (strcmp(ebpf_1_str_full_file, fn) == 0)
		return BINARY_FILE_CONTENT(template_1_str_full_c);

	if (strcmp(ebpf_2_str_sl_file, fn) == 0)
		return BINARY_FILE_CONTENT(template_2_str_sl_c);

	if (strcmp(ebpf_2_str_ml_file, fn) == 0)
		return BINARY_FILE_CONTENT(template_2_str_ml_c);

	if (strcmp(ebpf_2_str_const_file, fn) == 0)
		return BINARY_FILE_CONTENT(template_2_str_const_c);

	if (strcmp(ebpf_2_str_full_file, fn) == 0)
		return BINARY_FILE_CONTENT(template_2_str_full_c);

	if (strcmp(ebpf_3_str_sl_file, fn) == 0)
		return BINARY_FILE_CONTENT(template_3_str_sl_c);

	if (strcmp(ebpf_3_str_ml_file, fn) == 0)
		return BINARY_FILE_CONTENT(template_3_str_ml_c);

	if (strcmp(ebpf_3_str_const_file, fn) == 0)
		return BINARY_FILE_CONTENT(template_3_str_const_c);

	if (strcmp(ebpf_3_str_full_file, fn) == 0)
		return BINARY_FILE_CONTENT(template_3_str_full_c);

	if (strcmp(ebpf_fork_file, fn) == 0)
		return BINARY_FILE_CONTENT(template_fork_c);

	if (strcmp(ebpf_exit_file, fn) == 0)
		return BINARY_FILE_CONTENT(template_exit_c);

	if (strcmp(ebpf_tracepoints_file, fn) == 0)
		return BINARY_FILE_CONTENT(template_tracepoints_c);

	if (strcmp(ebpf_const_string_mode, fn) == 0)
		return BINARY_FILE_CONTENT(macro_const_string_mode_c);

	if (strcmp(ebpf_full_string_mode, fn) == 0)
		return BINARY_FILE_CONTENT(macro_full_string_mode_c);

	if (strcmp(ebpf_pid_own_file, fn) == 0)
		return BINARY_FILE_CONTENT(macro_pid_own_c);

	if (strcmp(ebpf_pid_ff_disabled_file, fn) == 0)
		return BINARY_FILE_CONTENT(macro_pid_ff_disabled_c);

	if (strcmp(ebpf_pid_ff_full_file, fn) == 0)
		return BINARY_FILE_CONTENT(macro_pid_ff_full_c);

	return NULL;
}
