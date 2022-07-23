#pragma once

struct Global_Variables_Structure
{
	__int8 Additional_Bytes[8];

	float Absolute_Frame_Time;

	float Current_Time;

	float Frame_Time;

	__int32 Maximum_Clients;

	__int32 Tick_Number;

	float Interval_Per_Tick;
};

struct Interface_Structure
{
	__int8 Additional_Bytes_1[32];

	char* String;

	__int8 Additional_Bytes_2[4];

	float Floating_Point;

	__int32 Integer;

	__int8 Additional_Bytes_3[24];
};

struct Player_Data_Structure
{
	__int8 Priority;

	__int32 Memorized;

	__int32 Tolerance;

	__int32 Shots_Fired;

	float Memorized_Y;
};

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