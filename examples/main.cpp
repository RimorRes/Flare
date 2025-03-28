//
// Created by maxim on 23/03/2025.
//

#include "main.h"

#include <libflare.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}