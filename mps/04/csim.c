#include "cachelab.h"
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

// Direct mapped cache simulator


typedef unsigned long long int mem_addr_t; // Implements the data storage type for the data in the cache(the data storage size for a cache is 8 bytes, so this is why we use unsigned long long)

typedef struct{
    int valid; // flag that indicates the presence of a valid bit in a row
    mem_addr_t tag; //Tag stores the memory address of the data fetched 
    int line_row_cnt; // Indicates which specific row we are in accessing the cache

}cache_line; // Total struct is one row of the cache line (Data) 

typedef struct{
    cache_line *lines; // Points to an array of rows in a cache (set)
}cache_set;

typedef struct{
    int numb_sets, numb_lines, block_size;
    cache_set * sets; // Points to an array of sets in a cache set

}cache;

int main(int argc, char *argv[] )
{
    int E = 0;
    int b = 0;
    int s = 0;
    char *t; 
    int misses = 0
    int hits = 0;
    int evicts = 0
    int size; 
    char command
    unsigned long long int address; // Initializes the data storage in the cache
    char parse_cmdline;
    extern char *optarg; // Needed for the getopt function

    while((parse_cmdLine = getopt(argc, argv, "hvs:E:b:t:"))!= -1) {// Parses cmd Line arguments
        switch(parse_cmdLine){
            case 's':
                s = atoi(optarg); // if option has a value, it points to the extern optarg, so you have to call the atoi() to convert the string to an int value
                break;
            case 'E':
                E = atoi(optarg);
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                t = optarg;
                break;  
        }
    }

    File *trace; // check to see if the tracefile in our command line exists
    if (( trace = fopen(t, "r")) == NULL){ // use the f open command and r to open and read the file. If it is equal to null, the tracefile isn't available to open
        printf("Could not open %s\n",t);
        exit(1);
    }

    cache c; //Initialize the cache structure itself
    cache_set set; // 
    cache_line line;

    cache.numbsets = b;
    cache.numb_lines = E;
    cache.block_size = s;

    c.sets = (cache_set *) malloc(sizeof(cache_set)*(pow(2.0,s)) ); // Initialize the cache sets and allowcate memory for it. 
    for (int i = 0; i < pow(2,s), i++){
        set.lines = (cache_line *) malloc(sizeof(cache_line)*(E));
        c.sets[i] = set; 
    }
    printSummary(0, 0, 0);
    return 0;
}
