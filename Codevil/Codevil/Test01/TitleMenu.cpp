// smpl
#include "all.h"

static void DrawWall(void)
{
	DrawCurtain();
//	DrawRect(P_WHITEBOX, 100, 100, SCREEN_W - 200, SCREEN_H - 200);
	DrawRect(P_TITLE_WALL, 0, 0, SCREEN_W, SCREEN_H);
}

static void LeaveTitleMenu(void)
{
	MusicFade();
	SetCurtain(30, -1.0);
}
static void ReturnTitleMenu(void)
{
	MusicPlay(MUS_TITLE);
}

static void BGMVolumeChanged(double volume)
{
	Gnd.MusicVolume = volume;
	UpdateMusicVolume();
}
static void SEVolumeChanged(double volume)
{
	Gnd.SEVolume = volume;
	UpdateSEVolume();
}
static void SEVolumePulse(void)
{
	SEPlay(rndPct(50) ? SE_PAUSE_IN : SE_PAUSE_OUT);
}
static void SettingMenu(void)
{
	SetCurtain();
	FreezeInput();

	char *MENU_ITEMS[] =
	{
		"�p�b�h�̃{�^���ݒ�",
		"�E�B���h�E�T�C�Y�ύX",
		"�a�f�l����",
		"�r�d����",
		"�߂�",
	};
	int selectIndex = 0;

	for(; ; )
	{
		selectIndex = SimpleMenu("�ݒ�", MENU_ITEMS, lengthof(MENU_ITEMS), selectIndex);

		switch(selectIndex)
		{
		case 0:
			SimplePadConfig();
			break;

		case 1:
			SimpleWindowSizeConfig();
			break;

		case 2:
			SimpleVolumeConfig("�a�f�l����", Gnd.MusicVolume, 0, 100, 1, 10, BGMVolumeChanged); 
			break;

		case 3:
			SimpleVolumeConfig("�r�d����", Gnd.SEVolume, 0, 100, 1, 10, SEVolumeChanged, SEVolumePulse); 
			break;

		case 4:
			goto endMenu;

		default:
			error();
		}
	}
endMenu:
	FreezeInput();
}
void TitleMenu(void)
{
	SetCurtain();
	FreezeInput();

	MusicPlay(MUS_TITLE);

	char *MENU_ITEMS[] =
	{
		"�Q�[���X�^�[�g",
		"�R���e�j���[�H",
		"�ݒ�",
		"�I��",
	};
	int selectIndex = 0;

//	SimpleMenu_WallColor = GetColor(0, 0, 64); // test
	SimpleMenu_WallPicId = P_TITLE_WALL;

	for(; ; )
	{
		selectIndex = SimpleMenu("Codevil", MENU_ITEMS, lengthof(MENU_ITEMS), selectIndex);

		switch(selectIndex)
		{
		case 0:
			LeaveTitleMenu();
			GameInit();
			GameMain();
			GameFnlz();
			ReturnTitleMenu();
			break;

		case 1:
			// TODO
			break;

		case 2:
			SettingMenu();
			break;

		case 3:
			goto endMenu;

		default:
			error();
		}
	}
endMenu:
	FreezeInput();
	MusicFade();
	SetCurtain(30, -1.0);

	forscene(40)
	{
		DrawWall();
		EachFrame();
	}
	sceneLeave();
}
