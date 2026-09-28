F_EXT:= elf
SOURCES:= 
OBJS:=./src/ejercicios.o ./src/getch.o ./src/getop.o ./src/main.o ./src/stack.o
#si bien no hay referencia directa a getch por getop, 
#este funciona dado que la dependencia se resuleve al incluir el .o de
#getch en la compilacion final
build:$(OBJS)
	gcc ${OBJS} -o program.${F_EXT} -lm
	
	

########COMPILING RULES
##make esta creado para cualquier lenguaje, pero hay algunos que lo usan tan seguido,
#que ahora tiene esto, si una regla no tine receta, pero las extenciones a usar
#son conocidas (referirse al manual oficial) entonces la genera solo
./src/ejercicios.o : ./src/ejercicios.h
./src/getch.o :
./src/stack.o : ./src/calc.h
./src/getop.o : ./src/calc.h ./src/ejercicios.h
./src/main.o : ./src/calc.h ./src/main.c
	$(CC) ./src/main.c -c -o ./src/main.o
	

########LIFE IMPROVEMENT RULES
#no me creo que funciono!!!!!!
commit-m-%:
	git add .
	git commit -m "$@"	
