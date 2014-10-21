all: build

build:
	g++ -Wall --std=gnu++11 -lm -I"." -I"src" src/main.cpp -o main

test:
	g++ -Wall --std=gnu++11 -lm -I"." -I"src" src/queens-test-main.cpp -o queens-test-main
