#include "c:\RTExamples\rt.h"
#include <atomic>


atomic_flag flag;
long x = 0;

// A child thread to update x
UINT __stdcall Thread1(void* args)
{
	cout << "Child running\n";
	for (long i = 0; i < 50000000L; i++) {
		while (flag.test_and_set() == true)
			;
		x = x + 1;
		flag.clear();
	}
	return 0;
}

// The main thread in the process
int main()
{
	flag.clear();
	CThread  Child(Thread1);

	cout << "Parent running\n";
	for (long i = 0; i < 50000000L; i++) {
		while (flag.test_and_set() == true)
			;
		x = x + 1;
		flag.clear();
	}

	Child.WaitForThread();
	cout << "Final x = " << x << endl;

	getchar();
	return 0;
}
