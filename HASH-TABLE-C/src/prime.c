#include<math.h>

#include "prime.h"

int is_prime(const int m){
    if(m < 2) return -1;
    if(m < 4) return 1;
    if((m % 2) == 0) return 0;

    for(int i=3; i < floor(sqrt((double) m)); i += 2){
        if((m%2) == 0){
            return 0;
        }
    }

    return 1;
}

int next_prime(int x){
    while(is_prime(x) != 1){
        x++;
    }
    return x;
}