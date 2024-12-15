all : day15 day15b

.PHONY : test

CFLAGS:=-g -O4 -I..

day15 : day15.c
	gcc $(CFLAGS) -o $@ $^

day15b : day15b.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day15 day15b
	test "$(shell ./day15 < sample.txt)" = "10092"
	test "$(shell ./day15b < sample.txt)" = "9021"

testinput : day15 day15b
	test "$(shell ./day15 < input.txt)" = "1563092"
	test "$(shell ./day15b < input.txt)" = "1582688"

clean :
	rm -rf day15 day15b

