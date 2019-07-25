enum
{
	ETC_DATSTRINGS,
	ETC_JCHAR,

	// app > @ ETC_

	ETC_FONT_RIIT,
	ETC_FONT_GENKAI_MINCHO,

	// < app

	ETC_MAX, // num of member
};

autoList<uchar> *GetEtcFileData(int etcId);
