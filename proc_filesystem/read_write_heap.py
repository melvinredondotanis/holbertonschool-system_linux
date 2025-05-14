#!/usr/bin/env python3
"""Script to find and replace a string in the heap of a process."""

import os
import sys


def read_write_heap(pid, target_string, new_string):
    """
    Find and replace a string in the heap of a process.

    Args:
        pid: Process ID
        target_string: String to find in heap
        new_string: Replacement string
    """
    if os.geteuid() != 0:
        print('This script needs to be executed with sudo')
        sys.exit(1)

    target_bytes = target_string.encode('utf-8')
    tmp = (len(target_string) - len(new_string))
    padded_new_string = new_string + '\0' * tmp
    del tmp
    new_bytes = padded_new_string.encode('utf-8')

    print(f'[*] maps: /proc/{pid}/maps')
    print(f'[*] mem: /proc/{pid}/mem')

    try:
        heap_info = None
        with open(f'/proc/{pid}/maps', 'r') as maps_file:
            for line in maps_file:
                if '[heap]' in line:
                    heap_info = line.strip()
                    addresses = line.split()[0]
                    start_addr, end_addr = addresses.split('-')
                    start = int(start_addr, 16)
                    end = int(end_addr, 16)
                    break

        if not heap_info:
            print('[!] No heap found in process memory')
            sys.exit(1)

        print('[*] Found [heap]:')
        print('\tpathname = [heap]')
        print(f'\taddresses = {start_addr}-{end_addr}')
        print(f'\tpermissions = {heap_info.split()[1]}')
        print(f'\toffset = {heap_info.split()[2]}')
        print(f'\tinode = {heap_info.split()[3]}')
        print(f'[*] Addr start [{hex(start)}] | end [{hex(end)}]')

    except Exception as e:
        print(f'Error while reading memory map: {e}')
        sys.exit(1)

    try:
        with open(f"/proc/{pid}/mem", "rb") as mem_file:
            mem_file.seek(start)
            heap_data = mem_file.read(end - start)

            address = None
            occurrences = []
            offset = 0
            while True:
                offset = heap_data.find(target_bytes, offset)
                if offset == -1:
                    break
                address = start + offset
                occurrences.append(address)
                offset += len(target_bytes)

            if not occurrences:
                print(f"[!] String '{target_string}' not found in heap")
                sys.exit(1)

            address = occurrences[0]
            print(f"[*] Found '{target_string}' at {hex(address)}")

    except Exception as e:
        print(f'Error while reading memory: {e}')
        sys.exit(1)

    try:
        print(f"[*] Writing '{new_string}' at {hex(address)}")
        with open(f'/proc/{pid}/mem', 'rb+') as mem_file:
            for addr in occurrences:
                mem_file.seek(addr)
                mem_file.write(new_bytes)

    except Exception as e:
        print(f'Error while writing memory: {e}')
        sys.exit(1)


if __name__ == "__main__":
    try:
        if len(sys.argv) < 4:
            print(f"Usage: sudo {sys.argv[0]} <pid> <target> <new_string>")
            sys.exit(1)

        pid = int(sys.argv[1])
        target = sys.argv[2]
        new_string = sys.argv[3]

        read_write_heap(pid, target, new_string)
    except KeyboardInterrupt:
        print("\n[!] Exiting...")
        sys.exit(1)
    except Exception as e:
        print(f"[!] An error occurred: {e}")
        sys.exit(1)
