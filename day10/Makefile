all : day10 day10b

.PHONY : test

CFLAGS:=-g -O3 -I..

day10 : day10.c
	gcc $(CFLAGS) -o $@ $^

day10b : day10.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day10 day10b
	test "$(shell ./day10 < sample.txt)" = "36"
	test "$(shell ./day10b < sample.txt)" = "81"

testinput : day10 day10b
	test "$(shell ./day10 < input.txt)" = "786"
	test "$(shell ./day10b < input.txt)" = "1722"

clean :
	rm -rf day10 day10b

