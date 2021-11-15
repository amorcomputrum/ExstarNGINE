namespace exstar{
	class Vector2d{
	private:
		int data [2];
	public:
		Vector2d(int x,int y){
			data[0] = x;
			data[1] = y;
		}
		float dot(Vector2d v){
			return (getX()*v.getY()) + (v.getX() * getY());
		}
		float magnitude(){
			return std::sqrt((data[0]*data[0])+(data[1]*data[1]));
		}
		void add(Vector2d vec){
			data[0] += vec.getX();
			data[1] += vec.getY();
		}
		void add(int x,int y){
			data[0] += x;
			data[1] += y;
		}
		void min(Vector2d vec){
			data[0] -= vec.getX();
			data[1] -= vec.getY();
		}
		void min(int x,int y){
			data[0] -= x;
			data[1] -= y;
		}
		void mul(Vector2d vec){
			data[0] *= vec.getX();
			data[1] *= vec.getY();
		}
		void mul(int x,int y){
			data[0] *= x;
			data[1] *= y;
		}
		void div(Vector2d vec){
			data[0] /= vec.getX();
			data[1] /= vec.getY();
		}
		void div(int x,int y){
			data[0] /= x;
			data[1] /= y;
		}
		void set(int x,int y){
			data[0] = x;
			data[1] = y;
		}
		int getX(){
			return data[0];
		}
		int getY(){
			return data[1];
		}
	};
}