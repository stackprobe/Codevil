#include "all.h"

int IgnoreEscapeKey;

// ���̃t�@�C������� read only {
__int64 FrameStartTime;
__int64 HzChaserTime;
int FrameProcessingMillis;
int FrameProcessingMillis_Worst;
int FrameProcessingMillis_WorstFrame;
int ProcFrame;
int FreezeInputFrame;
int WindowIsActive;
// }

static void CheckHz(void)
{
	__int64 currTime = GetCurrTime();

	HzChaserTime += 16; // 16.666 ��菬�����̂ŁA60Hz�Ȃ�ǂ�ǂ�����������͂��B
	m_range(HzChaserTime, currTime - 100, currTime + 100);

	while(currTime < HzChaserTime)
	{
		Sleep(1);
		currTime = GetCurrTime();
	}
	FrameStartTime = currTime;
}

void EachFrame(void)
{
	// app > @ enter EachFrame

	// < app

	if(!SEEachFrame())
	{
		MusicEachFrame();
	}
	Gnd.EL->ExecuteAllTask();
	CurtainEachFrame();

	if(Gnd.MainScreen && CurrDrawScreenHandle == GetHandle(Gnd.MainScreen))
	{
		ChangeDrawScreen(DX_SCREEN_BACK);

		if(Gnd.RealScreenDraw_W == -1)
		{
			errorCase(DrawExtendGraph(0, 0, Gnd.RealScreen_W, Gnd.RealScreen_H, GetHandle(Gnd.MainScreen), 0)); // ? ���s
		}
		else
		{
			errorCase(DrawBox(0, 0, Gnd.RealScreen_W, Gnd.RealScreen_H, GetColor(0, 0, 0), 1)); // ? ���s
			errorCase(DrawExtendGraph(
				Gnd.RealScreenDraw_L,
				Gnd.RealScreenDraw_T,
				Gnd.RealScreenDraw_L + Gnd.RealScreenDraw_W,
				Gnd.RealScreenDraw_T + Gnd.RealScreenDraw_H, GetHandle(Gnd.MainScreen), 0)); // ? ���s
		}
	}

	// app > @ before ScreenFlip

	// < app

	FrameProcessingMillis = (int)(GetCurrTime() - FrameStartTime);

	if(FrameProcessingMillis_Worst < FrameProcessingMillis || !m_countDown(FrameProcessingMillis_WorstFrame))
	{
		FrameProcessingMillis_Worst = FrameProcessingMillis;
		FrameProcessingMillis_WorstFrame = 120;
	}

	// DxLib >

	ScreenFlip();

	if(!IgnoreEscapeKey && CheckHitKey(KEY_INPUT_ESCAPE) == 1 || ProcessMessage() == -1)
	{
		EndProc();
	}

	// < DxLib

	// app > @ after ScreenFlip

	// < app

	CheckHz();

	ProcFrame++;
	errorCase(IMAX < ProcFrame); // 192.9�����x�ŃJ���X�g
	m_countDown(FreezeInputFrame);
	WindowIsActive = IsWindowActive();

	PadEachFrame();
	KeyEachFrame();
	InputEachFrame();
	MouseEachFrame();

	if(Gnd.RealScreen_W != SCREEN_W || Gnd.RealScreen_H != SCREEN_H || Gnd.RealScreenDraw_W == -1)
	{
		if(!Gnd.MainScreen)
			Gnd.MainScreen = CreateSubScreen(SCREEN_W, SCREEN_H);

		ChangeDrawScreen(Gnd.MainScreen);
	}
	else
	{
		if(Gnd.MainScreen)
		{
			ReleaseSubScreen(Gnd.MainScreen);
			Gnd.MainScreen = NULL;
		}
	}

	// app > @ leave EachFrame

	// < app
}
void FreezeInput(int frame) // frame: 1 == ���̃t���[���̂�, 2 == ���̃t���[���Ǝ��̃t���[�� ...
{
	errorCase(frame < 1 || IMAX < frame);

	m_maxim(FreezeInputFrame, frame); // frame ��蒷���t���[���������ɐݒ肳��Ă�����A�������D�悷��B
}
