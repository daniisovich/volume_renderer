#include <iostream>

#include "Application.h"


int main() {

	try {
		const std::array<uint32_t, 2> size{ 800, 600 };
		Application app{ size };
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}	

	return EXIT_SUCCESS;

}