src = $(wildcard ./src/*.c) # src/add.c src/sub.c src/test.c
obj = $(patsubst ./src/%.c, ./obj/%.o, $(src)) # add.o sub.o test.o

inc_path = ./inc



ALL:a.out

a.out:$(obj)
	gcc $^ -o $@

./obj/%.o:./src/%.c
	gcc -c $< -o $@ -I $(inc_path)
clean:
	-rm -rf $(obj) a.out
.PHONY: clean ALL
