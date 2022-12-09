void* Original_Finish_Move_Caller_Location;

void __thiscall Redirected_Finish_Move(void* Unknown_Parameter_1, void* Player, void* Unknown_Parameter_3, void* Move_Data)
{
	float X = *(float*)((unsigned __int32)Move_Data + 76);

	if (X > 180)
	{
		X -= 360;
	}
	
	*(float*)((unsigned __int32)Move_Data + 76) = std::clamp(X, -90.f, 90.f);

	(decltype(&Redirected_Finish_Move)(Original_Finish_Move_Caller_Location))(Unknown_Parameter_1, Player, Unknown_Parameter_3, Move_Data);

	using Set_Collision_Bounds_Type = void(__thiscall*)(void* Collision_Property, float* Minimum, float* Maximum);

	__int8 In_Crouch = (*(__int32*)((unsigned __int32)Player + 692) & 2) == 2;

	Set_Collision_Bounds_Type(604660272)((void*)((unsigned __int32)Player + 352), (float*)((unsigned __int32)608155796 + 24 * In_Crouch), (float*)((unsigned __int32)608155808 + 24 * In_Crouch));
}