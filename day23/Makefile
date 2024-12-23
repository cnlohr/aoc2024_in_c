all : day23 day23b

.PHONY : test

CFLAGS:=-g -O2 -I.. -Wall

day23 : day23.c
	gcc $(CFLAGS) -o $@ $^

day23b : day23b.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

test : day23 day23b
	test "$(shell ./day23 < sample.txt)" = "7"
	test "$(shell ./day23b < sample.txt)" = "co,de,ka,ta"

testinput : day23 day23b
	test "$(shell ./day23 < input.txt)" = "1046"
	test "$(shell ./day23b < input.txt)" = "de,id,ke,ls,po,sn,tf,tl,tm,uj,un,xw,yz"

clean :
	rm -rf day23 day23b

