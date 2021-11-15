#include <vector>
namespace exstar{
	template<class T>
	class ArrayList
	{
	public:
		int size;
		std::vector<T> data;
		ArrayList(){
			size = 0;
			this->data.clear();
		}
		void add(T n){
			this->data.push_back(n);
			size++;
		}
		void replace(int i,T n){
			this->data[i] = n;
		}
		void remove(int i){
			this->data.erase(this->data.begin()+i);
			size--;
		}
		T get(int g){
			if(g > -1 && g < size){
				return this->data[g];
			}else{
				throw std::invalid_argument("Out of Range");
			}
		}
		
		
	};
}