all : day17 day17b

.PHONY : test

CFLAGS:=-g -O2 -I..

day17 : day17.c
	gcc $(CFLAGS) -o $@ $^

day17b : day17.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day17 day17b
	test "$(shell ./day17 < sample.txt)" = "4,6,3,5,6,3,5,2,1,0"

testinput : day17 day17b
	test "$(shell ./day17 < input.txt)" = "7,1,3,4,1,2,6,7,1"
	test "$(shell ./day17b < input.txt)" = "109019476330651"

clean :
	rm -rf day17 day17b

