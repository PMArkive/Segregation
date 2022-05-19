#pragma once

void Redirected_Draw_Crosshair()
{
	*(__int8*)608051340 = 0;

	static float Rotation_Angle;

	auto Uber_Alles = [&](__int32 X, __int8 Red, __int32 Y)
	{
		using Set_Color_Type = void(__thiscall*)(void* Surface, unsigned __int8 Red, unsigned __int8 Green, unsigned __int8 Blue, unsigned __int8 Alpha);

		static void* Surface = *(void**)608279384;

		static void* Set_Color_Location = *(void**)(*(unsigned __int32*)Surface + 44);

		Set_Color_Type((unsigned __int32)Set_Color_Location)(Surface, Red * 255, 0, 0, 255);

		float Uber_Alles = 2 * Console_Variable_Uber_Alles_Scale.Integer;

		__int32 Points[16]
		{
			(__int32)__builtin_roundf(Uber_Alles * __builtin_sinf((Rotation_Angle - 90) * 3.1415927f / 180)),

			(__int32)__builtin_roundf(Uber_Alles * __builtin_cosf((Rotation_Angle - 90) * 3.1415927f / 180)),

			(__int32)__builtin_roundf(Uber_Alles * __builtin_sinf((Rotation_Angle - 90) * 3.1415927f / 180)),

			(__int32)__builtin_roundf(Uber_Alles * __builtin_cosf((Rotation_Angle - 90) * 3.1415927f / 180 + 1)),

			(__int32)__builtin_roundf(Uber_Alles * __builtin_sinf(Rotation_Angle * 3.1415927f / 180)),

			(__int32)__builtin_roundf(Uber_Alles * __builtin_cosf(Rotation_Angle * 3.1415927f / 180)),

			(__int32)__builtin_roundf(Uber_Alles * __builtin_sinf(Rotation_Angle * 3.1415927f / 180 + 1)),

			(__int32)__builtin_roundf(Uber_Alles * __builtin_cosf(Rotation_Angle * 3.1415927f / 180)),

			(__int32)__builtin_roundf(Uber_Alles * __builtin_sinf((Rotation_Angle + 90) * 3.1415927f / 180)),

			(__int32)__builtin_roundf(Uber_Alles * __builtin_cosf((Rotation_Angle + 90) * 3.1415927f / 180)),

			(__int32)__builtin_roundf(Uber_Alles * __builtin_sinf((Rotation_Angle + 90) * 3.1415927f / 180)),

			(__int32)__builtin_roundf(Uber_Alles * __builtin_cosf((Rotation_Angle + 90) * 3.1415927f / 180 + 1)),

			(__int32)__builtin_roundf(Uber_Alles * __builtin_sinf((Rotation_Angle + 180) * 3.1415927f / 180)),

			(__int32)__builtin_roundf(Uber_Alles * __builtin_cosf((Rotation_Angle + 180) * 3.1415927f / 180)),

			(__int32)__builtin_roundf(Uber_Alles * __builtin_sinf((Rotation_Angle + 180) * 3.1415927f / 180 + 1)),

			(__int32)__builtin_roundf(Uber_Alles * __builtin_cosf((Rotation_Angle + 180) * 3.1415927f / 180)),
		};

		using Draw_Line_Type = void(__thiscall*)(void* Surface, __int32 From_X, __int32 From_Y, __int32 To_X, __int32 To_Y);

		static void* Draw_Line_Location = *(void**)(*(unsigned __int32*)Surface + 60);

		Draw_Line_Type((unsigned __int32)Draw_Line_Location)(Surface, X, Y, X + Points[0], Y - Points[1]);

		Draw_Line_Type((unsigned __int32)Draw_Line_Location)(Surface, X + Points[0], Y - Points[1], X + Points[2], Y - Points[3]);

		Draw_Line_Type((unsigned __int32)Draw_Line_Location)(Surface, X, Y, X + Points[4], Y - Points[5]);

		Draw_Line_Type((unsigned __int32)Draw_Line_Location)(Surface, X + Points[4], Y - Points[5], X + Points[6], Y - Points[7]);

		Draw_Line_Type((unsigned __int32)Draw_Line_Location)(Surface, X, Y, X + Points[8], Y - Points[9]);

		Draw_Line_Type((unsigned __int32)Draw_Line_Location)(Surface, X + Points[8], Y - Points[9], X + Points[10], Y - Points[11]);

		Draw_Line_Type((unsigned __int32)Draw_Line_Location)(Surface, X, Y, X + Points[12], Y - Points[13]);

		Draw_Line_Type((unsigned __int32)Draw_Line_Location)(Surface, X + Points[12], Y - Points[13], X + Points[14], Y - Points[15]);
	};

	using Get_Screen_Size_Type = __int32(__cdecl*)();

	__int32 Screen_Width = Get_Screen_Size_Type(604542880)() / 2;

	__int32 Screen_Height = Get_Screen_Size_Type(604542848)() / 2;

	Uber_Alles(Screen_Width - 1, 0, Screen_Height);

	Uber_Alles(Screen_Width, 0, Screen_Height - 1);

	Uber_Alles(Screen_Width + 1, 0, Screen_Height);

	Uber_Alles(Screen_Width, 0, Screen_Height + 1);

	Uber_Alles(Screen_Width - 1, 0, Screen_Height - 1);

	Uber_Alles(Screen_Width + 1, 0, Screen_Height - 1);

	Uber_Alles(Screen_Width - 1, 0, Screen_Height + 1);

	Uber_Alles(Screen_Width + 1, 0, Screen_Height + 1);

	Uber_Alles(Screen_Width, 1, Screen_Height);

	static Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)607726732;

	Rotation_Angle = __builtin_remainderf(Rotation_Angle - (Global_Variables->Absolute_Frame_Time * Console_Variable_Uber_Alles_Speed.Integer), 360);
}