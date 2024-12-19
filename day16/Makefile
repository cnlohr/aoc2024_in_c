all : day16 day16b

.PHONY : test

CFLAGS:=-g -Og -I..

day16 : day16.c
	gcc $(CFLAGS) -o $@ $^

day16b : day16.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day16 day16b
	test "$(shell ./day16 < sample.txt)" = "7036"
	test "$(shell ./day16b < sample.txt)" = "45"

testinput : day16 day16b
	test "$(shell ./day16 < input.txt)" = "102460"
	test "$(shell ./day16b < input.txt)" = "527"

clean :
	rm -rf day16 day16b

