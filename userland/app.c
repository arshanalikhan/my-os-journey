#include "libc.h"

void main() {
    // Create an empty array inside Userland memory to hold the input
    char name[100]; 

    print("\n=========================================\n");
    print("         WELCOME TO ARSHAN OS!           \n");
    print("=========================================\n");
    
    print("Please enter your name: ");
    
    // Stop the app, trigger Syscall 3, and let the Kernel fill 'name'
    scan(name); 
    
    print("\nHello, ");
    print(name);
    print("! You successfully wrote an interactive Userland app.\n");
    print("=========================================\n\n");
}
