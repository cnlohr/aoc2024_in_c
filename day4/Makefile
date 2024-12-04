all : day4 day4b

.PHONY : test

CFLAGS:=-g -O1 -I..

day4 : day4.c
	gcc $(CFLAGS) -o $@ $^

day4b : day4b.c
	gcc $(CFLAGS) -o $@ $^

test : day4 day4b
	test "$(shell ./day4 < sample.txt)" = "18"
	test "$(shell ./day4 < input.txt)" = "2344"
	test "$(shell ./day4b < sample.txt)" = "9"
	test "$(shell ./day4b < input.txt)" = "1815"

clean :
	rm -rf day4 day4b

