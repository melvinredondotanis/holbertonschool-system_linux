#include "laps.h"

/**
 * main - entry point.
 *
 * Return: always 0.
 */
int main(void)
{

	int ids1[3] = {1, 42, 101};
	int ids2[1] = {11};

	race_state(ids1, 3);
	printf("--\n");
	race_state(ids1, 3);
	printf("--\n");
	race_state(ids1, 3);
	printf("--\n");
	race_state(ids2, 1);
	printf("--\n");
	race_state(ids1, 3);
	printf("--\n");
	race_state(ids2, 1);
	printf("--\n");
	race_state(ids1, 3);
	printf("--\n");
	race_state(ids2, 1);
	printf("--\n");
	race_state(ids1, 3);
	printf("--\n");
	race_state(ids2, 1);
	printf("--\n");
	race_state(NULL, 0);
	return (0);
}
