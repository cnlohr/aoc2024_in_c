all : day16 day16b

.PHONY : test

CFLAGS:=-g -Og -I..

day16 : day16.c
	gcc $(CFLAGS) -o $@ $^

day16b : day16b.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day16 day16b
	test "$(shell ./day16 < sample.txt)" = "10092"
	test "$(shell ./day16b < sample.txt)" = "9021"

testinput : day16 day16b
	test "$(shell ./day16 < input.txt)" = "1563092"
	test "$(shell ./day16b < input.txt)" = "1582688"

clean :
	rm -rf day16 day16b

