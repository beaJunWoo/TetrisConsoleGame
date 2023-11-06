#include "DoubleBuffer.h"
#include "ScenesManager.h"
#include "DataBase.h"

int main()

 {
	ULONGLONG deltatime = GetTickCount64();

	ScenesManager::Get()->Initalize(LOGO);
	DoubleBuffer::Get()->InitBuffer();


	while (true)
	{
		
		DoubleBuffer::Get()->FlipBuffer();
		DoubleBuffer::Get()->ClearBuffer();
		ScenesManager::Get()->Progress();
		ScenesManager::Get()->Render();
		deltatime = GetTickCount64();
		
		
	}

	DoubleBuffer::Get()->ReleaseBuffer();
	ScenesManager::Get()->Release();
	return 0;
}