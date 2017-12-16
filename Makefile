all:
	gcc ./src/Shell.c ./src/Fat.c -o ./obj/program -I ./include

run:
	./obj/program

clean:
	rm -rf ./obj/*
