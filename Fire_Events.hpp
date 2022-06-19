#pragma once

void* Original_Fire_Events_Caller_Location;

void Redirected_Fire_Events()
{
	void* Local_Player = *(void**)607867332;

	if (Local_Player != nullptr)
	{
		if (*(__int8*)((unsigned __int32)Local_Player + 135) == 0)
		{
			(decltype(&Redirected_Fire_Events)(Original_Fire_Events_Caller_Location))();
		}
	}
}