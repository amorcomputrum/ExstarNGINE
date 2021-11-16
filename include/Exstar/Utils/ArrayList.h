#include <vector>
namespace exstar{
	template<class T>
	class ArrayList
	{
	public:
		int size;
		std::vector<T> data;
		ArrayList();
		void add(T n);
		void replace(int i,T n);
		void remove(int i);
		T get(int g);
		
	};
}