#include "all.h"

// ---- FontFile ----

static autoList<char *> *FontFileList;

static char *GetFontDir(void)
{
	static char *dir;

	if(!dir)
	{
		dir = makeTempDir();
		createDir(dir);
	}
	return dir;
}
static void RemoveAllFontFile(void)
{
LOGPOS(); // test
	while(FontFileList->GetCount())
	{
		errorCase(!RemoveFontResourceEx(FontFileList->UnaddElement(), FR_PRIVATE, NULL)); // ? 失敗
	}
}
void AddFontFile(int etcId, char *localFile)
{
	char *file = combine(GetFontDir(), localFile);

	{
		autoList<uchar> *fileData = GetEtcFileData(etcId);
		writeAllBytes(file, fileData);
		delete fileData;
	}

	LOG("AddFontResourceEx ST %u\n", (uint)time(NULL));
	errorCase(!AddFontResourceEx(file, FR_PRIVATE, NULL)); // ? 失敗
	LOG("AddFontResourceEx ED %u\n", (uint)time(NULL));

	if(!FontFileList)
	{
		FontFileList = new autoList<char *>();
		GetEndProcFinalizers()->AddFunc(ReleaseAllFontHandle);
		GetFinalizers()->AddFunc(RemoveAllFontFile);
	}
	FontFileList->AddElement(file);
}

// ---- FontHandle ----

/*
	fontThick: 0 〜 9 (デフォルト値：6)

		値域の根拠
			マニュアル
				https://dxlib.xsrv.jp/function/dxfunc_graph2.html#R17N10

		デフォルト値の根拠
			マニュアル
				https://dxlib.xsrv.jp/function/dxfunc_graph2.html#R17N8

			src
				C:\wb2\20191209_src\DxLibMake3_20\DxFont.cpp
					CreateFontToHandle_Static()
						if( Thick < 0 ) Thick = DEFAULT_FONT_THINCK ;

				C:\wb2\20191209_src\DxLibMake3_20\DxLib.h
					#define DEFAULT_FONT_THINCK (6)
*/
FontHandle_t *CreateFontHandle(char *fontName, int fontSize, int fontThick, int antiAliasing, int edgeSize, int italicFlag)
{
	errorCase(m_isEmpty(fontName));
	errorCase(!m_isRange(fontSize, 1, IMAX));
	errorCase(!m_isRange(fontThick, 0, 9));
	// antiAliasing
	errorCase(!m_isRange(edgeSize, 0, IMAX));
	// italicFlag

	int h = CreateFontToHandle(
		fontName,
		fontSize,
		fontThick,
		DX_FONTTYPE_NORMAL | (antiAliasing ? DX_FONTTYPE_ANTIALIASING : 0) | (edgeSize ? DX_FONTTYPE_EDGE : 0),
		-1,
		edgeSize
		);

	errorCase(h == -1); // ? 失敗

	FontHandle_t *fh = nb_(FontHandle_t);
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

// <-- cdtor

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
LOGPOS(); // test
	while(GetFontHandleList()->GetCount())
	{
		ReleaseFontHandle(GetFontHandleList()->UnaddElement());
	}
}

// ----

void DrawStringByFont(int x, int y, char *str, FontHandle_t *fh, int tategakiFlag, int color, int edgeColor)
{
	errorCase(!str);
	errorCase(!fh);

	DrawStringToHandle(x, y, str, color, fh->Handle, edgeColor, tategakiFlag);
}
int GetDrawStringByFontWidth(char *str, FontHandle_t *fh, int tategakiFlag)
{
	errorCase(!str);
	errorCase(!fh);

	return GetDrawStringWidthToHandle(str, strlen(str), fh->Handle, tategakiFlag);
}
void DrawStringByFont_XCenter(int x, int y, char *str, FontHandle_t *fh, int tategakiFlag, int color, int edgeColor)
{
	x -= GetDrawStringByFontWidth(str, fh, tategakiFlag) / 2;

	DrawStringByFont(x, y, str, fh, tategakiFlag, color, edgeColor);
}
