all : test

.PHONY : test

CFLAGS:=-g -O1 -I..

day2 : day2.c
	gcc $(CFLAGS) -o $@ $^

day2b : day2b.c
	gcc $(CFLAGS) -o $@ $^

test : day2 day2b sample.txt
	test "$(shell ./day2 < sample.txt)" = "2"
	test "$(shell ./day2b < sample.txt)" = "4"

clean :
	rm -rf day2 day2b

