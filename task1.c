#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <math.h>

int checkP2(int x);
int *dTob(int n,int l);
int bTod(int a[],int l);

int main(){
    int pgs=4; //page size
    int ms=32; //memory size
    int nof=ms/pgs; //number of frames
    int la[]={8,4,3,2,15,18,25}; //logical addresses generated by the CPU
    int pmt[]={3,6,8,12,2}; //page table

    int offset_bit = log2(pgs); //find out # of bits required for offset
    int pg_num_bit = log2(nof); //find out # of bits required for page number 
    int m = pow(2, pg_num_bit + offset_bit); //find out address spaces required in main memory


    printf("Page size: %d\n", pgs);
    printf("Memory size: %d\n", ms);
    printf("Number of frames required: %d\n", nof);
    printf("Page number bits: %d\n", pg_num_bit);
    printf("Offset bits: %d\n", offset_bit);
    printf("Number of address spaces: %d\n", m);

    printf("Page Table_____\n");
    for (int i = 0; i < sizeof(pmt)/sizeof(pmt[0]); i++) {
        printf("%d -> %d\n", i, pmt[i]);
    }

    for (int i = 0; i < sizeof(la)/sizeof(la[0]); i++) {
        int logical_address = la[i];
        int page_number = logical_address/pgs;
        int offset = logical_address % (pgs);

        if (page_number >= sizeof(pmt)/sizeof(pmt[0])) {
            printf("%d is an invalid page number\n", page_number);
            continue;
        } 
        int frame_number = pmt[page_number];
        int physical_address = frame_number * pgs + offset;

        if(physical_address >= ms){
            printf("%d is an invalid physical address\n", physical_address);
            continue;
        }
        printf("Corresponding physical address of logical address %d: %d\n", la[i], physical_address);
    }
    return 0;
}



int checkP2(int x){
    // Check if x is a power of 2
    return x && (!(x & (x - 1)));
}

int *dTob(int n,int l){
    // Decimal to Binary conversion
    int *b=(int *)malloc(l*sizeof(int));
    int i;
    for(i=l-1;n>0;i--){
        b[i]=n%2;
        n=n/2;
    }
    for(i=i;i>=0;i--){
        b[i]=0;
    }
    return b;
}

int bTod(int a[],int l){
    // Binary to Decimal conversion
    int i=0,d=0;
    for(i=0;i<l;i++){
        d+=a[i]*pow(2,l-i-1);
    }
    return d;
}



