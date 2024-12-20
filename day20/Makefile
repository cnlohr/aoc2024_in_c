all : day20 day20b

.PHONY : test

CFLAGS:=-g -O2 -I.. -Wall

day20 : day20.c
	gcc $(CFLAGS) -o $@ $^

day20b : day20b.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day20 day20b
	test "$(shell ./day20 < sample.txt)" = "10,0"
	test "$(shell ./day20b < sample.txt)" = "2268,0"

testinput : day20 day20b
	test "$(shell ./day20 < input.txt)" = "4216,1463"
	test "$(shell ./day20b < input.txt)" = "1505959,985332"

clean :
	rm -rf day20 day20b

