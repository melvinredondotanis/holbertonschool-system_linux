#include <Python.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * print_python_bytes - ...
 * @p: ...
 */
void print_python_bytes(PyObject *p)
{
    ssize_t sz, i;

    printf("[.] bytes object info\n");
    if (p->ob_type != &PyBytes_Type)
    {
        printf("  [ERROR] Invalid Bytes Object\n"),
        return;
    }

    sz = ((PyVarObject *)p)->ob_size;
    printf("  size: %ld\n", sz);
    printf("  trying string: %s\n", ((PyBytesObject *)p)->ob_sval);
    sz = sz < 9 ? sz + 1 : 10;
    printf("  first %ld bytes: ", sz);
    for (i = 0; i < sz; i++)
        printf("%02hhx%c",
               ((PyBytesObject *)p)->ob_sval[i], i + 1 == sz ? '\n' : ' ');
}

/**
 * print_python_list - ...
 * @p: ...
 */
void print_python_list(PyObject *p)
{
    ssize_t sz = ((PyVarObject *)p)->ob_size, i;

    printf("%s", "[*] Python list info\n");
    printf("[*] Size of the Python List = %ld\n", sz);
    printf("[*] Allocated = %ld\n", ((PyListObject *)p)->allocated);
    for (i = 0; i < sz; i++)
    {
        PyObject *p_obj = ((PyListObject *)p)->ob_item[i];

        printf("Element %ld: %s\n", i, p_obj->ob_type->tp_name);
        if (p_obj->ob_type == &PyBytes_Type)
            print_python_bytes(p_obj);
    }
}
