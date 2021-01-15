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

typedef struct{
    doubleLine d[32];
}pointerPage;


typedef struct{
    pointerPage page[256];
}pointer_book;


void generateRandomBook(pointerPage **book, int numPages);
void generateStraightBook(pointerPage **book, int numPages);


#endif /* pointerManaging_hpp */
