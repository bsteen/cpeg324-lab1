# Benjamin Steenkamer
# CPEG 324-010
# Lab 1 - 8 Bit ISA Simulator
# 3/3/17

build:
	gcc -o simulator main.c

test: build
	./simulator test_program

clean:
	rm -f simulator

git-push:
	git push origin master
