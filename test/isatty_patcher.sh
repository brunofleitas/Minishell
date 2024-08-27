#!/bin/bash

mini_dir="$1"

echo "Searching for files containing readline..."
files=$(grep -l '[^a-zA-Z1-9_]readline(' $(find "$mini_dir" -name "*.c" -print));
if [ $? -ne "0" ]; then
	echo "You are not using readline?"
	exit 1
fi
count=$(echo "$files" | wc -l)
echo "found $count files using readline:"
echo "$files";
echo "Do you want to patch them to use get_next_line if not running interactively? Y/n"
read do_patch
case "$do_patch" in
	[Nn]* )
		echo "bye"
		exit 1
	;;
esac
for file in $files; do
	echo "patching $file"
	patched=$(sed -E 's/([^[:alnum:]_])readline\(/\1!isatty(0) ? gnl(0) : readline(/g' "$file")
	patched=$(echo '#include <unistd.h>' | cat - <(echo "$patched"))
	patched=$(echo 'char	*gnl(int fd);' | cat - <(echo "$patched"))
	echo "$patched" | cat - > "$file"
done
echo "done patching"

echo "Searching for files containing add_history..."
files=$(grep -l '[^a-zA-Z1-9_]add_history(' $(find "$mini_dir" -name "*.c" -print));
if [ $? -ne "0" ]; then
	echo "You are not using add_history?"
	exit 1
fi
count=$(echo "$files" | wc -l)
echo "found $count files using add_history"
echo "$files";
echo "Do you want to patch them to only use add_history if running interactively? Y/n"
read do_patch
case "$do_patch" in
	[Nn]* )
		echo "ok, then not"
	;;
esac
for file in $files; do
	echo "patching $file"
	patched=$(sed -E 's/([^[:alnum:]_])add_history\(/\1!isatty(0) ? 0 : add_history(/g' "$file")
	echo '#include <unistd.h>' | cat - <(echo "$patched") > "$file"
done

echo "Searching for main function to add destructor..."
files=$(find "$mini_dir" -name "*.c" -print | grep -l 'void[ 	]+main(');
if [[ $(echo "$files" | wc -l) -eq "0" ]]; then
	echo "Could not locate a main function!"
	exit 1
elif [[ $(echo "$files" | wc -l) -ne "1" ]]; then
	echo "Found multiple main functions!"
	exit 1
fi
echo "

void __attribute__((destructor)) free_gnl_buffer();

void free_gnl_buffer() { gnl(-1); }
" >> "$file"

echo "copy get_next_line.c and patch Makefile"
cp get_next_line.c "$mini_dir"/
sed -i -E 's/(\$\(NAME\):.*)/\1\n\tcc get_next_line.c -c/' "$mini_dir"/Makefile
echo "Please edit the Makefile now to link get_next_line.o to the binary"
echo "When you are done press enter to continue the tester...";
read
