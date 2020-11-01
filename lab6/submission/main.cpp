#include "car.h"
#include "technicians.h"
#include "rt.h"
#include <thread>

void create_racecars(car**, int, int);
void setup();
void podium(car**);
void pits();
void lights();
void clear_traffic();

int main(void) {
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

	//car* cars[10];
	const int laps = 69;
	const int pitstop1 = 15;
	const int pitstop2 = 45;
	car* cars[10];
	lights();
	create_racecars(cars, pitstop1, pitstop2);
	setup();
	thread t1(pits);
	thread t2(clear_traffic);

	Supervisor* S1 = new Supervisor();
	Jacking* JF = new Jacking(0); //front jack
	Jacking* JR = new Jacking(1); //rear jack
	Refuelling* RF = new Refuelling();
	WheelNut* WNFL = new WheelNut(1);
	WheelNut* WNFR = new WheelNut(2);
	WheelNut* WNRL = new WheelNut(3);
	WheelNut* WNRR = new WheelNut(4);
	WheelRemoval* WREFL = new WheelRemoval(1);
	WheelRemoval* WREFR = new WheelRemoval(2);
	WheelRemoval* WRERL = new WheelRemoval(3);
	WheelRemoval* WRERR = new WheelRemoval(4);
	WheelRefitting* WRAFL = new WheelRefitting(1);
	WheelRefitting* WRAFR = new WheelRefitting(2);
	WheelRefitting* WRARL = new WheelRefitting(3);
	WheelRefitting* WRARR = new WheelRefitting(4);
	Visor* VS = new Visor();
	Debris* DB = new Debris();

	for (int i = 0; i < 10; i++) {
		cars[i]->Resume();
	}

	S1->Resume();
	JF->Resume();
	JR->Resume();
	RF->Resume();
	WNFL->Resume();
	WNFR->Resume();
	WNRL->Resume();
	WNRR->Resume();
	WREFL->Resume();
	WREFR->Resume();
	WRERL->Resume();
	WRERR->Resume();
	WRAFL->Resume();
	WRAFR->Resume();
	WRARL->Resume();
	WRARR->Resume();
	VS->Resume();
	DB->Resume();

	Sleep(1000);
	for (int i = 0; i < 10; i++) {
		cars[i]->WaitForThread();
	}
	completion.Signal();

	PEL.Signal();
	PEXL.Signal();
	pitEmpty.Signal();
	pitFull.Signal();

	jackerfront.Signal();
	jackerback.Signal();

	Refuel.Signal();

	Visor1.Signal();
	Debris1.Signal();

	FrontWheelNut1.Signal();
	FrontWheelNut2.Signal();
	RearWheelNut1.Signal();
	RearWheelNut2.Signal();

	FrontWheelRemove1.Signal();
	FrontWheelRemove2.Signal();
	RearWheelRemove1.Signal();
	RearWheelRemove2.Signal();

	FrontWheelReplace1.Signal();
	FrontWheelReplace2.Signal();
	RearWheelReplace1.Signal();
	RearWheelReplace2.Signal();


	S1->WaitForThread();
	JF->WaitForThread();
	JR->WaitForThread();
	RF->WaitForThread();
	WNFL->WaitForThread();
	WNFR->WaitForThread();
	WNRL->WaitForThread();
	WNRR->WaitForThread();
	WREFL->WaitForThread();
	WREFR->WaitForThread();
	WRERL->WaitForThread();
	WRERR->WaitForThread();
	WRAFL->WaitForThread();
	WRAFR->WaitForThread();
	WRARL->WaitForThread();
	WRARR->WaitForThread();
	VS->WaitForThread();
	DB->WaitForThread();
	t1.join();
	t2.join();
	console.Wait();
	podium(cars);
	console.Signal();
	for (int i = 0; i < 10; i++) {
		delete cars[i];
	}
	getchar();
	return 0;
}


void setup() {
	MOVE_CURSOR(0, 0);
	cout << "Car#" << endl;
	MOVE_CURSOR(5, 0);
	cout << "Driver" << endl;
	MOVE_CURSOR(25, 0);
	cout << "Lap#" << endl;
	MOVE_CURSOR(30, 0);
	cout << "Time" << endl;
	MOVE_CURSOR(40, 0);
	cout << "Status" << endl;
}

void pits() {
	CSemaphore completion("racers done", 0, 1);
	CMutex console("F1");
	bool asdf = false;
	
	while (completion.Read() != 1) {
		console.Wait();
		MOVE_CURSOR(0, 12);
		if (!asdf)
			cout << R"(
             vroooom!                              
     .-----------,-.-----.                        
     | :_M_a_r_l//(_)\r_o_|:                     
  ___||====== =// ,--.\===.|  ___                  
.'.""'\\____.'/ | (__)\__|\.'.""'.               
| |"""||._       '---'__   `-|"""|               
| |"""||. '-.___  ` -'--'     `-.| ___         
| |"""|| '-.'.""'.----._     .---:'.""'.            
`.'_".'|   | |"""|_____ `. /\ \___||_""|           
        '-.| |""_/_____\  \ \\ \_____\_|            
           | |"|____    ', '.__/   ____|          
           `.'__.'  `'---'-'---'-'.'__.'                 )" << endl;
		else
			cout << R"(
     .-----------,-.-----.                  
     | :_M_a_r_l//(_)\r_o_|:                   
  ___||====== =// ,--.\===.|  ___                
.'.""'\\____.'/ | (__)\__|\.'.""'.              
| |"""||._       '---'__   `-|"""|              
| |"""||. '-.___  ` -'--'     `-.| ___             
| |"""|| '-.'.""'.----._     .---:'.""'.           
`.'_".'|   | |"""|_____ `. /\ \___||_""|           
        '-.| |""_/_____\  \ \\ \_____\_|          
           | |"|____    ', '.__/   ____|          
           `.'__.'  `'---'-'---'-'.'__.'          
                   vroooom!						)" << endl;

		console.Signal();
		Sleep(2000);
		asdf = !asdf;
	}
	return;
}

void podium(car* cars[]) {
	car* pod[3] = { cars[0],cars[1] ,cars[2] };
	int top[3] = { 0,0,0 };
	for (int i = 0; i < 10; i++) {
		if (cars[i]->racet() <= top[0]) {
			pod[2] = pod[1];
			pod[1] = pod[0];
			pod[0] = cars[i];
		}
		else if (cars[i]->racet() >= top[0] && cars[i]->racet() <= top[1]) {
			pod[2] = pod[1];
			pod[1] = cars[i];
		}
		else if (cars[i]->racet() >= top[1] && cars[i]->racet() <= top[2]) {
			pod[2] = cars[i];
		}
		top[0] = pod[0]->racet();
		top[1] = pod[1]->racet();
		top[2] = pod[2]->racet();
	}
	MOVE_CURSOR(0, 34);
	cout << R"(------------------ Podium of the Grand Prix -----------------)" << endl;
	MOVE_CURSOR(0, 35);
	cout << "------------------ #1 " << pod[0]->desc() << "   ----------------" << endl;
	MOVE_CURSOR(0, 36);
	cout << "------------------ #2 " << pod[1]->desc() << "    ----------------" << endl;
	MOVE_CURSOR(0, 37);
	cout << "------------------ #3 " << pod[2]->desc() << "      ----------------" << endl;
	MOVE_CURSOR(0, 34);
	MOVE_CURSOR(60, 11);
	cout << R"(                           (
*                           )   *
              )     *      (
    )        (                   (
   (          )     (             )
    )    *           )        )  (
   (                (        (      *
    )          H     )        )                     
              [ ]            (                      
       (  *   |-|       *     )    (                  
 *      )     |_|        .          )                  
       (      | |    .                              
 )           /   \     .    ' .        *
(           |_____|  '  .    .  
 )          | ___ |  \~~~/  ' .   (
        *   | \ / |   \_/  \~~~/   )
            | _Y_ |    |    \_/   (
*           |-----|  __|__   |      *
            `-----`        __|__)" << endl;
	cout << "Press Return to end the Race Weekend" << endl;
	for (int j = 0; j < 50; j++) {
		MOVE_CURSOR(60, j);
		cout << R"(                                                         )" << endl;
	}
}

void create_racecars(car* cars[], int pitstop1, int pitstop2) {
	cars[0] = new car(0, 44, "Lewis Hamilton", pitstop1 + (rand() %10), pitstop2 - (rand() % 10));
	cars[1] = new car(1, 33, "Max Verstappen", pitstop1 + (rand() % 10), pitstop2 - (rand() % 10));
	cars[2] = new car(2, 16, "Charles Leclerc", pitstop1 + (rand() % 10), pitstop2 - (rand() % 10));
	cars[3] = new car(3, 5, "Sebastian Vettel", pitstop1 + (rand() % 10), pitstop2 - (rand() % 10));
	cars[4] = new car(4, 4, "Lando Norris", pitstop1 + (rand() % 10), pitstop2 - (rand() % 10));
	cars[5] = new car(5, 55, "Carlos Sainz", pitstop1 + (rand() % 10), pitstop2 - (rand() % 10));
	cars[6] = new car(6, 3, "Daniel Ricciardo", pitstop1 + (rand() % 10), pitstop2 - (rand() % 10));
	cars[7] = new car(7, 10, "Pierre Gasly", pitstop1 + (rand() % 10), pitstop2 - (rand() % 10));
	cars[8] = new car(8, 7, "Kimi Raikkonnen", pitstop1 + (rand() % 10), pitstop2 - (rand() % 10));
	cars[9] = new car(9, 11, "Sergio Perez", pitstop1 + (rand() %10), pitstop2 - (rand() % 10));
	return;
}

void lights() {

	MOVE_CURSOR(100, 32);

	cout << R"(
            RACE STARTING, GET READY!!!
                      _[]_
                     [____]
                 .----'  '----.
             .===|    .==.    |===.
             \   |   /####\   |   /
             /   |   \####/   |   \
             '===|    `""`    |==='
             .===|    .==.    |===.
             \   |   /    \   |   /
             /   |   \    /   |   \
             '===|    `""`    |==='
             .===|    .==.    |===.
             \   |   /    \   |   /
             /   |   \    /   |   \
             '===|    `""`    |==='
                 '--.______.--'
)" << endl;
	Sleep(15000);
	MOVE_CURSOR(100, 32);

	cout << R"(
              ON YOUR MARKS!!!!!!!!!
                      _[]_
                     [____]
                 .----'  '----.
             .===|    .==.    |===.
             \   |   /####\   |   /
             /   |   \####/   |   \
             '===|    `""`    |==='
             .===|    .==.    |===.
             \   |   /    \   |   /
             /   |   \    /   |   \
             '===|    `""`    |==='
             .===|    .==.    |===.
             \   |   /    \   |   /
             /   |   \    /   |   \
             '===|    `""`    |==='
                 '--.______.--'
)" << endl;
	Sleep(3000);
	MOVE_CURSOR(100, 32);

	cout << R"(
                    GET SET ......
                      _[]_
                     [____]
                 .----'  '----.
             .===|    .==.    |===.
             \   |   /####\   |   /
             /   |   \####/   |   \
             '===|    `""`    |==='
             .===|    .==.    |===.
             \   |   /    \   |   /
             /   |   \    /   |   \
             '===|    `""`    |==='
             .===|    .==.    |===.
             \   |   /    \   |   /
             /   |   \    /   |   \
             '===|    `""`    |==='
                 '--.______.--'
)" << endl;
	Sleep(3000);
	MOVE_CURSOR(100, 32);

	cout << R"(
				   GO!!!!!!!!
                      _[]_
                     [____]
                 .----'  '----.
             .===|    .==.    |===.
             \   |   /    \   |   /
             /   |   \    /   |   \
             '===|    `""`    |==='
             .===|    .==.    |===.
             \   |   /    \   |   /
             /   |   \    /   |   \
             '===|    `""`    |==='
             .===|    .==.    |===.
             \   |   /####\   |   /
             /   |   \####/   |   \
             '===|    `""`    |==='
                 '--.______.--'
)" << endl;

}

void clear_traffic() {
	CMutex console("F1");
	Sleep(15000);
	MOVE_CURSOR(100, 32);
	console.Wait();
	cout << R"(                                                                                  
                                                                                                                           
                                                                                                                           
                                                                                                                           
                                                                                  
                                                                                                                           
                                                                                  
                                                                                  
                                                                                  
                                                                                                                            
                                                                                                                           
                                                                                                                           
                                                                                                                           
                                                                                                                           
                                                                                                                           
                                                                                  
                                                                                  
                                                                                                                           
)" << endl;
	console.Signal();

}