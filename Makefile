# Uncomment if using BB
#CC = arm-none-eabi-gcc
PROJ_NAME = RT_LOGGER
SRC = ./src
OBJ := ./build

OPTVAL = -O0

CFLAGS = -I./inc \

LIBS= -lpthread -lrt

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))
TARGET := $(PROJ_NAME)

$(TARGET): $(OBJECTS)
	$(CC)  $^ -o $@ $(LIBS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(OBJ)/*.o $(TARGET) logger.txt
