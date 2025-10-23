CC=gcc


PKGS += raylib


CFLAGS += -Wall -Wextra -pedantic
CFLAGS += -O2
CFLAGS += -Isrc/include
CFLAGS += $$(pkg-config --cflags $(PKGS))

LIBS += -lm -lalloc
LIBS += $$(pkg-config --libs $(PKGS))


OBJS += $(CACHE)/main.o


$(CACHE)/main.o: src/flashcard/main.c
	$(CC) $(CFLAGS) -c $< -o $@


$(RELEASE)/$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(RELEASE)/$(TARGET)


