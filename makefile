F_EXT:= elf

build:
	gcc -o program.${F_EXT} src/ejercicios.c src/main.c -lm
commit-m-%:
	git add .
	git commit -m "$@"	
