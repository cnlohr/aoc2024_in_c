all : test

.PHONY : test

CFLAGS:=-g -Og -I..

day2 : day2.c
	gcc $(CFLAGS) -o $@ $^

day2b : day2b.c
	gcc $(CFLAGS) -o $@ $^

test : day2 day2b input.txt
	test "$(shell ./day2 < sample.txt)" = "2"
	test "$(shell ./day2 < input.txt)" = "432"
	test "$(shell ./day2b < sample.txt)" = "4"
	test "$(shell ./day2b < input.txt)" = "488"

clean :
	rm -rf day2 day2b

