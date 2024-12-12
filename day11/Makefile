all : day11 day11b

.PHONY : test

CFLAGS:=-g -O4 -I..

day11 : day11.c
	gcc $(CFLAGS) -o $@ $^

day11b : day11b.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day11 day11b
	test "$(shell ./day11 < sample.txt)" = "27"
	test "$(shell ./day11b < sample.txt)" = "81"

testinput : day11 day11b
	test "$(shell ./day11 < input.txt)" = "786"
	test "$(shell ./day11b < input.txt)" = "1722"

clean :
	rm -rf day11 day11b

