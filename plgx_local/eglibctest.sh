#!/bin/sh

test_list=$1
timeout=$2

test_dir=$(pwd)
results_dir=${test_dir}/results

setup()
{
	mkdir -p ${results_dir}
	test_log=${results_dir}/test.$$.log
	results_log=${results_dir}/test.$$.sum
	STANDARD_LIBRARY_PATH=$LD_LIBRARY_PATH
	if [ -z ${timeout} ];then
		timeout=15
	fi
}

main ()
{
	for test in $(cat ${test_list});
	do
		path=$(echo $test | sed 's|\.\/\(.*\/\).*|\/tmp\/build-libc-final/\1|g')
		echo "---------------------" >> ${test_log}
		echo "BEGIN TEST: ${test}" >> ${test_log}
		LD_LIBRARY_PATH=${path}:$STANDARD_LIBRARY_PATH timeout -t ${timeout} ${test} >> ${test_log}
		rc=$?
		if [ "${rc}" == "0" ];then
			echo "PASS: ${test}" | tee -a ${results_log}
			echo "PASS" >> ${test_log}
		elif [ "${rc}" == "143" ];then
			echo "TIMEOUT: ${test}" | tee -a ${results_log}
			echo "Timed out after ${timeout}s" >> ${test_log}
		else
			echo "FAIL: ${test}" | tee -a ${results_log}
			echo "FAIL rc=${rc}" >> ${test_log}
		fi
		echo "END TEST: ${test}" >> ${test_log}
	done

	total_num=$(cat ${test_list} | wc -l )
	num_pass=$(grep "PASS" ${results_log} | wc -l )
	num_fail=$(grep "FAIL" ${results_log} | wc -l )
	num_timeout=$(grep "TIMEOUT" ${results_log} | wc -l )

	echo "" | tee -a ${results_log}
	echo "-----------------------------------------------------------------------------" | tee -a ${results_log}
	echo "" | tee -a ${results_log}
	echo " PetaLinux EGLIBC Test Run, $(date)" | tee -a ${results_log}
	echo " target is $(hostname)" | tee -a ${results_log}
	echo "" | tee -a ${results_log}
	echo " # of expected passes      ${num_pass} " | tee -a ${results_log}
	echo " # of unexpected failures  ${num_fail} " | tee -a ${results_log}
	echo " # of unsupported tests    ${num_timeout} " | tee -a ${results_log}
	echo "" | tee -a ${results_log}
	echo " # total                   ${total_num}" | tee -a ${results_log}
	echo "" | tee -a ${results_log}
	echo "-----------------------------------------------------------------------------" | tee -a ${results_log}
	echo "" | tee -a ${results_log}
	exit
}

setup
main

