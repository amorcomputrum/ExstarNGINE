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
		void resize(int width,int height){
			this->width = width;
			this->height = height;
		}
		void move(int x,int y){
			this->x+=x;
			this->y+=y;
		}
		void set(int x,int y){
			this->x += this->x-x;
			this->y += this->y-y;
		}
		Dimension getSize(){
			return Dimension{this->width,this->height};
		}
		int getWidth(){
			return this->width;
		}
		int getHeight(){
			return this->height;
		}
		int getX(){
			return x;
		}
		int getY(){
			return y;
		}


	private:
		int width,height,x,y;
	};
}