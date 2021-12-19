#include "Exstar/Utils/ArrayList.h"

template<class T>
exstar::ArrayList<T>::ArrayList(){
	size = 0;
	this->exstar::ArrayList<T>::data.clear();
}
template <class T>
void exstar::ArrayList<T>::add(T n){
	this->exstar::ArrayList<T>::data.push_back(n);
	size++;
}
template <class T>
void exstar::ArrayList<T>::replace(int i,T n){
	this->exstar::ArrayList<T>::data[i] = n;
}
template <class T>
void exstar::ArrayList<T>::remove(int i){
	this->exstar::ArrayList<T>::data.erase(this->data.begin()+i);
	size--;
}

template <class T>
T exstar::ArrayList<T>::get(int g){
	if(g > -1 && g < size){
		return this->data[g];
	}else{
		throw std::invalid_argument("Out of Range");
	}
}