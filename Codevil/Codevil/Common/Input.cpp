/*
	nフレーム間ボタンを押すと ... 0, 0, 0... 0, 1, 2... (n-2), (n-1), n, -1, 0, 0, 0... となる。

	FreezeInput()により途中スキップすることがあるので、
	常に1ずつ増えるとか、(-1)の直前は常に1以上とか、最後は常に(-1)になるとか想定するのは危険！

	... 0, 0, 0, 1, 2, 0, 4, 5, -1, 0, 0, 0...
	                   ^
	              FreezeInput();

	... 0, 0, 0, 1, 2, 3, 4, 0, -1, 0, 0, 0...
	                         ^
	                    FreezeInput();

	... 0, 0, 0, 1, 2, 3, 4, 5, 0, 0, 0, 0...
	                            ^
	                       FreezeInput();
*/

#include "all.h"

static int InputStatus[INP_MAX];

static void MixInput(int inpId, int keyId, int btnId)
{
	int freezeInputFrame_BKUP = FreezeInputFrame;
	FreezeInputFrame = 0;

	int keyDown = 1 <= GetKeyInput(keyId);
	int btnDown = 1 <= GetPadInput(Gnd.PrimaryPadId, btnId);

	FreezeInputFrame = freezeInputFrame_BKUP;

	updateInput(InputStatus[inpId], keyDown || btnDown);
}
void InputEachFrame(void)
{
	MixInput(INP_DIR_2, Gnd.KbdKeyId.Dir_2, Gnd.PadBtnId.Dir_2);
	MixInput(INP_DIR_4, Gnd.KbdKeyId.Dir_4, Gnd.PadBtnId.Dir_4);
	MixInput(INP_DIR_6, Gnd.KbdKeyId.Dir_6, Gnd.PadBtnId.Dir_6);
	MixInput(INP_DIR_8, Gnd.KbdKeyId.Dir_8, Gnd.PadBtnId.Dir_8);
	MixInput(INP_A, Gnd.KbdKeyId.A, Gnd.PadBtnId.A);
	MixInput(INP_B, Gnd.KbdKeyId.B, Gnd.PadBtnId.B);
	MixInput(INP_C, Gnd.KbdKeyId.C, Gnd.PadBtnId.C);
	MixInput(INP_D, Gnd.KbdKeyId.D, Gnd.PadBtnId.D);
	MixInput(INP_E, Gnd.KbdKeyId.E, Gnd.PadBtnId.E);
	MixInput(INP_F, Gnd.KbdKeyId.F, Gnd.PadBtnId.F);
	MixInput(INP_L, Gnd.KbdKeyId.L, Gnd.PadBtnId.L);
	MixInput(INP_R, Gnd.KbdKeyId.R, Gnd.PadBtnId.R);
	MixInput(INP_PAUSE, Gnd.KbdKeyId.Pause, Gnd.PadBtnId.Pause);
	MixInput(INP_START, Gnd.KbdKeyId.Start, Gnd.PadBtnId.Start);
}
int GetInput(int inpId)
{
	errorCase(inpId < 0 || INP_MAX <= inpId);

	return FreezeInputFrame ? 0 : InputStatus[inpId];
}
int GetPound(int inpId)
{
	errorCase(inpId < 0 || INP_MAX <= inpId);

	return FreezeInputFrame ? 0 : isPound(InputStatus[inpId]);
}
