//As per Professor Davies' answer in @53, cut and pasted from his rt.cpp library

#include "cprocess.h"



CProcess::CProcess(
	const string &Name,		// path/name of executable program (.exe)
	int Priority,			// Priority of the process
	BOOL bUseNewWindow,		// use OWN_WINDOW to make new process run in its own window
							// use PARENT_WINDOW to make it share its parent window
	BOOL bCreateSuspended,	// use SUSPENDED to make new child process's main thread suspended when process is created
							// use ACTIVE to make new child processes main thread active when process iscreated

	const string &ChildProcessArgString)

	: ProcessName(Name)
{
	// Check priority level is valid



	PERR(((Priority == HIGH_PRIORITY_CLASS) ||
		(Priority == IDLE_PRIORITY_CLASS) ||
		(Priority == NORMAL_PRIORITY_CLASS) ||
		(Priority == REALTIME_PRIORITY_CLASS)),
		string("Illegal 2nd Argument (Process Priority) for Process: ") + Name);


	PERR((bUseNewWindow == OWN_WINDOW || bUseNewWindow == PARENT_WINDOW),
		string("Use OWN_WINDOW or PARENT_WINDOW as 3rd argument for Process: ") + Name);
	PERR((bCreateSuspended == SUSPENDED || bCreateSuspended == ACTIVE),
		string("Use SUSPENDED or ACTIVE as 4th Argument for Process: ") + Name);


	STARTUPINFO	StartupInfo = {
		sizeof(STARTUPINFO) ,
		NULL ,			// reserved
		NULL ,			// ignored in console applications
		(char *)(Name.c_str()) ,	// displayed in title bar for console applications
		0,0,			// dwx, dwy, offset of top left of new window relative to top left of screen in pixel
						// flags below must specify STARTF_USEPOSITION. Ignored for console apps'
						0,0,			// dwxsize, dwysize: Width and height of the window if new window specified
										// must use flags STARTF_USESIZE. Ignored for console apps'
										0,0,			// size of console in characters, only if STARTF_USECOUNTCHARS flag specified, 
														// Ignored for console apps
														0,				// Colour control, for background and text. Ignored for console apps
														0,				// Flags. Ignored for console applications
														0,				// ignored unless showwindow flag set
														0 ,
														NULL,
														0,0,0			// stdin, stdout and stderr handles (inherited from parent)
	};

	UINT flags = Priority; // Priority,

	if (bUseNewWindow == OWN_WINDOW)		// if caller has specified that child should have its won window
		flags |= CREATE_NEW_CONSOLE;

	if (bCreateSuspended == SUSPENDED)	// if caller has specified that child process should be immediately suspended
		flags |= CREATE_SUSPENDED;

	BOOL Success = CreateProcess(NULL,	// application name
		(char *)(Name.c_str()),			// Command line to the process if you want to pass one to main() in the process
		NULL,			// process attributes
		NULL,			// thread attributes
		TRUE,			// inherits handles of parent
		flags,			// Priority and Window control flags,
		NULL,			// use environent of parent
		NULL,			// use same drive and directory as parent
		&StartupInfo,	// controls appearance of process (see above)
		&pInfo			// Stored process handle and ID into this object
	);
	PERR(Success == TRUE, string("CProcess Call Unable to Create New Process: ") + Name);	// check for error and print message if appropriate
}



//##ModelId=3DE6123A009C
BOOL CProcess::SetPriority(int Priority) const
{
	BOOL Success;

	// Check priority level 

	PERR(((Priority == HIGH_PRIORITY_CLASS) || (Priority == IDLE_PRIORITY_CLASS) ||
		(Priority == NORMAL_PRIORITY_CLASS) || (Priority == REALTIME_PRIORITY_CLASS)),
		string("Illegal Priority value in call to SetPiority()"));

	Success = SetPriorityClass(GetProcessHandle(), Priority);
	PERR(Success == TRUE, string("Unable to Set Thread Priority of Process: ") + ProcessName);	// check for error and print error message as appropriate

	return Success;
}

//
//	These two functions can be called to suspend and resume a processes activity. 
//	Actually, it suspend/resumes the process primary thread and not necessarily any
//	other child threads it may have. Once suspended	the thread will no longer 
//	run and consume CPU time. Note that if you suspend a process more than once, 
//	then it will require the appropriate number	of resumes to allow it to continue
//
//
//	Returns TRUE on Success, FALSE on Failure
//

//##ModelId=3DE6123A007F
BOOL CProcess::Suspend() const
{
	UINT	Result = SuspendThread(GetThreadHandle());
	PERR(Result != 0xffffffff, string("Cannot Suspend Process: ") + ProcessName);

	if (Result != 0xffffffff)	// if no error
		return TRUE;
	else
		return FALSE;
}

//##ModelId=3DE6123A0088
BOOL CProcess::Resume() const
{
	UINT	Result = ResumeThread(GetThreadHandle());
	PERR(Result != 0xffffffff, string("Cannot Resume Process: ") + ProcessName);

	if (Result != 0xffffffff)	// if no error
		return TRUE;
	else
		return FALSE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	This function waits for a child process to terminate provide it has been
//	created as a CProcess Object. Or returns if the specified time elapses before the process has terminates
//
//	Note that if the child process has already terminated, when the call to wait for
//	it is made, then this is deemed a success, NOT a failure and the function returns immediately without waiting
//
//	This function returns WAIT_FAILED if there was an error, WAIT_TIMEOUT if the wait operation timed out
//	of WAIT_OBJECT_0 if the operation did in fact wait and then returned
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//##ModelId=3DE6123A0092
BOOL	CProcess::WaitForProcess(DWORD Time) const
{
	UINT Result = WaitForSingleObject(GetProcessHandle(), Time);
	PERR(Result != WAIT_FAILED, string("Cannot Wait for Child Process: ") + ProcessName + string(" to Terminate.\n It might already be dead"));	// check for error and print message if appropriate== WAIT_OBJECT_0 ) 

	return Result;
}


//	The following function sends a message to a process' main thread
//	If the thread is currently suspended, waiting for a message, then posting it a message
//	will wake it up and allow it to continue
//
//	The Message must be in the range 0 - 32000
//	In order to receive messages, the thread receiving the message must have created a message queue.
//	(See CMessageQueue later)
//

//##ModelId=3DE6123A00AF
BOOL CProcess::Post(UINT Message) const	// message value and ID of thread
{
	BOOL Result;

	if (Message > 32000) {
		PERR(Message <= 32000, string("Could not Signal Process:") + ProcessName + string("\nReason: Message Value > 32000"));	// check for error and print error message as appropriate
		return FALSE;
	}
	else {
		Result = PostThreadMessage(GetThreadId(), WM_USER + Message, 0, 0L);
		PERR(Result != 0, string("Could not Signal Process:") + ProcessName + string("\nProcess May be Dead"));	// check for error and print error message as appropriate
		return Result;
	}
}

//
//	This calls standard exit() function to terminate the process
//

//##ModelId=3DE6123A00BA
void CProcess::Exit(UINT ExitCode) const
{
	exit(ExitCode);
}


//
//	This function suspends the current thread until the specified time has elapsed
//	This allows other processes with the same priority to run. Co-operative processing
//	can be implemented with the help of this function,as processes voluntarily relinquish
//	control of the CPU. If the delay is 0, the processes simply gives up the remainder of
//	its CPU time. If the value is 'INFINITE', then the process waits forever. 
//	If the delay is somewhere inbetween, the process is suspended for the duration specified
//	sending it a message will not wake it up prematurely.
//

void	SLEEP(UINT	Time)
{
	Sleep(Time);
}

//
//	This function tests the keyboard to see if a key has been pressed. If so, the value TRUE is
//	returned and the thread can read the character without getting suspended using a function
//	such as _getch(), _getche() etc.
//

BOOL	TEST_FOR_KEYBOARD()
{
	return _kbhit();
}


//
//	These functions returns handles to a console standard input/output and error device
//	i.e. keyboard, screen and screen respectively. NULL is returned on error
//	For more example of console functions read the Vis C++ Help/Win32 functions by category/console functions
//

HANDLE	GET_STDIN()
{
	return GetStdHandle(STD_INPUT_HANDLE);
}

HANDLE	GET_STDOUT()
{
	return GetStdHandle(STD_OUTPUT_HANDLE);
}

HANDLE	GET_STDERR()
{
	return GetStdHandle(STD_ERROR_HANDLE);
}

//
//	This function pauses the thread/process until user input is entered at the keyboard
//
//	This function returns WAIT_FAILED if there was an error, WAIT_TIMEOUT if the wait operation timed out
//	of WAIT_OBJECT_0 if the operation did in fact wait and then returned
//

UINT WAIT_FOR_CONSOLE_INPUT(HANDLE hEvent, DWORD Time)
{
	UINT	Status = WaitForSingleObject(hEvent, Time);
	PERR(Status != WAIT_FAILED, string("Cannot Wait for Console Input"));	// check for error and print message if appropriate
	return Status;
}

//	moves the cursor to the x,y coord on the screen. [0,0] is top left
//	all calls to printf cause output to occur at the current cursor position
//	obviously, the cursor moves with text output operations

void MOVE_CURSOR(int x, int y)
{
	COORD	c = { (short)x, (short)y };
	SetConsoleCursorPosition(GET_STDOUT(), c);
}

//
//	These two function turns off/on the cursor so that it is not visible
//	but it still operates and output text still occurs at the current curso
//	position
//

void CURSOR_OFF()
{
	CONSOLE_CURSOR_INFO	cci = { 1, FALSE };
	SetConsoleCursorInfo(GET_STDOUT(), &cci);
}

void CURSOR_ON()
{
	CONSOLE_CURSOR_INFO	cci = { 1, TRUE };
	SetConsoleCursorInfo(GET_STDOUT(), &cci);
}

//
//	These two functions turns on/off reverse video, so that text comes black on white background
//	For more details set the SetConsoleTextAttribute() function in on-line
//	help
//

void REVERSE_ON()
{
	SetConsoleTextAttribute(GET_STDOUT(),
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
}

void REVERSE_OFF()
{
	SetConsoleTextAttribute(GET_STDOUT(),
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void CLEAR_SCREEN()
{
	for (int i = 0; i < 50; i++)
		putchar('\n');
}

/*Contains a function to change the text colour.

To Use:

This function takes 2 arguments, foreground and background.
foreground and background select one of 15 colours numbered as follows:

0 - Black
1 - Dark Blue
2 - Dark Green
3 - Dark Cyan
4 - Dark Red
5 - Dark Magenta
6 - Dark Yellow
7 - Grey
8 - Black (again)
9 - Blue
10 - Green
11 - Cyan
12 - Red
13 - Magenta
14 - Yellow
15 - White

Note... background and foreground cannot be the same value, and an
error (-1) will be returned.

If colours are valid, and operation was successful, 0 will be returned.

Use TEXT_COLOUR with no arguements to return values to default.

A foreground colour only can be specified, eg TEXT_COLOUR(4) will make text dark red .*/

int TEXT_COLOUR(unsigned char foreground, unsigned char background)
{
	if ((foreground>15) || (foreground<0) || (background>15) || (background<0) || (background == foreground))
	{
		return -1;
	}
	int colour = 0;
	background = background << 4;
	colour = colour | background | foreground;
	SetConsoleTextAttribute(GET_STDOUT(), colour);
	return 0;
}


void flush(istream &is)		// can be used to flush an input stream, useful for removing operator entered rubbish
{
	is.clear();
	streambuf  *ptr = is.rdbuf();		// get pointer to stream buffer
	int avail = (int)(ptr->in_avail());			// get number of chars waiting to be read
	is.ignore(avail);						// ignore this many characters
	is.clear();
}

void PERR(bool bSuccess, string ErrorMessageString)
{
	UINT LastError = GetLastError();

	if (!(bSuccess)) {
		char buff[512];
		Beep(500, 100);
		MOVE_CURSOR(0, 0);
		REVERSE_ON();
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, LastError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buff, 1024, NULL);
		printf(" Error %d in Process %s: line %d:\n", LastError, __FILE__, __LINE__);
		printf(" Translation: %s Error: %s", buff, ErrorMessageString.c_str());
		REVERSE_OFF();
		printf("\n\nPress Return to Continue...");
		_getch();
	}
}