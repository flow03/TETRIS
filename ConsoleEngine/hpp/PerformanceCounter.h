#include <Windows.h>

class CStopwatch
{
public:
	CStopwatch();
	void Start();
	LONGLONG Now();
	LONGLONG Time();
private:
	LARGE_INTEGER m_liPerfFreq;
	LARGE_INTEGER m_liPerfStart;
};

#ifdef MY_PERFORMENCE_COUNTER

CStopwatch::CStopwatch()
{
    QueryPerformanceFrequency(&m_liPerfFreq);
    Start();
}

void CStopwatch::Start()
{
    QueryPerformanceCounter(&m_liPerfStart);
}

LONGLONG CStopwatch::Now()
{
    // возвращает число миллисекунд после вызова Start
        LARGE_INTEGER liPerfNow;
        QueryPerformanceCounter(&liPerfNow);
	return (((liPerfNow.QuadPart - m_liPerfStart.QuadPart) * (LONGLONG)1000) / m_liPerfFreq.QuadPart);
}

LONGLONG CStopwatch::Time()
{
    LARGE_INTEGER liPerfNow;
	QueryPerformanceCounter(&liPerfNow);
	return ((liPerfNow.QuadPart * (LONGLONG)1000) / m_liPerfFreq.QuadPart);
}

#endif
