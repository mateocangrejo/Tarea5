#phony.mk

all: Results_hw5.pdf


Results_hw5.pdf : Results_hw5.tex
	pdflatex Results_hw5.tex  
Resultados_hw5.tex: Plots.py datos.txt
	python plots.py 

datos.txt : bayes.x 
	./bayes.x

bayes.x : CurvaRotacion.c 
	gcc -Wall CurvaRotacion.c -o bayes.x -lm

