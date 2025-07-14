#include "hnm.h"

/**
 * swap_32 - swap bytes for 32-bit value if needed
 * @value: value to swap
 * Return: swapped value if needed
 */
uint32_t swap_32(uint32_t value)
{
return ((value >> 24) | ((value >> 8) & 0xff00) |
		((value << 8) & 0xff0000) | (value << 24));
}

/**
 * swap_64 - swap bytes for 64-bit value if needed
 * @value: value to swap
 * Return: swapped value if needed
 */
uint64_t swap_64(uint64_t value)
{
return ((((uint64_t)swap_32(value)) << 32) |
		swap_32(value >> 32));
}
