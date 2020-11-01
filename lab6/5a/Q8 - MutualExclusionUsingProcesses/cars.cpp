#include "car.h"

car::car() {
	carnum = 0;
	driver = "error";
	pitstop1 = 0;
	pitstop2 = 0;
	idx = -1;
	lap_time = rand() % 40 + 30;
	lapnum = 0;
	race_time = 0;
}

car::car(int index,int num, string name, int p1, int p2) {
	idx = index;
	carnum = num;
	driver = name;
	pitstop1 = p1;
	pitstop2 = p2;
	lap_time = rand() % 80 + 60;
	lapnum = 0;
	race_time = 0;
}

car::~car() {}

int car::main() {
	CMutex console("F1");
	CSemaphore PEL("PitEntryLight", 0, 1);
	CSemaphore PEXL("PitExitLight", 0, 1);
	CSemaphore pitEmpty("Empty", 0, 1);
	CSemaphore pitFull("Full", 0, 1);

	bool pitflag1 = false;
	bool pitflag2 = false;

	while (lapnum <= 69) {
		Sleep(lap_time*10);
		lapnum++;
		race_time = race_time+ (lap_time * 10);
		console.Wait();
		stat();
		console.Signal();
		if (lapnum == pitstop1) {
			pitflag1 = true;
		}
		else if(lapnum == pitstop2) {
			pitflag2 = true;
		}
		if (pitflag1 || pitflag2) {
			if (PEL.Read() == 1) {
				pitFull.Signal();
				console.Wait();
				MOVE_CURSOR(40, idx + 1);
				cout << "In the Pits" << endl;
				console.Signal();
				PEXL.Wait();
				pitEmpty.Signal();
				if (pitflag1) pitflag1 = false;
				else if (pitflag2) pitflag2 = false;
			}
		}
		console.Wait();
		MOVE_CURSOR(40, idx + 1);
		cout << "Racing             " << endl;
		console.Signal();
	}
	console.Wait();
	MOVE_CURSOR(40, idx + 1);
	cout << "Done             " << endl;
	console.Signal();
	return 0;
};

void car::stat() {
	MOVE_CURSOR(0,idx+1);
	cout << "#" << carnum << endl;
	MOVE_CURSOR(5, idx+1);
	cout << driver << endl;
	MOVE_CURSOR(25, idx+1);
	cout << lapnum << endl;
	//test
	MOVE_CURSOR(30, idx + 1);
	cout << race_time << endl;
}

int car::racet() {
	return race_time;
}

string car::desc() {
	return "#" + to_string(carnum) + " " + driver;
}