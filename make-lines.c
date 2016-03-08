#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

#define STRLEN 100

int main(void) 
{
	int ch, is_last_punct = 0;
	FILE *fin, *fout;
	char *inpath =  NULL, *outpath = NULL;

	outpath = malloc(sizeof(char) * 10);
	if(outpath == NULL)
	{
		free(inpath);
		perror(NULL);
		return EXIT_FAILURE;
	}

	printf("Enter input file path: ");

	inpath = getln(inpath, stdin);
	if(inpath == NULL)
	{
		perror(NULL);
		free(outpath);
		return EXIT_FAILURE;
	}

	outpath = strcpy(outpath, "lines.txt");

	fin = fopen(inpath, "r");
	if(fin == NULL)
	{
		perror(inpath);
		free(inpath);
		free(outpath);
		return EXIT_FAILURE;
	}
	fout = fopen(outpath, "a");
	if(fout == NULL)
	{
		perror(outpath);
		free(inpath);
		free(outpath);
		fclose(fin);
		return EXIT_FAILURE;
	}

	while((ch = getc(fin)) != EOF)
	{
		if(is_blacklisted(ch))
		{
			is_last_punct = is_punct(ch);
			continue;
		}
		if(is_last_punct && ch == ' ')
		{
			putchar('\n');
			putc('\n', fout);
		}
		else
		{
			putchar(ch);
			putc(ch, fout);
		}
		
		is_last_punct = is_punct(ch);
	}

	fclose(fin);
	fclose(fout);

	free(inpath);
	free(outpath);

	return EXIT_SUCCESS;
}
