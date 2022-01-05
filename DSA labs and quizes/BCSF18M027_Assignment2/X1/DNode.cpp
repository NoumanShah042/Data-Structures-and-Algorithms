#include<iostream>
using namespace std;
#include"DNode.h"

template<typename T>
DNode<T>::DNode()
{
	next = nullptr;
	prev = nullptr;
}

template<typename T>
DNode<T>::DNode(T val)
{
	info = val;
	next = nullptr;
	prev = nullptr;
}