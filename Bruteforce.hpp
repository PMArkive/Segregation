#pragma once

constexpr float Bruteforce_Angles[5] =
{
	0,

	-45,

	45,

	-90,

	90
};

void Bruteforce_Reset_Memory()
{
	__int32 Entity_Number = 0;

	Traverse_Players_Data_Label:
	{
		Player_Data_Structure* Player_Data = &Players_Data[Entity_Number];

		Player_Data->Memorized = 0;

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
	Bruteforce_Reset_Memory();

	Bruteforce_Reset_Tolerance();
}
