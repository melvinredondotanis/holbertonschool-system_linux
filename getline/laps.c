#include "laps.h"

cars *create_cars_node(int id)
{
    cars *new;

    new = malloc(sizeof(*new));
    if (!new)
        return (NULL);
    new->id = id;
    new->laps = 0;
    new->next = NULL;
    return (new);
}

void add_cars(cars **head, cars *new)
{
    cars **current;

    current = head;
    while (*current && new->id > (*current)->id)
        current = &(*current)->next;
    new->next = *current;
    *current = new;
}

void print_state(cars **head)
{
    cars **current;

    printf("Race state:\n");
    current = head;
    while (*current)
    {
        printf("Car %i [%lu laps]\n", (*current)->id, (*current)->laps);
        current = &(*current)->next;
    }
}

void check_cars(cars **head, int *id, size_t size)
{
    cars **current;
    size_t i;

    for (i = 0; i < size; ++i)
    {
        for (current = head; *current; current = &(*current)->next)
            if (id[i] == (*current)->id)
            {
                ++(*current)->laps;
                break;
            }
        if (!*current)
        {
            printf("Car %i joined the race\n", id[i]);
            add_cars(head, create_cars_node(id[i]));
        }
    }
}

void race_state(int *id, size_t size)
{
    static cars *head;
    cars *current;

    current = head;
    if (size)
    {
        check_cars(&head, id, size);
        print_state(&head);
    }
    else
    {
        while (current)
        {
            current = current->next;
            free(head);
            head = current;
        }
        
    }
}