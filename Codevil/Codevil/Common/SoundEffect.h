enum
{
	SE_DUMMY,

	// app > @ SE_

	SE_PAUSE_IN,
	SE_PAUSE_OUT,

	// < app

	SE_MAX, // num of member
};

#define SE_HANDLE_MAX 64

typedef struct SEInfo_st
{
	int HandleList[SE_HANDLE_MAX];
	int HandleIndex;
	double Volume; // 0.0 - 1.0, def: 0.5
	int AlterCommand;
}
SEInfo_t;

int SEEachFrame(void);
void SEPlay(int seId);
void SEStop(int seId);
void UpdateSEVolume(void);
