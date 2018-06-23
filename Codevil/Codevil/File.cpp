#include "all.h"

/*
	unsigned attrib;
		_A_ARCH
		_A_HIDDEN
		_A_NORMAL
		_A_RDONLY
		_A_SUBDIR
		_A_SYSTEM

	time_t time_create;
	time_t time_access;
	time_t time_write;
	_fsize_t size;
	char name[_MAX_PATH];
*/
struct _finddata_t lastFindData;

/*
	dir 直下のサブディレクトリ・ファイルのリストを返す。
	返すサブディレクトリ・ファイルは「ローカル名」なので注意！

	subDirs: NULL == 出力しない。
	files: NULL == 出力しない。
*/
void getFileList(char *dir, autoList<char *> *subDirs, autoList<char *> *files)
{
	errorCase(m_isEmpty(dir));

	char *wCard = xcout("%s\\*", dir);
	intptr_t h = _findfirst(wCard, &lastFindData);
	memFree(wCard);

	if(h != -1)
	{
		do
		{
			char *name = lastFindData.name;

			if(name[0] == '.' && (name[1] == '\0' || name[1] == '.' && name[2] == '\0')) // ".", ".." を除外
				continue;

			errorCase(m_isEmpty(name));
			errorCase(strchr(name, '?')); // ? 変な文字を含む

			if(lastFindData.attrib & _A_SUBDIR) // ? subDir
			{
				if(subDirs)
					subDirs->AddElement(strx(name));
			}
			else // ? file
			{
				if(files)
					files->AddElement(strx(name));
			}
		}
		while(_findnext(h, &lastFindData) == 0);

		_findclose(h);
	}
}
void updateFindData(char *path)
{
	errorCase(m_isEmpty(path));

	intptr_t h = _findfirst(path, &lastFindData);
	errorCase(h == -1);
	_findclose(h);
}

// ----

int accessible(char *path)
{
	return !_access(path, 0);
}
char *refLocalPath(char *path)
{
	char *p = mbs_strrchr(path, '\\');

	if(p)
		return p + 1;

	return path;
}
void createDir(char *dir)
{
	errorCase(m_isEmpty(dir));
	errorCase(_mkdir(dir)); // ? 失敗
}
void deleteDir(char *dir)
{
	errorCase(m_isEmpty(dir));

	autoList<char *> *subDirs = new autoList<char *>();
	autoList<char *> *files = new autoList<char *>();

	getFileList(dir, subDirs, files);
	addCwd(dir);

	for(int index = 0; index < subDirs->GetCount(); index++)
		deleteDir(subDirs->GetElement(index));

	for(int index = 0; index < files->GetCount(); index++)
		remove(files->GetElement(index));

	unaddCwd();
	_rmdir(dir);

	releaseList(subDirs, (void (*)(char *))memFree);
	releaseList(files, (void (*)(char *))memFree);
}

static oneObject(autoList<char *>, new autoList<char *>(), GetCwdStack);

char *getCwd(void)
{
	char *tmp = _getcwd(NULL, 0);

	errorCase(m_isEmpty(tmp));

	char *dir = strx(tmp);
	free(tmp);
	return dir;
}
void changeCwd(char *dir)
{
	errorCase(m_isEmpty(dir));
	errorCase(_chdir(dir)); // ? 失敗
}
void addCwd(char *dir)
{
	GetCwdStack()->AddElement(getCwd());
	changeCwd(dir);
}
void unaddCwd(void)
{
	char *dir = GetCwdStack()->UnaddElement();

	changeCwd(dir);
	memFree(dir);
}

#define APP_TEMP_DIR_UUID "{8f8ce7a6-fea3-455c-8d7a-a6ebfd9b9944}" // shared_uuid@g -- このソースを使い回すので、global指定

static char *GetSystemTempDir(void)
{
	static char *dir;

	if(!dir)
	{
		dir = getenv("TMP");

		if(m_isEmpty(dir))
		{
			dir = getenv("TEMP");
			errorCase(m_isEmpty(dir));
		}
	}
	return dir;
}
static void DeleteAppTempDir(void)
{
	deleteDir(getAppTempDir());
}
char *getAppTempDir(void)
{
	static char *dir;

	if(!dir)
	{
		dir = combine(GetSystemTempDir(), APP_TEMP_DIR_UUID);

		if(accessible(dir))
			deleteDir(dir);

		createDir(dir);
		GetFinalizers()->AddFunc(DeleteAppTempDir);
	}
	return dir;
}
