all : day21
#day21b

.PHONY : test

CFLAGS:=-g -O2 -I.. -Wall

day21 : day21.c
	gcc $(CFLAGS) -o $@ $^

day21b : day21b.c
	gcc $(CFLAGS) -o $@ $^ -DPARTB=1

#day21b
test : day21
	test "$(shell ./day21 < sample.txt)" = "126384"
	#test "$(shell ./day21b < sample.txt)" = "2268,0"

#day21b
testinput : day21
	test "$(shell ./day21 < input.txt)" = "157908"
	#test "$(shell ./day21b < input.txt)" = "196910339808654"

clean :
	rm -rf day21 day21b

