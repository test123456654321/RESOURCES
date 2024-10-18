
#include "LoopbackCapture.h"
#define DECLARE extern "C" __declspec(dllexport)

DECLARE void StartCaptureAsync(void (*datacb)(void *ptr, size_t size), void (*handlecb)(HANDLE))
{
    auto mutex = CreateSemaphoreW(NULL, 0, 1, NULL);
    handlecb(mutex);
    CLoopbackCapture loopbackCapture;
    loopbackCapture.StartCaptureAsync(GetCurrentProcessId(), false);
    WaitForSingleObject(mutex, INFINITE);
    CloseHandle(mutex);
    loopbackCapture.StopCaptureAsync();
    datacb(loopbackCapture.buffer.data(), loopbackCapture.buffer.size());
}

DECLARE void StopCaptureAsync(HANDLE m)
{
    ReleaseSemaphore(m, 1, NULL);
}