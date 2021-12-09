namespace exstar{
	exstar::ArrayList<unsigned char *>* images = new exstar::ArrayList<unsigned char *>;
	exstar::ArrayList<int>* numUsers = new exstar::ArrayList<int>;
	int* addImage(const char* file);
	void removeImage(int index);
}