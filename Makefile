PLATFORM ?= linux_x86_64

CACHE = .cache
RELEASE = $(CACHE)/release
TARGET = flashcard


all: build

-include config/$(PLATFORM).mk

build: env $(RELEASE)/$(TARGET)


.PHONY: env exec clean install 


exec: build
	$(RELEASE)/$(TARGET)


env:
	mkdir -pv $(CACHE)
	mkdir -pv $(RELEASE)


install:
	cp $(RELEASE)/$(TARGET) $(BINDIR)/$(TARGET)


clean:
	rm -rvf $(CACHE)


