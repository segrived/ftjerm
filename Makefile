CC ?= gcc
LD = ${CC}
PREFIX ?= /usr
BINDIR ?= $(PREFIX)/bin
MANDIR ?= $(PREFIX)/share/man/man8
PRGDIR ?= $(PREFIX)/share/ftjerm

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib

PACKAGES = x11 xinerama gtk+-2.0 vte
LDFLAGS = $(shell pkg-config --libs $(PACKAGES)) -lm
CFLAGS += -Wall -Os $(shell pkg-config --cflags $(PACKAGES))

SRC = main.c mainwindow.c config.c term.c popupmenu.c shortcut.c
OBJ = ${SRC:.c=.o}

all: ftjerm

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: ftjerm.h

ftjerm: ${OBJ}
	@echo LD $@
	@${LD} -o $@ ${OBJ} ${LDFLAGS}
	@strip $@
    
clean:
	@rm -f ${OBJ} ftjerm
    
install: all
	@echo installing executable file to ${DESTDIR}${BINDIR}
	@install -Dm755 ftjerm "$(DESTDIR)$(BINDIR)/ftjerm"
	@echo installing manual pages to ${DESTDIR}${MANDIR}
	@install -Dm644 ftjerm.8 "$(DESTDIR)$(MANDIR)/ftjerm.8.gz"

uninstall:
	@echo removing executable file from ${DESTDIR}${BINDIR}
	@rm -f "$(DESTDIR)$(BINDIR)/ftjerm"
	@echo removing manual pages from ${DESTDIR}${MANDIR}
	@rm -f "$(DESTDIR)$(MANDIR)/ftjerm.8.gz"
    
.PRECIOUS: *.o
