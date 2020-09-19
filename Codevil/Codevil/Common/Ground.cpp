#include "all.h"

Gnd_t Gnd;

void Gnd_INIT(void)
{
	memset(&Gnd, 0x00, sizeof(Gnd_t));

	Gnd.EL = new taskList();
	Gnd.PrimaryPadId = -1;

	// app > @ Gnd_INIT

	// < app

	// SaveData -->

	Gnd.RealScreen_W = SCREEN_W;
	Gnd.RealScreen_H = SCREEN_H;

	Gnd.RealScreenDraw_W = -1;

	Gnd.MusicVolume = DEFAULT_VOLUME;
	Gnd.SEVolume = DEFAULT_VOLUME;

	Gnd.PadBtnId.Dir_2 = SNWPB_DIR_2;
	Gnd.PadBtnId.Dir_4 = SNWPB_DIR_4;
	Gnd.PadBtnId.Dir_6 = SNWPB_DIR_6;
	Gnd.PadBtnId.Dir_8 = SNWPB_DIR_8;
	Gnd.PadBtnId.A = SNWPB_A1;
	Gnd.PadBtnId.B = SNWPB_B1;
	Gnd.PadBtnId.C = SNWPB_A2;
	Gnd.PadBtnId.D = SNWPB_B2;
	Gnd.PadBtnId.E = SNWPB_A3;
	Gnd.PadBtnId.F = SNWPB_B3;
	Gnd.PadBtnId.L = SNWPB_L;
	Gnd.PadBtnId.R = SNWPB_R;
	Gnd.PadBtnId.Pause = SNWPB_DSTART;
	Gnd.PadBtnId.Start = SNWPB_USTART;

	Gnd.KbdKeyId.Dir_2 = KEY_INPUT_DOWN;
	Gnd.KbdKeyId.Dir_4 = KEY_INPUT_LEFT;
	Gnd.KbdKeyId.Dir_6 = KEY_INPUT_RIGHT;
	Gnd.KbdKeyId.Dir_8 = KEY_INPUT_UP;
	Gnd.KbdKeyId.A = KEY_INPUT_Z;
	Gnd.KbdKeyId.B = KEY_INPUT_X;
	Gnd.KbdKeyId.C = KEY_INPUT_C;
	Gnd.KbdKeyId.D = KEY_INPUT_V;
	Gnd.KbdKeyId.E = KEY_INPUT_A;
	Gnd.KbdKeyId.F = KEY_INPUT_S;
	Gnd.KbdKeyId.L = KEY_INPUT_D;
	Gnd.KbdKeyId.R = KEY_INPUT_F;
	Gnd.KbdKeyId.Pause = KEY_INPUT_SPACE;
	Gnd.KbdKeyId.Start = KEY_INPUT_RETURN;

	Gnd.RO_MouseDispMode = 0;

	// app > @ Gnd_INIT SaveData

	// memo: リビルドすると SaveData.dat は無視(削除)される。

//	Gnd.RO_MouseDispMode = 1;

	// < app
}
void Gnd_FNLZ(void)
{
LOGPOS(); // test
	delete Gnd.EL;

	// app > @ Gnd_FNLZ

	// < app

	// SaveData -->

	// app > @ Gnd_FNLZ SaveData

	// < app
}

// ---- SaveData ----

#define SAVE_FILE "SaveData.dat"
#define SAVEDATA_SIGNATURE "__Codevil__SaveData " __DATE__ " " __TIME__

static autoList<uchar> *SaveData;
static int SDIndex;

static char *SD_ReadLine(void) // ret: bind
{
	static char *line;

	memFree(line);
	line = readLine(SaveData, SDIndex);

	if(!line)
		line = strx("");

	return line;
}
static int SD_ReadBoolean(void)
{
	return atoi(SD_ReadLine()) ? 1 : 0;
}
static int SD_ReadInt(int minval = -IMAX, int maxval = IMAX)
{
	int value = atoi(SD_ReadLine());
	m_range(value, minval, maxval);
	return value;
}
static __int64 SD_ReadInt64(__int64 minval = -IMAX_64, __int64 maxval = IMAX_64)
{
	__int64 value = _atoi64(SD_ReadLine());
	m_range(value, minval, maxval);
	return value;
}
static double SD_ReadDouble(double minval, double maxval, int denom)
{
	errorCase(denom < 1);

	double value = (double)atoi(SD_ReadLine()) / denom;
	m_range(value, minval, maxval);
	return value;
}
static void SD_ReadBitList(bitList *dest)
{
	dest->Clear();

	char *line = SD_ReadLine();

	for(int index = 0; line[index]; index++)
	{
		switch(line[index])
		{
		case '0':
//			dest->PutBit(index, 0); // 不要
			break;

		case '1':
			dest->PutBit(index, 1);
			break;

		default:
			error();
		}
	}
}
static void SD_ReadLines(autoList<char *> *lines)
{
	errorCase(!lines);

	int count = SD_ReadInt(0, IMAX);

	lines->BufferExtend(count);

	for(int index = 0; index < count; index++)
	{
		lines->AddElement(strx(SD_ReadLine()));
	}
}

static void SD_WriteLine(char *line)
{
	writeLine(SaveData, line);
}
static void SD_WriteLine_x(char *line)
{
	SD_WriteLine(line);
	memFree(line);
}
static void SD_WriteInt(int value)
{
	SD_WriteLine_x(xcout("%d", value));
}
static void SD_WriteInt64(__int64 value)
{
	SD_WriteLine_x(xcout("%I64d", value));
}
static void SD_WriteDouble(double value, int denom)
{
	SD_WriteInt(d2i(value * denom));
}
static void SD_WriteBitList(bitList *src)
{
	autoList<char> *buff = new autoList<char>();
	int finalBitPos = src->GetFinalBitPos();

	for(int index = 0; index <= finalBitPos; index++)
	{
		buff->AddElement(src->RefBit(index) ? '1' : '0');
	}
	SD_WriteLine_x(unbindBlock2Line(buff));
}
static void SD_WriteLines(autoList<char *> *lines)
{
	SD_WriteInt(lines->GetCount());

	for(int index = 0; index < lines->GetCount(); index++)
	{
		SD_WriteLine(lines->GetElement(index));
	}
}
static void SD_WriteLines_x(autoList<char *> *lines)
{
	SD_WriteLines(lines);
	releaseList(lines, (void (*)(char *))memFree);
}

// パッド
static int *PPadBtns[] =
{
	&Gnd.PadBtnId.Dir_8,
	&Gnd.PadBtnId.Dir_2,
	&Gnd.PadBtnId.Dir_4,
	&Gnd.PadBtnId.Dir_6,
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
static void AntiPadBtnIdConflict(void)
{
	/*
		重複して割り当てられていた場合、両方 -1 にする。
	*/
	for(int index = 1; index < lengthof(PPadBtns); index++)
	{
		for(int ndx = 0; ndx < index; ndx++)
		{
			if(*PPadBtns[index] == *PPadBtns[ndx])
			{
				*PPadBtns[index] = -1;
				*PPadBtns[ndx] = -1;
				break;
			}
		}
	}
}
void UnassignAllPadBtnId(void)
{
	/*
		全て割り当てナシにする。
	*/
	for(int index = 0; index < lengthof(PPadBtns); index++)
	{
		*PPadBtns[index] = -1;
	}
}

// キーボード
static int *PKbdKeys[] =
{
	&Gnd.KbdKeyId.Dir_8,
	&Gnd.KbdKeyId.Dir_2,
	&Gnd.KbdKeyId.Dir_4,
	&Gnd.KbdKeyId.Dir_6,
	&Gnd.KbdKeyId.A,
	&Gnd.KbdKeyId.B,
	&Gnd.KbdKeyId.C,
	&Gnd.KbdKeyId.D,
	&Gnd.KbdKeyId.E,
	&Gnd.KbdKeyId.F,
	&Gnd.KbdKeyId.L,
	&Gnd.KbdKeyId.R,
	&Gnd.KbdKeyId.Pause,
	&Gnd.KbdKeyId.Start,
};
static void AntiKbdKeyIdConflict(void)
{
	/*
		重複して割り当てられていた場合、両方 -1 にする。
	*/
	for(int index = 1; index < lengthof(PKbdKeys); index++)
	{
		for(int ndx = 0; ndx < index; ndx++)
		{
			if(*PKbdKeys[index] == *PKbdKeys[ndx])
			{
				*PKbdKeys[index] = -1;
				*PKbdKeys[ndx] = -1;
				break;
			}
		}
	}
}
void UnassignAllKbdKeyId(void)
{
	/*
		全て割り当てナシにする。
	*/
	for(int index = 0; index < lengthof(PKbdKeys); index++)
	{
		*PKbdKeys[index] = -1;
	}
}

void LoadFromDatFile(void)
{
	if(!accessible(SAVE_FILE))
	{
		LOG("セーブデータファイル無し\n");
		return;
	}
	SaveData = readAllBytes(SAVE_FILE);

#if LOG_ENABLED == 0
	if(!Jammer(SaveData, 0)) // ? セーブデータ破損
	{
		delete SaveData;
		return;
	}
#endif
	SDIndex = 0;

	if(strcmp(SD_ReadLine(), SAVEDATA_SIGNATURE) != 0) // ? セーブデータ破損
	{
		LOG("セーブデータファイル_Signature不一致\n");
		delete SaveData;
		return;
	}

	// -- セーブデータ項目 ここから

	Gnd.RealScreen_W = SD_ReadInt(SCREEN_W, SCREEN_W_MAX);
	Gnd.RealScreen_H = SD_ReadInt(SCREEN_H, SCREEN_H_MAX);

	Gnd.RealScreenDraw_L = SD_ReadInt();
	Gnd.RealScreenDraw_T = SD_ReadInt();
	Gnd.RealScreenDraw_W = SD_ReadInt();
	Gnd.RealScreenDraw_H = SD_ReadInt();

	Gnd.MusicVolume = SD_ReadDouble(0.0, 1.0, IMAX);
	Gnd.SEVolume = SD_ReadDouble(0.0, 1.0, IMAX);

	Gnd.PadBtnId.Dir_2 = SD_ReadInt(-1, PAD_BUTTON_MAX - 1);
	Gnd.PadBtnId.Dir_4 = SD_ReadInt(-1, PAD_BUTTON_MAX - 1);
	Gnd.PadBtnId.Dir_6 = SD_ReadInt(-1, PAD_BUTTON_MAX - 1);
	Gnd.PadBtnId.Dir_8 = SD_ReadInt(-1, PAD_BUTTON_MAX - 1);
	Gnd.PadBtnId.A = SD_ReadInt(-1, PAD_BUTTON_MAX - 1);
	Gnd.PadBtnId.B = SD_ReadInt(-1, PAD_BUTTON_MAX - 1);
	Gnd.PadBtnId.C = SD_ReadInt(-1, PAD_BUTTON_MAX - 1);
	Gnd.PadBtnId.D = SD_ReadInt(-1, PAD_BUTTON_MAX - 1);
	Gnd.PadBtnId.E = SD_ReadInt(-1, PAD_BUTTON_MAX - 1);
	Gnd.PadBtnId.F = SD_ReadInt(-1, PAD_BUTTON_MAX - 1);
	Gnd.PadBtnId.L = SD_ReadInt(-1, PAD_BUTTON_MAX - 1);
	Gnd.PadBtnId.R = SD_ReadInt(-1, PAD_BUTTON_MAX - 1);
	Gnd.PadBtnId.Pause = SD_ReadInt(-1, PAD_BUTTON_MAX - 1);
	Gnd.PadBtnId.Start = SD_ReadInt(-1, PAD_BUTTON_MAX - 1);

	Gnd.KbdKeyId.Dir_2 = SD_ReadInt(-1, KEY_MAX - 1);
	Gnd.KbdKeyId.Dir_4 = SD_ReadInt(-1, KEY_MAX - 1);
	Gnd.KbdKeyId.Dir_6 = SD_ReadInt(-1, KEY_MAX - 1);
	Gnd.KbdKeyId.Dir_8 = SD_ReadInt(-1, KEY_MAX - 1);
	Gnd.KbdKeyId.A = SD_ReadInt(-1, KEY_MAX - 1);
	Gnd.KbdKeyId.B = SD_ReadInt(-1, KEY_MAX - 1);
	Gnd.KbdKeyId.C = SD_ReadInt(-1, KEY_MAX - 1);
	Gnd.KbdKeyId.D = SD_ReadInt(-1, KEY_MAX - 1);
	Gnd.KbdKeyId.E = SD_ReadInt(-1, KEY_MAX - 1);
	Gnd.KbdKeyId.F = SD_ReadInt(-1, KEY_MAX - 1);
	Gnd.KbdKeyId.L = SD_ReadInt(-1, KEY_MAX - 1);
	Gnd.KbdKeyId.R = SD_ReadInt(-1, KEY_MAX - 1);
	Gnd.KbdKeyId.Pause = SD_ReadInt(-1, KEY_MAX - 1);
	Gnd.KbdKeyId.Start = SD_ReadInt(-1, KEY_MAX - 1);

	Gnd.RO_MouseDispMode = SD_ReadBoolean();

	// app > @ LoadFromDatFile

	// < app

	// -- セーブデータ項目 ここまで

	delete SaveData;

	// app > @ LoadFromDatFile data loaded

	AntiPadBtnIdConflict();
//	AntiKbdKeyIdConflict();

	// < app
}
void SaveToDatFile(void)
{
	SaveData = new autoList<uchar>();

	SD_WriteLine(SAVEDATA_SIGNATURE);

	// -- セーブデータ項目 ここから

	SD_WriteInt(Gnd.RealScreen_W);
	SD_WriteInt(Gnd.RealScreen_H);

	SD_WriteInt(Gnd.RealScreenDraw_L);
	SD_WriteInt(Gnd.RealScreenDraw_T);
	SD_WriteInt(Gnd.RealScreenDraw_W);
	SD_WriteInt(Gnd.RealScreenDraw_H);

	SD_WriteDouble(Gnd.MusicVolume, IMAX);
	SD_WriteDouble(Gnd.SEVolume, IMAX);

	SD_WriteInt(Gnd.PadBtnId.Dir_2);
	SD_WriteInt(Gnd.PadBtnId.Dir_4);
	SD_WriteInt(Gnd.PadBtnId.Dir_6);
	SD_WriteInt(Gnd.PadBtnId.Dir_8);
	SD_WriteInt(Gnd.PadBtnId.A);
	SD_WriteInt(Gnd.PadBtnId.B);
	SD_WriteInt(Gnd.PadBtnId.C);
	SD_WriteInt(Gnd.PadBtnId.D);
	SD_WriteInt(Gnd.PadBtnId.E);
	SD_WriteInt(Gnd.PadBtnId.F);
	SD_WriteInt(Gnd.PadBtnId.L);
	SD_WriteInt(Gnd.PadBtnId.R);
	SD_WriteInt(Gnd.PadBtnId.Pause);
	SD_WriteInt(Gnd.PadBtnId.Start);

	SD_WriteInt(Gnd.KbdKeyId.Dir_2);
	SD_WriteInt(Gnd.KbdKeyId.Dir_4);
	SD_WriteInt(Gnd.KbdKeyId.Dir_6);
	SD_WriteInt(Gnd.KbdKeyId.Dir_8);
	SD_WriteInt(Gnd.KbdKeyId.A);
	SD_WriteInt(Gnd.KbdKeyId.B);
	SD_WriteInt(Gnd.KbdKeyId.C);
	SD_WriteInt(Gnd.KbdKeyId.D);
	SD_WriteInt(Gnd.KbdKeyId.E);
	SD_WriteInt(Gnd.KbdKeyId.F);
	SD_WriteInt(Gnd.KbdKeyId.L);
	SD_WriteInt(Gnd.KbdKeyId.R);
	SD_WriteInt(Gnd.KbdKeyId.Pause);
	SD_WriteInt(Gnd.KbdKeyId.Start);

	SD_WriteInt(GetMouseDispMode());

	// app > @ SaveToDatFile

	// < app

	// -- セーブデータ項目 ここまで

#if LOG_ENABLED == 0
	errorCase(!Jammer(SaveData, 1));
#endif

	writeAllBytes_cx(SAVE_FILE, SaveData);
}
