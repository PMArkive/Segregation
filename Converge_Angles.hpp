void* Original_Converge_Angles_Caller_Location;

void __thiscall Redirected_Converge_Angles(void* Animation_State, float Goal, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, float* Current)
{
	__int8 Instant = 0;

	if (Interface_Bruteforce.Integer == 1)
	{
		void* Entity = *(void**)((unsigned __int32)Animation_State + 20);

		if (Entity != *(void**)607867332)
		{
			if (*(void**)Entity == (void*)607350148)
			{
				Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int32)Entity + 80) - 1];

				if (Player_Data->Priority != -2)
				{
					if (Interface_Bruteforce_Memory.Integer == 0)
					{
						Bruteforce_Label:
						{
							Goal = *(float*)((unsigned __int32)Animation_State + 24) + Bruteforce_Angles[Player_Data->Shots_Fired];
						}
					}
					else
					{
						if (Player_Data->Memorized == 0)
						{
							goto Bruteforce_Label;
						}

						Goal = *(float*)((unsigned __int32)Animation_State + 24) + Player_Data->Memorized_Y;
					}

					Instant = 1;
				}
			}
		}
	}

	if (Goal != *(float*)Current)
	{
		if (Instant == 0)
		{
			(decltype(&Redirected_Converge_Angles)(Original_Converge_Angles_Caller_Location))(Animation_State, Goal, Unknown_Parameter_1, Unknown_Parameter_2, Unknown_Parameter_3, Current);
		}
		else
		{
			*(float*)Current = __builtin_remainderf(Goal, 360);
		}

		*(float*)((unsigned __int32)Animation_State + 52) = (*(Global_Variables_Structure**)607726732)->Current_Time;
	}
}