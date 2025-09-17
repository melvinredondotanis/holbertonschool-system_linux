#ifndef MULTITHREADING_H
#define MULTITHREADING_H

#include "list.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>

/* -------------------------------------------------------------------------- */

/**
 * struct pixel_s - RGB pixel
 *
 * @r: Red component
 * @g: Green component
 * @b: Blue component
 */

typedef struct pixel_s
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} pixel_t;

/**
 * struct img_s - Image
 *
 * @w:      Image width
 * @h:      Image height
 * @pixels: Array of pixels
 */

typedef struct img_s
{
	size_t w;
	size_t h;
	pixel_t *pixels;
} img_t;

/**
 * struct kernel_s - Convolution kernel
 *
 * @size:   Size of the matrix (both width and height)
 * @matrix: Kernel matrix
 */

typedef struct kernel_s
{
	size_t size;
	float **matrix;
} kernel_t;

/**
 * struct blur_portion_s - Information needed to blur a portion of an image
 *
 * @img:      Source image
 * @img_blur: Destination image
 * @x:        X position of the portion in the image
 * @y:        Y position of the portion in the image
 * @w:        Width of the portion
 * @h:        Height of the portion
 * @kernel:   Convolution kernel to use
 */

typedef struct blur_portion_s
{
	img_t const *img;
	img_t *img_blur;
	size_t x;
	size_t y;
	size_t w;
	size_t h;
	kernel_t const *kernel;
} blur_portion_t;

/* task 6 - 22-prime_factors.c */

typedef void *(*task_entry_t)(void *);

/**
 * enum task_status_e - Task statuses
 *
 * @PENDING: Task is pending
 * @STARTED: Task has been started
 * @SUCCESS: Task has completed successfully
 * @FAILURE: Task has completed with issues
 */

typedef enum task_status_e
{
	PENDING = 0,
	STARTED,
	SUCCESS,
	FAILURE
} task_status_t;

/**
 * struct task_s - Structure for managing tasks in a multitasking system
 *
 * @entry: a pointer to the function representing the task to be executed
 * @param: a pointer to the parameters to be passed to the task function
 * @status: the current status of the task, represented by task_status_t
 * @result: a pointer to store the result of the task execution
 * @lock: mutex to ensure thread-safety of task modifications
 */

typedef struct task_s
{
	task_entry_t entry;
	void *param;
	task_status_t status;
	void *result;
	pthread_mutex_t lock;
} task_t;

/* -------------------------------------------------------------------------- */

/* task 0 */
void *thread_entry(void *arg);

/* task 1 */
int tprintf(char const *format, ...);

/* task 2 */
void blur_portion(blur_portion_t const *portion);

/* task 3 */
void *blurPortionThreadEntry(blur_portion_t *portion);
blur_portion_t *portionImage(img_t *img_blur, const img_t *img,
							 const kernel_t *kernel, size_t portion_ct);
void blur_image(img_t *img_blur, img_t const *img, kernel_t const *kernel);

/* task 4 */
void init_mutex(void);
void destroy_mutex(void);
int tprintf(char const *format, ...);

/* task 5 */
int add_to_list(list_t *list, unsigned long factor);
list_t *prime_factors(char const *s);
void free_list(list_t *list);

/* task 6 */
void initTaskStatusMutex(void);
void destroyTaskStatusMutex(void);
task_t *create_task(task_entry_t entry, void *param);
void destroy_task(task_t *task);
void *exec_tasks(list_t const *tasks);

#endif /* MULTITHREADING_H */