typedef struct DrawPicExtra_st
{
	taskList *TL;
	resCluster<PicInfo_t *> *PicRes;
	int BlendInvOn;
	int MosaicOn;
	int IntPosOn;
	int IgnoreError;

	// change by DPE_*() -->

	double A;
	int AlphaOn;
	int BlendAddOn;
	double R;
	double G;
	double B;
	int BrightOn;
	int GraphicHandleFlag;
	i2D_t GraphicSize; // GraphicHandleFlag != 0 �̂Ƃ� DrawCenter(), DrawBegin() �ŕK�v�B
}
DrawPicExtra_t;

extern DrawPicExtra_t DPE;

void DrawFree(int picId, double ltx, double lty, double rtx, double rty, double rbx, double rby, double lbx, double lby);
void DrawRect_LTRB(int picId, double l, double t, double r, double b);
void DrawRect(int picId, double l, double t, double w, double h);
void DrawSimple(int picId, double x, double y);
void DrawCenter(int picId, double x, double y);

// DrawBegin �` DrawEnd >

void DrawBeginRect_LTRB(int picId, double l, double t, double r, double b);
void DrawBeginRect(int picId, double l, double t, double w, double h);
void DrawBegin(int picId, double x, double y);
void DrawSlide(double x, double y);
void DrawRotate(double rot);
void DrawZoom_X(double z);
void DrawZoom_Y(double z);
void DrawZoom(double z);
void DrawSetSize_W(double w);
void DrawSetSize_H(double h);
void DrawSetSize(double w, double h);
void DrawEnd(void);

// < DrawBegin �` DrawEnd

void DPE_SetAlpha(double a);
void DPE_SetBlendAdd(double a);
void DPE_SetBright(double cR, double cG, double cB);
void DPE_SetBright(int color);
void DPE_SetGraphicSize(i2D_t size);
void DPE_Reset(void);