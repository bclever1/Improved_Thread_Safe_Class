// Threads.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "threadSafeSingleton.h"

int main()
{
	myDataClass<int> dc_1(1);

	threadSafeSingleton<int>::GetInst()->addElement(&dc_1);

	int t = dc_1.getData();

	threadSafeSingleton<int>::GetInst()->removeElementAt(0);

    return 0;
}

