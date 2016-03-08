CC=gcc
CFLAGS=-Wall -Wextra -pedantic
WCC=i686-w64-mingw32-gcc
WCFLAGS=-lmingw32
OBJECT=util.o wutil.o
BIN=sanitize sanitize.exe make-lines make-lines.exe

all: make-lines wmake-lines sanitize wsanitize
make-lines: util.o make-lines.c
	${CC} ${CFLAGS} -o make-lines make-lines.c util.o
wmake-lines: wutil.o make-lines.c
	${WCC} ${CFLAGS} ${WCFLAGS} -o make-lines.exe wutil.o
sanitize: util.o sanitize.c
	${CC} ${CFLAGS} -o sanitize sanitize.c util.o
wsanitize: wutil.o sanitize.c
	${WCC} ${CFLAGS} ${WCFLAGS} -o sanitize.exe wutil.o
util.o: util.c
	${CC} ${CFLAGS} -c util.c
wutil.o: util.c
	${WCC} ${CFLAGS} ${WCFLAGS} -o wutil.o -c wutil.c
clean:
	rm $OBJECT $BIN
