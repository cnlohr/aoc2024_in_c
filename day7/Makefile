all : day7 day7b

.PHONY : test

CFLAGS:=-g -O3 -I..

day7 : day7.c
	gcc $(CFLAGS) -o $@ $^

day7b : day7b.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day7 day7b
	test "$(shell ./day7 < sample.txt)" = "3749"
	test "$(shell ./day7b < sample.txt)" = "11387"

testinput : day7 day7b
	test "$(shell ./day7 < input.txt)" = "945512582195"
	test "$(shell ./day7b < input.txt)" = "271691107779347"

clean :
	rm -rf day7 day7b

