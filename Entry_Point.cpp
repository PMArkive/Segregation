#include <Windows.h>

#include <cstdio>

#define Bits_32

#include "Byte_Manager/Byte_Manager.hpp"

#include "Redirection_Manager/Redirection_Manager.hpp"

#include "Frame_Stage_Notify.hpp"

#include "Extended_Interface.hpp"

#pragma comment(lib, "WinMM.Lib")

#include "Sounds.hpp"

#include "Event_Listener.hpp"

#include "Write_Events.hpp"

#include "Shutdown.hpp"

#include "Interpolate.hpp"

#include "Update_Animation.hpp"

#include "Converge_Angles.hpp"

#include "Run_Simulation.hpp"

#include "Setup_Move.hpp"

#include "Item_Post_Frame.hpp"

#include "Weapon_Spread.hpp"

#include <vector>

#include <algorithm>

#include "Copy_User_Command.hpp"

#include "Send_Move.hpp"

#include "Draw_Crosshair.hpp"

#include "Precache.hpp"

__int32 __stdcall DllMain(void* This_Module_Location, unsigned __int32 Call_Reason, void* Reserved)
{
	if (Call_Reason == DLL_PROCESS_DETACH)
	{
		__fastfail(EXIT_SUCCESS);
	}
	else
	{
		if (Call_Reason == DLL_PROCESS_ATTACH)
		{
			Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)LoadLibraryW(L"vaudio_speex.dll") + 9360), 1, 195);

			AllocConsole();

			SetConsoleTitleW(L"Segregation");

			_wfreopen(L"CONOUT$", L"w", stdout);

			SetConsoleOutputCP(65001);

			HANDLE Standard_Output_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

			CONSOLE_FONT_INFOEX Console_Font_Information;

			Console_Font_Information.cbSize = sizeof(CONSOLE_FONT_INFOEX);

			Console_Font_Information.nFont = 0;

			Console_Font_Information.dwFontSize.X = 0;

			Console_Font_Information.dwFontSize.Y = 12;

			Console_Font_Information.FontFamily = FF_DONTCARE;

			Console_Font_Information.FontWeight = FW_NORMAL;
			
			wcscpy(Console_Font_Information.FaceName, L"Terminal");

			SetCurrentConsoleFontEx(Standard_Output_Handle, 0, &Console_Font_Information);

			CONSOLE_CURSOR_INFO Console_Cursor_Information;

			Console_Cursor_Information.bVisible = 0;

			Console_Cursor_Information.dwSize = sizeof(Console_Cursor_Information);

			SetConsoleTextAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED);

			SetConsoleCursorInfo(Standard_Output_Handle, &Console_Cursor_Information);

			CONSOLE_SCREEN_BUFFER_INFO Console_Screen_Buffer_Information;

			GetConsoleScreenBufferInfo(Standard_Output_Handle, &Console_Screen_Buffer_Information);

			COORD Top_Left =
			{
				0,

				0
			};

			DWORD Characters_Written_Count;

			FillConsoleOutputAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED, Console_Screen_Buffer_Information.dwSize.X * Console_Screen_Buffer_Information.dwSize.Y, Top_Left, &Characters_Written_Count);

			wprintf(L"[ + ] Delimit Interface\n");
			{
				unsigned __int8 Cheat_Flag_Bytes[4] =
				{
					254,

					65,

					44,

					195
				};

				Byte_Manager::Copy_Bytes(1, (void*)538391351, sizeof(Cheat_Flag_Bytes), Cheat_Flag_Bytes);

				*(__int8*)542242676 = 1;

				Byte_Manager::Set_Bytes(1, (void*)537349277, 1, 235);
			}

			wprintf(L"[ + ] Extend Interface\n");
			{
				Implement_Extended_Interface();
			}

			wprintf(L"[ + ] Events\n");
			{
				Redirection_Manager::Redirect_Function(Original_Frame_Stage_Notify_Caller_Location, 1, (void*)604538592, 1, (void*)Redirected_Frame_Stage_Notify);

				Byte_Manager::Set_Bytes(1, (void*)537149578, 1, 235);

				void* Event_Listener = (void*)malloc(sizeof(void*));

				void* Event_Listener_Table = malloc(sizeof(void*) * 2);

				*(void**)((unsigned __int32)Event_Listener_Table + 4) = (void*)Event_Processor;

				*(void**)Event_Listener = Event_Listener_Table;

				using Add_Listener_Type = __int8(__thiscall*)(void* Game_Event_Manager, void* Listener, char* Event, void* Unknown_Parameter);

				Add_Listener_Type(537586416)((void*)540812808, Event_Listener, (char*)"player_hurt", nullptr);

				Add_Listener_Type(537586416)((void*)540812808, Event_Listener, (char*)"player_death", nullptr);

				Add_Listener_Type(537586416)((void*)540812808, Event_Listener, (char*)"bullet_impact", nullptr);

				Redirection_Manager::Redirect_Function(Original_Write_Events_Caller_Location, 2, (void*)537582208, 1, (void*)Redirected_Write_Events);

				Redirection_Manager::Redirect_Function(Original_Shutdown_Caller_Location, 0, (void*)537926128, 1, (void*)Redirected_Shutdown);
			}

			wprintf(L"[ + ] Interpolation\n");
			{
				Redirection_Manager::Redirect_Function(Original_Interpolate_Caller_Location, 0, (void*)604201536, 1, (void*)Redirected_Interpolate);
			}

			wprintf(L"[ + ] Animations\n");
			{
				unsigned __int8 Maintain_Sequence_Transitions_Bytes[3] =
				{
					194,

					24,

					0
				};

				Byte_Manager::Copy_Bytes(1, (void*)604206416, sizeof(Maintain_Sequence_Transitions_Bytes), Maintain_Sequence_Transitions_Bytes);

				Redirection_Manager::Redirect_Function(Original_Update_Animation_Caller_Location, 4, (void*)605800256, 1, (void*)Redirected_Update_Animation);

				Byte_Manager::Set_Bytes(1, (void*)604287917, 2, 144);

				Byte_Manager::Set_Bytes(1, (void*)605800287, 1, 235);

				Byte_Manager::Set_Bytes(1, (void*)604022867, 2, 144);

				Byte_Manager::Set_Bytes(1, (void*)604022906, 12, 144);

				Redirection_Manager::Redirect_Function(Original_Converge_Angles_Caller_Location, 3, (void*)604019936, 1, (void*)Redirected_Converge_Angles);
			}

			wprintf(L"[ + ] Prediction\n");
			{
				Byte_Manager::Set_Bytes(1, (void*)537158868, 5, 144);

				Byte_Manager::Set_Bytes(1, (void*)605209595, 1, 235);

				Redirection_Manager::Redirect_Function(Original_Run_Simulation_Caller_Location, 0, (void*)605206096, 1, (void*)Redirected_Run_Simulation);

				Redirection_Manager::Redirect_Function(Original_Setup_Move_Caller_Location, 0, (void*)605206752, 1, (void*)Redirected_Setup_Move);

				Byte_Manager::Set_Bytes(1, (void*)605954536, 9, 144);

				Redirection_Manager::Redirect_Function(Original_Player_Item_Post_Frame_Caller_Location, 0, (void*)604081184, 1, (void*)Redirected_Item_Post_Frame);

				Redirection_Manager::Redirect_Function(Original_Weapon_Item_Post_Frame_Caller_Location, 4, (void*)605953776, 1, (void*)Redirected_Item_Post_Frame);

				Redirection_Manager::Redirect_Function(Original_Weapon_Spread_Caller_Location, 1, (void*)605949248, 1, (void*)Redirected_Weapon_Spread);
			}

			wprintf(L"[ + ] Input\n");
			{
				Byte_Manager::Set_Bytes(1, (void*)604993824, 3, 144);

				Redirection_Manager::Redirect_Function(Original_Copy_User_Command_Caller_Location, 0, (void*)604850464, 1, (void*)Redirected_Copy_User_Command);
			}

			wprintf(L"[ + ] Network\n");
			{
				Redirection_Manager::Redirect_Function(1, (void*)537142224, (void*)Redirected_Send_Move);
			}

			wprintf(L"[ + ] View Effects\n");
			{
				unsigned __int8 Apply_View_Effects_Bytes[30] =
				{
					7,

					144,

					144,

					144,

					144,

					144,

					144,

					217,

					31,

					217,

					71,

					4,

					144,

					144,

					144,

					144,

					144,

					144,

					217,

					95,

					4,

					217,

					71,

					8,

					144,

					144,

					144,

					144,

					144,

					144
				};

				Byte_Manager::Copy_Bytes(1, (void*)604082899, sizeof(Apply_View_Effects_Bytes), Apply_View_Effects_Bytes);
			}

			wprintf(L"[ + ] Crosshair\n");
			{
				Redirection_Manager::Redirect_Function(1, (void*)605951488, (void*)Redirected_Draw_Crosshair);
			}

			wprintf(L"[ + ] Materials\n");
			{
				Byte_Manager::Set_Bytes(1, (void*)537873811, 1, 255);

				Redirection_Manager::Redirect_Function(Original_Precache_Caller_Location, 5, (void*)((unsigned __int32)GetModuleHandleW(L"MaterialSystem.dll") + 21984), 1, (void*)Redirected_Precache);

				Byte_Manager::Set_Bytes(1, (void*)605809168, 1, 195);

				unsigned __int8 Smoke_Bytes[3] =
				{
					194,

					8,

					0
				};

				Byte_Manager::Copy_Bytes(1, (void*)605610608, sizeof(Smoke_Bytes), Smoke_Bytes);
			}
		}
	}

	return 1;
}