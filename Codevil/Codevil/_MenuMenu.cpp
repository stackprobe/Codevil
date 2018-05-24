#include "all.h"

static void DrawWall(void)
{
	DrawCurtain();
	DrawRect(P_WHITEBOX, 100, 100, SCREEN_W - 200, SCREEN_H - 200);
}
static void SettingMenu(void)
{
	char *MENU_ITEMS[] =
	{
		"",
		"",
		"",
	};
	int selectIndex = 0;

	// TODO
	// TODO
	// TODO
}
void MainMenu(void)
{
	SetCurtain();
	FreezeInput();

	MusicPlay(MUS_TITLE);

	char *MENU_ITEMS[] =
	{
		"ゲームスタート",
		"コンテニュー",
		"DEBUG_TEST",
		"設定",
		"終了",
	};
	int selectIndex = 0;

	for(; ; )
	{
		selectIndex = KariMenu("Codevil", MENU_ITEMS, lengthof(MENU_ITEMS), selectIndex);

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
