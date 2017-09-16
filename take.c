#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

void append_char_to_string(char* string, char character) {
    int len = strlen(string);
    string[len] = character;
    string[len + 1] = '\0';    
}

void spill_into(char* buffer, int * idx_out) {
    /* Convert buffer to int and set as the result of idx_out */
    if (strlen(buffer) != 0) {
        *idx_out = atoi(buffer);
        buffer[0] = '\0';
    }
}

void parse(char* str, char* buffer, int * start_out, int * end_out, int * step_out) {
	int start = 0;
	int end = 0;
	int step = 1;
	int colon_index = 0;	

	for (int i=0; i<strlen(str); i++) {
		if  (str[i] != ':') {
			append_char_to_string(buffer, str[i]);
		}
		else {
			if (colon_index == 0) {
				spill_into(buffer, &start);
			}

			if (colon_index == 1) {
				spill_into(buffer, &end);
			}			
			
			colon_index ++;			
		}
	}
    if (colon_index == 2) {    
        spill_into(buffer, &step);
    }

    else if (colon_index == 1) {    
        spill_into(buffer, &end);
    }
    *start_out = start;
	*end_out = end;
	*step_out = step;
}


void slice(char* str, char* buf, int start, int end, int step) { 
    
    int length = strlen(str);
    /* Allow negative indexes */
    if (start < 0) {
        start += length;
    }

    if (end <= 0) {
        end += length;
    }
    
    int buffers_running_index = 0;
    if (step > 0) {
        for (int i = start; i < end; i += step) {
            buf[buffers_running_index++] = str[i];
        }
    }
    else {
       for (int i = end - 1; i >= start; i += step) {
            buf[buffers_running_index++] = str[i];
       }
    }

    buf[buffers_running_index] = '\0';
}


int main(int argc, char * argv[]) {
	int start = 0;
    int end = 0;
    int step = 1;
    char buf[256] = "";
	char* slice_expr = argv[1];
    char str_to_slice[USHRT_MAX] = "";    
    
    scanf("%[^\t]", str_to_slice);
    if (argc == 2) { 
        str_to_slice[strlen(str_to_slice) - 1] = '\0'; 
	    parse(slice_expr, buf, &start, &end, &step);
        slice(str_to_slice, buf, start, end, step);
    }

    // a --by-lines (or -l) flag was supplied.
    else if (argc == 3) { 
        if (!(argv[2] == "--by-lines" || argv[2] == "-l" || 
              argv[3] == "--by-lines" || argv[3] == "-l")) {
            printf("Unparsable command.\n");
            return 2;
        }
       
    }

    else {
        printf("Illegal number of arguments supplied.\n");
        return 1;
    }

    printf("%s\n", buf);
	return 0;
}
