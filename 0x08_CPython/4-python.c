#include <stdio.h>
#include <stdlib.h>
#include <Python.h>

/**
 * print_python_string - ...
 * @p: ...
 */
void print_python_string(PyObject *p)
{
    wprintf(L"[.] string object info\n");
    if (!p || !PyUnicode_Check(p))
    {
        wprintf(L"  [ERROR] Invalid String Object\n");
        return;
    }
    if (((PyASCIIObject *)p)->state.ascii)
        wprintf(L"  type: compact ascii\n");
    else
        wprintf(L"  type: compact unicode object\n");
    wprintf(L"  length: %ld\n", ((PyASCIIObject *)p)->length);
    wchar_t *value = PyUnicode_AsWideCharString(p, NULL);
    if (value)
    {
        wprintf(L"  value: %ls\n", value);
        PyMem_Free(value);
    }
}
