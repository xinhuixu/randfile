test: randfile.c
	gcc randfile.c -o test.o
clean:
	rm *~
run: test
	./test.o
