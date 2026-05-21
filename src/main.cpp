/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Thu, Mar, 2026                                                     *
 * Title           - Arcade                                                             *
 * Description     -                                                                    *
 *     main                                                                             *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#include <iostream>
#include <stdexcept>

#include "main.hpp"
#include "Core/Core.hpp"

int main(int argc, char **argv)
{
	if (argc != 2) {
        std::cerr << "Usage: ./arcade ./lib/arcade_[lib].so" << std::endl;
        return 84;
    }
    try {
        Arcade::Core core(argv[1]);
        core.run();
        return 0;
    } catch (const std::runtime_error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
}
