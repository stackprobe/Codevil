enum
{
	ENUM_RANGE(D_DUMMY_00, 4)

	// app > @ D_

	// < app

	D_MAX, // num of member
};

typedef struct DerInfo_st
{
	int ParentPicId;
	int X;
	int Y;
	int W;
	int H;
}
DerInfo_t;

int Der(int derId);
int Der(int derId, resCluster<PicInfo_t *> *resclu);
int Der_W(int derId);
int Der_H(int derId);

void UnloadAllDer(autoList<int> *derHandleList);
