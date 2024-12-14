dall : day14 day14b day14s day14bs

.PHONY : test

CFLAGS:=-g -O4 -I..

day14 : day14.c
	gcc $(CFLAGS) -o $@ $^

day14b : day14.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

day14s : day14.c
	gcc $(CFLAGS) -o $@ $^ -DSAMPLE=1

day14bs : day14.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1 -DSAMPLE=1

test : day14 day14b
	test "$(shell ./day14s < sample.txt)" = "12"
#	test "$(shell ./day14bs < sample.txt)" = "1406"

testinput : day14 day14b
	test "$(shell ./day14 < input.txt)" = "231852216"
#	test "$(shell ./day14b < input.txt)" = "99548032866004"

clean :
	rm -rf day14 day14b

