namespace exstar{
	class exception {
	public:
		exception(std::string message){
			std::cerr << message << std::endl;
		}
	};
}