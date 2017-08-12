#include "all.h"

// ---- FontFile ----

static autoList<char *> *FontFileList;

static char *GetFontDir(void)
{
	static char *dir;

	if(!dir)
	{
		dir = combine(getAppTempDir(), "Font");
		createDir(dir);
	}
	return dir;
}
static void RemoveAllFontFile(void)
{
	while(FontFileList->GetCount())
	{
		errorCase(!RemoveFontResourceEx(FontFileList->UnaddElement(), FR_PRIVATE, NULL)); // ? 失敗
	}
}
void AddFontFile(int etcId, char *localFile)
{
	char *file = combine(GetFontDir(), localFile);

	{
		autoList<uchar> *fileData = GetEtcRes()->GetHandle(etcId);
		writeFile(file, fileData);
	}

	GetEtcRes()->UnloadAllHandle(); // 粗大ゴミ開放

	LOG("AddFontResourceEx ST %u\n", (uint)time(NULL));
	errorCase(!AddFontResourceEx(file, FR_PRIVATE, NULL)); // ? 失敗
	LOG("AddFontResourceEx ED %u\n", (uint)time(NULL));

	if(!FontFileList)
	{
		FontFileList = new autoList<char *>();
		GetFinalizers()->AddFunc(RemoveAllFontFile);
	}
	FontFileList->AddElement(file);
}

// ---- FontHandle ----

/*
	fontThick: 1 - 9, def == 6   -- 多分 DxLib のソースの SetFontThickness() を見てデフォが 6 だったんだと思う。
*/
FontHandle_t *CreateFontHandle(char *fontName, int fontSize, int fontThick, int antiAliasing, int edgeSize, int italicFlag)
{
	errorCase(m_isEmpty(fontName));
	errorCase(!m_isRange(fontSize, 1, IMAX));
	errorCase(!m_isRange(fontThick, 1, 9));
	// antiAliasing
	errorCase(!m_isRange(edgeSize, 0, IMAX));
	// italicFlag
	
	int h = CreateFontToHandle(
		fontName,
		fontSize,
		fontThick,
		antiAliasing ? DX_FONTTYPE_ANTIALIASING : DX_FONTTYPE_NORMAL,
		-1,
		edgeSize
		);

	errorCase(h == -1); // ? 失敗

	FontHandle_t *fh = nb(FontHandle_t);
	fh->Handle = h;
	fh->FontName = strx(fontName);
	fh->FontSize = fontSize;
	fh->FontThick = fontThick;
	fh->AntiAliasing = antiAliasing;
	fh->EdgeSize = edgeSize;
	fh->ItalicFlag = italicFlag;
	return fh;
}
void ReleaseFontHandle(FontHandle_t *fh)
{
	if(!fh)
		return;

	errorCase(DeleteFontToHandle(fh->Handle)); // ? 失敗
	memFree(fh->FontName);
	memFree(fh);
}

// ---- GetFontHandle ----

static oneObject(autoList<FontHandle_t *>, new autoList<FontHandle_t *>(), GetFontHandleList);

FontHandle_t *GetFontHandle(char *fontName, int fontSize, int fontThick, int antiAliasing, int edgeSize, int italicFlag)
{
	errorCase(!fontName);

	FontHandle_t *fh;

	for(int index = 0; index < GetFontHandleList()->GetCount(); index++)
	{
		fh = GetFontHandleList()->GetElement(index);

		if(
			!strcmp(fh->FontName, fontName) &&
			fh->FontSize == fontSize &&
			fh->FontThick == fontThick &&
			(fh->AntiAliasing ? antiAliasing : !antiAliasing) &&
			fh->EdgeSize == edgeSize &&
			(fh->ItalicFlag ? italicFlag : !italicFlag)
			)
		{
			goto found;
		}
	}
	fh = CreateFontHandle(fontName, fontSize, fontThick, antiAliasing, edgeSize, italicFlag);
	GetFontHandleList()->AddElement(fh);
found:
	return fh;
}
void ReleaseAllFontHandle(void)
{
	while(GetFontHandleList()->GetCount())
	{
		ReleaseFontHandle(GetFontHandleList()->UnaddElement());
	}
}

// ----

/*
		// 文字テスト

		DrawStringByFont(
			0, 200,
			"あああ",
			GetFontHandle("りいてがき筆", 100, 6)
			);
		SetPrint(0, 100);
		Print("いいいううう");
		DrawStringByFont(
			0, 0,
			"cerulean.charlotte",
			GetFontHandle("りいてがき筆", 40, 6, 1, 10, 1),
			0,
			GetColor(255, 255, 255),
			GetColor(0, 20, 40)
			);
*/

void DrawStringByFont(int x, int y, char *str, FontHandle_t *fh, int tategakiFlag, int color, int edgeColor)
{
	errorCase(!str);
	errorCase(!fh);

	DrawStringToHandle(x, y, str, color, fh->Handle, edgeColor, tategakiFlag);
}
