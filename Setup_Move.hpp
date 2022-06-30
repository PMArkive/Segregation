#pragma once

void* Original_Setup_Move_Caller_Location;

void __thiscall Redirected_Setup_Move(void* Unknown_Parameter_1, void* Player, User_Command_Structure* User_Command, void* Unknown_Parameter_3, void* Unknown_Parameter_4)
{
	Byte_Manager::Set_Bytes(0, (float*)((unsigned __int32)Player + 276), sizeof(float[3]), 0);

	void* Weapon = *(void**)((unsigned __int32)607973860 + (((*(unsigned __int32*)((unsigned __int32)Player + 2872) & 4095) - 4097) << 4));

	if (Weapon != nullptr)
	{
		using Get_Weapon_Data_Type = void*(__thiscall*)(void* Weapon);

		*(float*)((unsigned __int32)Player + 3488) = *(float*)((unsigned __int32)Get_Weapon_Data_Type(604037872)(Weapon) + 1620);
	}

	auto Compress_Angle = [](float Value, __int32 Shift) -> float
	{
		return ((__int32)(Value / 360 * Shift) & Shift - 1) * (360 / (float)Shift);
	};

	User_Command->View_Angles[0] = Compress_Angle(User_Command->View_Angles[0], 65536);

	User_Command->View_Angles[1] = Compress_Angle(User_Command->View_Angles[1], 65536);

	User_Command->View_Angles[2] = Compress_Angle(User_Command->View_Angles[2], 256);

	(decltype(&Redirected_Setup_Move)(Original_Setup_Move_Caller_Location))(Unknown_Parameter_1, Player, User_Command, Unknown_Parameter_3, Unknown_Parameter_4);
}