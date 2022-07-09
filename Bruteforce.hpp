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
