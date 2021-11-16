namespace exstar{
	class Vector2d{
	private:
		int data [2];
	public:
		Vector2d(int x,int y);
		float dot(exstar::Vector2d v);
		float magnitude();
		void add(exstar::Vector2d vec);
		void add(int x,int y);
		void min(exstar::Vector2d vec);
		void min(int x,int y);
		void mul(exstar::Vector2d vec);
		void mul(int x,int y);
		void div(exstar::Vector2d vec);
		void div(int x,int y);
		void set(int x,int y);
		int getX();
		int getY();
	};
}