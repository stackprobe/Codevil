enum
{
	MOUBTN_L,
	MOUBTN_M,
	MOUBTN_R,

	MOUBTN_MAX, // num of member
};

#define MouseRot (MouseRot_Get())

extern int MouseX;
extern int MouseY;
extern int MouseMoveX;
extern int MouseMoveY;

void MouseEachFrame(void);
int GetMouInput(int mouBtnId);
int GetMouPound(int mouBtnId);
int MouseRot_Get(void);
void UpdateMousePos(void);
void ApplyMousePos(void);
void UpdateMouseMove(void);
