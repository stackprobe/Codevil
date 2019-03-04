#include "all.h"

static char *GetVersionString(void)
{
	const char *CONCERT_PTN = "{a9a54906-791d-4e1a-8a71-a4c69359cf68}:0.00"; // shared_uuid@g
	return (char *)strchr(CONCERT_PTN, ':') + 1;
}

int ProcMtxHdl;
int DxLibInited;

int Monitor_L;
int Monitor_T;
int Monitor_W;
int Monitor_H;

static void ReleaseProcMtxHdl(void)
{
	mutexRelease(ProcMtxHdl);
	handleClose(ProcMtxHdl);
}
static void PostSetScreenSize(int w, int h)
{
	if(Monitor_W == w && Monitor_H == h)
	{
		SetScreenPosition(Monitor_L, Monitor_T);
	}
}
void EndProc(void)
{
	GetEndProcFinalizers()->Flush();

	ExportSaveData();
	ReleaseAllFontHandle(); // Finalizers �� RemoveAllFontFile() �������Ă���BEndProcFinalizers ����Ȃ��̂ŁA�����ŗǂ��I
	Gnd_FNLZ();

	if(DxLibInited)
	{
		DxLibInited = 0;
		errorCase(DxLib_End()); // ? ���s
	}
	termination();
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	memAlloc_INIT();

	/*
		APP_TEMP_DIR_UUID �� shared_uuid
	*/
	{
		ProcMtxHdl = mutexOpen("{c808da96-120f-4de5-846a-8c1c120b4a69}"); // shared_uuid@g -- �S�Q�[�������v���C�֎~�̂��߁A@g(global)�w��

		if(!waitForMillis(ProcMtxHdl, 0))
		{
			handleClose(ProcMtxHdl);
			return 0;
		}
		GetFinalizers()->AddFunc(ReleaseProcMtxHdl);
	}

	initRnd((int)time(NULL));

	if(argIs("/L"))
	{
		termination(LOG_ENABLED ? 1 : 0);
	}

	Gnd_INIT();
	ImportSaveData();
	ImportConfig();

	// DxLib >

#if LOG_ENABLED
	SetApplicationLogSaveDirectory("C:\\tmp");
#endif
	SetOutApplicationLogValidFlag(LOG_ENABLED); // DxLib �̃��O���o�� 1: ���� 0: ���Ȃ�

	SetAlwaysRunFlag(1); // ? ��A�N�e�B�u���� 1: ���� 0: �~�܂�

	SetMainWindowText(xcout(
#if LOG_ENABLED
		"(LOG_ENABLED, DEBUGGING_MODE) %s %s"
#else
		GetDatString(DATSTR_PCT_S_SPC_PCT_S)//"%s %s"
#endif
		,GetDatString(DATSTR_APPNAME)
		,GetVersionString()
		));

//	SetGraphMode(SCREEN_W, SCREEN_H, 32);
	SetGraphMode(Gnd.RealScreen_W, Gnd.RealScreen_H, 32);
	ChangeWindowMode(1); // 1: �E�B���h�E 0: �t���X�N���[��

//	SetFullSceneAntiAliasingMode(4, 2); // �K���Ȓl���������B�t���X�N���[���p�~�����̂ŕs�v

	SetWindowIconID(333); // �E�B���h�E����̃A�C�R��

	if(Conf_DisplayIndex != -1)
		SetUseDirectDrawDeviceIndex(Conf_DisplayIndex);

	errorCase(DxLib_Init()); // ? ���s

	DxLibInited = 1;

	SetMouseDispMode(Gnd.RO_MouseDispMode); // ? �}�E�X��\�� 1: ���� 0: ���Ȃ�
	SetWindowSizeChangeEnableFlag(0); // �E�B���h�E�̉E�����h���b�O�ŐL�k 1: ���� 0: ���Ȃ�

	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawMode(DX_DRAWMODE_BILINEAR); // ������f�t�H���g�Ƃ���B

	// < DxLib

	// *_Reset
	{
		DPE_Reset();
		CEE_Reset();
		PE_Reset();
	}

	GetDefaultState(&Monitor_W, &Monitor_H, NULL, NULL, &Monitor_L, &Monitor_T);

	errorCase(!m_isRange(Monitor_W, 1, IMAX));
	errorCase(!m_isRange(Monitor_H, 1, IMAX));
	errorCase(!m_isRange(Monitor_L, -IMAX, IMAX));
	errorCase(!m_isRange(Monitor_T, -IMAX, IMAX));

	PostSetScreenSize(Gnd.RealScreen_W, Gnd.RealScreen_H);

#if LOG_ENABLED // ���̊m�F
	{
		char *b = na(char, 32);
		int s = 32;
		aes128_decrypt_extend(b, s, 1);
		memFree(b);
	}
#endif

	// app > @ INIT

	AddFontFile(ETC_FONT_RIIT, "RiiT_F.otf");
	AddFontFile(ETC_FONT_GENKAI_MINCHO, "genkai-mincho.ttf");

	// < app

	LOGPOS();
	ProcMain();
	LOGPOS();

	EndProc();
	return 0; // dummy
}

// DxPrv_ >

static int DxPrv_GetMouseDispMode(void)
{
	return GetMouseDispFlag() ? 1 : 0;
}
static void DxPrv_SetMouseDispMode(int mode)
{
	SetMouseDispFlag(mode ? 1 : 0);
}
static void UnloadGraph(int &hdl)
{
	if(hdl != -1)
	{
		errorCase(DeleteGraph(hdl)); // ? ���s
		hdl = -1;
	}
}
static void DxPrv_SetScreenSize(int w, int h)
{
	int mdm = GetMouseDispMode();

	UnloadAllPicResHandle();
	UnloadAllSubScreenHandle();
	ReleaseAllFontHandle();

	errorCase(SetGraphMode(w, h, 32) != DX_CHANGESCREEN_OK); // ? ���s

	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	SetMouseDispMode(mdm);
}

// < DxPrv_

int GetMouseDispMode(void)
{
	return DxPrv_GetMouseDispMode();
}
void SetMouseDispMode(int mode)
{
	DxPrv_SetMouseDispMode(mode);
}
void ApplyScreenSize(void)
{
	DxPrv_SetScreenSize(Gnd.RealScreen_W, Gnd.RealScreen_H);
}
void SetScreenSize(int w, int h)
{
	m_range(w, SCREEN_W, SCREEN_W_MAX);
	m_range(h, SCREEN_H, SCREEN_H_MAX);

	if(Gnd.RealScreen_W != w || Gnd.RealScreen_H != h)
	{
		Gnd.RealScreen_W = w;
		Gnd.RealScreen_H = h;

		ApplyScreenSize();

		PostSetScreenSize(w, h);
	}
}
void SetScreenPosition(int l, int t)
{
	SetWindowPosition(l, t);

	POINT p;

	p.x = 0;
	p.y = 0;

	ClientToScreen(GetMainWindowHandle(), &p);

	int pToTrgX = l - (int)p.x;
	int pToTrgY = t - (int)p.y;

	SetWindowPosition(l + pToTrgX, t + pToTrgY);
}