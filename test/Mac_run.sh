#!/bin/bash

echo "        _       _     _          _ _    _           _            
  /\/\ (_)_ __ (_)___| |__   ___| | |  | |_ ___ ___| |_ ___ _ __ 
 /    \| | '_ \| / __| '_ \ / _ \ | |  | __/ _ / __| __/ _ | '__|
/ /\/\ \ | | | | \__ \ | | |  __/ | |  | ||  __\__ | ||  __| |   
\/    \/_|_| |_|_|___/_| |_|\___|_|_|   \__\___|___/\__\___|_|   
                                                                 "
all=1
bonus=0
valgrind=0
if [ "$1" = "b" ] || [ "$1" = "a" ]; then
	if [ "$1" = "b" ]; then
		all=0
	fi
	bonus=1
fi
if [ "$1" = "valgrind" ] || [ "$2" = "valgrind" ]; then
	valgrind=1
fi

do_make() {
	out=$(make -C ..)
	if [ "$?" != "0" ]; then
		echo "$out"
		echo -e "\033[1;31mCompilation failed!\033[0m"
		exit 1
	fi
}

do_make

echo "testing if piping into minishell works correctly"
test_out=$(echo 'echo test' | ../minishell)
if [ "$test_out" == "test" ]; then
	echo -e "\033[1;32mWorking!\033[0m"
else
	echo -e "\033[1;31mNot working!\033[0m"
	echo "expected 'test' but found '$test_out'"
	echo "trying to auto patch"
	./isatty_patcher.sh '..'
	if [ $? -ne '0' ]; then
		echo -e "\033[1;31mNo patching was done, abort\033[0m"
		exit 1
	fi
	echo "patching finished, press any key to continue with the tests"
	do_make
	read
fi

errcount=0
rm -rf diffs temp all.diff
mkdir diffs temp

handle_valgrind() {
	cd temp
	echo "infile content" > infile
	echo "infile second line" >> infile
	touch readonly
	chmod -wx readonly
	out=$(echo "$1" | tr ';' '\n' | valgrind $2 2>&1 >/dev/null)
	cd ..
	rm -rf temp/*
	lost=$(echo "$out" | grep " lost: [^0]" | wc -l)
	reachable=$(echo "$out" | grep "still reachable: [^0]" | wc -l)
	problems=$(echo "$out" | grep -e "Invalid read" -e "Invalid free" -e "uninitialised value" | wc -l)
	if [[ "$problems" -ne "0" ]]; then
		echo -en "\033[1;31mPROBLEMS\033[0m "
		if [[ "$lost" -eq "0" ]]; then
			errcount=$((errcount + 1))
		fi
	fi
	if [[ "$lost" -ne "0" ]]; then
		echo -e "\033[1;31mLEAK\033[0m"
		errcount=$((errcount + 1))
	elif [[ "$reachable" -ne "0" ]]; then
		echo -e "\033[1;33mREACHABLE\033[0m"
	else
		echo -e "\033[1;32mALL FREED\033[0m"
	fi
}

handle_cmd() {
	cd temp
	echo "infile content" > infile
	echo "infile second line" >> infile
	touch readonly
	chmod -wx readonly
	echo "$2" | tr ';' '\n' | $3 2> ../out_stderr | grep -v 'declare -x _=\|declare -x SHLVL=' > ../outfile
	res="$?"
	cd ..
	rm -rf temp/*
	mv outfile "$1" 2> /dev/null
	err=$(cat out_stderr | sed 's/[^:]\+: \(line [^:]\+: \)\?/[progname]: /')
	echo "" >> "$1"
	echo "======== stderr =======" >> "$1"
	echo "$err" | sed 's/: \.\/infile:/: infile:/' | tr '\n' '\r' | sed "s/.*syntax error.*/[syntax error msg]\n/" | tr '\r' '\n' >> "$1"
	echo "======== return =======" >> "$1"
	echo "return value: $res" >> "$1"
}
handle_diff() {
	diff="$2"
	diff --unified=100 expected found > diff.diff
	if [ -s diff.diff ]; then
		echo "diff of execution of:" > "$diff"
		echo "$1" >> "$diff"
		cat diff.diff >> "$diff"
		errcount=$((errcount + 1))
		echo -e "\033[1;31mERROR\033[0m"
	else
		echo -e "\033[1;32mOK\033[0m"
	fi
	rm -f found expected out_stderr diff.diff
}

execute_file_tests() {
	filename=$1
	echo ""
	echo "==== $filename ===="
	while read line; do
		IFS='	'; set -f; array=($line); unset IFS; set +f
		CMD="${array[1]//\[\[USER\]\]/$USER}"
		echo -n "$CMD "
		diff="diffs/${array[0]}.diff"
		if [[ $valgrind -eq "1" ]]; then
			handle_valgrind "$CMD" "../../minishell"
		else
			handle_cmd "expected" "$CMD" "bash"
			handle_cmd "found" "$CMD" "../../minishell"
			handle_diff "echo '${CMD//\'/\\\'}' | tr ';' '\\n' | [shell]" "$diff"
		fi;
	done < "$filename";
}

if [[ "$1" == /* ]]; then
	execute_file_tests "test_cases$1"
else
	for filename in $(find test_cases -type f -exec echo "{}" \;); do
		if [[ $filename == test_cases/bonus/* && $bonus -eq "0" ]]; then
			continue
		fi
		if [[ $filename != test_cases/bonus/* && $all -eq "0" ]]; then
			continue
		fi
		execute_file_tests "$filename"
	done
fi

rm -rf temp

echo ""
if [[ $errcount -eq 0 ]]; then
	echo -e "\033[1;32mALL OK!\033[0m"
	rmdir diffs
elif [[ $errcount -eq 1 ]]; then
	echo -e "\033[1;31mONE TEST FAILED!\033[0m"
	echo "diff has been written to ./diffs/"
else
	echo -e "\033[1;31m${errcount} TESTS FAILED!\033[0m"
	if [[ $valgrind -ne "1" ]]; then
		echo "diffs have been written to ./diffs/"
		tail -n +1 diffs/* > all.diff
		echo "concatenation of all diffs has been written do ./all.diff"
	else
		rmdir diffs
	fi
fi
