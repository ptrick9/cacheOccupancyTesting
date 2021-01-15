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

int64_t counterVal = 0;
bool run = true;
int64_t *timeVals;


void timerFunc() {
    while(run)
    {
        counterVal++;
    }
}




int main(int argc, const char * argv[]) {
       
    
    
    FILE *myFile = fopen("/Users/patrickcronin/Dropbox/Patrick/udel/WINTER2021/CacheOccupancy/pythonExaminer/test.txt", "w");
    thread countThread(timerFunc);
    
    

    
    int maxSize = 5001;
    int maxIterations = 500;
    int timeCount = 0;
    volatile int temp;
    int numLines = 32;
    
    timeVals = (int64_t*)malloc(maxIterations*100*sizeof(int64_t));
    
    for(int size = 1; size <= maxSize; size+=500) {
        
        
        for(int iteration = 0; iteration < maxIterations; iteration++) {
        
            
            numLines=32;
            doublePointerPage **data = (doublePointerPage**)malloc(sizeof(doublePointerPage *) * size);
            for (int i = 0; i < size; i++) {
                data[i] = (doublePointerPage*)valloc(sizeof(doublePointerPage));
            }
            
            //generateRandomBook(data, size);
            generateStraightBook(data, size);
            
            doubleLine *old = data[0]->d[0].next;
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
            
            //probe
            int64_t start = counterVal;
            old = data[0]->d[0].next;
            for(int i = 0; i < numLines*size-1; i++) {
                old = old->next;
            }
            
            int64_t end = counterVal;
            
            timeVals[timeCount++] = end-start;
            
            for (int i = 0; i < size; i++) {
                free(data[i]);
            }
            free(data);
            
            printf("%d %d/%d\n", size, iteration, 1000);
        }
        
        
        
        
        
               
    }
    
    run = false;
    for(int i = 0; i < timeCount; i++) {
        fprintf(myFile, "%d %d %lld\n", 1, 1, timeVals[i]);
    }
    
    fclose(myFile);
    
    countThread.join();
    
    
    
    
    
    /*
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
     */
    return 0;
}

