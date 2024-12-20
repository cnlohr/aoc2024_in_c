all : day20 day20b

.PHONY : test

CFLAGS:=-g -O2 -I.. -Wall

day20 : day20.c
	gcc $(CFLAGS) -o $@ $^

day20b : day20b.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day20 day20b
	test "$(shell ./day20 < sample.txt)" = "6"
	test "$(shell ./day20b < sample.txt)" = "16"

testinput : day20 day20b
	test "$(shell ./day20 < input.txt)" = "319"
	test "$(shell ./day20b < input.txt)" = "985332"

clean :
	rm -rf day20 day20b

