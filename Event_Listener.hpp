__int32 Primary_Ammo_Capacity_Snapshot;

float Shot_Time;

void __stdcall Event_Processor(void* Event)
{
	void* Local_Player = *(void**)607867332;

	if (Local_Player != nullptr)
	{
		using Get_Name_Type = char*(__thiscall*)(void* Event);

		char* Name = Get_Name_Type((unsigned __int32)537579280)(Event);

		using Identifier_To_Number_Type = __int32(__thiscall*)(void* Engine, __int32 Identifier);

		using Get_Integer_Type = __int32(__thiscall*)(void* Event, char* Key, void* Unknown_Parameter);

		__int32 Local_Player_Number = *(__int32*)((unsigned __int32)Local_Player + 80);

		if (Name[0] == 'p')
		{
			__int32 Victim_Number = Identifier_To_Number_Type(537020000)((void*)540435380, Get_Integer_Type(537579136)(Event, (char*)"userid", nullptr));

			__int32 Killer_Number = Identifier_To_Number_Type(537020000)((void*)540435380, Get_Integer_Type(537579136)(Event, (char*)"attacker", nullptr));

			if (Victim_Number != Killer_Number)
			{
				if (Killer_Number != 0)
				{
					if (Victim_Number == Local_Player_Number)
					{
						if (Name[7] == 'd')
						{
							Player_Data_Structure* Player_Data = &Players_Data[Killer_Number - 1];

							Player_Data->Memorized = 0;

							if (Console_Variable_Commentator.Integer == 1)
							{
								PlaySoundW((wchar_t*)Sounds_Laugh, nullptr, SND_ASYNC | SND_MEMORY);
							}
						}
					}
					else
					{
						if (Killer_Number == Local_Player_Number)
						{
							if (Console_Variable_Bruteforce.Integer == 1)
							{
								if (Victim_Number == Recent_Player_Data_Number - 63)
								{
									Player_Data_Structure* Player_Data = &Players_Data[Victim_Number - 1];

									if (Player_Data->Priority != -2)
									{
										if (Name[7] == 'h')
										{
											if (Player_Data->Memorized == 0)
											{
												if (Player_Data->Tolerance == Console_Variable_Bruteforce_Tolerance.Integer)
												{
													Player_Data->Shots_Fired = ((Player_Data->Shots_Fired - 1) % Bruteforce_Angles_Count + Bruteforce_Angles_Count) % Bruteforce_Angles_Count;
												}
												else
												{
													Player_Data->Tolerance = Console_Variable_Bruteforce_Tolerance.Integer;
												}
											}
										}
										else
										{
											if (Console_Variable_Bruteforce_Memory.Integer == 1)
											{
												if (Player_Data->Memorized == 0)
												{
													Player_Data->Tolerance = 0;

													Player_Data->Memorized_Y = Bruteforce_Angles[Player_Data->Shots_Fired];
												}

												Player_Data->Memorized = Primary_Ammo_Capacity_Snapshot;
											}
										}
									}
								}
							}

							if (Name[7] == 'd')
							{
								if (Console_Variable_Commentator.Integer == 1)
								{
									PlaySoundW((wchar_t*)Sounds_Exclamation, nullptr, SND_ASYNC | SND_MEMORY);
								}
							}
						}
					}
				}
			}
		}
		else
		{
			__int32 Shooter_Number = Identifier_To_Number_Type(537020000)((void*)540435380, Get_Integer_Type(537579136)(Event, (char*)"userid", nullptr));

			if (Shooter_Number == Local_Player_Number)
			{
				Shot_Time = 0;
			}
		}
	}
}