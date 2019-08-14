extern int IgnoreEscapeKey;

extern __int64 FrameStartTime;
extern __int64 LangolierTime;
extern int FrameProcessingMillis;
extern int ProcFrame;
extern int FreezeInputFrame;
extern int WindowIsActive;

void EachFrame(void);
void FreezeInput(int frame = 1);
