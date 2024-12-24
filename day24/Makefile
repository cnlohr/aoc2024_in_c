all : day24 day24b

.PHONY : test

CFLAGS:=-g -O2 -I.. -Wall

day24 : day24.c
	gcc $(CFLAGS) -o $@ $^

day24b : day24b.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day24 day24b
	test "$(shell ./day24 < sample.txt)" = "4"

testinput : day24 day24b
	test "$(shell ./day24 < input.txt)" = "48806532300520"

clean :
	rm -rf day24 day24b

