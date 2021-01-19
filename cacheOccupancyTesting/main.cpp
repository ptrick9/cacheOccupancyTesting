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
#include <unistd.h>
//#include <cstdio>

using namespace std;

volatile int64_t counterVal = 0;
volatile bool run = true;
int64_t *timeVals;


void timerFunc() {
    while(run)
    {
        counterVal++;
    }
}

void runSizeTest() {
    FILE *myFile = fopen("/Users/patrickcronin/Dropbox/Patrick/udel/WINTER2021/CacheOccupancy/pythonExaminer/test.txt", "w");
    thread countThread(timerFunc);
    
    int maxSize = 5001;
    int maxIterations = 500;
    int timeCount = 0;
    volatile int temp;
    int numLines = 32;
    
    timeVals = (int64_t*)malloc(maxIterations*100*sizeof(int64_t));
    
    for(int size = 1; size <= maxSize; size+=500) {
        
        numLines=32;
        doublePointerPage **data = (doublePointerPage**)malloc(sizeof(doublePointerPage *) * size);
        for (int i = 0; i < size; i++) {
            data[i] = (doublePointerPage*)valloc(sizeof(doublePointerPage));
        }
        
        //generateRandomBook(data, size);
        generateStraightBook(data, size);
        
        volatile doubleLine *old = data[0]->d[0].next;
        //prime
        for(int i = 0; i < 32*size-1; i++) {
            old = old->next;
        }
        
        /*
        numLines=64
        singlePointerPage **data = (singlePointerPage**)malloc(sizeof(doublePointerPage *) * size);
        for (int i = 0; i < size; i++) {
            data[i] = (singlePointerPage*)valloc(sizeof(doublePointerPage));
        }
        
        generateRandomBook(data, size);
        //generateStraightBook(data, size);
        
        singleLine *old = data[0]->d[0].next;
        //prime
        for(int i = 0; i < 64*size-1; i++) {
            old = old->next;
        }*/

        
        for(int iteration = 0; iteration < maxIterations; iteration++) {
        
            //probe
            int64_t start = counterVal;
            old = data[0]->d[0].next;
            for(int i = 0; i < numLines*size-1; i++) {
                old = old->next;
            }
            
            int64_t end = counterVal;
            
            timeVals[timeCount++] = end-start;

            printf("%d %d/%d\n", size, iteration, 1000);
        }
        
        for (int i = 0; i < size; i++) {
            free(data[i]);
        }
        free(data);
               
    }
    
    run = false;
    for(int i = 0; i < timeCount; i++) {
        fprintf(myFile, "%d %d %lld\n", 1, 1, timeVals[i]);
    }
    
    fclose(myFile);
    
    countThread.join();
}



int main(int argc, const char * argv[]) {
       
    
    //runSizeTest();
    
    
    
    
    bool gather = false;
    if(argc == 2 && gather) {
        
        int numLines=32;
        int size = 2000;
        int maxIters = 1500;
        int timeCount = 0;
        
        timeVals = (int64_t*)malloc(maxIters*sizeof(int64_t));
        char buffer[200];
        sprintf(buffer, "/Users/patrickcronin/Dropbox/Patrick/udel/WINTER2021/CacheOccupancy/pythonExaminer/Data/%s.txt", argv[1]);
        FILE *myFile = fopen(buffer, "w");
        thread countThread(timerFunc);
        
        doublePointerPage **data = (doublePointerPage**)malloc(sizeof(doublePointerPage *) * size);
        for (int i = 0; i < size; i++) {
            data[i] = (doublePointerPage*)valloc(sizeof(doublePointerPage));
        }
        
        //generateRandomBook(data, size);
        generateStraightBook(data, size);
        
        volatile doubleLine *old = data[0]->d[0].next;
        //prime
        for(int i = 0; i < numLines*size-1; i++) {
            old = old->next;
        }
        for(int iteration = 0; iteration < maxIters; iteration++) {
            //probe
            int64_t start = counterVal;
            old = data[0]->d[0].next;
            for(int i = 0; i < numLines*size-1; i++) {
                old = old->next;
            }
            int64_t end = counterVal;
            timeVals[timeCount++] = end-start;

        }
        for (int i = 0; i < size; i++) {
            free(data[i]);
        }
        free(data);
        
        run = false;
        for(int i = 0; i < timeCount; i++) {
            fprintf(myFile, "%lld\n", timeVals[i]);
        }
        
        fclose(myFile);
        
        countThread.join();
    } else {
        printf("provide a file name\n");
    }
    return 0;
}

