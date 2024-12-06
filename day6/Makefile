all : day6 day6b

.PHONY : test

CFLAGS:=-g -O1 -I..

day6 : day6.c
	gcc $(CFLAGS) -o $@ $^

day6b : day6b.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day6 day6b
	test "$(shell ./day6 < sample.txt)" = "41"
	test "$(shell ./day6b < sample.txt)" = "6"

clean :
	rm -rf day6 day6b

