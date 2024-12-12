all : day11 day11b

.PHONY : test

CFLAGS:=-g -O4 -I..

day11 : day11.c
	gcc $(CFLAGS) -o $@ $^

day11b : day11b.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day11 day11b
	test "$(shell ./day11 < sample.txt)" = "55312"
	test "$(shell ./day11b < sample.txt)" = "65601038650482"

testinput : day11 day11b
	test "$(shell ./day11 < input.txt)" = "186203"
	test "$(shell ./day11b < input.txt)" = "221291560078593"

clean :
	rm -rf day11 day11b

