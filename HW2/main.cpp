#include "shell.h"

int main() {
    MyShell shell; // Create a MyShell object
    shell.loadState();  // Load the initial state of the shell

    string command; // String to store user commands
    do {
        cout << "> ";
        getline(cin, command);
        shell.processCommand(command);
        shell.saveState();  // Save the updated state after each command
    } while (command != "exit");

    return 0;
}