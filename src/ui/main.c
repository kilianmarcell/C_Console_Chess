#include <windows.h> // Include for SetConsoleOutputCP
#include <stdio.h>

int main() {
    SetConsoleOutputCP(CP_UTF8); // Set console output to UTF-8

    printf("Hello, World!\n");
    return 0;
}