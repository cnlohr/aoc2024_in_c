all : day21 day21b

.PHONY : test

CFLAGS:=-g -O2 -I.. -Wall

day21 : day21.c
	gcc $(CFLAGS) -o $@ $^

day21b : day21b.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day21 day21b
	test "$(shell ./day21 < sample.txt)" = "10,0"
	test "$(shell ./day21b < sample.txt)" = "2268,0"

testinput : day21 day21b
	test "$(shell ./day21 < input.txt)" = "4216,1463"
	test "$(shell ./day21b < input.txt)" = "1505959,985332"

clean :
	rm -rf day21 day21b

