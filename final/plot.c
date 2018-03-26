#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *pipe = popen("gnuplot -persist","w");
	system("clear");
	fprintf(pipe,"set terminal x11 0\n");
	fprintf(pipe,"set style data lines\n");
	fprintf(pipe,"set title 'hit rate vs Cache size '\n");
	fprintf(pipe,"set xlabel 'Cache size'\n");
	fprintf(pipe,"set ylabel 'Hit rate'\n");
	fprintf(pipe,"plot 'data1_c.txt'\n");


	fprintf(pipe,"set terminal x11 1\n");
	fprintf(pipe,"set style data lines\n");
	fprintf(pipe,"set title 'hit rate vs block size '\n");
	fprintf(pipe,"set xlabel 'Block size'\n");
	fprintf(pipe,"set ylabel 'Hit rate'\n");
	fprintf(pipe,"plot 'data1_b.txt'\n");
	

	fprintf(pipe,"set terminal x11 2\n");
	fprintf(pipe,"set style data lines\n");
	fprintf(pipe,"set title 'hit rate vs Associativity '\n");
	fprintf(pipe,"set xlabel 'Associativity'\n");
	fprintf(pipe,"set ylabel 'Hit rate'\n");
	fprintf(pipe,"plot 'data1_e.txt'\n");
	pclose(pipe);
	return 0;
}

