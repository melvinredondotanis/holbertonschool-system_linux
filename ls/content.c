#include "hls.h"

/**
 * init_content - Initializes a content struct
 * @cnt: Pointer to the content struct to initialize
 *
 * Return: void
 */
static void init_content(content *cnt)
{
    if (cnt == NULL)
        exit(EXIT_FAILURE);

    cnt->name = malloc(256);
    if (cnt->name == NULL)
        exit(EXIT_FAILURE);

    cnt->tperm = malloc(11);
    if (cnt->tperm == NULL)
    {
        free(cnt->name);
        free(cnt->name);
        exit(EXIT_FAILURE);
    }

    cnt->usr = malloc(256);
    if (cnt->usr == NULL)
    {
        free(cnt->name);
        free(cnt->tperm);
        exit(EXIT_FAILURE);
    }

    cnt->grp = malloc(256);
    if (cnt->grp == NULL)
    {
        free(cnt->name);
        free(cnt->tperm);
        free(cnt->usr);
        exit(EXIT_FAILURE);
    }

    cnt->mtim = malloc(12);
    if (cnt->mtim == NULL)
    {
        free(cnt->name);
        free(cnt->tperm);
        free(cnt->usr);
        free(cnt->grp);
        free(cnt->mtim);
        exit(EXIT_FAILURE);
    }

    cnt->lc = 0;
    cnt->uid = 0;
    cnt->gid = 0;
    cnt->siz = 0;
}

/**
 * init_content_for_file - Initializes a content struct for a file
 * @cnt: Pointer to the content struct to initialize
 * @name: Name of the file
 *
 * Return: void
 */
static void init_content_for_file(content *cnt, char *name)
{
    if (cnt == NULL || name == NULL)
        exit(EXIT_FAILURE);

    init_content(cnt);
    


}