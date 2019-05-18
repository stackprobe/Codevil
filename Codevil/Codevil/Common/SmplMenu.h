extern int SmplMenu_Color;
extern int SmplMenu_BorderColor;
extern int SmplMenu_WallColor;
extern int SmplMenu_WallPicId;
extern double SmplMenu_WallCurtain;
extern int SmplMenu_X;
extern int SmplMenu_Y;
extern int SmplMenu_YStep;

int SmplMenu(char *menuTitle, char **menuItems, int selectMax, int selectIndex = 0);
double SmplVolumeConfig(char *menuTitle, double rate, int minval, int maxval, int valStep, int valFastStep, void (*valChanged)(double), void (*pulse)(void) = NULL);
void SmplPadConfig(void);
void SmplWindowSizeConfig(void);
