# Benjamin Steenkamer
# CPEG 324-010
# Lab 1 - 8 Bit ISA Simulator
# 3/3/17

#git commit
#git push origin master

build:
	gcc -o simulator main.c

test-load-print1: build
	./simulator test-load-print1

test-load-print2: build
	./simulator test-load-print2

test-add-sub: build
	./simulator test-add-sub

test-cmp: build
	./simulator test-cmp

clean:
	rm -f simulator
