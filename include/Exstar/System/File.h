#pragma once

#include <fstream>

namespace exstar{
	class File{
	public:
		int numLines;
		
		File(std::string filename);
		~File();
		std::string getLine(unsigned int line);
		std::string getFileLocation();
		void setLine(unsigned int line,std::string data);
		void writeLine(std::string data);
		void open();
		void close();
		void rename(std::string newName);
		exstar::File operator<<(std::string param);
	private:
		char ABC[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
		std::ifstream input;
		std::ofstream output;
		std::string fileLoc;
		std::string to_bytes(std::string data);
	};
}
