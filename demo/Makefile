CC := gcc
OBJ := main.o
main: $(OBJ)
	$(CC) -o $@ $^ -L./ -lzkfp 
$(OBJ): main.c
	$(CC) -c $< -o $@
clean:
	rm -f $(OBJ) main

