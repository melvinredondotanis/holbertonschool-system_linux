#ifndef LAPS_H
#define LAPS_H

#include <stdlib.h>
#include <stdio.h>

/**
 * struct cars - linked list to organize the race
 * @id: id of the car
 * @lap: current lap of the car
 * @next: next car node
 */
typedef struct cars
{
    int id;
    size_t laps;
    struct cars *next;
} cars;

void race_state(int *id, size_t size);

#endif /* LAPS_H */