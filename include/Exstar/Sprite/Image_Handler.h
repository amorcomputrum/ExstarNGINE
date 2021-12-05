namespace exstar{
	std::vector<unsigned char *> images;
	int images_size = 0;
	exstar::ArrayList<int>* numUsers = new exstar::ArrayList<int>;
	int addImage(const char* file,int w,int h);
	void removeImage(int index);
}