#pragma once

void* Original_Player_Item_Post_Frame_Caller_Location;

void* Original_Weapon_Item_Post_Frame_Caller_Location;

void __thiscall Redirected_Item_Post_Frame(void* Reserved)
{
	if (__builtin_signbitf(Shot_Time) == 0)
	{
		if (__builtin_return_address(0) == (void*)604316089)
		{
			(decltype(&Redirected_Item_Post_Frame)(Original_Player_Item_Post_Frame_Caller_Location))(Reserved);
		}
		else
		{
			float Accuracy = *(float*)((unsigned __int32)Reserved + 1888);

			(decltype(&Redirected_Item_Post_Frame)(Original_Weapon_Item_Post_Frame_Caller_Location))(Reserved);

			if (Is_First_Command_Predicted == 1)
			{
				*(float*)((unsigned __int32)Reserved + 1888) = Accuracy;
			}
		}
	}
}