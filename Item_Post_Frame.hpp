void* Original_Player_Item_Post_Frame_Caller_Location;

void* Original_Weapon_Item_Post_Frame_Caller_Location;

void __thiscall Redirected_Item_Post_Frame(void* Reserved)
{
	if (__builtin_return_address(0) == (void*)604316089)
	{
		if (__builtin_signbitf(Shot_Time) == 0)
		{
			(decltype(&Redirected_Item_Post_Frame)(Original_Player_Item_Post_Frame_Caller_Location))(Reserved);
		}
	}
	else
	{
		float Accuracy = *(float*)((unsigned __int32)Reserved + 1888);

		(decltype(&Redirected_Item_Post_Frame)(Original_Weapon_Item_Post_Frame_Caller_Location))(Reserved);

		if (*(__int8*)(*(unsigned __int32*)540494880 + 9) == 0)
		{
			*(float*)((unsigned __int32)Reserved + 1888) = Accuracy;
		}
	}
}