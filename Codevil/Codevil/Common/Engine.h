extern int IgnoreEscapeKey;

extern __int64 FrameStartTime;
extern __int64 HzChaserTime;
extern int FrameProcessingMillis;
extern int FrameProcessingMillis_Worst;
extern int FrameProcessingMillis_WorstFrame;
extern int ProcFrame;
extern int FreezeInputFrame;
extern int WindowIsActive;

void EachFrame(void);
void FreezeInput(int frame = 1);
