#pragma once

#include <iostream>

namespace exstar{
	class exception {
	public:
		/**
		 * When thrown the message will be outputed and program stopped
		 * throw exstar::exception("That didn't work");
		 * 
		 * @param message The message to output
		*/
		exception(std::string message);
	};
}
