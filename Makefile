CC ?= gcc
LD = ${CC}
PREFIX ?= /usr
BINDIR ?= $(PREFIX)/bin
MANDIR ?= $(PREFIX)/share/man/man8

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib

PACKAGES = x11 xinerama gtk+-2.0 vte
LDFLAGS = $(shell pkg-config --libs $(PACKAGES)) -lm
CFLAGS += -Wall -Os $(shell pkg-config --cflags $(PACKAGES))

SRC = main.c mainwindow.c config.c term.c popupmenu.c shortcut.c
OBJ = ${SRC:.c=.o}

all: options stjerm

options:
	@echo stjerm build options:
	@echo "CFLAGS = ${CFLAGS}"
	@echo "LDFLAGS = ${LDFLAGS}"
	@echo "CC = ${CC}"
	@echo "LD = ${LD}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: stjerm.h

stjerm: ${OBJ}
	@echo LD $@
	@${LD} -o $@ ${OBJ} ${LDFLAGS}
	@strip $@
    
clean:
	@rm -f ${OBJ} stjerm
    
install: all
	@echo installing executable file to ${DESTDIR}${BINDIR}
	@install -Dm755 stjerm "$(DESTDIR)$(BINDIR)"/stjerm
	@echo installing manual pages to ${DESTDIR}${MANDIR}
	@install -Dm644 stjerm.8 "$(DESTDIR)$(MANDIR)"/stjerm.8.gz
    
.PRECIOUS: *.o