#include "technicians.h"

CMutex console("F1");
CSemaphore PEL("PitEntryLight", 0, 2);
CSemaphore PEXL("PitExitLight", 0, 2);
CSemaphore pitEmpty("Empty", 0, 2);
CSemaphore pitFull("Full", 0, 2);

//jacks
CSemaphore jackerfront("jacku", 0, 2);
CSemaphore jackerback("jacku2", 0, 2);

CSemaphore Refuel("startrefuel", 0, 2);

CSemaphore Visor1("visorman", 0, 2);
CSemaphore Debris1("debrisman", 0, 2);

CSemaphore FrontWheelNut1("FWN1", 0, 2);
CSemaphore FrontWheelNut2("FWN2", 0, 2);
CSemaphore RearWheelNut1("RWN1", 0, 2);
CSemaphore RearWheelNut2("RWN2", 0, 2);

CSemaphore FrontWheelRemove1("FWRem1", 0, 2);
CSemaphore FrontWheelRemove2("FWRem2", 0, 2);
CSemaphore RearWheelRemove1("RWRem1", 0, 2);
CSemaphore RearWheelRemove2("RWRem2", 0, 2);

CSemaphore FrontWheelReplace1("FWRep1", 0, 2);
CSemaphore FrontWheelReplace2("FWRep2", 0, 2);
CSemaphore RearWheelReplace1("RWRep1", 0, 2);
CSemaphore RearWheelReplace2("RWRep2", 0, 2);

CSemaphore completion("racers done", 0, 1);


int Supervisor::main(void) {
	int total_pitstops = 1;
	while (completion.Read()!=1) { //todo, use csemaphore instead

		PEL.Signal();
		pitFull.Wait();
		PEL.Wait();

		Refuel.Signal();
		Visor1.Signal();
		Debris1.Signal();
		jackerfront.Signal();
		jackerback.Signal();

		jackerfront.Wait();
		jackerback.Wait();
		Debris1.Wait();
		Visor1.Wait();
		Refuel.Wait();

		PEXL.Signal();
		pitEmpty.Wait();

		console.Wait();
		for (int j = 0; j < 50; j++) {
			MOVE_CURSOR(60, j);
			cout << R"(                                                         )" << endl;
		}
		console.Signal();
		total_pitstops++;
	}
	return 0;
};

int Jacking::main() {
	int idx = 0;
	string jacker_pos = "Front Jacking Tech";
	if (pos == 1) {
		jacker_pos = "Rear Jacking Tech";
		idx = 2;
	}
	while (completion.Read() != 1) {
		if (!pos) {
			jackerfront.Wait();
		}
		else {
			jackerback.Wait();
		}
		if (completion.Read() == 1) break;
		console.Wait();
		MOVE_CURSOR(60, 7+idx);
		cout << jacker_pos << " raised car " << endl;
		console.Signal();
		Sleep(500 + rand() % 200);
		if (completion.Read() == 1) break;

		if (!pos) {
			FrontWheelNut1.Signal();
			FrontWheelNut2.Signal();
		}
		else {
			RearWheelNut1.Signal();
			RearWheelNut2.Signal();
		}

		if (!pos) {
			FrontWheelNut1.Wait();
			FrontWheelNut2.Wait();
		}
		else {
			RearWheelNut1.Wait();
			RearWheelNut2.Wait();
		}
		
		console.Wait();
		MOVE_CURSOR(60, 8+idx);
		cout << jacker_pos << " lowered car " << endl;
		console.Signal();
		if (!pos) {
			jackerfront.Signal();
		}
		else {
			jackerback.Signal();
		}
	}
	return 0;
};

int Refuelling::main() {
	while (completion.Read() != 1) {
		Refuel.Wait();
		if (completion.Read() == 1) break;

		console.Wait();
		MOVE_CURSOR(60, 0);
		cout << "Refuel started " << endl;
		console.Signal();
		Sleep(2000+rand()%200);

		if (completion.Read() == 1) break;

		console.Wait();
		MOVE_CURSOR(60, 1);
		cout << "Refuel completed " << endl;
		console.Signal();
		Refuel.Signal();
	}
	return 0;
};

int WheelNut::main() {
	while (completion.Read() != 1) {
		switch(wheelnum) {
		case 1: FrontWheelNut1.Wait(); break;
		case 2: FrontWheelNut2.Wait(); break;
		case 3: RearWheelNut1.Wait(); break;
		case 4: RearWheelNut2.Wait(); break;
		}
		if (completion.Read() == 1) break;

		console.Wait();
		MOVE_CURSOR(60, 14+wheelnum);
		cout << "Wheel nut removed "<< wheelnum << endl;
		console.Signal();
		Sleep(500 + rand() % 200);
		if (completion.Read() == 1) break;

		switch (wheelnum) {
		case 1: FrontWheelRemove1.Signal(); break;
		case 2: FrontWheelRemove2.Signal(); break;
		case 3: RearWheelRemove1.Signal(); break;
		case 4: RearWheelRemove2.Signal(); break;
		}

		switch (wheelnum) {
		case 1: FrontWheelRemove1.Wait(); break;
		case 2: FrontWheelRemove2.Wait(); break;
		case 3: RearWheelRemove1.Wait(); break;
		case 4: RearWheelRemove2.Wait(); break;
		}		
		console.Wait();
		MOVE_CURSOR(60, 36+wheelnum);
		cout << "Wheel nut added back "<<wheelnum << endl;
		console.Signal();
		switch (wheelnum) {
		case 1: FrontWheelNut1.Signal(); break;
		case 2: FrontWheelNut2.Signal(); break;
		case 3: RearWheelNut1.Signal(); break;
		case 4: RearWheelNut2.Signal(); break;
		}
	}
	return 0;
};

int WheelRemoval::main() {
	while (completion.Read() != 1) {
		switch (wheelnum) {
		case 1: FrontWheelRemove1.Wait(); break;
		case 2: FrontWheelRemove2.Wait(); break;
		case 3: RearWheelRemove1.Wait(); break;
		case 4: RearWheelRemove2.Wait(); break;
		}
		if (completion.Read() == 1) break;

		console.Wait();
		MOVE_CURSOR(60, 19+wheelnum);
		cout << "Wheel removed started "<<wheelnum << endl;
		console.Signal();
		Sleep(500 + rand() % 200);
		if (completion.Read() == 1) break;

		console.Wait();
		MOVE_CURSOR(60, 25+wheelnum);
		cout << "Wheel removed "<<wheelnum << endl;
		console.Signal();
		switch (wheelnum) {
		case 1: FrontWheelReplace1.Signal(); break;
		case 2: FrontWheelReplace2.Signal(); break;
		case 3: RearWheelReplace1.Signal(); break;
		case 4: RearWheelReplace2.Signal(); break;
		}
		switch (wheelnum) {
		case 1: FrontWheelReplace1.Wait(); break;
		case 2: FrontWheelReplace2.Wait(); break;
		case 3: RearWheelReplace1.Wait(); break;
		case 4: RearWheelReplace2.Wait(); break;
		}
		switch (wheelnum) {
		case 1: FrontWheelRemove1.Signal(); break;
		case 2: FrontWheelRemove2.Signal(); break;
		case 3: RearWheelRemove1.Signal(); break;
		case 4: RearWheelRemove2.Signal(); break;
		}
	}
	return 0;
};

int WheelRefitting::main() {
	while (completion.Read() != 1) {
		switch (wheelnum) {
		case 1: FrontWheelReplace1.Wait(); break;
		case 2: FrontWheelReplace2.Wait(); break;
		case 3: RearWheelReplace1.Wait(); break;
		case 4: RearWheelReplace2.Wait(); break;
		}
		if (completion.Read() == 1) break;

		console.Wait();
		MOVE_CURSOR(60, 30+wheelnum);
		cout << "Wheel Replace started "<<wheelnum << endl;
		console.Signal();
		Sleep(500 + rand() % 200);
		if (completion.Read() == 1) break;

		console.Wait();
		MOVE_CURSOR(60, 36 +wheelnum);
		cout << "Wheel replace completed "<<wheelnum << endl;
		console.Signal();
		switch (wheelnum) {
		case 1: FrontWheelReplace1.Signal(); break;
		case 2: FrontWheelReplace2.Signal(); break;
		case 3: RearWheelReplace1.Signal(); break;
		case 4: RearWheelReplace2.Signal(); break;
		}
	}
	return 0;
};

int Visor::main() {
	while (completion.Read() != 1) {
		Visor1.Wait();
		if (completion.Read() == 1) break;

		console.Wait();
		MOVE_CURSOR(60, 3);
		cout << "Visor cleaning started " << endl;
		console.Signal();
		Sleep(2000 + rand() % 200);
		if (completion.Read() == 1) break;

		console.Wait();
		MOVE_CURSOR(60, 4);
		cout << "Visor cleaning completed " << endl;
		console.Signal();
		Visor1.Signal();
	}
	return 0;
}

int Debris::main() {
	while (completion.Read() != 1) {
		Debris1.Wait();
		if (completion.Read() == 1) break;

		console.Wait();
		MOVE_CURSOR(60, 5);
		cout << "Debris cleaning started " << endl;
		console.Signal();
		Sleep(2000 + rand() % 200);
		if (completion.Read() == 1) break;

		console.Wait();
		MOVE_CURSOR(60, 6);
		cout << "Debris cleaning completed " << endl;
		console.Signal();
		Debris1.Signal();
	}
	return 0;
};