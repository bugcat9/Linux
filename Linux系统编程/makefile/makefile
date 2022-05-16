src = $(wildcard *.c) # add.c sub.c test.c
obj = $(patsubst %.c, %.o, $(src)) # add.o sub.o test.o

ALL:a.out

a.out:$(obj)
	gcc $^ -o $@

%.o:%.c
	gcc -c $< -o $@
clean:
	-rm -rf $(obj) a.out
.PHONY: clean ALL
