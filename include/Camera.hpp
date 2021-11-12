namespace exstar{
	class Camera
	{
	public:
		Camera(int width,int height,int x,int y){
			this->width = width;
			this->height = height;
			this->x = x;
			this->y = y;
		}

	private:
		int width,height,x,y;
	};
}