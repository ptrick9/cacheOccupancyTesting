//
//  pointerManaging.hpp
//  cacheOccupancyTesting
//
//  Created by Patrick Cronin on 1/14/21.
//

#ifndef pointerManaging_hpp
#define pointerManaging_hpp

#include <stdio.h>



typedef struct doubleLine{
    struct doubleLine* next;
    int filler[30];
}doubleLine;

typedef struct singleLine{
    struct singleLine* next;
    int filler[14];
}singleLine;

typedef struct{
    doubleLine d[32];
}doublePointerPage;

typedef struct{
    singleLine d[64];
}singlePointerPage;




void generateRandomBook(doublePointerPage **book, int numPages);
void generateStraightBook(doublePointerPage **book, int numPages);

void generateRandomBook(singlePointerPage **book, int numPages);
void generateStraightBook(singlePointerPage **book, int numPages);


#endif /* pointerManaging_hpp */
