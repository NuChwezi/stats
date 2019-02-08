stats: stats.o
	gcc -o stats stats.o -lm

stats.o: stats.c
	gcc -c stats.c 

clean:
	rm -rf *.o stats
