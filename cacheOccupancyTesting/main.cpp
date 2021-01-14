//
//  main.cpp
//  cacheObserver
//
//  Created by Patrick Cronin on 1/13/21.
//

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <thread>
#include <random>
#include <sys/time.h>
#include "pointerManaging.hpp"
//#include <cstdio>

using namespace std;

int64_t counterVal = 0;
bool run = true;
int *dummyArr;
int64_t *timeVals;


void timerFunc() {
    while(run)
    {
        counterVal++;
    }
}




int main(int argc, const char * argv[]) {
       
    if(argc == 2) {
        char buffer[200];
        sprintf(buffer, "/Users/patrickcronin/Dropbox/Patrick/udel/WINTER2021/CacheOccupancy/pythonExaminer/%s.txt", argv[1]);
        FILE *myFile = fopen(buffer, "w");
        thread countThread(timerFunc);
        

        
        volatile int temp;
        int size = 4E6;
        int maxIters = 10000;
        dummyArr = (int*)malloc(size*sizeof(int));
        timeVals = (int64_t*)malloc(maxIters*sizeof(int64_t));
        
        //prime
        for(int i = 0; i < size; i+=64) {
            dummyArr[i] = i;
            //indexArr[i] = i;
        }
        
        for(int iteration = 0; iteration < maxIters; iteration++) {
        
            
            //probe
            int64_t start = counterVal;
            
            for(int i = 0; i < size; i+=64) {
                //temp = dummyArr[indexArr[i]];
                temp = dummyArr[i];
            }
            int64_t end = counterVal;

            timeVals[iteration] = end-start;
            //
            //printf("%d/%d\n", iteration, 100);
        }
        free(dummyArr);
        printf("%d\n\n", size);
        
        for(int i = 0; i < maxIters; i++) {
            fprintf(myFile, "%d %d %lld\n", size, i, timeVals[i]);
        }
        free(timeVals);
                   
        
        
        fclose(myFile);
        
        
        
        
        
        run = false;
        countThread.join();
    } else {
        printf("provide a file name\n");
    }
    return 0;
}

