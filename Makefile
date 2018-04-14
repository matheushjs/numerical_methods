all:
	gcc -O3 -Wall prog.c -o prog

clean:
	find -name "*~" -exec rm -vf '{}' \;
