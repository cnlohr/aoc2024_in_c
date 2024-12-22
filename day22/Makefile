all : day22 day22b

.PHONY : test

CFLAGS:=-g -O2 -I.. -Wall

day22 : day22.c
	gcc $(CFLAGS) -o $@ $^

day22b : day22b.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day22 day22b
	test "$(shell ./day22 < sample.txt)" = "37327623"
	test "$(shell ./day22b < sample2.txt)" = "23"

testinput : day22 day22b
	test "$(shell ./day22 < input.txt)" = "20441185092"
	test "$(shell ./day22b < input.txt)" = "2268"

clean :
	rm -rf day22 day22b

