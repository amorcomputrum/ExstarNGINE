namespace exstar{
	/**
	 * The images data
	*/
	exstar::ArrayList<unsigned char *>* images = new exstar::ArrayList<unsigned char *>;
	/**
	 * The amount of Objects that are using each file that is stored in the images ArrayList
	*/
	exstar::ArrayList<int>* numUsers = new exstar::ArrayList<int>;
	/**
	 * Add an image to the images ArrayList
	 * 
	 * @param file The file to load
	 * 
	 * @return The index,width, and height of the file
	*/
	int* addImage(const char* file);
	/**
	 * Removes an image from the images ArrayList
	 * 
	 * @param index The location of the image to remove
	*/
	void removeImage(int index);
}