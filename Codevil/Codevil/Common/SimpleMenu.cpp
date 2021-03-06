#include "all.h"

int SimpleMenu_Color = -1;
int SimpleMenu_BorderColor = -1;
int SimpleMenu_WallColor = -1;
int SimpleMenu_WallPicId = -1;
double SimpleMenu_WallCurtain = 0.0;
int SimpleMenu_X = 16;
int SimpleMenu_Y = 16;
int SimpleMenu_YStep = 32;

int SimpleMenu(char *menuTitle, char **menuItems, int selectMax, int selectIndex)
{
	SetCurtain();
	FreezeInput();

	for(; ; )
	{
		if(GetPound(INP_A))
		{
			break;
		}
		if(GetPound(INP_B))
		{
			if(selectIndex == selectMax - 1)
				break;

			selectIndex = selectMax - 1;
		}
		if(GetPound(INP_DIR_8))
		{
			selectIndex--;
		}
		if(GetPound(INP_DIR_2))
		{
			selectIndex++;
		}

		selectIndex += selectMax;
		selectIndex %= selectMax;

		DrawCurtain();

		if(SimpleMenu_WallColor != -1)
			DrawBox(0, 0, SCREEN_W, SCREEN_H, SimpleMenu_WallColor, 1);

		if(SimpleMenu_WallPicId != -1)
		{
			DrawRect(SimpleMenu_WallPicId, 0, 0, SCREEN_W, SCREEN_H);
//			DrawCenter(SimpleMenu_WallPicId, SCREEN_W / 2.0, SCREEN_H / 2.0); // old
			DrawCurtain(SimpleMenu_WallCurtain);
		}
		if(SimpleMenu_Color != -1)
			PE.Color = SimpleMenu_Color;

		if(SimpleMenu_BorderColor != -1)
			PE_Border(SimpleMenu_BorderColor);

		SetPrint(SimpleMenu_X, SimpleMenu_Y, SimpleMenu_YStep);
//		SetPrint(16, 16, 32); // old
		Print(menuTitle);
		PrintRet();

		for(int c = 0; c < selectMax; c++)
		{
			Print_x(xcout("[%c]　%s", selectIndex == c ? '>' : ' ', menuItems[c]));
			PrintRet();
		}
		PE_Reset();

		EachFrame();
	}
	FreezeInput();

	return selectIndex;
}

// ---- ボタン設定 ----

static void *PadBtnIdBkup;

static void RestorePadBtnId(void)
{
	memcpy(&Gnd.PadBtnId, PadBtnIdBkup, sizeof(Gnd.PadBtnId));
}
void SimplePadConfig(void)
{
	int *BtnPList[INP_MAX] =
	{
		&Gnd.PadBtnId.Dir_2,
		&Gnd.PadBtnId.Dir_4,
		&Gnd.PadBtnId.Dir_6,
		&Gnd.PadBtnId.Dir_8,
		&Gnd.PadBtnId.A,
		&Gnd.PadBtnId.B,
		&Gnd.PadBtnId.C,
		&Gnd.PadBtnId.D,
		&Gnd.PadBtnId.E,
		&Gnd.PadBtnId.F,
		&Gnd.PadBtnId.L,
		&Gnd.PadBtnId.R,
		&Gnd.PadBtnId.Pause,
		&Gnd.PadBtnId.Start,
	};

	/*
		NULL == 使用していない。
	*/
	char *BTN_LIST[INP_MAX] =
	{
		// app > @ BTN_LIST

		"下", // INP_DIR_2
		"左", // INP_DIR_4
		"右", // INP_DIR_6
		"上", // INP_DIR_8
		"ショットボタン", // INP_A
		"低速ボタン", // INP_B
		"ボムボタン", // INP_C
		NULL, // INP_D
		NULL, // INP_E
		NULL, // INP_F
		NULL, // INP_L
		NULL, // INP_R
		"ポーズボタン", // INP_PAUSE
		NULL, // INP_START

		// < app
	};

	PadBtnIdBkup = memClone(&Gnd.PadBtnId, sizeof(Gnd.PadBtnId));
	GetEndProcFinalizers()->AddFunc(RestorePadBtnId);

	for(int c = 0; c < INP_MAX; c++)
		*BtnPList[c] = -1;

	SetCurtain();
	FreezeInput();

	int currBtnIndex = 0;

	while(currBtnIndex < INP_MAX)
	{
		if(!BTN_LIST[currBtnIndex])
		{
			currBtnIndex++;
			continue;
		}

		if(GetKeyInput(KEY_INPUT_SPACE) == 1)
		{
			RestorePadBtnId();
			break;
		}
		if(GetKeyInput(KEY_INPUT_Z) == 1)
		{
			currBtnIndex++;
			goto endInput;
		}
		int pressBtnId = -1;

		for(int padId = 0; padId < GetPadCount(); padId++)
		for(int btnId = 0; btnId < PAD_BUTTON_MAX; btnId++)
			if(GetPadInput(padId, btnId) == 1)
				pressBtnId = btnId;

		for(int c = 0; c < currBtnIndex; c++)
			if(*BtnPList[c] == pressBtnId)
				pressBtnId = -1;

		if(pressBtnId != -1)
		{
			*BtnPList[currBtnIndex] = pressBtnId;
			currBtnIndex++;
		}
endInput:

		DrawCurtain();

		if(SimpleMenu_WallColor != -1)
			DrawBox(0, 0, SCREEN_W, SCREEN_H, SimpleMenu_WallColor, 1);

		if(SimpleMenu_WallPicId != -1)
		{
			DrawRect(SimpleMenu_WallPicId, 0, 0, SCREEN_W, SCREEN_H);
//			DrawCenter(SimpleMenu_WallPicId, SCREEN_W / 2.0, SCREEN_H / 2.0); // old
			DrawCurtain(SimpleMenu_WallCurtain);
		}
		if(SimpleMenu_Color != -1)
			PE.Color = SimpleMenu_Color;

		if(SimpleMenu_BorderColor != -1)
			PE_Border(SimpleMenu_BorderColor);

		SetPrint(SimpleMenu_X, SimpleMenu_Y, SimpleMenu_YStep);
//		SetPrint(16, 16, 32); // old
		Print("ゲームパッドのボタン設定");
		PrintRet();

		for(int c = 0; c < INP_MAX; c++)
		{
			if(!BTN_LIST[c])
				continue;

			Print_x(xcout("[%c]　%s", currBtnIndex == c ? '>' : ' ', BTN_LIST[c]));

			if(c < currBtnIndex)
			{
				int btnId = *BtnPList[c];

				Print("　->　");

				if(btnId == -1)
					Print("割り当てナシ");
				else
					Print_x(xcout("%d", btnId));
			}
			PrintRet();
		}
		Print("★　カーソルの機能に割り当てるボタンを押して下さい。");
		PrintRet();
		Print("★　スペースを押すとキャンセルします。");
		PrintRet();
		Print("★　[Z]を押すとボタンの割り当てをスキップします。");
		PrintRet();

		EachFrame();
	}

	GetEndProcFinalizers()->RemoveFunc(RestorePadBtnId);
	memFree(PadBtnIdBkup);

	FreezeInput();
}

// ---- 画面サイズ ----

static int WinSzExp(int size, int index)
{
	return (size * (8 + index)) / 8;
}
void SimpleWindowSizeConfig(void)
{
	char *MENU_ITEMS[] =
	{
		xcout("%d x %d (デフォルト)", SCREEN_W, SCREEN_H),
		xcout("%d x %d", WinSzExp(SCREEN_W,  1), WinSzExp(SCREEN_H,  1)),
		xcout("%d x %d", WinSzExp(SCREEN_W,  2), WinSzExp(SCREEN_H,  2)),
		xcout("%d x %d", WinSzExp(SCREEN_W,  3), WinSzExp(SCREEN_H,  3)),
		xcout("%d x %d", WinSzExp(SCREEN_W,  4), WinSzExp(SCREEN_H,  4)),
		xcout("%d x %d", WinSzExp(SCREEN_W,  5), WinSzExp(SCREEN_H,  5)),
		xcout("%d x %d", WinSzExp(SCREEN_W,  6), WinSzExp(SCREEN_H,  6)),
		xcout("%d x %d", WinSzExp(SCREEN_W,  7), WinSzExp(SCREEN_H,  7)),
		xcout("%d x %d", WinSzExp(SCREEN_W,  8), WinSzExp(SCREEN_H,  8)),
		xcout("%d x %d", WinSzExp(SCREEN_W,  9), WinSzExp(SCREEN_H,  9)),
		xcout("%d x %d", WinSzExp(SCREEN_W, 10), WinSzExp(SCREEN_H, 10)),
		"フルスクリーン 画面に合わせる",
		"フルスクリーン 縦横比維持",
		"フルスクリーン 黒背景 (推奨)",
		"戻る",
	};

	int selectIndex = 0;

	for(; ; )
	{
		selectIndex = SimpleMenu("ウィンドウサイズ設定", MENU_ITEMS, lengthof(MENU_ITEMS), selectIndex);

		switch(selectIndex)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			SetScreenSize(WinSzExp(SCREEN_W, selectIndex), WinSzExp(SCREEN_H, selectIndex));
			break;

		case 11:
			SetScreenSize(Gnd.MonitorRect.W, Gnd.MonitorRect.H);
			break;

		case 12:
			{
				int w = Gnd.MonitorRect.W;
				int h = (SCREEN_H * Gnd.MonitorRect.W) / SCREEN_W;

				if(Gnd.MonitorRect.H < h)
				{
					h = Gnd.MonitorRect.H;
					w = (SCREEN_W * Gnd.MonitorRect.H) / SCREEN_H;

					errorCase(Gnd.MonitorRect.W < w);
				}
				SetScreenSize(w, h);
			}
			break;

		case 13:
			{
				int w = Gnd.MonitorRect.W;
				int h = (SCREEN_H * Gnd.MonitorRect.W) / SCREEN_W;

				if(Gnd.MonitorRect.H < h)
				{
					h = Gnd.MonitorRect.H;
					w = (SCREEN_W * Gnd.MonitorRect.H) / SCREEN_H;

					errorCase(Gnd.MonitorRect.W < w);
				}
				SetScreenSize(Gnd.MonitorRect.W, Gnd.MonitorRect.H);

				Gnd.RealScreenDraw_L = (Gnd.MonitorRect.W - w) / 2;
				Gnd.RealScreenDraw_T = (Gnd.MonitorRect.H - h) / 2;
				Gnd.RealScreenDraw_W = w;
				Gnd.RealScreenDraw_H = h;
			}
			break;

		case 14:
			goto endLoop;

		default:
			error();
		}
	}
endLoop:
	for(int i = 0; i < lengthof(MENU_ITEMS); i++)
		if(isdigit(*MENU_ITEMS[i]))
			memFree(MENU_ITEMS[i]);
}

// ---- ボリューム ----
/*
	-- e.g.

	static void XXX_BGMVolumeChanged(double volume)
	{
		Gnd.MusicVolume = volume;
		UpdateMusicVolume();
	}
	static void XXX_SEVolumeChanged(double volume)
	{
		Gnd.SEVolume = volume;
		UpdateSEVolume();
	}
	static void XXX_SEVolumePulse(void)
	{
		SEPlay(rndPct(50) ? SE_PAUSE_IN : SE_PAUSE_OUT);
	}

	SimpleVolumeConfig("ＢＧＭ音量", Gnd.MusicVolume, 0, 100, 1, 10, XXX_BGMVolumeChanged);

	SimpleVolumeConfig("ＳＥ音量", Gnd.SEVolume, 0, 100, 1, 10, XXX_SEVolumeChanged, XXX_SEVolumePulse);
*/

static double SVC_ValueToRate(int value, int minval, int valRange)
{
	return (double)(value - minval) / valRange;
}

/*
	(ret, rate): 0.0 - 1.0
	pulse: NULL == 無効
*/
double SimpleVolumeConfig(char *menuTitle, double rate, int minval, int maxval, int valStep, int valFastStep, void (*valChanged)(double), void (*pulse)(void))
{
	const int PULSE_FRM = 60;

	int valRange = maxval - minval;
	int value = minval + d2i(rate * valRange);
	int origval = value;

	SetCurtain();
	FreezeInput();

	for(; ; )
	{
		int chgval = 0;

		if(GetPound(INP_A))
		{
			break;
		}
		if(GetPound(INP_B))
		{
			if(value == origval)
				break;

			value = origval;
			chgval = 1;
		}
		if(GetPound(INP_DIR_8))
		{
			value += valFastStep;
			chgval = 1;
		}
		if(GetPound(INP_DIR_6))
		{
			value += valStep;
			chgval = 1;
		}
		if(GetPound(INP_DIR_4))
		{
			value -= valStep;
			chgval = 1;
		}
		if(GetPound(INP_DIR_2))
		{
			value -= valFastStep;
			chgval = 1;
		}
		if(chgval)
		{
			m_range(value, minval, maxval);
			valChanged(SVC_ValueToRate(value, minval, valRange));
		}
		if(pulse && ProcFrame % PULSE_FRM == 0)
		{
			pulse();
		}

		DrawCurtain();

		if(SimpleMenu_WallColor != -1)
			DrawBox(0, 0, SCREEN_W, SCREEN_H, SimpleMenu_WallColor, 1);

		if(SimpleMenu_WallPicId != -1)
		{
			DrawRect(SimpleMenu_WallPicId, 0, 0, SCREEN_W, SCREEN_H);
			DrawCurtain(SimpleMenu_WallCurtain);
		}
		if(SimpleMenu_Color != -1)
			PE.Color = SimpleMenu_Color;

		if(SimpleMenu_BorderColor != -1)
			PE_Border(SimpleMenu_BorderColor);

		SetPrint(SimpleMenu_X, SimpleMenu_Y, SimpleMenu_YStep);
		Print(menuTitle);
		PrintRet();

		Print_x(xcout("[ %d ]　最小=%d　最大=%d", value, minval, maxval));
		PrintRet();

		Print("★　左＝下げる");
		PrintRet();
		Print("★　右＝上げる");
		PrintRet();
		Print("★　下＝速く下げる");
		PrintRet();
		Print("★　上＝速く上げる");
		PrintRet();
		Print("★　調整が終わったら決定ボタンを押して下さい。");
		PrintRet();

		EachFrame();
	}
	FreezeInput();

	return SVC_ValueToRate(value, minval, valRange);
}
