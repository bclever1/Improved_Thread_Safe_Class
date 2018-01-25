#pragma once


#include <mutex>
#include <iostream>
#include <list>
#include <memory>
#include <algorithm>

template <typename T>
class myDataClass
{
public:
	myDataClass(T theData) 
	{
		myData = std::make_unique<T>(theData);
	}

	myDataClass()
	{

	}

	~myDataClass() {}

	T& getData() 
	{
		
		return (*myData.get()); 
	}
	
	struct myDataClassDisplayFunctor
	{
		void operator()(std::shared_ptr<myDataClass<int>> c)
		{
			if (c != nullptr)
			{
				std::cout << c->getData() << std::endl;
			}
		}
	};

private:

	std::unique_ptr<T> myData;
};

template <typename T>
class threadSafeSingleton
{
public:

	static threadSafeSingleton* GetInst()
	{
		std::call_once(myOnceFlag, []() {new threadSafeSingleton(); });
		return threadSafeSingleton::myInstance;
	}

	void myFcn()
	{
		std::lock_guard<std::mutex> guard(myMutex);

		// Do something...
	}

	void addElement(myDataClass<T>* theElement)
	{
		std::lock_guard<std::mutex> guard(myMutex);
		myData.push_back(std::move(theElement));
	}

	void removeElementAt(int theIdx)
	{
		std::lock_guard<std::mutex> guard(myMutex);

		int myIdx = 0;
		for (auto itr = myData.begin();
             itr != myData.end();
			 ++itr)
		{
			if (myIdx == theIdx)
			{
				myData.erase(itr);
				break;
			}

			++myIdx;
		}
	}

	void displayAll()
	{
		myDataClassDisplayFunctor f;
		std::for_each(myData->begin(), myData->end(), f);
	}

private:

	threadSafeSingleton()
	{
		myInstance = this;
	}

	static threadSafeSingleton<T>* myInstance;
	std::list<myDataClass<T>*> myData;
	static std::once_flag myOnceFlag;
	std::mutex myMutex;
};

template <typename T>
std::once_flag threadSafeSingleton<T>::myOnceFlag;

template <typename T>
threadSafeSingleton<T>* threadSafeSingleton<T>::myInstance = NULL;