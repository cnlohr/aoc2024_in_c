dall : day13 day13b

.PHONY : test

CFLAGS:=-g -O4 -I..

day13 : day13.c
	gcc $(CFLAGS) -o $@ $^

day13b : day13.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day13 day13b
	test "$(shell ./day13 < sample.txt)" = "480"
	test "$(shell ./day13b < sample.txt)" = "875318608908"

testinput : day13 day13b
	test "$(shell ./day13 < input.txt)" = "29388"
	test "$(shell ./day13b < input.txt)" = "99548032866004"

clean :
	rm -rf day13 day13b

