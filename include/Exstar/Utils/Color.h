namespace exstar{
	class Color{
		
	public:
		int r,g,b,a;
		static const exstar::Color Black;
		static const exstar::Color Red;
		static const exstar::Color Green;
		static const exstar::Color Blue;
		static const exstar::Color White;
		Color(int r,int g,int b);
		Color(int r,int g,int b,int a);
		static float getFloat(int color){
			return (float)(color/255.0);
		}
	};
}