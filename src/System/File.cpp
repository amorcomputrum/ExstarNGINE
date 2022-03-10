#include "Exstar/System/File.h"
#include <cstddef>

exstar::File::File(std::string filename){
	fileLoc = filename;
	input.open(filename);
	output.open(filename,std::ios::app);
}

exstar::File::~File(){
	input.close();
	output.close();
}

std::string exstar::File::getLine(unsigned int line){
	std::string text;
	for(int i = 0; i < line; i++){
		std::getline(this->input,text);
	}
	return text;
}

std::string exstar::File::getFileLocation(){
	return fileLoc;
}

void exstar::File::setLine(unsigned int line, std::string data){
	int start = 0;
	for(int i = 0; i < line; i++){
		start += getLine(i).size();
	}
	int lineSize = getLine(line).size();
	//flush text
	std::string clearLine;
	for(int i = 0; i < lineSize; i++){
		clearLine += "\b";
	}
	//go to end of line
	output.seekp(start+lineSize);
	//clear line and write
	output << clearLine+data;

	//output.seekp(std::ios_base::cur,std::ios_base::end);
}

void exstar::File::writeLine(std::string data){
	//output.seekp(std::ios_base::cur,std::ios_base::end);
	if(output.tellp() != 0) output << std::endl << to_bytes(data);
	else output << to_bytes(data) << std::endl;
}

void exstar::File::open(){
	if(!input.is_open()){
		input.open(fileLoc);
	}
	if(!output.is_open()){
		output.open(fileLoc);
	}
}

void exstar::File::close(){
	input.close();
	output.close();
}

exstar::File exstar::File::operator<<(std::string param){
	output << to_bytes(param);
}

std::string exstar::File::to_bytes(std::string data){
	std::byte bytes[data.size()];
	std::string val = "";
	for(size_t i = 0; i < data.size(); i++){
		std::string temp;
		bytes[i] = std::byte(data[i]);
		temp += std::to_string(std::to_integer<int>(bytes[i]));
		int count = 1;
		bool doneCompressing = false;
		while(!doneCompressing){
			if(std::to_string(std::to_integer<int>(std::byte(data[i+count]))) == temp && count < 26){
				count++;
			}else{
				val += ABC[count-1];
				val += temp;
				i+= count-1;
				doneCompressing = true;
			}
		}
		val += " ";
		
	}
	return val;
}