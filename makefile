F_EXT:= elf
SOURCES:= 
CFLAGS:=-Wall
OBJS:=./src/getch.o ./src/main.o

########COMPILING RULES
build: ${OBJS}
	${CC} ${OBJS} -o program.${F_EXT} ${CFLAGS}
./src/main.o:
./src/getch.o:

########LIFE IMPROVEMENT RULES
#no me creo que funciono!!!!!!
commit-m-%:
	git add .
	git commit -m "$@"

clean:
	rm ${OBJS}
