#include "all.h"

static char *GetVersionString(void)
{
	const char *CONCERT_PTN = "{a9a54906-791d-4e1a-8a71-a4c69359cf68}:0.00"; // shared_uuid@g
	return (char *)strchr(CONCERT_PTN, ':') + 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetApplicationLogSaveDirectory("C:\\tmp");
	SetOutApplicationLogValidFlag(1);
	SetAlwaysRunFlag(1);

	{
		static char tmp[100];
		sprintf(tmp, "Codevil %s", GetVersionString());
		SetMainWindowText(tmp);
	}

	SetGraphMode(800, 600, 32);
	ChangeWindowMode(1);
	SetWindowIconID(333); // see Resource.rc

	if(DxLib_Init()) // ? Ž¸”s
	{
		return 1;
	}

	SetMouseDispFlag(0);
	SetWindowSizeChangeEnableFlag(1);
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	if(DxLib_End()) // ? Ž¸”s
	{
		return 1;
	}
}
