CC=gcc
CFLAGS=-c #ADD -wall 
LDFLAGS= # required flags (-lncurses)
SOURCES=console.c vect_list.c vect_math.c # source files
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=vect #executable name

all: $(SOURCES) $(EXECUTABLE)
# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
		$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
		$(CC) $(CFLAGS) $< -o $@
		$(CC) -MM $< > $*.d

clean:
		rm -rf $(OBJECTS) $(EXECUTABLE) *.d