# stats
A simple commandline C program for computing basic descriptive statistics on arbitrary input data

Usage:
--------

stat OP n,n,n,n,n,n,n...

Where: OP is one of c,t,m,v,s, for count, total or sum, mean,variance and standard deviation respectively, 
and n is any valid number


Examples:
----------

    echo "0,1, 2,3" | xargs ./stats m

Will output:

    Mean: 1.500000

Find the mean size of items in your home directory, expressed in bytes.

    du -b -Ss  ~/* | cut -d\/ -f1 | tr -d ' ' | paste -s -d "," | xargs ./stats m

Try c, v, t and s too!
