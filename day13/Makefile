dall : day13 day13b

.PHONY : test

CFLAGS:=-g -O4 -I..

day13 : day13.c
	gcc $(CFLAGS) -o $@ $^

day13b : day13b.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day13 day13b
	test "$(shell ./day13 < sample.txt)" = "1930"
	test "$(shell ./day13b < sample.txt)" = "1306"

testinput : day13 day13b
	test "$(shell ./day13 < input.txt)" = "186203"
	test "$(shell ./day13b < input.txt)" = "221391560078593"

clean :
	rm -rf day13 day13b

