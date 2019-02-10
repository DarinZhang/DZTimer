#include "Timer.h"

int main(int argc,TCHAR *argv[])
{
	//////////////////////////////////////////////////////////////////////////
	//instance 1
	//use class CEventTimer
	printf("Please enter any character to start event timer![Timer Period:%d]\n", 35);
	printf("and enter again to kill the event timer!\n");
	getchar();
	int nUserData = 123;
	int nTmInterval = 35;
	int nResolution = 1;
	CEventTimer cEventTimer(35, 1, TimeEvent, nUserData);
	cEventTimer.StartEventTimer();	
	getchar();
	cEventTimer.KillEventTimer();

	//////////////////////////////////////////////////////////////////////////
	//instance 2
	//use class CQueueTimer without CTimeQueue
	printf("\n\n\nPlease enter any character to start queue timer without queue![Timer Period:%d]\n", 50);
	printf("and enter again to kill the queue timer!\n");
	getchar();
	nUserData = 321;
	nTmInterval = 50;
	CQueueTimer cQueTimer(&nUserData, nTmInterval, nTmInterval, TimerRoutine, nullptr);
	cQueTimer.StartQueueTimer();
	getchar();
	cQueTimer.KillQueueTimer();
	
	//////////////////////////////////////////////////////////////////////////
	//instance 3
	//use class CQueueTimer with CTimeQueue
	printf("\n\n\nPlease enter any character to start queue timer with queue![Timer Period:%d]\n", 50);
	printf("and enter again to kill the timer queue!\n");
	getchar();
	CTimeQueue cTimerQueue;
	int nUserDataArray[3] = {0};
	nUserDataArray[0] = 100;
	nUserDataArray[1] = 101;
	nUserDataArray[2] = 102;
	CQueueTimer *pQueTimerOne = new CQueueTimer(&nUserDataArray[0], nTmInterval, nTmInterval, TimerRoutine, cTimerQueue.GetTimeQueue());
	pQueTimerOne->StartQueueTimer();
	cTimerQueue.AddTimer(pQueTimerOne);
	CQueueTimer *pQueTimerTwo = new CQueueTimer(&nUserDataArray[1], nTmInterval, nTmInterval, TimerRoutine, cTimerQueue.GetTimeQueue());
	pQueTimerTwo->StartQueueTimer();
	cTimerQueue.AddTimer(pQueTimerTwo);
	CQueueTimer *pQueTimerThree = new CQueueTimer(&nUserDataArray[2], nTmInterval, nTmInterval, TimerRoutine, cTimerQueue.GetTimeQueue());
	pQueTimerThree->StartQueueTimer();
	cTimerQueue.AddTimer(pQueTimerThree);
	getchar();
	cTimerQueue.DestroyQueue();
	getchar();
	return 0;
}