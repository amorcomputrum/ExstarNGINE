namespace exstar{
	class ShaderProgram{
		public:
			ShaderProgram(std::string Folder,std::string Name);
			void use();
			unsigned int get();
		private:
			unsigned int shaderProg;
			std::string loadSource(std::string path);
	};
}