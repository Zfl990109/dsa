#pragma once
#include<iostream>
#include "sort.h"

using namespace std;

typedef int Rank;
constexpr auto length = 5;

template<typename T> class vector{
protected:
	Rank _size;
	Rank _capacity;
	T* _elements;

public:
	vector();

	Rank size();

	T operator[](Rank r);

	T get(Rank r);

	void put(Rank r, T e);

	void insert(Rank r, T e);

	void remove(Rank r);

	bool disordered();

	void sort();

	Rank find(T e);

	//void deduplicate();

	void traverse();
	
};
template<typename T> vector<T>::vector() {
	this->_size = 0;
	this->_capacity = length;
	this->_elements = new T[this->_capacity];
}

template<typename T> Rank vector<T>::size() {
	return this->_size;
}

template<typename T> T vector<T>::operator[](Rank r) {
	return this->_elements[r];
}

template<typename T> T vector<T>::get(Rank r) {
	if (r < 0 || r > this->_size) {
		cout << "下标非法错误" << endl;
		return NULL;
	}
	return this->_elements[r];
}

template<typename T> void vector<T>::put(Rank r, T e) {
	if (r < 0 || r >= this->_size) {
		cout << "下标非法错误" << endl;
		return;
	}
	this->_elements[r] = e;
}

template<typename T> void vector<T>::insert(Rank r, T e) {
	if (this->_size >= this->_capacity) {
		this->_capacity *= 2;
		T* newElements = new T[this->_capacity];
		for (Rank i = 0; i < this->_size; i++)
		{
			newElements[i] = this->_elements[i];
		}
		delete[]this->_elements;
		this->_elements = newElements;
	}
	if (r < 0) {
		for (Rank i = this->_size; i > 0; i--)
		{
			this->_elements[i] = this->_elements[i - 1];
		}
		this->_elements[0] = e;
	}
	else if(r >= this->_size){
		this->_elements[this->_size] = e;
	}
	else {
		for (Rank i = this->_size; i > r; i--)
		{
			this->_elements[i] = this->_elements[i - 1];
		}
		this->_elements[r] = e;
	}
	this->_size++;
}

template<typename T> void vector<T>::remove(Rank r) {
	if (r < 0 || r >= this->_size) {
		cout << "下标非法错误" << endl;
		return;
	}
	for (Rank i = r; i < this->_size; i++) {
		this->_elements[i] = this->_elements[i + 1];
	}
	this->_size--;
	this->_elements[this->_size] = NULL;
}

template<typename T> bool vector<T>::disordered() {
	for (Rank i = 1; i < this._size; i++) {
		if (this->_elements[i] < this->_elements[i - 1]) {
			return false;
		}
	}
	return true;
}

template<typename T> void vector<T>::sort() {
	bubble_sort<T>(this->_elements, this->_size);
}

template<typename T> Rank vector<T>::find(T e) {
	for (Rank i = 0; i < this->_size; i++){
		if (this->_elements[i] == e) {
			return i;
		}
	}
	return -1;
}

template<typename T> void vector<T>::traverse() {
	for (Rank i = 0; i < this->_size; i++){
		cout << this->_elements[i] << " ";
	}
	cout << endl;
}