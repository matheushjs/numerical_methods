all:
	gcc -O3 -Wall prog.c -o prog -lm

run:
	./prog

clean:
	find -name "*~" -exec rm -vf '{}' \;
