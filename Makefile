X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib

INC = -I. -I/usr/include -I$(X11INC)
LIB = -L$(X11LIB) -lX11 -lXtst

CFLAGS = -Wall -Wextra -std=c99 -pedantic -O3 $(INC)
LDFLAGS = -s $(LIB)

SOURCE = keyMouse.c

MAKE = $(CC) $(CFLAGS) $(LDFLAGS) $(SOURCE) -o

all: keyMouse

keyMouse: $(SOURCE)
	$(MAKE) $@ $(BUILDFLAGS)
	chmod +x $@

install: keyMouse
	cp keyMouse /usr/bin/
	cp keyMouse.1 /usr/share/man/man1/keyMouse.1.gz

uninstall:
	rm -f /usr/bin/keyMouse
	rm -f /usr/share/man/man1/keyMouse.1.gz

clean:
	rm -f keyMouse
