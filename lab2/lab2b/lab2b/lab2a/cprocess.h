//As per Professor Davies' answer in @53, cut and pasted from his rt.h library

#pragma once

#ifndef	__RT__
#define __RT__

#include <process.h>	// for spawnl and createthread
#include <windows.h>	// for perror and sleep
#include <stdio.h>		// for printf
#include <limits.h>		// for UINT_MAX
#include <conio.h>		// for _kbhit(), getch() and getche()
#include <iostream>
#include <string>

using namespace std;

#define SUSPENDED			101000		// for threads
#define ACTIVE				101001		// for thread
#define OWN_WINDOW			101002		// for FORK_PROCESS
#define PARENT_WINDOW		101003		// ditto
#define MAXMESSAGEVALUE		32000		// maximum value of a user generated message

//	Miscellaneous functions
void	SLEEP(UINT	Time);			// suspend current thread for 'Time' mSec
BOOL	TEST_FOR_KEYBOARD();		// tests a keyboard for a key press returns true if key pressed
HANDLE	GET_STDIN();				// get handle to standard input device (keyboard)
HANDLE	GET_STDOUT();				// ditto output device
HANDLE	GET_STDERR();				// ditto erro device
UINT	WAIT_FOR_CONSOLE_INPUT(HANDLE hEvent, DWORD Time = INFINITE);	//wait for console input to happen


void	MOVE_CURSOR(int x, int y);	// move console cursor to x,y coord
void	CURSOR_ON();				// turn flashing cursor on (the default)
void	CURSOR_OFF();				// turn flashing cursor off
void	REVERSE_ON();				// turn on inverse video
void	REVERSE_OFF();				// turn off inverse video
void	CLEAR_SCREEN();			// clears the screen

void PERR(bool bSuccess, string ErrorMessageString);


UINT	WAIT_FOR_MULTIPLE_OBJECTS(UINT nCount,             // number of handles in the handle array
	CONST HANDLE *lpHandles, // pointer to the object-handle array
	DWORD Time = INFINITE
);


class CProcess {					// see Process related functions in rt.cpp for more details
private:
	PROCESS_INFORMATION pInfo;
	const string ProcessName;		// name of process

public:
	// constructor to create a child process, takes four 
	//arguments, note that the last 3 make use
	//	of default argument, that is, if you do not supply 
	//real arguments in the call, then the default values will
	//	be used for the ones you do NOT supply
	//	this means that when you create a new CProcess object, 
	//the only argument you HAVE to supply is the Name of the 
	//executable
	//	all other values can be supplied by default

	CProcess(const string &Name,							// pathlist/name of executable program (.exe) that will be the child process
		int Priority = NORMAL_PRIORITY_CLASS,		// Priority of the process
													//	The allowed priorities are:	
													//	HIGH_PRIORITY_CLASS			Use for important time critical tasks
													//	IDLE_PRIORITY_CLASS			Use for processes that run when all other processes are idle
													//	NORMAL_PRIORITY_CLASS		Normal processing shared with other normal processes
													//	REALTIME_PRIORITY_CLASS		highest priority blocks out all other processes including O.System so take care

		BOOL bUseNewWindow = PARENT_WINDOW,			// use OWN_WINDOW to make new process use its own windows
													// use PARENT_WINDOW to make it share its parent window

		BOOL bCreateSuspended = ACTIVE,				// use SUSPENDED to make new child processes main thread suspended when process is created
													// use ACTIVE to make new child processes main thread active when process iscreated
		const string &ChildProcessArgString = ""
	);

	virtual ~CProcess() {}				// destructor (does nothing by default)
	inline operator string	() const { return ProcessName; }
	inline string	GetName() const { return ProcessName; }

	inline HANDLE	GetProcessHandle() const { return pInfo.hProcess; }		// get the process's handle
	inline HANDLE	GetThreadHandle() const { return pInfo.hThread; }		// get the process's main thread handle
	inline UINT		GetProcessId() const { return pInfo.dwProcessId; }		// get the process's ID
	inline UINT		GetThreadId() const { return pInfo.dwThreadId; }		// get the main thread's ID

	inline operator PROCESS_INFORMATION() const { return pInfo; }	// get general info about process

	BOOL Suspend() const;										// called to suspend the child process i.e. pause it
	BOOL Resume() const;										// allows child to resume processing
	BOOL WaitForProcess(DWORD Time = INFINITE) const;			// allows parent to wait for child child process to finish
	BOOL SetPriority(int Priority) const;						// changes the priority of the child process (see allowed process values in constructor)
	BOOL Post(UINT Message) const;							// allows a signal/message to be sent to the process

private:
	void Exit(UINT ExitCode) const;		// called by process to terminate itself
	inline BOOL TerminateProcess(UINT ExitStatus = 0) { return ::TerminateProcess(GetProcessHandle(), ExitStatus); }
};


#endif