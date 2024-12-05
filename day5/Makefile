all : day5 day5b

.PHONY : test

CFLAGS:=-g -O1 -I..

day5 : day5.c
	gcc $(CFLAGS) -o $@ $^

day5b : day5.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day5 day5b
	test "$(shell ./day5 < sample.txt)" = "143"
	test "$(shell ./day5 < input.txt)" = "4689"
	test "$(shell ./day5b < sample.txt)" = "123"
	test "$(shell ./day5b < input.txt)" = "6336"

clean :
	rm -rf day5 day5b

