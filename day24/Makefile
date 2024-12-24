all : day24 day24b

.PHONY : test

CFLAGS:=-g -O2 -I.. -Wall

day24 : day24.c
	gcc $(CFLAGS) -o $@ $^

day24b : day24b.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day24 day24b
	test "$(shell ./day24 < sample.txt)" = "7"
	test "$(shell ./day24b < sample.txt)" = "co,de,ka,ta"

testinput : day24 day24b
	test "$(shell ./day24 < input.txt)" = "1046"
	test "$(shell ./day24b < input.txt)" = "de,id,ke,ls,po,sn,tf,tl,tm,uj,un,xw,yz"

clean :
	rm -rf day24 day24b

