all : test

.PHONY : test

CFLAGS:=-g -O1 -I..

day1 : day1.c
	gcc $(CFLAGS) -o $@ $^

day1b : day1b.c
	gcc $(CFLAGS) -o $@ $^

test : day1 day1b input.txt
	test "$(shell ./day1 < sample.txt)" = "11"
	test "$(shell ./day1b < sample.txt)" = "31"

clean :
	rm -rf day1 day1b

