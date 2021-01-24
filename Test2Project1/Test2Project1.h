// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 TEST2PROJECT1_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// TEST2PROJECT1_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef TEST2PROJECT1_EXPORTS
#define TEST2PROJECT1_API __declspec(dllexport)
#else
#define TEST2PROJECT1_API __declspec(dllimport)
#endif



//class Mat;

struct TEST2PROJECT1_API GPoint
{
	int x;
	int y;
	GPoint();
	GPoint(int _x, int _y);
	void toArray(int _array[2]);
};

struct TEST2PROJECT1_API GSize
{
	int x;
	int y;
	GSize();
	GSize(int _x, int _y);
	void toArray(int _array[2]);
	//int* toArray();
};

// 此类是从 dll 导出的
class TEST2PROJECT1_API GGenshinImpactMatch {
public:
	GGenshinImpactMatch(void);
	~GGenshinImpactMatch(void);
	// TODO: 在此处添加方法。

	bool setSource(void *_source);
	bool setTarget(void *_target);



	GPoint getPosition();

	//BOOL isMatchEnd();
	int outValue;
	void *testMat;
private:
	GPoint gPosition;
	//BITMAP testBIT;
	
	//BOOL isMatchEndFlag = false;

	bool gLoadSource();
};

extern TEST2PROJECT1_API int nTest2Project1;

TEST2PROJECT1_API int fnTest2Project1(void);
