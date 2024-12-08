all : day8 day8b

.PHONY : test

CFLAGS:=-g -O1 -I..

day8 : day8.c
	gcc $(CFLAGS) -o $@ $^

day8b : day8.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day8 day8b
	test "$(shell ./day8 < sample.txt)" = "14"
	test "$(shell ./day8b < sample.txt)" = "34"

clean :
	rm -rf day8 day8b

