#ifndef __technicians__
#define __technicians__

#include "rt.h"

class Supervisor : public ActiveClass {
	int main(void);
public:
	Supervisor(void) {};
	~Supervisor() {};
};

//2 Jacking techs, 1 front, 1 back
class Jacking : public ActiveClass {
	int total_pitstops = 1;
	int pos;
	int main(void);
public:
	Jacking(int num) { pos = num; };
	~Jacking() {};
};

//1 refuelling tech
class Refuelling : public ActiveClass {
	int total_pitstops = 1;
	int main(void);
public:
	Refuelling(void) {};
	~Refuelling() {};
};

//4 wheel nut techs, 1 for each wheel
class WheelNut : public ActiveClass {
	int wheelnum;
	int main(void);
public:
	WheelNut(int num) { wheelnum = num; };
	~WheelNut() {};
};

//4 wheel removal techs, 1 for each wheel
class WheelRemoval : public ActiveClass {
	int wheelnum;
	int main(void);
public:
	WheelRemoval(int num) { wheelnum = num; };
	~WheelRemoval() {};
};

//4 wheel refitting techs, 1 for each wheel
class WheelRefitting : public ActiveClass {
	int wheelnum;
	int main(void);
public:
	WheelRefitting(int num) { wheelnum = num; };
	~WheelRefitting() {};
};

//1 visor cleaner
class Visor : public ActiveClass {
	int main(void);
public:
	Visor(void) {};
	~Visor() {};
};

//1 Debris Cleaner
class Debris : public ActiveClass {
	int main(void);
public:
	Debris(void) {};
	~Debris() {};
};

#endif // __technicians__