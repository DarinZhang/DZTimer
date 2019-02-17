#include "Timer.h"

#pragma comment(lib, "winmm.lib")

static int s_nMarkEvent = 0;
static int s_nMarkQueTimer = 0;

//class EventTimer
CEventTimer::CEventTimer(int dwTimeInterval, int dwResolution, LPTIMECALLBACK pFunCb, DWORD_PTR dwUserData)
	: m_dwTimeInterval(dwTimeInterval), m_dwResolution(dwResolution), m_pFucCb(pFunCb), m_pUserData(dwUserData)
{
	m_dwTimerId = NULL;
}
CEventTimer::~CEventTimer()
{
	KillEventTimer();
}

void CEventTimer::StartEventTimer()
{
	if (NULL != m_dwTimerId)
	{
		//The timer has been started.
		return;
	}
	m_dwTimerId = timeSetEvent(m_dwTimeInterval, m_dwResolution, m_pFucCb, m_pUserData, TIME_PERIODIC);
	if (NULL == m_dwTimerId)
	{
		printf( "[%s-%d]Fail to start timer!\n", __FUNCTION__, __LINE__);
	}
}

void CEventTimer::KillEventTimer()
{
	if (NULL == m_dwTimerId)
	{
		return;
	}
	timeKillEvent(m_dwTimerId);
	m_dwTimerId = NULL;
}

void  CALLBACK TimeEvent(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{	
	SYSTEMTIME tTime;
	GetLocalTime(&tTime);
	printf("[%s-%d] TimerID:%d UserData:%d Mark:%d [Time:%d-%d-%d:%d]\n",__FUNCTION__, __LINE__, uTimerID, dwUser, s_nMarkEvent++,
		tTime.wHour, tTime.wMinute, tTime.wSecond, tTime.wMilliseconds);
	//to do
	//realize your callback
	// hahah branch tempconfig
}


//class CQueueTimer
CQueueTimer::CQueueTimer(PVOID pParam, DWORD dwDurTime, DWORD dwPeriod, WAITORTIMERCALLBACK pCbFunc, HANDLE hTimerQueue/* = nullptr*/)
	: m_hTimerQueue(hTimerQueue), m_pParam(pParam), m_dwDurTime(dwDurTime),m_dwPeriod(dwPeriod), m_pCbFunc(pCbFunc) 
{
	m_hTimer = nullptr;
}
CQueueTimer::~CQueueTimer()
{
	KillQueueTimer();
}

void CQueueTimer::StartQueueTimer()
{
	if (nullptr != m_hTimer)
	{
		//The timer has been started!
		return;
	}
	if(!CreateTimerQueueTimer(&m_hTimer, m_hTimerQueue, m_pCbFunc, m_pParam, m_dwDurTime, m_dwPeriod, WT_EXECUTEDEFAULT))
	{
		printf("[%s-%d]create queue timer failed[%d][Err:%d]\n", __FUNCTION__, __LINE__, *((int*)m_pParam), GetLastError());		
		return;
	}
	else
	{
		printf("[%s-%d]create queue timer success[%d]\n", __FUNCTION__, __LINE__, *((int*)m_pParam));
	}
}
void CQueueTimer::KillQueueTimer()
{
	if (m_hTimer)
	{
		DeleteTimerQueueTimer(m_hTimerQueue, m_hTimer, INVALID_HANDLE_VALUE);
		m_hTimer = nullptr;
	}
}
VOID CALLBACK TimerRoutine( PVOID lpParameter, BOOLEAN TimerOrWaitFired )
{
	if(nullptr == lpParameter)
	{
		printf("[%s-%d] The pointer lpParameter is null!\n", __FUNCTION__, __LINE__);
		return;
	}
 
	SYSTEMTIME tTime;
	GetLocalTime(&tTime);
	printf("the values of param is :%d %d [Time:%d-%d-%d:%d]\n",*(int*)lpParameter, s_nMarkQueTimer++, tTime.wHour, tTime.wMinute, tTime.wSecond, tTime.wMilliseconds);
}

//class CTimeQueue
CTimeQueue::CTimeQueue()
{
	m_vecTimer.clear();
	m_hTimerQueue = nullptr;
	m_hTimerQueue = CreateTimerQueue();
	if (nullptr == m_hTimerQueue)
	{
		printf("[%s-%d] Fail to create timer queue[Err:%d]!\n", __FUNCTION__, __LINE__, GetLastError());
	}
}
CTimeQueue::~CTimeQueue()
{
	DestroyQueue();
}

void CTimeQueue::AddTimer(CQueueTimer* pQueueTimer)
{
	if (nullptr == pQueueTimer)
	{
		printf("[%s-%d] The pointer pQueueTimer is null!\n", __FUNCTION__, __LINE__);
		return;
	}
	m_vecTimer.push_back(pQueueTimer);
}
void CTimeQueue::DestroyQueue()
{
	if (nullptr == m_hTimerQueue)
	{
		printf("[%s-%d] The pointer m_hTimerQueue is null!\n", __FUNCTION__, __LINE__);
		return;
	}
	std::vector<CQueueTimer *>::iterator iterVec = m_vecTimer.begin();
	for (; iterVec != m_vecTimer.end(); iterVec++)
	{
		if (*iterVec)
		{
			(*iterVec)->KillQueueTimer();
			delete (*iterVec);
		}
	}
	m_vecTimer.clear();
	DeleteTimerQueue(m_hTimerQueue);
	m_hTimerQueue = nullptr;
}

HANDLE CTimeQueue::GetTimeQueue()
{
	return m_hTimerQueue;
}