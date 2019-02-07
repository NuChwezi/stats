#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG 1
#ifdef DEBUG 
#define DPRINTF printf
#else
#define DPRINTF(...) // do nothing
#endif

/* program return status flags */
int S_OK=0, S_ERR=1;
char * PROG_NAME = "stat";

void print_usage(); /* print program usage */
char * show_op(char*); /* verbose name of given op */
long* parse_numbers(char *); /* take comma del string and output array of numbers */
void print_larray(long []);


int main(int argc, char **argv) {

    if(argc == 1) {
        printf("Missing parameters.\n");
        print_usage();
        return S_ERR;
    }
    if(argc == 2) {
        printf("Missing input list.\n");
        print_usage();
        return S_ERR;
    }

    char * OP = argv[1]; // operation to perform

    printf("Computing %s...\n", show_op(OP));
    // let's grab the input list...
    for(int i=2; i<argc; i++) {
        printf("\n%i : %s\n", i, argv[i]);
        long * nums_parsed = parse_numbers(argv[i]);
        //free(nums_parsed);
    }

    return S_OK;
}

void print_usage() {
    printf("Usage:\n\n%s OP n,n,n,n,n,n,n...\n\nWhere: OP is one of m,v,s for mean,variance and standard deviation\nand n is any valid number\n\n", PROG_NAME);
}

char* show_op(char * op) {
    if(strcmp(op,"m")==0)
        return "Mean";
    else if(strcmp(op,"v")==0)
        return "Variance";
    else if(strcmp("s",op)==0)
        return "Standard Deviation";
    else return "Unknown";

}


long * parse_numbers(char * input) {
    int n_char = sizeof(input)/sizeof(char);
    static long nums[100]; // possibly larger than needed.
    int token_count = 0;
    const char * delim = ",";
    char * tkn_ptr;

    while( (tkn_ptr = strsep(&input,delim)) != NULL ){
        printf( "- %s \n", tkn_ptr ); // what token are we currently at?
        printf( "~ %s \n", input ); // what's left of the input?
        char * end;
        nums[token_count] = strtol(tkn_ptr,&end,10); // save number in offset token_count of int vector nums
        token_count++;
        //print_larray(nums);
    }

    printf("\fFound %i tokens", token_count);

    return nums;
}

void print_larray(long * nums) {
    int size = sizeof(nums)/sizeof(long *);
    //DPRINTF("ARRAY SIZE: %ld,", nums[i]);
    for(int i = 0; i< size; i++)
        printf("ARRAY: %ld,", nums[i]);

}


