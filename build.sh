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
cmakeflags=""

for a in $@; do

	case $a in
	"-c" | "--clean")
		echo "INFO: Removing build/"
		clean=1
	;;
	"-d" | "--debug")
		echo "INFO: Building Debug target"
		cmakeflags="-DCMAKE_BUILD_TYPE=Debug"
	;;
	"-r" | "--release")
		echo "INFO: Building Release target"
		cmakeflags="-DCMAKE_BUILD_TYPE=Release"
	;;
	*) : ;;
	esac
done

if (($clean == 1)); then
	rm -rf build
fi

mkdir -p build

if [[ -n cmakeflags ]]; then
	cd build
	   cmake -S .. -B . ${cmakeflags} \
	&& make
	cd ..
fi