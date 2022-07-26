struct User_Command_Structure
{
	__int8 Additional_Bytes_1[4];

	__int32 Command_Number;

	__int32 Tick_Number;

	float Angles[3];

	float Move[3];

	__int32 Buttons;

	__int8 Additional_Bytes_2[9];

	__int32 Random_Seed;

	__int8 Additional_Bytes_3[4];

	__int8 Predicted;
};

__int8 Is_First_Command_Predicted;

void* Original_Run_Simulation_Caller_Location;

void __thiscall Redirected_Run_Simulation(void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, User_Command_Structure* User_Command, void* Player)
{
	Is_First_Command_Predicted = User_Command->Predicted;

	(decltype(&Redirected_Run_Simulation)(Original_Run_Simulation_Caller_Location))(Unknown_Parameter_1, Unknown_Parameter_2, Unknown_Parameter_3, User_Command, Player);

	using Set_Collision_Bounds_Type = void(__thiscall*)(void* Collision_Property, float* Minimum, float* Maximum);

	__int8 In_Crouch = (*(__int32*)((unsigned __int32)Player + 692) & 2) == 2;

	Set_Collision_Bounds_Type(604660272)((void*)((unsigned __int32)Player + 352), (float*)((unsigned __int32)608155796 + 24 * In_Crouch), (float*)((unsigned __int32)608155808 + 24 * In_Crouch));
}