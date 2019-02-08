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
double* parse_numbers(char *, int *); /* take comma del string and output array of numbers */
void print_larray(double *, int); /* pretty print the contents of an array */
void compute(char* op, double * inputs, int size); /* apply the given operation to the input array and display the results */
double compute_mean(double * , int ); /* given list of doubles, and size, return mean */
double compute_sum(double * , int ); /* given list of doubles, and size, return sum */
double compute_variance(double * , int ); /* given list of doubles, and size, return variance */
double compute_sdeviation(double * , int ); /* given list of doubles, and size, return standard deviation */
int stricmp(char const *a, char const *b); /* compare two strings irrespective of case */
double * darray_concat(double*, int, double*, int); /* return the concatenation of the second array to the first */



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

    //printf("Computing %s...\n", show_op(OP));
    // let's grab the input list...
    double * nums_parsed = {0};
    int np_size = 0;
    for(int i=2; i<argc; i++) {
        int s_parray[1] = {0};
        double * tmp = parse_numbers(argv[i], s_parray);
        if(nums_parsed == NULL){
            np_size = *s_parray;
            nums_parsed = darray_concat(nums_parsed, 0, tmp, *s_parray);
        } else {
            nums_parsed = darray_concat(nums_parsed, np_size, tmp, *s_parray);
            np_size += *s_parray;
        }
    }

	//print_larray(nums_parsed,np_size);
	compute(OP,nums_parsed,np_size);

    return S_OK;
}

void print_usage() {
    printf("Usage:\n\n%s OP n,n,n,n,n,n,n...\n\nWhere: OP is one of c,t,m,v,s, for count, total or sum, mean,variance and standard deviation respectively, \nand n is any valid number\n\n", PROG_NAME);
}

char* show_op(char * op) {
    if(stricmp(op,"c")==0)
        return "Count";
    else if(stricmp(op,"t")==0)
        return "Sum";
    else if(stricmp(op,"m")==0)
        return "Mean";
    else if(stricmp(op,"v")==0)
        return "Variance";
    else if(stricmp("s",op)==0)
        return "Standard Deviation";
    else return "Unknown";

}


double * parse_numbers(char * input, int * s_out) {
    int n_char = sizeof(input)/sizeof(char);
    static double nums[100]; // possibly larger than needed.
    int token_count = 0;
    const char * DELIM = ",";
    char * tkn_ptr;

    while( (tkn_ptr = strsep(&input,DELIM)) != NULL ){
        if(strcmp(tkn_ptr,"") == 0)
            continue;
        char * end;
        nums[token_count] = strtod(tkn_ptr,&end); // save number in offset token_count of int vector nums
        ++token_count;
    }

    *s_out = token_count; // return size of parsed array

    return nums;
}

void print_larray(double * nums, int size) {
    printf("\nIN ARRAY:[");
    for(int i = 0; i < size; i++)
        printf("%f%s", nums[i], i < size-1 ? ", " : "");

    printf("]");
}

void compute(char* op, double * inputs, int size) {
    if(stricmp(op,"c") == 0){
        double val = size;
        printf("%s: %f", show_op(op),val);
    }
    else if(stricmp(op,"t") == 0){
        double val = compute_sum(inputs, size);
        printf("%s: %f", show_op(op),val);
    }
    else if(stricmp(op,"m") == 0){
        double val = compute_mean(inputs, size);
        printf("%s: %f", show_op(op),val);
    }
    else if(stricmp(op,"v") == 0){
        double val = compute_variance(inputs, size);
        printf("%s: %f", show_op(op),val);
    }
    else if(stricmp(op,"s") == 0){
        double val = compute_sdeviation(inputs, size);
        printf("%s: %f", show_op(op),val);
    }
}

double compute_mean(double * inputs, int size){
    int sum = compute_sum(inputs, size);
    return sum * 1.0 / size;
}

double compute_sum(double * inputs, int size){
    double sum = 0;
    for(int i=0; i < size; i++) sum += *(inputs++);
    return sum;
}

double compute_variance(double * inputs, int size){
    double u = compute_mean(inputs, size);
    double sum_sq_mdiff = 0;
    for(int i=0; i < size; i++) {
        double x = *(inputs++);
        sum_sq_mdiff += (x - u) * (x - u);
    }
    return (1.0 / size) * sum_sq_mdiff;
}

double compute_sdeviation(double * inputs, int size){
    double v = compute_variance(inputs, size);
    return sqrt(v);

}

double * darray_concat(double* a, int sa, double* b, int sb) {
    int new_s = sa + sb, index = 0;
    double * concat = malloc(sizeof(double) * new_s);
    // print_larray(concat,new_s);

    for(int i=0; i<sa; i++, index++) concat[i] = *a++;
    // print_larray(concat,new_s);
    for(int j=0; j<sb; j++) concat[(index)+j] = *b++;
    return concat;
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

