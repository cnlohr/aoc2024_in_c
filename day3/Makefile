all : day3 day3b

.PHONY : test

CFLAGS:=-g -O3 -I..

day3 : day3.c
	gcc $(CFLAGS) -o $@ $^

day3b : day3b.c
	gcc $(CFLAGS) -o $@ $^

test : day3 day3b
	test "$(shell ./day3 < sample.txt)" = "161"
	test "$(shell ./day3b < sample2.txt)" = "48"

testinput : day3 day3b
	test "$(shell ./day3 < input.txt)" = "155955228"
	test "$(shell ./day3b < input.txt)" = "100189366"

clean :
	rm -rf day3 day3b

