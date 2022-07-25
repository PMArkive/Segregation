#pragma once

void Bruteforce_Reset_Memory()
{
	__int32 Entity_Number = 0;

	Traverse_Players_Data_Label:
	{
		Players_Data[Entity_Number].Memorized = 0;

		Entity_Number += 1;

		if (Entity_Number != sizeof(Players_Data) / sizeof(Player_Data_Structure))
		{
			goto Traverse_Players_Data_Label;
		}
	}
}

void Bruteforce_Reset_Tolerance()
{
	__int32 Entity_Number = 0;

	Traverse_Players_Data_Label:
	{
		Players_Data[Entity_Number].Tolerance = Console_Variable_Bruteforce_Tolerance.Integer;

		Entity_Number += 1;

		if (Entity_Number != sizeof(Players_Data) / sizeof(Player_Data_Structure))
		{
			goto Traverse_Players_Data_Label;
		}
	}
}

void Bruteforce_Reset()
{
	__int32 Entity_Number = 0;

	Traverse_Players_Data_Label:
	{
		Player_Data_Structure* Player_Data = &Players_Data[Entity_Number];

		Player_Data->Memorized = 0;

		Player_Data->Tolerance = Console_Variable_Bruteforce_Tolerance.Integer;

		Player_Data->Shots_Fired = 0;

		Entity_Number += 1;

		if (Entity_Number != sizeof(Players_Data) / sizeof(Player_Data_Structure))
		{
			goto Traverse_Players_Data_Label;
		}
	}
}

__int8 Bruteforce_Angles_Count;

float* Bruteforce_Angles;

void Bruteforce_Set_Angles(Interface_Structure* Console_Variable)
{
	Bruteforce_Angles_Count = 1;

	Bruteforce_Angles = (float*)realloc(Bruteforce_Angles, Bruteforce_Angles_Count * sizeof(float));

	Bruteforce_Angles[0] = atof(Console_Variable->String);

	char* Counter_String = strchr(Console_Variable->String, ',');

	Count_Bruteforce_Angles_Label:
	{
		if (Counter_String != nullptr)
		{
			Bruteforce_Angles_Count += 1;

			Bruteforce_Angles = (float*)realloc(Bruteforce_Angles, Bruteforce_Angles_Count * sizeof(float));

			Counter_String = (char*)((unsigned __int32)Counter_String + 1);

			Bruteforce_Angles[Bruteforce_Angles_Count - 1] = atof(Counter_String);

			Counter_String = strchr(Counter_String, ',');

			goto Count_Bruteforce_Angles_Label;
		}
	}

	Bruteforce_Reset();
}