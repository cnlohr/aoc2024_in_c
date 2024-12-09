all : day9 day9b

.PHONY : test

CFLAGS:=-g -O3 -I..

day9 : day9.c
	gcc $(CFLAGS) -o $@ $^

day9b : day9.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day9 day9b
	test "$(shell ./day9 < sample.txt)" = "1928"
	test "$(shell ./day9b < sample.txt)" = "2858"

testinput : day9 day9b
	test "$(shell ./day9 < input.txt)" = "6346871685398"
	test "$(shell ./day9b < input.txt)" = "6373055193464"

clean :
	rm -rf day9 day9b

