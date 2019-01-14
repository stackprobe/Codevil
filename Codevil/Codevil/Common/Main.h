extern int ProcMtxHdl;
extern int DxLibInited;

extern int Monitor_L;
extern int Monitor_T;
extern int Monitor_W;
extern int Monitor_H;

void EndProc(void);
void ProcMain(void); // external

int GetMouseDispMode(void);
void SetMouseDispMode(int mode);
void ApplyScreenSize(void);
void SetScreenSize(int w, int h);
void SetScreenPosition(int l, int t);
