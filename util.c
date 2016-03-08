#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "util.h"

char *punctuation = { ".?!" };
int punct_size = 5;

char *blacklist = { "\"“”‘’" };
int blacklist_size = 5;

int is_blacklisted(int ch)
{       
        int count;
        for(count = 0; count < blacklist_size; count++)
        {       
                if(ch == blacklist[count])
                        return 1;
        }
        
        return 0;
}

int is_punct(int ch)
{       
        int count;
        for(count = 0; count < punct_size; count++)
        {       
                if(ch == punctuation[count])
                        return 1;
        }
        
        return 0;
}

char *getln(char *buff, FILE *stream)
{       
        int count, c, mult = 1;
        char *tmp;

        assert(stream != NULL && ALLOC_CHUNK_SIZE > 0);

        for (count = 0; ; count++)
        {       
                c = getc(stream);
                
                /* allocate another chunk if necessary */
                if ((count % ALLOC_CHUNK_SIZE) == 0)
                {       
                        tmp = realloc(buff, ALLOC_CHUNK_SIZE * sizeof *buff * mult);
                        if (tmp == NULL)
                                return NULL;
                        else    
                                buff = tmp;
                        
                        mult++;
                }
                
                if (c == '\n')
                {       
                        buff[count] = '\0';
                        break;
                }
                else if(c == EOF)
                {       
                        free(buff);
                        buff = NULL;
                        break;
                }
                else    
                        buff[count] = c;
        }
        
        return buff;
}
