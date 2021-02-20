#include "ATM_ObjectLists.h"

ATM_ObjectList::ATM_ObjectList()
{
}

ATM_ObjectList::ATM_ObjectList(int maxNumber):_maxNumber(maxNumber)
{
	_x = new int[_maxNumber];
	_y = new int[_maxNumber];
}

ATM_ObjectList::~ATM_ObjectList()
{
	if (_x != nullptr)
	{
		delete[] _x;
	}
	if (_y != nullptr)
	{
		delete[] _y;
	}
}

ATM_ObjectList & ATM_ObjectList::operator=(const ATM_ObjectList & objList)
{
	// TODO: 在此处插入 return 语句
	if (this == &objList)
	{
		return *this;
	}
	//delete
	if (_x != nullptr)
	{
		delete[] _x;
	}
	if (_y != nullptr)
	{
		delete[] _y;
	}
	this->_maxNumber = objList._maxNumber;
	this->_orderPtr = objList._orderPtr;
	this->_x = new int[_maxNumber];
	this->_y = new int[_maxNumber];
	for (int i = 0; i < objList._maxNumber; i++)
	{
		this->_x[i] = objList._x[i];
		this->_y[i] = objList._y[i];
	}
	return *this;
}

void ATM_ObjectList::append(int x, int y)
{
	if (_orderPtr >= _maxNumber)
	{
		throw "List Full";
	}
	_x[_orderPtr] = x;
	_y[_orderPtr] = y;
	_orderPtr++;
}

int ATM_ObjectList::x(int i)
{
	if (i < 0)
	{
		return _x[0];
	}
	if (i >= _maxNumber)
	{
		return _x[_maxNumber - 1];
	}
	return _x[i];
}

int ATM_ObjectList::y(int i)
{
	if (i < 0)
	{
		return _y[0];
	}
	if (i >= _maxNumber)
	{
		return _y[_maxNumber - 1];
	}
	return _y[i];
}

cv::Point ATM_ObjectList::p(int i)
{
	if (i < 0)
	{
		return cv::Point(_x[0], _y[0]);
	}
	if (i >= _maxNumber)
	{
		return cv::Point(_x[_maxNumber - 1], _y[_maxNumber - 1]);
	}
	return cv::Point(_x[i], _y[i]);
}

ATM_ObjectLists::ATM_ObjectLists()
{
	_objList = new ATM_ObjectList[_objectListsNumber];
	for (int i = 0; i < _objectListsNumber; i++)
	{
		_objList[i] = ATM_ObjectList(_objectMaxNumbers[i]);
	}
	Init();
}

ATM_ObjectLists::~ATM_ObjectLists()
{
	if (_objList != nullptr)
	{
		delete[] _objList;
	}
}

void ATM_ObjectLists::Init()
{
	Init0();
	Init1();
	Init2();
	Init3();
}

int ATM_ObjectLists::x(int klass, int i)
{
	return _objList[klass].x(i);
}

int ATM_ObjectLists::y(int klass, int i)
{
	return _objList[klass].y(i);
}

cv::Point ATM_ObjectLists::p(int klass, int i)
{
	return _objList[klass].p(i);
}

int ATM_ObjectLists::objectListsNumber()
{
	return _objectListsNumber;
}

int ATM_ObjectLists::objectsNumber(int klass)
{
	if (klass >= _objectListsNumber)
	{
		throw "Element Out Of Bounds";
	}
	return _objectMaxNumbers[klass];
}

bool ATM_ObjectLists::isShow(int klass)
{
	if (klass >= _objectListsNumber)
	{
		throw "Element Out Of Bounds";
	}
	return _isShow[klass];
}

void ATM_ObjectLists::setShow(int klass)
{
	if (klass >= _objectListsNumber)
	{
		throw "Element Out Of Bounds";
	}
	_isShow[klass] = !_isShow[klass];
}

void ATM_ObjectLists::setShow(int klass, bool isShow)
{
	if (klass >= _objectListsNumber)
	{
		throw "Element Out Of Bounds";
	}
	_isShow[klass] = isShow;
}

void ATM_ObjectLists::Init0()
{
	append(0, 1628, 747);
	append(0, 1754, 535);
	append(0, 1494, 570);
	append(0, 1660, 583);
	append(0, 1878, 761);
	append(0, 1749, 620);
	append(0, 1591, 726);
	append(0, 1549, 709);
	append(0, 1592, 679);
	append(0, 1425, 821);
	append(0, 1468, 794);
	append(0, 1522, 887);
	append(0, 1778, 1014);
	append(0, 1890, 925);
	append(0, 1711, 1115);
	append(0, 1988, 957);
	append(0, 2006, 849);
	append(0, 2064, 886);
	append(0, 2069, 827);
	append(0, 2030, 766);
	append(0, 2023, 720);
	append(0, 2114, 760);
	append(0, 2063, 991);
	append(0, 2112, 1050);
	append(0, 2058, 1108);
	append(0, 2090, 1190);
	append(0, 2158, 1271);
	append(0, 2312, 1192);
	append(0, 2273, 1377);
	append(0, 2046, 1435);
	append(0, 1948, 1515);
	append(0, 2076, 1555);
	append(0, 2389, 1316);
	append(0, 2474, 1314);
	append(0, 2536, 1444);
	append(0, 2601, 1468);
	append(0, 2606, 1511);
	append(0, 2649, 1601);
	append(0, 2684, 1395);
	append(0, 2802, 1471);
	append(0, 2841, 1551);
	append(0, 2813, 1631);
	append(0, 2979, 1671);
	append(0, 2867, 1874);
	append(0, 3050, 1781);
	append(0, 2958, 1749);
	append(0, 3229, 1661);
	append(0, 2593, 1318);
	append(0, 2712, 1342);
	append(0, 2780, 1368);
	append(0, 2722, 1292);
	append(0, 2822, 1251);
	append(0, 2719, 1207);
	append(0, 2718, 1015);
	append(0, 2950, 1069);
	append(0, 3115, 996);
	append(0, 3010, 866);
	append(0, 2665, 659);
	append(0, 2591, 550);
	append(0, 2967, 622);
	append(0, 3141, 509);
	append(0, 3592, 770);
	append(0, 3790, 1543);
	append(0, 2259, 749);
	append(0, 2296, 797);
}

void ATM_ObjectLists::Init1()
{
	append(1, 1139, 1159);
	append(1, 1081, 1345);
	append(1, 1067, 1295);
	append(1, 1243, 1303);
	append(1, 1158, 1378);
	append(1, 1310, 1421);
	append(1, 1366, 1394);
	append(1, 1194, 1429);
	append(1, 1046, 1461);
	append(1, 1129, 1493);
	append(1, 1277, 1483);
	append(1, 1307, 1501);
	append(1, 1388, 1507);
	append(1, 1254, 1580);
	append(1, 1036, 1563);
	append(1, 1114, 1641);
	append(1, 1142, 1622);
	append(1, 1240, 1684);
	append(1, 1222, 1760);
	append(1, 1270, 1641);
	append(1, 1440, 1612);
	append(1, 1372, 1667);
	append(1, 1364, 1720);
	append(1, 1381, 1805);
	append(1, 1437, 1700);
	append(1, 1576, 1592);
	append(1, 1495, 1757);
	append(1, 1571, 1826);
	append(1, 1390, 1997);
	append(1, 1278, 1933);
	append(1, 1833, 1872);
	append(1, 1466, 2122);
	append(1, 1441, 2117);
	append(1, 1513, 2167);
	append(1, 1605, 2080);
	append(1, 1913, 2082);
	append(1, 1838, 2132);
	append(1, 1917, 2164);
	append(1, 1795, 2176);
	append(1, 1788, 2239);
	append(1, 1952, 2246);
	append(1, 2060, 2466);
	append(1, 1901, 2375);
	append(1, 2082, 2297);
	append(1, 2121, 2339);
	append(1, 2082, 2448);
	append(1, 1881, 2534);
	append(1, 2324, 2512);
	append(1, 2173, 2918);
	append(1, 2430, 2905);
	append(1, 2519, 2989);
	append(1, 2304, 3090);
	append(1, 1711, 2312);
	append(1, 1679, 2395);
	append(1, 1355, 2471);
	append(1, 1561, 2564);
	append(1, 1365, 2617);
	append(1, 1564, 2611);
	append(1, 1621, 2636);
	append(1, 1810, 2617);
	append(1, 1459, 2726);
	append(1, 1555, 2805);
	append(1, 1835, 2791);
	append(1, 1754, 2869);
	append(1, 1359, 2998);
	append(1, 1464, 2950);
	append(1, 1534, 2923);
	append(1, 1164, 2740);
	append(1, 1161, 2556);
	append(1, 918, 2948);
	append(1, 989, 2959);
	append(1, 1030, 2945);
	append(1, 758, 3012);
	append(1, 836, 3086);
	append(1, 736, 3218);
	append(1, 881, 3248);
	append(1, 725, 3322);
	append(1, 1042, 3214);
	append(1, 1267, 3144);
	append(1, 1234, 3163);
	append(1, 1237, 3232);
	append(1, 1183, 3283);
	append(1, 1304, 3349);
	append(1, 1332, 3414);
	append(1, 1115, 3483);
	append(1, 996, 3480);
	append(1, 735, 3504);
	append(1, 609, 2702);
	append(1, 603, 2595);
	append(1, 820, 1569);
	append(1, 709, 1699);
	append(1, 756, 1734);
	append(1, 924, 1717);
	append(1, 715, 1866);
	append(1, 1026, 1915);
	append(1, 1317, 2212);
	append(1, 1215, 2178);
	append(1, 1087, 2505);
	append(1, 1054, 2336);
	append(1, 1868, 3340);
	append(1, 988, 2212);
	append(1, 888, 2320);
	append(1, 811, 2378);
	append(1, 747, 2312);
	append(1, 778, 2246);
	append(1, 720, 2255);
	append(1, 704, 2225);
	append(1, 643, 2332);
	append(1, 612, 2169);
	append(1, 753, 2082);
	append(1, 790, 2022);
	append(1, 697, 2049);
	append(1, 486, 1852);
	append(1, 444, 1962);
	append(1, 467, 2063);
	append(1, 367, 2074);
	append(1, 439, 2089);
	append(1, 471, 2107);
	append(1, 523, 2128);
	append(1, 355, 2242);
	append(1, 286, 2214);
	append(1, 280, 2308);
	append(1, 318, 2295);
	append(1, 410, 2262);
	append(1, 429, 2262);
	append(1, 1451, 1857);
	append(1, 1938, 2358);
	append(1, 1199, 2245);
	append(1, 979, 1771);
	append(1, 2620, 3136);
	append(1, 1295, 2113);
}

void ATM_ObjectLists::Init2()
{
	append(2, 2442, 1953);
	append(2, 2625, 2089);
	append(2, 2438, 2183);
	append(2, 2400, 2085);
	append(2, 2447, 2056);
	append(2, 2405, 2024);
	append(2, 2363, 2005);
	append(2, 2625, 2113);
	append(2, 2114, 2005);
	append(2, 2152, 1906);
	append(2, 2105, 1841);
	append(2, 2419, 1911);
	append(2, 2386, 1930);
	append(2, 2353, 1953);
	append(2, 2452, 2052);
	append(2, 2438, 2033);
	append(2, 2428, 2042);
	append(2, 2405, 2047);
	append(2, 2339, 2005);
	append(2, 2372, 2010);
	append(2, 2021, 1855);
	append(2, 2133, 1958);
	append(2, 2293, 1930);
	append(2, 2278, 1967);
	append(2, 2264, 1930);
	append(2, 2161, 1874);
	append(2, 2161, 1902);
	append(2, 2016, 1977);
	append(2, 2002, 1977);
	append(2, 2063, 1977);
	append(2, 2035, 2047);
	append(2, 2180, 2070);
	append(2, 2171, 2085);
	append(2, 2147, 2103);
	append(2, 2161, 2117);
	append(2, 2203, 2253);
	append(2, 2236, 2183);
	append(2, 2307, 2094);
	append(2, 2307, 2122);
	append(2, 2424, 2014);
	append(2, 2419, 1986);
	append(2, 2410, 1991);
	append(2, 2433, 2094);
	append(2, 2466, 2085);
	append(2, 2461, 2089);
	append(2, 2339, 2141);
	append(2, 2564, 2000);
	append(2, 2635, 2010);
	append(2, 2597, 2038);
	append(2, 2522, 2038);
	append(2, 2428, 2117);
	append(2, 2536, 2094);
	append(2, 2438, 2178);
	append(2, 2410, 2300);
	append(2, 2635, 2342);
	append(2, 2588, 2258);
	append(2, 2588, 2234);
	append(2, 2789, 2164);
	append(2, 2649, 2117);
	append(2, 2742, 2113);
	append(2, 2860, 2033);
	append(2, 2681, 1981);
	append(2, 2653, 1958);
	append(2, 2714, 1972);
	append(2, 2480, 1897);
	append(2, 2485, 1958);
	append(2, 2499, 1921);
	append(2, 2546, 1878);
	append(2, 2686, 1813);
	append(2, 2616, 1888);
	append(2, 2588, 1846);
	append(2, 2541, 1813);
	append(2, 2358, 1789);
	append(2, 2480, 1794);
	append(2, 2457, 1757);
	append(2, 2372, 1710);
	append(2, 2288, 1742);
	append(2, 2138, 1719);
	append(2, 2105, 1733);
	append(2, 2222, 1630);
}

void ATM_ObjectLists::Init3()
{
}

void ATM_ObjectLists::append(int i, int x, int y)
{
	if (i >= _objectListsNumber)
	{
		throw"Lists Full";
	}
	_objList[i].append(x, y);
}
