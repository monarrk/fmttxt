#include <stdio.h>
#include <stdlib.h>

#define WID 70 
#define LEN 40 

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Please enter a file\n");
		return 1;
	}

	FILE *fp;
	// open the arg file
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("ERROR!: Could not open file \"%s\"...\n", argv[1]);
		return 1;
	}

	char *data;
	size_t n = 0;
	int c;

	int posx = 0;
	int posy = 0;
	int pgnum = 1;

	while ((c = fgetc(fp)) != EOF) {
		// new page
		if (posx == 0 && posy == 0) {
			printf("\n\n\n");
		}

		// a new line
		if (c == '\n') {
			printf("%c", c);
			posx = 0;
			posy++;
			continue;
		}

		// start of line
		if (posx == 0) {
			printf("     ");
			posx += 5;
		}

		// end of line
		if (posx >= (WID - 5)) {
			printf("%c\n", c);
			posy++;
			posx = 0;
		} else {
			printf("%c", c);
			posx++;
		}

		// end of page
		if (posy > LEN) {
			printf("\n\n     %d\n\n\n", pgnum);
			posy = 0;
			posx = 0;
			pgnum++;
		}
	}

	// finish off page
	for (int i=0; i < posy; i++) {
		printf("\n");
	}
	printf("\n\n     %d\n\n\n", pgnum);

	return 0;
}
