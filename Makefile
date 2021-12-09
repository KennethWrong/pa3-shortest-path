#This is a makefile
WARNING = -Wall -Wshadow -pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -03 $(WARNING) $(ERROR)

pa4:
	$(CC) *.c -o pa3

all:
	$(CC) *.c -o pa3

exec:
	./pa3
clean:
	rm -rf pa3
	rm -rf *.exe
	rm -rf *.o

test1:
	./pa3 ./examples/4_5.b ./tests/4_5.t ./tests/4_5.f ./tests/4_5.p
test2:
	./pa3 ./examples/5_4.b ./tests/5_4.t ./tests/5_4.f ./tests/5_4.p
test3:
	./pa3 ./examples/5_5.b ./tests/5_5.t ./tests/5_5.f ./tests/5_5.p
test4:
	./pa3 ./examples/7_7.b ./tests/7_7.t ./tests/7_7.f ./tests/7_7.p
test5:
	./pa3 ./examples/4_5.b ./tests/4_5.t ./tests/4_5.f ./tests/4_5.p
