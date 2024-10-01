#!/bin/bash

# help
function show_help {
	echo "Usage: $0 [option]"
	echo "Options:"
	echo "  clean  : Remove temporary files."
	echo "  exec   : Execute the test scripts (default)."
	echo "  help   : Display this help message."
}

if [ "$1" == "clean" ]; then
	echo "Cleaning up temporary files..."
	rm -f test/origin_msg
	rm -f test/pipex_msg
	rm -f test/result.txt
	rm -f test/backup_path
	rm -f test/tmp/*
	rm -f test/tmp2/*
	rm -f test.out
	exit 0
elif [ "$1" == "help" ]; then
	show_help
	exit 0
elif [ "$1" != "exec" ] && [ -n "$1" ]; then
	echo "Unknown option: $1"
	show_help
	exit 1
fi

# default or exec

chmod 755 test/test_scripts/test_prepare.sh 
chmod 755 test/test_scripts/test_origin.sh 
chmod 755 test/test_scripts/test_pipex.sh
chmod 755 test/test_scripts/test_compare.sh
echo "Executing test scripts..."
test/test_scripts/test_prepare.sh && \
test/test_scripts/test_origin.sh > test/origin_msg 2>&1 && \
test/test_scripts/test_pipex.sh > test/pipex_msg 2>&1 && \
test/test_scripts/test_compare.sh > test/result.txt 2>&1 && \
echo "Completed"
