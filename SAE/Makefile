but : code.out

win.o : win.h
affichage.o : variables.h
decoupe.o : variables.h
position.o : variables.h
gameplay.o : win.h variables.h
lobby.o : variables.h
main.o : affichage.h decoupe.h position.h gameplay.h lobby.h variables.h

code.out : win.o affichage.o decoupe.o position.o gameplay.o lobby.o main.o
	gcc -o code.out win.o affichage.o decoupe.o position.o gameplay.o lobby.o main.o -lgraph
