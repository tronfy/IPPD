hello:
	gcc -O3 -fopenmp hello.c -o hello.x

pi:
	gcc -O3 pi.c -o pi.x

pi_par:
	gcc -O3 -fopenmp pi_par.c -o pi_par.x

pi_compare: pi pi_par
	./pi.x 1 $(n)
	./pi_par.x $(threads) $(n)

traprule:
	gcc -O3 traprule.c -o traprule.x -lm

traprule_par:
	gcc -O3 -fopenmp traprule_par.c -o traprule_par.x -lm

traprule_compare: traprule traprule_par
	./traprule.x
	./traprule_par.x
