CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

SRCS = src/main.c src/game.c src/character.c src/data_structures.c src/game_logic.c src/minigame.c src/file_handler.c
OBJS = $(SRCS:.c=.o)
TARGET = rpg_throne_of_glass

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) savegame.dat config.txt
