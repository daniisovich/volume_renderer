#include <iostream>

#include "glwindow.h"


int main() {
	
	std::cout << "Direct Volume Renderer start" << std::endl;

	try {

		GLWindow window{};

		while (!window.shouldClose()) {

			window.swapAndPoll();
		}

	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	

	return EXIT_SUCCESS;

}