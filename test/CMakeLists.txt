#
# Copyright 2017, Intel Corporation
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in
#       the documentation and/or other materials provided with the
#       distribution.
#
#     * Neither the name of the copyright holder nor the names of its
#       contributors may be used to endorse or promote products derived
#       from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

add_cstyle(test)

add_c_flag(-Wno-unused-result)

include_directories(${PROJECT_BINARY_DIR})
include(FindThreads)

add_executable(test_syscalls test_syscalls.c)
target_link_libraries(test_syscalls ${CMAKE_THREAD_LIBS_INIT})

# check if the running kernel meets version requirements
execute_process(COMMAND utils/check-kernel.sh ${VLTRACE_MINIMUM_KERNEL_VERSION}
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		RESULT_VARIABLE VLTRACE_KERNEL_OK)

if (NOT ${VLTRACE_KERNEL_OK} EQUAL 0)
	message( WARNING "Tests skipped (required kernel >= ${VLTRACE_MINIMUM_KERNEL_VERSION})" )
else ()

	# running kernel meets version requirements, so we can add tests
	set(TEST_APP "./test_syscalls")
	set(TEST_DIR "${CMAKE_SOURCE_DIR}/test")

	#
	# TESTS
	#
	foreach(OUTPUT_FORMAT "binary" "text")

		if (${OUTPUT_FORMAT} STREQUAL "text")
			set(FMT "-t")
			# Turn on the delay (busy wait) between syscalls only in the text mode,
			# because the text mode is much slower and it needs more time
			# for packet processing before the next packet arrives.
			set(WAIT "wait")
		else ()
			set(FMT "")
			set(WAIT "do-not-wait")
		endif ()

		foreach(STR_LEN 126 382)
			# 1
			add_test(NAME "${OUTPUT_FORMAT}-${STR_LEN}-basic-syscalls"
				COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 0 ${STR_LEN})

			# 2
			add_test(NAME "${OUTPUT_FORMAT}-${STR_LEN}-basic-syscalls-with-fork"
				COMMAND ${TEST_DIR}/test-match ${FMT} -f ${TEST_APP} ${WAIT} 1 ${STR_LEN})

			# 3
			add_test(NAME "${OUTPUT_FORMAT}-${STR_LEN}-basic-syscalls-with-double-fork"
				COMMAND ${TEST_DIR}/test-match ${FMT} -f ${TEST_APP} ${WAIT} 5 ${STR_LEN})

			# 4
			add_test(NAME "${OUTPUT_FORMAT}-${STR_LEN}-unsupported-syscalls"
				COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 2 ${STR_LEN})

			# 5
			add_test(NAME "${OUTPUT_FORMAT}-${STR_LEN}-unsupported-syscalls-with-fork"
				COMMAND ${TEST_DIR}/test-match ${FMT} -f ${TEST_APP} ${WAIT} 3 ${STR_LEN})

			# 6
			add_test(NAME "${OUTPUT_FORMAT}-${STR_LEN}-unsupported-syscalls-with-double-fork"
				COMMAND ${TEST_DIR}/test-match ${FMT} -f ${TEST_APP} ${WAIT} 6 ${STR_LEN})

			# 7
			add_test(NAME "${OUTPUT_FORMAT}-${STR_LEN}-syscall-vfork"
				COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 4 ${STR_LEN})

			# 8
			add_test(NAME "${OUTPUT_FORMAT}-${STR_LEN}-syscall-sigaction"
				COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 7 ${STR_LEN})
		endforeach(STR_LEN)

		add_test(NAME "${OUTPUT_FORMAT}-126-syscalls-string-arguments-126"
			COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 8 126)
		add_test(NAME "${OUTPUT_FORMAT}-126-syscalls-string-arguments-382"
			COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 8 382)
		add_test(NAME "${OUTPUT_FORMAT}-126-syscalls-string-arguments-765"
			COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 8 765)
		add_test(NAME "${OUTPUT_FORMAT}-126-syscalls-string-arguments-1148"
			COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 8 1148)
		add_test(NAME "${OUTPUT_FORMAT}-126-syscalls-string-arguments-1531"
			COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 8 1531)

		add_test(NAME "${OUTPUT_FORMAT}-382-syscalls-string-arguments-382"
			COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 9 382)
		add_test(NAME "${OUTPUT_FORMAT}-382-syscalls-string-arguments-765"
			COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 9 765)
		add_test(NAME "${OUTPUT_FORMAT}-382-syscalls-string-arguments-1148"
			COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 9 1148)
		add_test(NAME "${OUTPUT_FORMAT}-382-syscalls-string-arguments-1531"
			COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 9 1531)

		add_test(NAME "${OUTPUT_FORMAT}-765-syscalls-string-arguments-765"
			COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 10 765)
		add_test(NAME "${OUTPUT_FORMAT}-765-syscalls-string-arguments-1148"
			COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 10 1148)
		add_test(NAME "${OUTPUT_FORMAT}-765-syscalls-string-arguments-1531"
			COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 10 1531)

		add_test(NAME "${OUTPUT_FORMAT}-1148-syscalls-string-arguments-1148"
			COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 11 1148)
		add_test(NAME "${OUTPUT_FORMAT}-1148-syscalls-string-arguments-1531"
			COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 11 1531)

		add_test(NAME "${OUTPUT_FORMAT}-1531-syscalls-string-arguments-1531"
			COMMAND ${TEST_DIR}/test-match ${FMT} ${TEST_APP} ${WAIT} 12 1531)

		add_test(NAME "${OUTPUT_FORMAT}-1531-syscalls-string-arguments-with-fork"
			COMMAND ${TEST_DIR}/test-match ${FMT} -f ${TEST_APP} ${WAIT} 13 1531)
		add_test(NAME "${OUTPUT_FORMAT}-1531-syscalls-string-arguments-with-double-fork"
			COMMAND ${TEST_DIR}/test-match ${FMT} -f ${TEST_APP} ${WAIT} 14 1531)

	endforeach(OUTPUT_FORMAT)

	add_test(NAME "binary-126-multithreaded-string-arguments-126"
		COMMAND ${TEST_DIR}/test-match -f ${TEST_APP} "do-not-wait" 15 126)
endif ()
