all: median_finding.e

median_finding.e: median_finding.o
	gcc -g median_finding.o -o median_finding.e

median_finding.o: median_finding.c
	gcc -c median_finding.c