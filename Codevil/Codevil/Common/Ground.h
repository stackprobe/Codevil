typedef struct Gnd_st
{
	taskList *EL; // EffectList
	int PrimaryPadId; // -1 == ���ݒ�
	SubScreen_t *MainScreen; // NULL == �s�g�p
	iRect_t MonitorRect;

	// app > @ Gnd_t

	// < app

	// SaveData {

	int RealScreen_W;
	int RealScreen_H;

	int RealScreenDraw_L;
	int RealScreenDraw_T;
	int RealScreenDraw_W; // -1 == RealScreenDraw_LTWH �s�g�p
	int RealScreenDraw_H;

	/*
		����
		0.0 - 1.0
		def: DEFAULT_VOLUME
	*/
	double MusicVolume;
	double SEVolume;

	/*
		-1 == ���蓖�ăi�V
		0 - (PAD_BUTTON_MAX - 1) == ���蓖�ă{�^��ID
		def: SNWPB_* ��K���ɔz�u
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
		-1 == ���蓖�ăi�V
		0 - (KEY_MAX - 1) == ���蓖�ăL�[ID
		def: KEY_INPUT_* ��K���ɔz�u
	*/
	struct PadBtnId_st KbdKeyId;

	int RO_MouseDispMode;

	// app > @ Gnd_t SaveData

	// < app

	// } SaveData
}
Gnd_t;

extern Gnd_t Gnd;

void Gnd_INIT(void);
void Gnd_FNLZ(void);

void LoadFromDatFile(void);
void SaveToDatFile(void);

void UnassignAllPadBtnId(void);
void UnassignAllKbdKeyId(void);