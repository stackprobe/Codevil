extern int SimpleMenu_Color;
extern int SimpleMenu_BorderColor;
extern int SimpleMenu_WallColor;
extern int SimpleMenu_WallPicId;
extern double SimpleMenu_WallCurtain;
extern int SimpleMenu_X;
extern int SimpleMenu_Y;
extern int SimpleMenu_YStep;

int SimpleMenu(char *menuTitle, char **menuItems, int selectMax, int selectIndex = 0);
double SimpleVolumeConfig(char *menuTitle, double rate, int minval, int maxval, int valStep, int valFastStep, void (*valChanged)(double), void (*pulse)(void) = NULL);
void SimplePadConfig(void);
void SimpleWindowSizeConfig(void);
