CC         = gcc
CFLAGS     =
DEPS       = main.h english.h
OBJECTS    = main.o
EXECUTABLE = main

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

.PHONY: clean

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
