#ifndef ArrayList_H
#define ArrayList_H
	#include "vector"
	#include "ostream"
	#include <iostream>
	namespace exstar{
		template<class T>
		class ArrayList
		{
		public:
			/**
			 * The size of the ArrayList
			*/
			int size;
			/**
			 * Initialize the ArrayList<>();
			*/
			ArrayList();
			/**
			 * Add a value to the list
			 * 
			 * @param n The value to add to the list
			*/
			void add(T n);
			/**
			 * Replave a value on the list
			 * 
			 * @param i The location to replace
			 * @param n The value to replace the selected location
			 * 
			 * i will become equal to n
			*/
			void replace(int i,T n);
			/**
			 * Remove a value in the list
			 * 
			 * @param i The location to remove
			 * 
			 * i will be removed from the list and size will decrement
			*/
			void remove(int i);
			/** 
			 * Return a value
			 * 
			 * @param g The location to return
			 * 
			 * @return The value located at g
			*/
			T get(int g);
		private:
			/**
			 * The stored data in the ArrayList
			*/
			std::vector<T> data;
		};
	};

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

#endif