#include <stdio.h>
#include <stdlib.h>
#include <Python.h>

/**
 * print_python_string - func
 * @p: PyObject
 */
void print_python_string(PyObject *p)
{
	char *ascii = "compact ascii",
		 *ucode = "compact unicode object";
	PyASCIIObject *str_ob = NULL;

	setbuf(stdout, NULL);
	printf("[.] string object info\n");
	if (!PyUnicode_Check(p))
	{
		printf("  [ERROR] Invalid String Object\n");
		return;
	}
	str_ob = (PyASCIIObject *)p;
	printf("  type: %s\n", ((str_ob->state.ascii) ? ascii : ucode));
	printf("  length: %lu\n", str_ob->length);
	printf("  value: %s\n", PyUnicode_AsUTF8(p));
}
