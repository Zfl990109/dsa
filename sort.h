#pragma once
#include<iostream>
typedef int Rank;

template<typename T> void swap(T& a, T& b) {
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

template<typename T>Rank bubble_one(T* arr, Rank lo, Rank hi) {
	Rank index = lo++;
	while (lo < hi) {
		if (arr[lo - 1] > arr[lo]) {
			swap(arr[lo - 1], arr[lo]);
			index = lo;
		}
		lo++;
	}
	return index;
}

template<typename T> void bubble_sort(T* arr, Rank len) {
	Rank lo = 0, hi = len;//[lo,hi)
	while (lo < hi) {
		(hi = bubble_one(arr, lo, hi));
	};
}
