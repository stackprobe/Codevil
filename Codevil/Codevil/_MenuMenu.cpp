#include "all.h"

static void DrawWall(void)
{
	DrawCurtain();
	DrawRect(P_WHITEBOX, 100, 100, SCREEN_W - 200, SCREEN_H - 200);
}
void MainMenu(void)
{
	SetCurtain();
	FreezeInput();

	MusicPlay(MUS_TITLE);

	char *menuItems[] =
	{
		"ゲームスタート",
		"コンテニュー",
		"設定",
		"終了",
	};

	int selectIndex = 0;

	for(; ; )
	{
		switch(selectIndex = KariMenu("Codevil", menuItems, lengthof(menuItems), selectIndex))
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
			goto endMainLoop;

		default:
			error();
		}
	}
endMainLoop:
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
