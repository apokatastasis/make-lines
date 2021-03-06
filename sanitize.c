#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

//#define DEBUG

char *delete_at_index(int index, char *arr, int arr_size)
{
	unsigned int count;
	char *arr_tmp;

	if(index > arr_size -1)
		return NULL;

	/* TODO: this is a quick and dirty hack */
	if(((int)arr[index] == -30 && (int)arr[index+1] == -128 && (int)arr[index+2] == -100)
		|| ((int)arr[index] == -30 && (int)arr[index+1] == -128 && (int)arr[index+2] == -99))
	{
		for(count = index; count < (strlen(arr) - 2); count++)
			arr[count] = arr[count + 3];

		return arr;
	}

	for(count = index; count < strlen(arr); count++)
	{

#ifdef DEBUG
		printf("DEBUG: %c -> %c\n", arr[count], arr[count+1]);
#endif

		arr[count] = arr[count + 1];
	}

	arr_tmp = realloc(arr, (arr_size - 1) * sizeof *arr);
	if(arr_tmp == NULL)
	{
		free(arr);
		return NULL;
	}
	else
		arr = arr_tmp;

	return arr;
}

int main(int argc, char **argv)
{
	unsigned int count;
	char *buffer = NULL;
	char *filename = NULL;
	FILE *fin = NULL;
	FILE *fout = NULL;

	printf("Enter file to sanitize: ");

	filename = getln(filename, stdin);
	if(filename == NULL)
	{
		perror(NULL);
		return EXIT_FAILURE;
	}

	fin = fopen(filename, "r");
	if(fin == NULL)
	{
		perror(NULL);
		free(filename);
		return EXIT_FAILURE;
	}

	fout = fopen("tmp_lns", "w");
	if(fout == NULL)
	{
		perror(NULL);
		free(filename);
		fclose(fin);
		return EXIT_FAILURE;
	}
	
	while((buffer = getln(buffer, fin)) != NULL)
	{
		if(!strcmp(buffer, "\n"))
			continue;

#ifdef DEBUG
		for(count = 0; count < strlen(buffer); count++)
			printf("DEBUG: buffer[%d] = %d\n", count, buffer[count]);
#endif

		for(count = 0; count < strlen(buffer); count++)
		{
			if(is_blacklisted(buffer[count]))
			{
				buffer = delete_at_index(count, buffer, strlen(buffer));

#ifdef DEBUG
				printf("DEBUG: (%d) modified buffer = %s\n", count, buffer);
#endif

			}
		}

#ifdef DEBUG
		printf("DEBUG: final modified buffer = %s\n", buffer);
#endif

		fprintf(fout, "%s\n", buffer);
	}

	fclose(fin);
	fclose(fout);
	free(buffer);
	free(filename);

	return 0;
}
