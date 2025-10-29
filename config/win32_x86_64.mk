CC=gcc


PKGS += raylib


CFLAGS += -Wall -Wextra -pedantic
CFLAGS += -O2
CFLAGS += -Isrc/include
CFLAGS += $$(pkg-config --cflags $(PKGS))

LIBS += -lm -lalloc -ljson
LIBS += $$(pkg-config --libs $(PKGS))


OBJS += $(CACHE)/main.o
OBJS += $(CACHE)/screen_context.o
OBJS += $(CACHE)/screen_manager.o
OBJS += $(CACHE)/screen_main.o
OBJS += $(CACHE)/screen_review.o
OBJS += $(CACHE)/button.o
OBJS += $(CACHE)/text.o


$(CACHE)/main.o: src/flashcard/main.c
	$(CC) $(CFLAGS) -c $< -o $@


$(CACHE)/screen_context.o: src/flashcard/screen_context.c
	$(CC) $(CFLAGS) -c $< -o $@


$(CACHE)/screen_manager.o: src/flashcard/screen_manager.c
	$(CC) $(CFLAGS) -c $< -o $@


$(CACHE)/screen_main.o: src/flashcard/screen_main.c
	$(CC) $(CFLAGS) -c $< -o $@


$(CACHE)/screen_review.o: src/flashcard/screen_review.c
	$(CC) $(CFLAGS) -c $< -o $@


$(CACHE)/button.o: src/flashcard/button.c
	$(CC) $(CFLAGS) -c $< -o $@


$(CACHE)/text.o: src/flashcard/text.c
	$(CC) $(CFLAGS) -c $< -o $@


$(RELEASE)/$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(RELEASE)/$(TARGET)


