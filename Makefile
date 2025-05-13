CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude
LDFLAGS = -linput -ljson-c -lpthread -lrt -lyaml

TARGET = waykey

SRCDIR = src

INCDIR = include

OUTDIR = out
BINDIR = bin

INSTALL_DIR = $(DESTDIR)/usr/bin

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OUTDIR)/%.o,$(SRCS))

.PHONY: all clean install uninstall cleaninstall

all: $(OUTDIR) $(BINDIR) $(BINDIR)/$(TARGET)

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OUTDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OUTDIR)/*.o
	rm -f $(BINDIR)/$(TARGET)
	rmdir --ignore-fail-on-non-empty $(OUTDIR)
	rmdir --ignore-fail-on-non-empty $(BINDIR)

install: $(BINDIR)/$(TARGET)
	install -d $(INSTALL_DIR)
	install -m 755 $(BINDIR)/$(TARGET) $(INSTALL_DIR)/

uninstall:
	rm -f $(INSTALL_DIR)/$(TARGET)
