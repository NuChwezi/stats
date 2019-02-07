#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

/* program return status flags */
int S_OK=0, S_ERR=1;
char * PROG_NAME = "stat";

void print_usage(); /* print program usage */
char * show_op(char*); /* verbose name of given op */
long* parse_numbers(char *, int *); /* take comma del string and output array of numbers */
void print_larray(long *, int); /* pretty print the contents of an array */
void compute(char* op, long * inputs, int size); /* apply the given operation to the input array and display the results */
double compute_mean(long * , int ); /* given list of longs, and size, return mean */
long compute_sum(long * , int ); /* given list of longs, and size, return sum */
double compute_variance(long * , int ); /* given list of longs, and size, return variance */
double compute_sdeviation(long * , int ); /* given list of longs, and size, return standard deviation */
int stricmp(char const *a, char const *b);


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
        int s_parray[1] = {0};
        long * nums_parsed = parse_numbers(argv[i], s_parray);
        print_larray(nums_parsed,*s_parray);
        compute(OP,nums_parsed,*s_parray);
    }

    return S_OK;
}

void print_usage() {
    printf("Usage:\n\n%s OP n,n,n,n,n,n,n...\n\nWhere: OP is one of t,m,v,s, for total or sum, mean,variance and standard deviation respectively, \nand n is any valid number\n\n", PROG_NAME);
}

char* show_op(char * op) {
    if(stricmp(op,"t")==0)
        return "Sum";
    else if(stricmp(op,"m")==0)
        return "Mean";
    else if(stricmp(op,"v")==0)
        return "Variance";
    else if(stricmp("s",op)==0)
        return "Standard Deviation";
    else return "Unknown";

}


long * parse_numbers(char * input, int * s_out) {
    int n_char = sizeof(input)/sizeof(char);
    static long nums[100]; // possibly larger than needed.
    int token_count = 0;
    const char * DELIM = ",";
    char * tkn_ptr;

    while( (tkn_ptr = strsep(&input,DELIM)) != NULL ){
        //printf( "- %s \n", tkn_ptr ); // what token are we currently at?
        //printf( "~ %s \n", input ); // what's left of the input?
        char * end;
        nums[token_count] = strtol(tkn_ptr,&end,10); // save number in offset token_count of int vector nums
        ++token_count;
    }

    printf("\fFound %i tokens", token_count);
    //print_larray(nums,token_count);

    *s_out = token_count; // return size of parsed array

    return nums;
}

void print_larray(long * nums, int size) {
    printf("\nIN ARRAY:[");
    //DPRINTF("ARRAY SIZE: %ld,", nums[i]);
    for(int i = 0; i < size; i++)
        printf("%ld%s", nums[i], i < size-1 ? ", " : "");

    printf("]");
}

void compute(char* op, long * inputs, int size) {
    if(stricmp(op,"t") == 0){
        double val = compute_sum(inputs, size);
        printf("\n%s: %f", show_op(op),val);
    }
    else if(stricmp(op,"m") == 0){
        double val = compute_mean(inputs, size);
        printf("\n%s: %f", show_op(op),val);
    }
    else if(stricmp(op,"v") == 0){
        double val = compute_variance(inputs, size);
        printf("\n%s: %f", show_op(op),val);
    }
    else if(stricmp(op,"s") == 0){
        double val = compute_sdeviation(inputs, size);
        printf("\n%s: %f", show_op(op),val);
    }
}

double compute_mean(long * inputs, int size){
    int sum = compute_sum(inputs, size);
    return sum * 1.0 / size;
}

long compute_sum(long * inputs, int size){
    long sum = 0;
    for(int i=0; i < size; i++) sum += *(inputs++);
    return sum;
}

double compute_variance(long * inputs, int size){
    double u = compute_mean(inputs, size);
    double sum_sq_mdiff = 0;
    for(int i=0; i < size; i++) {
        long x = *(inputs++);
        sum_sq_mdiff += (x - u) * (x - u);
    }
    return (1.0 / size) * sum_sq_mdiff;
}

double compute_sdeviation(long * inputs, int size){
    double v = compute_variance(inputs, size);
    return sqrt(v);

}

/* 
 * Extra Utils...
 *
 * */

int stricmp(char const *a, char const *b)
{
    for (;; a++, b++) {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d != 0 || !*a)
            return d;
    }
}

