#pragma once

float Absolute(float X)
{
	asm("fabs" : "+t"(X));

	return X;
}

float Arc_Tangent_2(float X, float Y)
{
	asm("fpatan" : "+t"(X) : "u"(Y) : "st(1)");

	return X;
}

float Square_Root(float X)
{
	asm("fsqrt" : "+t"(X));

	return X;
}

Player_Data_Structure* Previous_Player_Data_Location;

Player_Data_Structure Previous_Player_Data;

void Angle_Vectors(float* Angles, float* Forward, float* Right, float* Up)
{
	using Angle_Vectors_Type = void(__cdecl*)(float* Angles, float* Forward, float* Right, float* Up);

	Angle_Vectors_Type(606384752)(Angles, Forward, Right, Up);
}

void Vector_Normalize(float* Vector)
{
	using Vector_Normalize_Type = float(__thiscall*)(float* Vector);

	Vector_Normalize_Type(606378096)(Vector);
}

void* Original_Copy_User_Command_Caller_Location;

void __thiscall Redirected_Copy_User_Command(void* Unknown_Parameter, User_Command_Structure* User_Command)
{
	void* Local_Player = *(void**)607867332;

	if (*(__int8*)((unsigned __int32)Local_Player + 135) == 0)
	{
		using Update_Type = void(__thiscall*)(void* Prediction, void* Unknown_Parameter_1, __int8 Unknown_Parameter_2, void* Unknown_Parameter_3, __int32 Unknown_Parameter_4);

		void* Prediction = *(void**)540494880;

		Update_Type(605209536)(Prediction, *(void**)540609292, 1, *(void**)540627876, *(__int32*)540627868 + *(__int32*)540627872);

		__int32 Previous_Buttons_State = User_Command->Buttons_State;

		User_Command->Buttons_State &= ~1;

		float Local_Player_Previous_Velocity[2] =
		{
			*(float*)((unsigned __int32)Local_Player + 224),

			*(float*)((unsigned __int32)Local_Player + 228)
		};

		float Local_Player_Previous_Origin[3] =
		{
			*(float*)((unsigned __int32)Local_Player + 668),

			*(float*)((unsigned __int32)Local_Player + 672),

			*(float*)((unsigned __int32)Local_Player + 676),
		};

		using Run_Command_Type = void(__thiscall*)(void* Prediction, void* Local_Player, User_Command_Structure* User_Command, void* Move_Helper);

		Run_Command_Type(605207600)(Prediction, Local_Player, User_Command, (void*)607735532);

		User_Command->Buttons_State = Previous_Buttons_State;

		float Move_Angles[3] =
		{
			User_Command->View_Angles[0],

			User_Command->View_Angles[1],

			0
		};

		static float Previous_Move_Angle_Y = Move_Angles[1];

		if ((User_Command->Buttons_State & 2) == 2)
		{
			User_Command->Move[0] = 0;

			if (*(__int32*)((unsigned __int32)Local_Player + 456) != -1)
			{
				User_Command->Buttons_State &= ~2;
			}

			float Difference = __builtin_remainderf(User_Command->View_Angles[1] - Previous_Move_Angle_Y, 360);

			Previous_Move_Angle_Y = User_Command->View_Angles[1];

			if (Absolute(Difference) < Arc_Tangent_2(Square_Root(__builtin_powf(Local_Player_Previous_Velocity[0], 2) + __builtin_powf(Local_Player_Previous_Velocity[1], 2)), 30) * 180 / 3.1415927f)
			{
				float Strafe_Angle = __builtin_remainderf(User_Command->View_Angles[1] - Arc_Tangent_2(Local_Player_Previous_Velocity[0], Local_Player_Previous_Velocity[1]) * 180 / 3.1415927f, 360);

				if (__builtin_signbitf(Strafe_Angle) == 0)
				{
					User_Command->Move[1] = -400;
				}
				else
				{
					User_Command->Move[1] = 400;
				}

				Move_Angles[1] -= Strafe_Angle;
			}
			else
			{
				if (__builtin_signbitf(Difference) == 0)
				{
					User_Command->Move[1] = -400;
				}
				else
				{
					User_Command->Move[1] = 400;
				}
			}
		}
		else
		{
			Previous_Move_Angle_Y = User_Command->View_Angles[1];
		}
		
		__int32 Choked_Commands_Count = *(__int32*)540627872;

		__int8 Send_Packet;

		__int32 Predicted_Choked_Commands_Count = Choked_Commands_Count + 1;

		__int8 Predicted_Send_Packet = -1;

		float* Local_Player_Origin = (float*)((unsigned __int32)Local_Player + 668);

		if (Choked_Commands_Count < Console_Variable_Minimum_Choked_Commands.Integer)
		{
			Send_Packet = 0;

			if (Predicted_Choked_Commands_Count == Console_Variable_Minimum_Choked_Commands.Integer)
			{
				if (Predicted_Choked_Commands_Count < Console_Variable_Maximum_Choked_Commands.Integer)
				{
					goto Predict_Dynamic_Send_Packet_Label;
				}
				else
				{
					Predicted_Send_Packet = 1;
				}
			}
		}
		else
		{
			static float Previous_Networked_Origin[3];

			if (Choked_Commands_Count < Console_Variable_Maximum_Choked_Commands.Integer)
			{
				if (__builtin_powf(Previous_Networked_Origin[0] - Local_Player_Previous_Origin[0], 2) + __builtin_powf(Previous_Networked_Origin[1] - Local_Player_Previous_Origin[1], 2) + __builtin_powf(Previous_Networked_Origin[2] - Local_Player_Previous_Origin[2], 2) <= 4096)
				{
					Send_Packet = 0;
				}
				else
				{
					Byte_Manager::Copy_Bytes(0, Previous_Networked_Origin, sizeof(Previous_Networked_Origin), Local_Player_Origin);

					Send_Packet = 1;
				}

				Predict_Dynamic_Send_Packet_Label:
				{
					if (Predicted_Choked_Commands_Count == Console_Variable_Maximum_Choked_Commands.Integer)
					{
						Predicted_Send_Packet = 1;
					}
					else
					{
						if (__builtin_powf(Previous_Networked_Origin[0] - Local_Player_Origin[0], 2) + __builtin_powf(Previous_Networked_Origin[1] - Local_Player_Origin[1], 2) + __builtin_powf(Previous_Networked_Origin[2] - Local_Player_Origin[2], 2) > 4096)
						{
							Predicted_Send_Packet = 1;
						}
					}
				}
			}
			else
			{
				Byte_Manager::Copy_Bytes(0, Previous_Networked_Origin, sizeof(Previous_Networked_Origin), Local_Player_Origin);

				Send_Packet = 1;
			}
		}

		__int32 Entity_Number = 1;

		__int32 Team_Number = *(__int32*)((unsigned __int32)Local_Player + 144);

		struct Target_Structure
		{
			__int8 Priority;

			float Distance;

			void* Target;
		};

		static std::vector<Target_Structure> Sorted_Target_List;

		Sorted_Target_List.clear();

		Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)607726732;

		__int32 Maximum_Clients = Global_Variables->Maximum_Clients;

		Traverse_Entity_List_Label:
		{
			Player_Data_Structure* Player_Data = &Players_Data[Entity_Number - 1];

			if (Player_Data->Priority != -1)
			{
				void* Entity = *(void**)((unsigned __int32)607973860 + ((Entity_Number - 4097) << 4));

				if (Entity != nullptr)
				{
					if (*(__int8*)((unsigned __int32)Entity + 135) == 0)
					{
						if (*(__int32*)((unsigned __int32)Entity + 144) != Team_Number)
						{
							if (*(__int8*)((unsigned __int32)Entity + 320) == 0)
							{
								float* Entity_Origin = (float*)((unsigned __int32)Entity + 668);

								Target_Structure Target =
								{
									Player_Data->Priority,

									Square_Root(__builtin_powf(Local_Player_Origin[0] - Entity_Origin[0], 2) + __builtin_powf(Local_Player_Origin[1] - Entity_Origin[1], 2) + __builtin_powf(Local_Player_Origin[2] - Entity_Origin[2], 2)),

									Entity
								};

								Sorted_Target_List.push_back(Target);
							}
						}
					}
				}
			}
		
			if (Entity_Number != Maximum_Clients)
			{
				Entity_Number += 1;

				goto Traverse_Entity_List_Label;
			}
		}

		auto Target_List_Sort = [](Target_Structure X, Target_Structure Y) -> __int8
		{
			if (X.Priority > Y.Priority)
			{
				return 1;
			}

			return X.Distance < Y.Distance;
		};
	
		std::sort(Sorted_Target_List.begin(), Sorted_Target_List.end(), Target_List_Sort);

		__int8 In_Attack = 0;

		if (Absolute(Global_Variables->Current_Time - Shot_Time) > 0.5f)
		{
			if (Shot_Time == 0)
			{
				if ((User_Command->Buttons_State & 2048) == 0)
				{
					if (Send_Packet == 0)
					{
						if (Predicted_Send_Packet == 1)
						{
							if (*(float*)((unsigned __int32)Local_Player + 2544) <= Global_Variables->Current_Time)
							{
								void* Weapon = *(void**)((unsigned __int32)607973860 + (((*(unsigned __int32*)((unsigned __int32)Local_Player + 2872) & 4095) - 4097) << 4));

								if (Weapon != nullptr)
								{
									if (*(__int32*)((unsigned __int32)Weapon + 1788) > 0)
									{
										if (*(float*)((unsigned __int32)Weapon + 1720) <= Global_Variables->Current_Time)
										{
											size_t Target_Number = 0;

											void* Optimal_Target;

											using Get_Eye_Position_Type = void(__thiscall*)(void* Player, float* Eye_Position);

											float Local_Player_Eye_Position[3];

											Get_Eye_Position_Type(604058320)(Local_Player, Local_Player_Eye_Position);

											__int32 Target_Tick_Number;

											using Get_Latency_Type = float(__thiscall*)(void* Network_Channel, __int32 Flow_Type);

											void* Network_Channel = *(void**)540608912;

											float Total_Latency = Get_Latency_Type(537919008)(Network_Channel, 0) + Get_Latency_Type(537919008)(Network_Channel, 1);

											float Interpolation_Ratio = std::clamp(*(float*)607906336, *(float*)542242312, *(float*)542242072);

											__int32 Update_Rate = std::clamp(*(__int32*)540495212, *(__int32*)542221268, *(__int32*)542221412);

											float Interpolation_Time = max(*(float*)541928632, Interpolation_Ratio / Update_Rate);

											float Corrected_Interpolation_Time = std::clamp(Total_Latency + Interpolation_Time, 0.f, 1.f);

											float Aim_Angles[2];

											Traverse_Sorted_Target_List_Label:
											{
												if (Target_Number == Sorted_Target_List.size())
												{
													Optimal_Target = nullptr;
												}
												else
												{
													Optimal_Target = Sorted_Target_List.at(Target_Number).Target;
												
													using Setup_Bones_Type = __int8(__thiscall*)(void* Entity, void* Bones, __int32 Maximum_Bones, __int32 Mask, float Current_Time);

													float Bones[128][3][4];

													if (Setup_Bones_Type(604209888)((void*)((unsigned __int32)Optimal_Target + 4), Bones, 128, 524032, Global_Variables->Current_Time) == 1)
													{
														void* Model = *(void**)((unsigned __int32)Optimal_Target + 92);

														if (Model != nullptr)
														{
															using Get_Studio_Model_Type = void*(__thiscall*)(void* Model_Cache, void* Model);

															static void* Get_Studio_Model_Location = (void*)((unsigned __int32)GetModuleHandleW(L"datacache.dll") + 46416);

															static void* Model_Cache = (void*)((unsigned __int32)GetModuleHandleW(L"datacache.dll") + 125464);

															void* Studio_Model = Get_Studio_Model_Type((unsigned __int32)Get_Studio_Model_Location)(Model_Cache, *(void**)((unsigned __int32)Model + 144));

															if (Studio_Model != nullptr)
															{
																auto Trace_Ray = [&](float* End) -> __int8
																{
																	struct Ray_Structure
																	{
																		__int8 Additional_Bytes[50];
																	};

																	struct Trace_Structure
																	{
																		__int8 Additional_Bytes_1[76];

																		void* Entity;

																		__int8 Additional_Bytes_2[4];
																	};

																	using Trace_Ray_Type = void(__cdecl*)(Ray_Structure* Ray, __int32 Mask, void* Skip, __int32 Group, Trace_Structure* Trace);

																	using Initialize_Ray_Type = void(__thiscall*)(Ray_Structure* Ray, float* Start, float* End);

																	Ray_Structure Ray;

																	Initialize_Ray_Type(537380224)(&Ray, Local_Player_Eye_Position, End);

																	Trace_Structure Trace;

																	Trace_Ray_Type(604317152)(&Ray, 1174421515, Local_Player, 0, &Trace);

																	if (Trace.Entity == nullptr)
																	{
																		return 1;
																	}

																	if (Trace.Entity == Optimal_Target)
																	{
																		return 1;
																	}

																	return 0;
																};

																void* Hitbox_Set = (void*)((unsigned __int32)Studio_Model + *(__int32*)((unsigned __int32)Studio_Model + 176));

																float* Bounding_Box_Minimum = (float*)((unsigned __int32)Hitbox_Set + 836);

																float Hitbox_Minimum[3] =
																{
																	Bounding_Box_Minimum[0] * Bones[14][0][0] + Bounding_Box_Minimum[1] * Bones[14][0][1] + Bounding_Box_Minimum[2] * Bones[14][0][2] + Bones[14][0][3],

																	Bounding_Box_Minimum[0] * Bones[14][1][0] + Bounding_Box_Minimum[1] * Bones[14][1][1] + Bounding_Box_Minimum[2] * Bones[14][1][2] + Bones[14][1][3],

																	Bounding_Box_Minimum[0] * Bones[14][2][0] + Bounding_Box_Minimum[1] * Bones[14][2][1] + Bounding_Box_Minimum[2] * Bones[14][2][2] + Bones[14][2][3]
																};

																float* Bounding_Box_Maximum = (float*)((unsigned __int32)Hitbox_Set + 848);

																float Hitbox_Maximum[3] =
																{
																	Bounding_Box_Maximum[0] * Bones[14][0][0] + Bounding_Box_Maximum[1] * Bones[14][0][1] + Bounding_Box_Maximum[2] * Bones[14][0][2] + Bones[14][0][3],

																	Bounding_Box_Maximum[0] * Bones[14][1][0] + Bounding_Box_Maximum[1] * Bones[14][1][1] + Bounding_Box_Maximum[2] * Bones[14][1][2] + Bones[14][1][3],

																	Bounding_Box_Maximum[0] * Bones[14][2][0] + Bounding_Box_Maximum[1] * Bones[14][2][1] + Bounding_Box_Maximum[2] * Bones[14][2][2] + Bones[14][2][3]
																};

																float Optimal_Target_Origin[3] =
																{
																	(Hitbox_Minimum[0] + Hitbox_Maximum[0]) / 2,

																	(Hitbox_Minimum[1] + Hitbox_Maximum[1]) / 2,

																	Hitbox_Minimum[2] + (Hitbox_Maximum[2] - Hitbox_Minimum[2]) * Console_Variable_Aim_Height.Floating_Point
																};
																
																if (Trace_Ray(Optimal_Target_Origin) == 1)
																{
																	Target_Tick_Number = (*(float*)((unsigned __int32)Optimal_Target + 104) + Interpolation_Time) / Global_Variables->Interval_Per_Tick + 0.5f;

																	__int32 Tick_Number_Difference = Global_Variables->Tick_Number + 1 + Total_Latency / Global_Variables->Interval_Per_Tick + 0.5f - Target_Tick_Number;
																	
																	if (Absolute(Corrected_Interpolation_Time - Tick_Number_Difference * Global_Variables->Interval_Per_Tick) <= 0.2f)
																	{
																		float Origin_Difference[3] =
																		{
																			Optimal_Target_Origin[0] - Local_Player_Eye_Position[0],

																			Optimal_Target_Origin[1] - Local_Player_Eye_Position[1],

																			Optimal_Target_Origin[2] - Local_Player_Eye_Position[2]
																		};

																		Aim_Angles[0] = Arc_Tangent_2(Square_Root(__builtin_powf(Origin_Difference[0], 2) + __builtin_powf(Origin_Difference[1], 2)), -Origin_Difference[2]) * 180 / 3.1415927f;

																		Aim_Angles[1] = Arc_Tangent_2(Origin_Difference[0], Origin_Difference[1]) * 180 / 3.1415927f;

																		User_Command->Buttons_State |= 1;

																		goto Found_Optimal_Target_Label;
																	}
																}
															}
														}
													}

													Target_Number += 1;

													goto Traverse_Sorted_Target_List_Label;

													Found_Optimal_Target_Label:
													{

													}
												}
											}

											if ((User_Command->Buttons_State & 1) == 1)
											{
												Shot_Time = Global_Variables->Current_Time;

												Previous_Player_Data_Location = nullptr;

												In_Attack = 1;
											
												if (Optimal_Target != nullptr)
												{
													User_Command->Tick_Number = Target_Tick_Number;

													Byte_Manager::Copy_Bytes(0, User_Command->View_Angles, sizeof(Aim_Angles), Aim_Angles);

													if (Console_Variable_Bruteforce.Integer == 1)
													{
														Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int32)Optimal_Target + 80) - 1];

														if (Player_Data->Priority != -2)
														{
															Previous_Player_Data_Location = Player_Data;

															Byte_Manager::Copy_Bytes(0, &Previous_Player_Data, sizeof(Previous_Player_Data), Previous_Player_Data_Location);

															if (Console_Variable_Bruteforce_Memory.Integer == 0)
															{
																Bruteforce_Label:
																{
																	if (Player_Data->Tolerance == 0)
																	{
																		Player_Data->Shots_Fired = (Player_Data->Shots_Fired + 1) % (sizeof(Bruteforce_Angles) / sizeof(float));

																		Player_Data->Tolerance = Console_Variable_Bruteforce_Tolerance.Integer;
																	}
																	else
																	{
																		Player_Data->Tolerance -= 1;
																	}
																}
															}
															else
															{
																if (Player_Data->Memorized == 0)
																{
																	goto Bruteforce_Label;
																}

																Player_Data->Memorized -= 1;
															}
														}
													}
												}

												User_Command->View_Angles[2] = 0;

												float Forward[3];

												float Right[3];

												float Up[3];

												Angle_Vectors(User_Command->View_Angles, Forward, Right, Up);

												User_Command->Command_Number = -2076434770;

												constexpr __int32 Random_Seed = 32;

												User_Command->Random_Seed = Random_Seed;

												using Random_Seed_Type = void(__cdecl*)(__int32 Seed);

												static void* Random_Seed_Location = (void*)((unsigned __int32)GetModuleHandleW(L"vstdlib.dll") + 11856);

												Random_Seed_Type((unsigned __int32)Random_Seed_Location)((Random_Seed & 255) + 1);

												using Random_Float_Type = float(__cdecl*)(float Minimum, float Maximum);

												static void* Random_Float_Location = (void*)((unsigned __int32)GetModuleHandleW(L"vstdlib.dll") + 11872);

												float Random_X = Random_Float_Type(Random_Float_Location)(-0.5f, 0.5f) + Random_Float_Type(Random_Float_Location)(-0.5f, 0.5f);

												Weapon_Spread = -1;

												using Primary_Attack_Type = void(__thiscall**)(void* Weapon);

												(*Primary_Attack_Type(*(unsigned __int32*)Weapon + 856))(Weapon);

												float Random_Y = Random_Float_Type(Random_Float_Location)(-0.5f, 0.5f) + Random_Float_Type(Random_Float_Location)(-0.5f, 0.5f);

												float Direction[3] =
												{
													Forward[0] + Random_X * Weapon_Spread * Right[0] + Random_Y * Weapon_Spread * Up[1],

													Forward[1] + Random_X * Weapon_Spread * Right[1] + Random_Y * Weapon_Spread * Up[1],

													Forward[2] + Random_X * Weapon_Spread * Right[2] + Random_Y * Weapon_Spread * Up[2]
												};

												Weapon_Spread = 0;

												float Spread_Angles[3] =
												{
													Arc_Tangent_2(Square_Root(__builtin_powf(Direction[0], 2) + __builtin_powf(Direction[1], 2)), -Direction[2]) * 180 / 3.1415927f - User_Command->View_Angles[0],

													Arc_Tangent_2(Direction[0], Direction[1]) * 180 / 3.1415927f - User_Command->View_Angles[1],

													0
												};

												using Angle_Vectors_Transpose_Type = void(__cdecl*)(float* Angles, float* Forward, float* Right, float* Up);

												Angle_Vectors_Transpose_Type(574033968)(Spread_Angles, Forward, nullptr, Up);

												float* Recoil = (float*)((unsigned __int32)Local_Player + 2992);

												User_Command->View_Angles[0] += Arc_Tangent_2(Square_Root(__builtin_powf(Forward[0], 2) + __builtin_powf(Forward[1], 2)), -Forward[2]) * 180 / 3.1415927f - Recoil[0] * 2;

												User_Command->View_Angles[1] += Arc_Tangent_2(Forward[0], Forward[1]) * 180 / 3.1415927f - Recoil[1] * 2;
												
												User_Command->View_Angles[2] += Arc_Tangent_2(Forward[0] * (Forward[0] * Up[2] - Forward[2] * Up[0]) - Forward[1] * (Forward[2] * Up[1] - Forward[1] * Up[2]), Forward[1] * Up[0] - Forward[0] * Up[1]) * 180 / 3.1415927f - Recoil[2] * 2;
											}
										}
									}
								}
							}
						}
					}
				}
			}
			else
			{
				Shot_Time = 0;

				if (Previous_Player_Data_Location != nullptr)
				{
					Byte_Manager::Copy_Bytes(0, Previous_Player_Data_Location, sizeof(Previous_Player_Data), &Previous_Player_Data);
				}
			}
		}

		if (In_Attack == 0)
		{
			User_Command->Buttons_State &= ~1;

			if (Sorted_Target_List.size() != 0)
			{
				User_Command->View_Angles[0] = Console_Variable_Angle_X.Floating_Point;

				float* Optimal_Target_Origin = (float*)((unsigned __int32)Sorted_Target_List.at(0).Target + 668);
				
				float Origin_Difference[2] =
				{
					Optimal_Target_Origin[0] - Local_Player_Origin[0],

					Optimal_Target_Origin[1] - Local_Player_Origin[1]
				};

				if (Send_Packet == 0)
				{
					if ((User_Command->Command_Number % 2) == 0)
					{
						User_Command->View_Angles[1] = Arc_Tangent_2(Origin_Difference[0], Origin_Difference[1]) * 180 / 3.1415927f + Console_Variable_First_Choked_Angle_Y.Floating_Point;
					}
					else
					{
						User_Command->View_Angles[1] = Arc_Tangent_2(Origin_Difference[0], Origin_Difference[1]) * 180 / 3.1415927f + Console_Variable_Second_Choked_Angle_Y.Floating_Point;
					}
				}
				else
				{
					User_Command->View_Angles[1] = Arc_Tangent_2(Origin_Difference[0], Origin_Difference[1]) * 180 / 3.1415927f + Console_Variable_Angle_Y.Floating_Point;
				}
			}
			
			if (Send_Packet == 1)
			{
				Byte_Manager::Copy_Bytes(0, Update_Animation_Angle, sizeof(Update_Animation_Angle), User_Command->View_Angles);
			}
		}

		*(__int8*)((unsigned __int32)__builtin_frame_address(0) + 24) = Send_Packet;

		float Desired_Move_Forward[3];

		float Desired_Move_Right[3];

		Angle_Vectors(Move_Angles, Desired_Move_Forward, Desired_Move_Right, nullptr);

		Desired_Move_Forward[2] = 0;

		Desired_Move_Right[2] = 0;

		Vector_Normalize(Desired_Move_Forward);

		Vector_Normalize(Desired_Move_Right);

		float Desired_Move[2] =
		{
			Desired_Move_Forward[0] * User_Command->Move[0] + Desired_Move_Right[0] * User_Command->Move[1],

			Desired_Move_Forward[1] * User_Command->Move[0] + Desired_Move_Right[1] * User_Command->Move[1]
		};

		float Move_Forward[3];

		float Move_Right[3];

		Angle_Vectors(User_Command->View_Angles, Move_Forward, Move_Right, nullptr);

		Move_Forward[2] = 0;

		Move_Right[2] = 0;

		Vector_Normalize(Move_Forward);

		Vector_Normalize(Move_Right);

		float Divider = Move_Forward[0] * Move_Right[1] - Move_Right[0] * Move_Forward[1];

		User_Command->Move[0] = __builtin_roundf((Desired_Move[0] * Move_Right[1] - Move_Right[0] * Desired_Move[1]) / Divider);

		User_Command->Move[1] = __builtin_roundf((Move_Forward[0] * Desired_Move[1] - Desired_Move[0] * Move_Forward[1]) / Divider);
	}

	(decltype(&Redirected_Copy_User_Command)(Original_Copy_User_Command_Caller_Location))(Unknown_Parameter, User_Command);
}