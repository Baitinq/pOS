out_dir="..\/out"
include="-I pOS/include -I pOS/include/libc"

mkdir $out_dir 2> /dev/null

for f in $(find pOS/ -type f \( -iname \*.cpp -o -iname \*.c \))
do
	out_file=$(echo $f | sed 's/pOS/..\/out\/pOS/g' | sed 's/\.cpp/\.o/g' | sed 's/\.c/\.o/g')
	mkdir -p $(dirname $out_file)
	i686-elf-g++ $include -g -std=c++11 -c $f -o $out_file -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
done

mkdir -p ../out/bootloader

nasm -f elf32 bootloader/boot.s -o ../out/bootloader/boot.o

i686-elf-g++ -T linker.ld -o ../out/pOS.bin -ffreestanding -O2 -nostdlib $(find ../out -type f -name "*.o") -lgcc
