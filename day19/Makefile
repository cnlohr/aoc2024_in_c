all : day19 day19b

.PHONY : test

CFLAGS:=-g -O2 -I..

day19 : day19.c
	gcc $(CFLAGS) -o $@ $^

day19b : day19.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day19
	test "$(shell ./day19 < sample.txt)" = "6"
	test "$(shell ./day19b < sample.txt)" = "16"

testinput : day19 day19b
	test "$(shell ./day19 < input.txt)" = "319"
	test "$(shell ./day19b < input.txt)" = "692575723305545"

clean :
	rm -rf day19 day19b

