//
//  pointerManaging.cpp
//  cacheOccupancyTesting
//
//  Created by Patrick Cronin on 1/14/21.
//

#include "pointerManaging.hpp"
#include <random>
#include <stdio.h>

using namespace std;

int c_row(int num) {
    return num%32;
}
int c_col(int num) {
    return num/32;
}

int c_rowS(int num) {
    return num%64;
}
int c_colS(int num) {
    return num/64;
}

void generateRandomBook(doublePointerPage **book, int numPages) {
    
    int totalInds = 32*numPages;
    int *temp = (int*)malloc(totalInds*sizeof(int));
    
    for(int i = 0; i < totalInds; i++) {
        temp[i] = i;
    }
    
    shuffle(temp+1, temp + totalInds, default_random_engine(1));
        
    for(int i = 1; i < totalInds; i++) {
        book[c_col(temp[i-1])]->d[c_row(temp[i-1])].next = &book[c_col(temp[i])]->d[c_row(temp[i])];
    }
    
    free(temp);
}

void generateRandomBook(singlePointerPage **book, int numPages) {
    
    int totalInds = 64*numPages;
    int *temp = (int*)malloc(totalInds*sizeof(int));
    
    for(int i = 0; i < totalInds; i++) {
        temp[i] = i;
    }
    
    shuffle(temp+1, temp + totalInds, default_random_engine(1));
        
    for(int i = 1; i < totalInds; i++) {
        book[c_colS(temp[i-1])]->d[c_rowS(temp[i-1])].next = &book[c_colS(temp[i])]->d[c_rowS(temp[i])];
    }
    
    free(temp);
}

void generateStraightBook(singlePointerPage **book, int numPages) {
    
    for(int i = 0; i < 64; i++) {
        for(int j = 0; j < numPages; j++) {
            if (j < numPages - 1) {
                book[j]->d[i].next = &book[j+1]->d[i];
            } else if (j == numPages - 1 && i < 63) {
                book[j]->d[i].next = &book[0]->d[i+1];
            } else {
                book[j]->d[i].next = NULL;
            }
        }
    }
}

void generateStraightBook(doublePointerPage **book, int numPages) {
    
    for(int i = 0; i < 32; i++) {
        for(int j = 0; j < numPages; j++) {
            if (j < numPages - 1) {
                book[j]->d[i].next = &book[j+1]->d[i];
            } else if (j == numPages - 1 && i < 31) {
                book[j]->d[i].next = &book[0]->d[i+1];
            } else {
                book[j]->d[i].next = NULL;
            }
        }
    }
}


