#
#  E10_0.cpp
#  Ludovico Lapo Luperi
#  ludovicolapo.luperi@studenti.unimi.it
#

LIBS:= `root-config --libs`
INCS:= `root-config --cflags`

SMACHD = -g -Wall -pedantic

.phony: all
all: main esegui

main: main.cpp random.h BasicFunction.h
		g++ -std=c++11 -o main main.cpp ${INCS} ${LIBS} ${SMACHD}

esegui:
	./main 10
	
clean:
	rm main
	


