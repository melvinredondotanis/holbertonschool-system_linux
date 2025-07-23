#include <Python.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * print_python_list - prints info about a python list
 * @p: pointer to python object struct
 */
void print_python_list(PyObject *p)
{
	size_t size = ((PyVarObject *)p)->ob_size, i = 0;

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %ld\n", size);
	printf("[*] Allocated = %ld\n", ((PyListObject *)p)->allocated);
	for (i = 0; i < size; i++)
		printf("Element %ld: %s\n", i,
			((PyListObject *)p)->ob_item[i]->ob_type->tp_name);
}
