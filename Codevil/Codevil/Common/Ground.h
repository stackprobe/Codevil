typedef struct Gnd_st
{
	taskList *EL; // EffectList
	int PrimaryPadId; // -1 == 未設定
	SubScreen_t *MainScreen; // NULL == 不使用
	iRect_t MonitorRect;

	// app > @ Gnd_t

	// < app

	// -- セーブデータ項目 ここから

	int RealScreen_W;
	int RealScreen_H;

	int RealScreenDraw_L;
	int RealScreenDraw_T;
	int RealScreenDraw_W; // -1 == RealScreenDraw_LTWH 不使用
	int RealScreenDraw_H;

	/*
		音量
		0.0 - 1.0
		def: DEFAULT_VOLUME
	*/
	double MusicVolume;
	double SEVolume;

	/*
		-1 == 割り当てナシ
		0 - (PAD_BUTTON_MAX - 1) == 割り当てボタンID
		def: SNWPB_* を適当に配置
	*/
	struct PadBtnId_st
	{
		int Dir_2;
		int Dir_4;
		int Dir_6;
		int Dir_8;
		int A;
		int B;
		int C;
		int D;
		int E;
		int F;
		int L;
		int R;
		int Pause;
		int Start;
	}
	PadBtnId;

	/*
		-1 == 割り当てナシ
		0 - (KEY_MAX - 1) == 割り当てキーID
		def: KEY_INPUT_* を適当に配置
	*/
	struct PadBtnId_st KbdKeyId;

	int RO_MouseDispMode;

	// app > @ Gnd_t SaveData

	// < app

	// -- セーブデータ項目 ここまで
}
Gnd_t;

extern Gnd_t Gnd;

void Gnd_INIT(void);
void Gnd_FNLZ(void);

void LoadFromDatFile(void);
void SaveToDatFile(void);

void UnassignAllPadBtnId(void);
void UnassignAllKbdKeyId(void);
