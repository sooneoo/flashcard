CC=gcc


PKGS += raylib


CFLAGS += -Wall -Wextra -pedantic
CFLAGS += -O2
CFLAGS += -Isrc/include
CFLAGS += $$(pkg-config --cflags $(PKGS))

LIBS += -lm -lalloc
LIBS += $$(pkg-config --libs $(PKGS))


OBJS += $(CACHE)/main.o
OBJS += $(CACHE)/screen_context.o
OBJS += $(CACHE)/screen_manager.o
OBJS += $(CACHE)/screen_main.o
OBJS += $(CACHE)/screen_flashcard.o


$(CACHE)/main.o: src/flashcard/main.c
	$(CC) $(CFLAGS) -c $< -o $@


$(CACHE)/screen_context.o: src/flashcard/screen_context.c
	$(CC) $(CFLAGS) -c $< -o $@


$(CACHE)/screen_manager.o: src/flashcard/screen_manager.c
	$(CC) $(CFLAGS) -c $< -o $@


$(CACHE)/screen_main.o: src/flashcard/screen_main.c
	$(CC) $(CFLAGS) -c $< -o $@


$(CACHE)/screen_flashcard.o: src/flashcard/screen_flashcard.c
	$(CC) $(CFLAGS) -c $< -o $@


$(RELEASE)/$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(RELEASE)/$(TARGET)


