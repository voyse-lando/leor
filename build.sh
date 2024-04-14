#!/usr/bin/env bash
# mkdir -p build &&\
# cd build &&\
# cmake -S .. -B . -DCMAKE_BUILD_TYPE=Debug &&\
# make &&\
# cd ..

print_help() {
	echo "LEOR build tools"
	echo "Usage:"
	echo -e "\t$0 [options]"

	echo "Options:"
	echo -e "\t-c, --clean\t\t- remove all files from build directory"
	echo -e "\t-d, --debug\t\t- build debug"
	echo -e "\t-r, --release\t\t- build release"
}

if (($# == 0)); then
	print_help
	exit
fi

clean=0
build_target=""
should_run=0

for a in $@; do

	if [[ -z "${a%\-*}" ]] && [ "${a:0:1}" = "-" ]; then
		x="${a#\-}"
		for ((i=0; i<${#x}; i++)); do
			c="${x:$i:1}"
			echo $c
			case "$c" in
			"c")
				clean=1
			;;
			"d") 
				build_target="Debug"
			;;
			"r")
				build_target="Debug"
			;;
			"x")
				should_run=1
			;;
			*)
				echo "Error: unknown option '-$c\'"
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
		*) : ;;
		esac
	fi
done

if (($clean == 1)); then
	echo "INFO: Removing build/"
	rm -rf build
fi

mkdir -p build

if [[ -n "$build_target" ]]; then
	echo "INFO: Building $build_target target"
	cd build
	   cmake -S .. -B . -DCMAKE_BUILD_TYPE=$build_target \
	&& make
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