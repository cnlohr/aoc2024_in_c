all : test

.PHONY : test

CFLAGS:=-g -O3 -I..

day1 : day1.c
	gcc $(CFLAGS) -o $@ $^

day1b : day1b.c
	gcc $(CFLAGS) -o $@ $^

test : day1 day1b input.txt
	test "$(shell ./day1 < sample.txt)" = "11"
	test "$(shell ./day1b < sample.txt)" = "31"

testinput : day1 day1b input.txt
	time test "$(shell ./day1 < input.txt)" = "2580760"
	time test "$(shell ./day1b < input.txt)" = "25358365"

clean :
	rm -rf day1 day1b

