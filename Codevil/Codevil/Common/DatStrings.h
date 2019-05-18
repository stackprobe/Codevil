enum
{
	DATSTR_APPNAME,
	DATSTR_AUTHOR,
	DATSTR_COPYRIGHT,
	DATSTR_PCT_S_SPC_PCT_S,

	// app > @ DATSTR_

	// < app

	DATSTR_MAX, // num of member
};

char *GetDatString(int datStrId);
