#include "all.h"

static void DrawWall(void)
{
	DrawCurtain();
	DrawRect(P_WHITEBOX, 100, 100, SCREEN_W - 200, SCREEN_H - 200);
}
static void SM_BGMVolumeChanged(double volume)
{
	Gnd.MusicVolume = volume;
	UpdateMusicVolume();
}
static void SM_SEVolumeChanged(double volume)
{
	Gnd.SEVolume = volume;
	UpdateSEVolume();
}
static void SM_SEVolumePulse(void)
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
		selectIndex = SmplMenu("�ݒ�", MENU_ITEMS, lengthof(MENU_ITEMS), selectIndex);

		switch(selectIndex)
		{
		case 0:
			SmplPadConfig();
			break;

		case 1:
			SmplWindowSizeConfig();
			break;

		case 2:
			SmplVolumeConfig("�a�f�l����", Gnd.MusicVolume, 0, 100, 1, 10, SM_BGMVolumeChanged); 
			break;

		case 3:
			SmplVolumeConfig("�r�d����", Gnd.SEVolume, 0, 100, 1, 10, SM_SEVolumeChanged, SM_SEVolumePulse); 
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
		"�R���e�j���[",
		"DEBUG_TEST",
		"�ݒ�",
		"�I��",
	};
	int selectIndex = 0;

	for(; ; )
	{
		selectIndex = SmplMenu("Codevil", MENU_ITEMS, lengthof(MENU_ITEMS), selectIndex);

		switch(selectIndex)
		{
		case 0:
			// TODO
			break;

		case 1:
			// TODO
			break;

		case 2:
			// TODO
			break;

		case 3:
			SettingMenu();
			break;

		case 4:
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
