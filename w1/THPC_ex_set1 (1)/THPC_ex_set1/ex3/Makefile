# Makefile

all: target

dep_a1:
	echo "This is dep_a1 content" > dep_a1

dep_b1:
	echo "This is dep_b1 content" > dep_b1

dep_a2: dep_a1
	cp dep_a1 dep_a2

dep_b2: dep_b1
	cp dep_b1 dep_b2

target: dep_a2 dep_b2
	cat dep_a2 dep_b2 > target

clean:
	rm -f dep_a1 dep_a2 dep_b1 dep_b2 target

.PHONY: all clean

