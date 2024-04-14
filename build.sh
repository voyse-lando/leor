#!/usr/bin/env bash

print_help() {
	echo "LEOR build tools"
	echo "Usage:"
	echo -e "\t$0 [options]"

	echo "Options:"
	echo -e "\t-h, --help\t\t- show this dialog"
	echo -e "\t-c, --clean\t\t- remove all files from the build directory"
	echo -e "\t-d, --debug\t\t- build debug target"
	echo -e "\t-r, --release\t\t- build release target"
	echo -e "\t-x, --execute\t\t- execute target"
	echo -e "\t-s, --silent\t\t- suppress output of building tools"
}

if (($# == 0)); then
	print_help
	exit
fi

silent=0
clean=0
build_target=""
should_run=0

for a in $@; do

	if [[ -z "${a%\-*}" ]] && [ "${a:0:1}" = "-" ]; then
		x="${a#\-}"
		for ((i=0; i<${#x}; i++)); do
			c="${x:$i:1}"
			case "$c" in
			"c")
				clean=1
			;;
			"d") 
				build_target="Debug"
			;;
			"r")
				build_target="Release"
			;;
			"x")
				should_run=1
			;;
			"s")
				silent=1
			;;
			"h")
				print_help
				exit
			;;
			*)
				echo "Error: unknown option '-$c' (use '-h' for help)"
				exit
			esac
		done
	else
		case $a in
		"--clean")
			clean=1
		;;
		"--debug")
			build_target="Debug"
		;;
		"--release")
			build_target="Release"
		;;
		"--execute")
			should_run=1
		;;
		"--silent")
			silent=1
		;;
		"--help")
			print_help
			exit
		;;
		*)
			echo "Error: unknown option '$a' (use '-h' for help)"
			exit
		;;
		esac
	fi
done

out_to_null=""
if (($silent == 1)); then
	echo() { :; }
	out_to_null=">/dev/null"
fi

if (($clean == 1)); then
	echo "INFO: Removing build/"
	rm -rf build
fi

mkdir -p build

generate() {
	   cmake -S .. -B . -DCMAKE_BUILD_TYPE=$build_target \
	&& make 
}

if [[ -n "$build_target" ]]; then
	echo "INFO: Building $build_target target"
	cd build
	if (($silent == 1)); then
		generate >/dev/null
	else
		generate
	fi
	cd ..
fi

if (($should_run == 1)); then
	if [[ -e build/leor ]]; then
		echo "INFO: Running target"
		build/leor
	else
		echo "INFO: Target 'build/leor' does not exist; ignoring"
	fi
fi