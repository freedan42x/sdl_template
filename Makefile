CC = gcc
CFLAGS = -std=c99 -Wall -Wextra `pkg-config --cflags sdl2`
LIBS = -lm `pkg-config --libs sdl2`

SRCDIR = src
OBJDIR = obj

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $< $(CFLAGS) $(LIBS) -o $@

main: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^
