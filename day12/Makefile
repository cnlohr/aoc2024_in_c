all : day12 day12b

.PHONY : test

CFLAGS:=-g -O4 -I..

day12 : day12.c
	gcc $(CFLAGS) -o $@ $^

day12b : day12b.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day12 day12b
	test "$(shell ./day12 < sample.txt)" = "55312"
	test "$(shell ./day12b < sample.txt)" = "65601038650482"

testinput : day12 day12b
	test "$(shell ./day12 < input.txt)" = "186203"
	test "$(shell ./day12b < input.txt)" = "221291560078593"

clean :
	rm -rf day12 day12b

