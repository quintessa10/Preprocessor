# Custom C Preprocessor Implementation

This project is a systems programming application written in standard C that mimics the fundamental operations of a C preprocessor. It processes C source code files to handle compiler directives and strip comments before the actual compilation phase begins, ultimately generating a clean, preprocessed .i output file.

## Key Features & Functionalities

* **1. Header File Inclusion (`#include`):** Identifies include directives, searches standard directories like `/usr/include/`, and seamlessly injects the contents of the header files directly into the source stream.
* **2. Macro Expansion (`#define`):** Parses macro definitions and dynamically stores their names and values. It then scans the code to find and replace all valid macro occurrences with their respective values, intelligently ignoring text enclosed in double quotes.
* **3. Comment Stripping:** Systematically reads the source code character by character to identify and completely remove both single-line (`//`) and multi-line (`/* ... */`) comments.
* **4. Automated File Pipeline:** Manages the creation, reading, and deletion of intermediate temporary files (`temp.c`) to safely transition the original `.c` code into the final `.i` output file.

## Technical Concepts Applied

* **A. Singly Linked Lists (SLL):** Utilized to dynamically store and manage an arbitrary number of macro definitions (`struct stu`) without relying on fixed-size arrays.
* **B. Advanced File Handling:** Extensive use of file I/O operations including `fopen()`, `fgetc()`, `fgets()`, `fseek()`, and `rewind()` to manipulate file cursors and text data.
* **C. String Manipulation:** Relies heavily on `<string.h>` functions (`strstr()`, `strncmp()`) and custom implementations (`mystrcat()`) for precise text search, concatenation, and replacement.
* **D. Dynamic Memory Allocation:** Uses `malloc()` to dynamically allocate memory for 2D character arrays (storing lines of code) and linked list nodes, optimizing memory usage based on the size of the source file.
