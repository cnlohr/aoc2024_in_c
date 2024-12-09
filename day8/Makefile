all : day8 day8b

.PHONY : test

CFLAGS:=-g -O3 -I..

day8 : day8.c
	gcc $(CFLAGS) -o $@ $^

day8b : day8.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day8 day8b
	test "$(shell ./day8 < sample.txt)" = "14"
	test "$(shell ./day8b < sample.txt)" = "34"

testinput : day8 day8b
	test "$(shell ./day8 < input.txt)" = "259"
	test "$(shell ./day8b < input.txt)" = "927"

clean :
	rm -rf day8 day8b

