all: src/
	cd src && make -f .Makefile && cd ..

run: all
	@echo -e "\033[32m"
	@qemu-system-i386 -kernel out/pOS.bin -serial stdio
	@echo -e "\033[0;39m"
clean:
	rm -rf out
