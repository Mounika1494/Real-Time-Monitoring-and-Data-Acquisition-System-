SRC = ./src
OBJ := ./build
CFLAGS = -I./inc
LIBS= -lpthread -lrt
SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

myprog: $(OBJECTS)
	$(CC)  $^ -o $@ $(LIBS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJ)/*.o myprog
