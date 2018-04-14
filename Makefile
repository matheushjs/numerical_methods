all:
	gcc -O3 -Wall prog.c -o prog -lm

clean:
	find -name "*~" -exec rm -vf '{}' \;
