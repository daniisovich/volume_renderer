#include <iostream>

#include "dvr/application.h"


int main() {

	try {
		const std::array<uint32_t, 2> size{ 800, 600 };
		dvr::Application app{ size };
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}	

	return EXIT_SUCCESS;

}