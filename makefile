F_EXT:= elf
SOURCES:= 
CFLAGS:=-Wall
OBJS:=./src/getch.o ./src/main.o ./src/funciones.o

########COMPILING RULES
build: ${OBJS}
	${CC} ${OBJS} -o program.${F_EXT} ${CFLAGS}
./src/main.o:./src/funciones.h
./src/getch.o:
./src/funciones.o:./src/funciones.h

########LIFE IMPROVEMENT RULES
#no me creo que funciono!!!!!!
commit-m-%:
	git add .
	git commit -m "$@"

clean:
	rm ${OBJS}
