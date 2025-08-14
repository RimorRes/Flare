//
// Created by maxim on 23/03/2025.
//

#include "main.h"

#include <libflare.h>

#include <iostream>
#include <csignal>
#include <cstdlib>
#include <memory>

TriangleApp app;

// Function to handle termination signal
void signalHandler(const int signum) {
    std::cout << std::endl;
    std::cout << "Interrupt signal (" << signum << ") received.\n";
    app.interrupt = true;
}

int main() {

    // Register signal handler
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}