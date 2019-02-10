#ifndef MY_TIMER_H
#define MY_TIMER_H

#include <stdio.h>
#include <windows.h>
#include <vector>

class CEventTimer
{
public:
	CEventTimer(int dwTimeInterval, int dwResolution, LPTIMECALLBACK pFunCb, DWORD_PTR dwUserData);
	virtual ~CEventTimer();

	void StartEventTimer();
	void KillEventTimer();

private:
	unsigned int m_dwTimerId;
	unsigned int m_dwTimeInterval;
	int m_dwResolution;
	LPTIMECALLBACK m_pFucCb;
	DWORD_PTR m_pUserData;
};
void  CALLBACK TimeEvent(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);

class CQueueTimer
{
public:
	CQueueTimer(PVOID pParam, DWORD dwDurTime, DWORD dwPeriod, WAITORTIMERCALLBACK pCbFunc, HANDLE hTimerQueue = nullptr);
	virtual ~CQueueTimer();

	void StartQueueTimer();
	void KillQueueTimer();
	
private:
	HANDLE m_hTimer;
	HANDLE m_hTimerQueue;
	PVOID m_pParam;
	DWORD m_dwDurTime;
	DWORD m_dwPeriod;
	WAITORTIMERCALLBACK m_pCbFunc; 
};
VOID CALLBACK TimerRoutine( PVOID lpParameter, BOOLEAN TimerOrWaitFired );


class CTimeQueue
{
public:
	CTimeQueue();
	virtual ~CTimeQueue();
	
	void AddTimer(CQueueTimer* pQueueTimer);
	void DestroyQueue();
	
	HANDLE GetTimeQueue();
private:
	HANDLE m_hTimerQueue;
	std::vector<CQueueTimer *> m_vecTimer;
};

#endif //!MY_TIMER_H