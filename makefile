src=$(wildcard *.c)
obj=$(patsubst *.o, *.c, $(src))

