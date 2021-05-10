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

ATM_ObjectFlag::ATM_ObjectFlag()
{

}

ATM_ObjectFlag::~ATM_ObjectFlag()
{
}

void ATM_ObjectFlag::append(int x, int y)
{
	_x.push_back(x);
	_y.push_back(y);
	_maxNumber++;
}

void ATM_ObjectFlag::deleteId(int id)
{
	if (id < _maxNumber)
	{
		_x.erase(_x.begin() + id);
		_y.erase(_y.begin() + id);
		_maxNumber--;
	}

}

int ATM_ObjectFlag::x(int i)
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

int ATM_ObjectFlag::y(int i)
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

cv::Point ATM_ObjectFlag::p(int i)
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

int ATM_ObjectFlag::getSize()
{
	return _maxNumber;
}

void ATM_ObjectFlag::clear()
{
	_maxNumber = 0;
	_orderPtr = 0;
	_x.clear();
	_y.clear();
}


ATM_ObjectLists::ATM_ObjectLists()
{
	_objList = new ATM_ObjectList[_objectListsNumber];
	for (int i = 0; i < _objectListsNumber; i++)
	{
		_objList[i] = ATM_ObjectList(_objectMaxNumbers[i]);
	}
	
	collectionState[0] = &_collectionStateFST;
	collectionState[1] = &_collectionStateYST;
	collectionState[2] = &_collectionStateFHYS;
	collectionState[3] = &_collectionStateSJK;
	collectionState[4] = &_collectionStateSB;
	collectionState[5] = &_collectionStateLLBH;
	collectionState[6] = &_collectionStateQX;
	collectionState[7] = &_collectionStateLLD;
	collectionState[8] = &_collectionStateGGG;
	collectionState[9] = &_collectionStateXDC;
	collectionState[10] = &_collectionStateXL;

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
	Init4();
	Init5();
	Init6();
	Init7();
	Init8();
	Init9();
	Init10();
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

cv::Point ATM_ObjectLists::fp(int i)
{
	return _objFlag.p(i);
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

int ATM_ObjectLists::flagNumber()
{
	return _objFlag.getSize();
}

bool ATM_ObjectLists::isShow(int klass)
{
	if (klass >= _objectListsNumber)
	{
		throw "Element Out Of Bounds";
	}
	return _isShow[klass];
}

bool ATM_ObjectLists::isShowFlag()
{
	return _isShowFlag;
}

void ATM_ObjectLists::setShow(int klass)
{
	if (klass >= _objectListsNumber)
	{
		throw "Element Out Of Bounds";
	}
	_isShow[klass] = !_isShow[klass];
}

void ATM_ObjectLists::setShowFlag()
{
	_isShowFlag = !_isShowFlag;
}

void ATM_ObjectLists::setShow(int klass, bool isShow)
{
	if (klass >= _objectListsNumber)
	{
		throw "Element Out Of Bounds";
	}
	_isShow[klass] = isShow;
}

void ATM_ObjectLists::setShowFlag(bool isShow)
{
	_isShowFlag = isShow;
}

void ATM_ObjectLists::appendFlag(int x, int y)
{
	_objFlag.append(x, y);
	if (_collectionStateFlag.row()<= _objFlag.getSize())
	{
		ATM_Matrix stateFlagTmp = ATM_Matrix(2, _objFlag.getSize());
		for (int i = 0; i < _collectionStateFlag.col(); i++)
		{
			for (int ii = 0; ii < _collectionStateFlag.row(); ii++)
			{
				stateFlagTmp[i][ii] = _collectionStateFlag[i][ii];
			}
		}
		_collectionStateFlag = stateFlagTmp;
	}
	_collectionStateFlag.set(0, _objFlag.getSize() - 1, x);
	_collectionStateFlag.set(1, _objFlag.getSize() - 1, y);
}

void ATM_ObjectLists::deleteFlag(int id)
{
	_objFlag.deleteId(id);
	if (_collectionStateFlag.row() > _objFlag.getSize())
	{
		_collectionStateFlag = ATM_Matrix(2, _objFlag.getSize());
		for (int ii = 0; ii < _collectionStateFlag.row(); ii++)
		{
			_collectionStateFlag[0][ii] = _objFlag.x(ii);
			_collectionStateFlag[1][ii] = _objFlag.y(ii);
		}
	}
}

void ATM_ObjectLists::setCollectionState(int klass, int i, int state)
{
	(*collectionState[klass]).set(0,i, state);
}

int ATM_ObjectLists::getCollectionState(int klass, int i)
{
	return (*collectionState[klass]).at(0, i);
}

void ATM_ObjectLists::copyFrom(int klass, ATM_Matrix & mat)
{
	 mat.copyTo((*collectionState[klass]));
	 if (klass == 3)
	 {
		 reAppendFlag();
	 }
}

void ATM_ObjectLists::copyTo(int klass, ATM_Matrix * mat)
{
	 (collectionState[klass])->copyTo(*mat);
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
	append(3, 2276, 2882);
	append(3, 2273, 2886);
	append(3, 2277, 2887);
	append(3, 2386, 3033);
	append(3, 2383, 3038);
	append(3, 2337, 3082);
	append(3, 2335, 3087);
	append(3, 2347, 3108);
	append(3, 2368, 3164);
	append(3, 2365, 3169);
	append(3, 2363, 3180);
	append(3, 2370, 3172);
	append(3, 2369, 3177);
	append(3, 2368, 3179);
	append(3, 2365, 3195);
	append(3, 1120, 1626);
	append(3, 1122, 1630);
	append(3, 1164, 1600);
	append(3, 1167, 1605);
	append(3, 1169, 1608);
	append(3, 1172, 1612);
	append(3, 925, 3521);
	append(3, 926, 3525);
	append(3, 735, 3511);
	append(3, 877, 3334);
	append(3, 876, 3340);
	append(3, 879, 3338);
	append(3, 1023, 3327);
	append(3, 1043, 3349);
	append(3, 1049, 3350);
	append(3, 1115, 3428);
	append(3, 1115, 3441);
	append(3, 1124, 3443);
	append(3, 1274, 3253);
	append(3, 1271, 3256);
	append(3, 1274, 3257);
	append(3, 1286, 3289);
	append(3, 1288, 3288);
	append(3, 1282, 3296);
	append(3, 1185, 3035);
	append(3, 1176, 3040);
	append(3, 1190, 3052);
	append(3, 1178, 3069);
	append(3, 917, 3066);
	append(3, 920, 3063);
	append(3, 909, 3075);
	append(3, 921, 3071);
	append(3, 915, 3076);
	append(3, 919, 3075);
	append(3, 849, 3096);
	append(3, 853, 3096);
	append(3, 858, 3093);
	append(3, 860, 3092);
	append(3, 651, 2768);
	append(3, 924, 2717);
	append(3, 924, 2724);
	append(3, 1224, 2600);
	append(3, 1221, 2593);
	append(3, 1215, 2597);
	append(3, 1149, 2516);
	append(3, 1150, 2519);
	append(3, 1153, 2529);
	append(3, 814, 2367);
	append(3, 451, 2546);
	append(3, 802, 2314);
	append(3, 723, 2344);
	append(3, 730, 2347);
	append(3, 656, 2310);
	append(3, 598, 2300);
	append(3, 572, 2284);
	append(3, 566, 2219);
	append(3, 516, 2231);
	append(3, 600, 2186);
	append(3, 678, 2186);
	append(3, 675, 2189);
	append(3, 686, 2180);
	append(3, 683, 2181);
	append(3, 730, 2230);
	append(3, 737, 2168);
	append(3, 760, 2130);
	append(3, 898, 2106);
	append(3, 944, 2075);
	append(3, 920, 2038);
	append(3, 810, 2033);
	append(3, 1025, 1945);
	append(3, 730, 1998);
	append(3, 669, 2025);
	append(3, 551, 2159);
	append(3, 561, 2141);
	append(3, 519, 2161);
	append(3, 584, 2054);
	append(3, 556, 2064);
	append(3, 645, 2087);
	append(3, 662, 2102);
	append(3, 504, 2181);
	append(3, 598, 2152);
	append(3, 590, 2162);
	append(3, 555, 2111);
	append(3, 624, 2065);
	append(3, 837, 2161);
	append(3, 1183, 2054);
	append(3, 461, 1953);
	append(3, 465, 1954);
	append(3, 463, 1959);
	append(3, 465, 1967);
	append(3, 454, 1968);
	append(3, 443, 1958);
	append(3, 436, 1964);
	append(3, 437, 1968);
	append(3, 910, 1886);
	append(3, 914, 1887);
	append(3, 836, 1798);
	append(3, 842, 1803);
	append(3, 650, 1752);
	append(3, 649, 1760);
	append(3, 516, 1777);
	append(3, 1004, 2606);
	append(3, 1049, 2565);
	append(3, 1050, 2569);
	append(3, 1024, 2483);
	append(3, 1026, 2529);
	append(3, 695, 2585);
	append(3, 698, 2585);
	append(3, 1313, 619);
	append(3, 1628, 473);
	append(3, 1302, 680);
	append(3, 1595, 670);
	append(3, 1617, 669);
	append(3, 1647, 672);
	append(3, 1701, 689);
	append(3, 1549, 722);
	append(3, 1535, 735);
	append(3, 1415, 723);
	append(3, 1430, 774);
	append(3, 1441, 807);
	append(3, 1451, 821);
	append(3, 1397, 834);
	append(3, 1458, 857);
	append(3, 1452, 908);
	append(3, 1538, 791);
	append(3, 1562, 796);
	append(3, 1533, 923);
	append(3, 1580, 916);
	append(3, 1560, 888);
	append(3, 1605, 939);
	append(3, 1648, 827);
	append(3, 1704, 777);
	append(3, 1656, 955);
	append(3, 2107, 734);
	append(3, 1997, 912);
	append(3, 1989, 958);
	append(3, 1761, 1203);
	append(3, 2069, 1023);
	append(3, 2057, 1118);
	append(3, 2057, 1121);
	append(3, 1999, 1202);
	append(3, 2185, 1145);
	append(3, 2222, 1235);
	append(3, 2277, 1517);
	append(3, 2286, 1512);
	append(3, 2291, 1516);
	append(3, 2293, 1518);
	append(3, 2677, 717);
	append(3, 2680, 1524);
	append(3, 2781, 712);
	append(3, 2790, 711);
	append(3, 2938, 625);
	append(3, 3003, 547);
	append(3, 3142, 1067);
}

void ATM_ObjectLists::Init4()
{
	append(4, 787, 3528);
	append(4, 808, 3473);
	append(4, 897, 3570);
	append(4, 1071, 3516);
	append(4, 1143, 3377);
	append(4, 1038, 3369);
	append(4, 1043, 3375);
	append(4, 1039, 3322);
	append(4, 1080, 3211);
	append(4, 772, 3375);
	append(4, 957, 3058);
	append(4, 858, 3097);
	append(4, 759, 3019);
	append(4, 1077, 2942);
	append(4, 863, 2647);
	append(4, 862, 2653);
	append(4, 749, 2716);
	append(4, 721, 2671);
	append(4, 828, 2587);
	append(4, 813, 2583);
	append(4, 1001, 2595);
	append(4, 1012, 2631);
	append(4, 994, 2649);
	append(4, 1109, 2737);
	append(4, 1115, 2739);
	append(4, 1110, 2743);
	append(4, 1157, 2709);
	append(4, 1158, 2737);
	append(4, 726, 2562);
	append(4, 677, 2516);
	append(4, 792, 2502);
	append(4, 886, 2506);
	append(4, 881, 2456);
	append(4, 968, 2509);
	append(4, 964, 2514);
	append(4, 859, 2406);
	append(4, 866, 2406);
	append(4, 961, 2328);
	append(4, 982, 2310);
	append(4, 1052, 2313);
	append(4, 1023, 2203);
	append(4, 1039, 2201);
	append(4, 1104, 2205);
	append(4, 1120, 2130);
	append(4, 934, 1905);
	append(4, 984, 1896);
	append(4, 978, 1899);
	append(4, 686, 1923);
	append(4, 545, 2043);
	append(4, 542, 2048);
	append(4, 433, 1988);
	append(4, 436, 1993);
	append(4, 438, 1997);
	append(4, 308, 2206);
	append(4, 309, 2213);
	append(4, 321, 2243);
	append(4, 326, 2244);
	append(4, 298, 2265);
	append(4, 310, 2312);
	append(4, 292, 2307);
	append(4, 300, 2303);
	append(4, 293, 2314);
	append(4, 300, 2312);
	append(4, 307, 2338);
	append(4, 250, 2336);
	append(4, 249, 2263);
	append(4, 265, 2238);
	append(4, 570, 2331);
	append(4, 574, 2332);
	append(4, 651, 1873);
	append(4, 591, 1869);
	append(4, 891, 1820);
	append(4, 895, 1818);
	append(4, 779, 1618);
	append(4, 1084, 1573);
	append(4, 1085, 1580);
	append(4, 1119, 1421);
	append(4, 1125, 1425);
	append(4, 1326, 1401);
	append(4, 1330, 1398);
	append(4, 1330, 1402);
	append(4, 1422, 1454);
	append(4, 1428, 1445);
	append(4, 1346, 1470);
	append(4, 1352, 1470);
	append(4, 1370, 1668);
	append(4, 1367, 1673);
	append(4, 1900, 1741);
	append(4, 1900, 1749);
	append(4, 1912, 1731);
	append(4, 1954, 1721);
	append(4, 1953, 1731);
	append(4, 1959, 1731);
	append(4, 2008, 2253);
	append(4, 2246, 2849);
	append(4, 2456, 2961);
	append(4, 2328, 3096);
	append(4, 2484, 3020);
	append(4, 2466, 3024);
	append(4, 2467, 3043);
	append(4, 1832, 2147);
	append(4, 1309, 1905);
	append(4, 1106, 2646);
	append(4, 1100, 2648);
}

void ATM_ObjectLists::Init5()
{
	append(5, 1507, 3337);
	append(5, 1509, 3340);
	append(5, 1393, 3309);
	append(5, 1416, 3276);
	append(5, 1368, 3300);
	append(5, 1376, 3298);
	append(5, 1398, 3293);
	append(5, 1345, 3174);
	append(5, 1359, 3181);
	append(5, 1333, 3211);
	append(5, 1363, 3218);
	append(5, 1356, 3226);
	append(5, 1352, 3230);
	append(5, 1332, 3241);
	append(5, 1386, 3239);
	append(5, 1386, 3239);
	append(5, 1386, 3247);
	append(5, 1281, 1329);
	append(5, 1263, 1328);
	append(5, 1247, 1319);
	append(5, 1244, 1327);
	append(5, 1243, 1344);
	append(5, 1210, 1322);
	append(5, 1181, 1336);
	append(5, 1145, 1330);
	append(5, 1280, 1348);
	append(5, 1234, 1377);
	append(5, 1269, 1373);
	append(5, 1152, 1423);
	append(5, 1154, 1397);
	append(5, 1148, 1399);
	append(5, 1291, 3122);
	append(5, 1232, 1450);
	append(5, 1288, 1442);
	append(5, 1504, 3340);
	append(5, 1343, 3179);

}

void ATM_ObjectLists::Init6()
{
	append(6, 1188, 2190);
	append(6, 1186, 2194);
	append(6, 1000, 2178);
	append(6, 961, 2256);
	append(6, 988, 3273);
	append(6, 1000, 3274);
	append(6, 988, 3278);
	append(6, 991, 3283);
	append(6, 355, 2161);
	append(6, 350, 2158);
	append(6, 347, 2161);
	append(6, 351, 2165);
	append(6, 425, 2135);
	append(6, 431, 2139);
	append(6, 426, 2140);
	append(6, 613, 1720);
	append(6, 651, 1782);

}

void ATM_ObjectLists::Init7()
{
	append(7, 1922, 1727);
	append(7, 1894, 1741);
	append(7, 1884, 1750);
	append(7, 1876, 1744);
	append(7, 1877, 1750);
	append(7, 1954, 1758);
	append(7, 1908, 1969);
	append(7, 1904, 1974);
	append(7, 1883, 1980);
	append(7, 1876, 2004);
	append(7, 1785, 2126);
	append(7, 1816, 2188);
	append(7, 1782, 2219);
	append(7, 1919, 2176);
	append(7, 2025, 2283);
	append(7, 2044, 2313);
	append(7, 1894, 2372);
	append(7, 1991, 2369);
	append(7, 1963, 2387);
	append(7, 1810, 2384);
	append(7, 2260, 2884);
	append(7, 2250, 2877);
	append(7, 1088, 1508);
	append(7, 1087, 1553);
	append(7, 1269, 1707);
	append(7, 1274, 1712);
	append(7, 1273, 1703);
	append(7, 1277, 1707);
	append(7, 1374, 1672);
	append(7, 1380, 1668);
	append(7, 1434, 1611);
	append(7, 1432, 1618);
	append(7, 1427, 1619);
	append(7, 1427, 1612);
	append(7, 1375, 1664);
	append(7, 1244, 1570);
	append(7, 1320, 1589);
	append(7, 649, 1760);
	append(7, 646, 1759);
	append(7, 649, 1753);
	append(7, 491, 2092);
	append(7, 500, 2084);
	append(7, 504, 2095);
	append(7, 408, 2258);
	append(7, 419, 2258);
	append(7, 1169, 2549);
	append(7, 1174, 2564);
	append(7, 1159, 2546);
	append(7, 1160, 2551);
	append(7, 1154, 2568);
	append(7, 801, 2966);
	append(7, 987, 3065);
	append(7, 1017, 3101);
	append(7, 966, 3106);
	append(7, 959, 3116);
	append(7, 973, 3107);
	append(7, 988, 3169);
	append(7, 749, 3212);
	append(7, 745, 3235);
	append(7, 754, 3249);
	append(7, 795, 3290);
	append(7, 921, 3301);
	append(7, 930, 3296);
	append(7, 1164, 3196);
	append(7, 1058, 3266);
	append(7, 1066, 3272);
	append(7, 1068, 3262);
	append(7, 1084, 3251);
	append(7, 1095, 3258);
	append(7, 1894, 2108);
	append(7, 1779, 2258);
	append(7, 1831, 2330);
	append(7, 1861, 2374);
	append(7, 1946, 2361);
	append(7, 1947, 2342);
	append(7, 2039, 2253);
	append(7, 1794, 2147);
	append(7, 1785, 2134);
	append(7, 1883, 1980);
	append(7, 1835, 2006);
	append(7, 1231, 1606);
	append(7, 1297, 1580);
	append(7, 1343, 1494);
	append(7, 1132, 3054);
	append(7, 605, 1693);
	append(7, 714, 1873);
	append(7, 723, 1887);
	append(7, 720, 1892);
	append(7, 754, 1897);
	append(7, 866, 1874);
	append(7, 870, 1872);
	append(7, 1352, 1535);
	append(7, 1812, 2193);
	append(7, 1812, 2181);
	append(7, 1787, 2140);
	append(7, 2025, 2274);
	append(7, 1971, 2359);
	append(7, 1702, 2421);
	append(7, 930, 3267);
	append(7, 927, 3273);
	append(7, 908, 3260);
	append(7, 782, 3092);
	append(7, 760, 3053);
	append(7, 857, 3099);
	append(7, 891, 3075);
	append(7, 920, 3048);
	append(7, 925, 3041);
	append(7, 1348, 2470);
	append(7, 1351, 2474);
	append(7, 1348, 2391);
	append(7, 1354, 2397);
	append(7, 1197, 2190);
	append(7, 379, 2117);
	append(7, 1157, 2057);
	append(7, 1165, 2058);
	append(7, 1151, 2052);
	append(7, 451, 2209);
	append(7, 980, 3267);
	append(7, 980, 3271);
	append(7, 1207, 2842);
}

void ATM_ObjectLists::Init8()
{
	append(8, 2068, 1121);
	append(8, 2060, 1148);
	append(8, 2065, 1151);
	append(8, 2043, 1192);
	append(8, 2036, 1205);
	append(8, 2053, 1231);
	append(8, 2033, 1221);
	append(8, 2036, 1226);
	append(8, 2029, 1219);
	append(8, 2029, 1224);
	append(8, 2033, 1253);
	append(8, 2021, 1269);
	append(8, 2007, 1245);
	append(8, 2013, 1247);
	append(8, 2000, 1237);
	append(8, 2026, 1211);
	append(8, 2015, 1209);
	append(8, 2019, 1212);
	append(8, 2006, 1221);
	append(8, 2009, 1221);
	append(8, 1987, 1223);
	append(8, 1991, 1227);
	append(8, 1984, 1229);
	append(8, 1986, 1259);
	append(8, 1937, 1308);
	append(8, 1943, 1310);
	append(8, 1913, 1316);
	append(8, 1926, 1317);
	append(8, 1897, 1295);
	append(8, 1900, 1300);
	append(8, 1897, 1298);
	append(8, 2094, 1213);
	append(8, 2015, 1212);

}

void ATM_ObjectLists::Init9()
{
	append(9, 3046, 1048);
	append(9, 3045, 1052);
	append(9, 3051, 1053);
	append(9, 3039, 1054);
	append(9, 3043, 1058);
	append(9, 2627, 1428);
	append(9, 2651, 1427);
	append(9, 2687, 1474);
	append(9, 2719, 1476);
	append(9, 2684, 1524);
	append(9, 2687, 1524);
	append(9, 2642, 1016);
	append(9, 2645, 1014);
	append(9, 2636, 968);
	append(9, 2637, 971);
	append(9, 2636, 974);
	append(9, 2601, 979);
	append(9, 2604, 973);
	append(9, 2600, 974);
	append(9, 2597, 973);
	append(9, 2596, 978);
	append(9, 2590, 969);
	append(9, 2591, 964);
	append(9, 2589, 945);
	append(9, 2585, 951);
	append(9, 2010, 902);
	append(9, 2925, 1263);
	append(9, 2932, 1254);
	append(9, 2967, 1240);
	append(9, 2958, 1243);
	append(9, 2954, 1236);
	append(9, 2940, 1258);
	append(9, 2948, 894);
	append(9, 2945, 896);
	append(9, 2948, 898);
	append(9, 2925, 849);
	append(9, 2924, 852);
	append(9, 2596, 1014);
	append(9, 2644, 1028);
	append(9, 2643, 1032);
	append(9, 2648, 1030);
	append(9, 2653, 1464);
	append(9, 2700, 1492);
	append(9, 1810, 1604);
	append(9, 1814, 1606);
	append(9, 1776, 1163);
	append(9, 1967, 1023);
	append(9, 1972, 1022);
	append(9, 1977, 1020);
	append(9, 1982, 1016);
	append(9, 1919, 998);
	append(9, 1923, 1001);
	append(9, 1917, 1005);
	append(9, 2075, 743);
	append(9, 2078, 744);
	append(9, 2075, 746);
	append(9, 1849, 1192);
	append(9, 1853, 1190);
	append(9, 1852, 1193);
	append(9, 2068, 1091);
	append(9, 2066, 1093);
	append(9, 2098, 1091);
	append(9, 2097, 1096);
	append(9, 2114, 1104);
	append(9, 2112, 1107);
	append(9, 2156, 1126);
	append(9, 2162, 1128);
	append(9, 2156, 1134);
	append(9, 2119, 1181);
	append(9, 2117, 1185);
	append(9, 2102, 1179);
	append(9, 1823, 1357);
	append(9, 1828, 1356);
	append(9, 1820, 1362);
	append(9, 1825, 1360);

}

void ATM_ObjectLists::Init10()
{
	append(10, 1778, 2781);
	append(10, 1963, 2616);
	append(10, 2266, 2702);
	append(10, 2078, 2931);
	append(10, 2063, 2951);
	append(10, 2083, 2979);
	append(10, 2158, 2929);
	append(10, 2210, 2887);
	append(10, 2252, 2852);
	append(10, 2362, 2919);
	append(10, 2401, 2895);
	append(10, 2427, 2865);
	append(10, 2520, 2944);
	append(10, 2405, 3025);
	append(10, 2378, 3047);
	append(10, 2402, 3052);
	append(10, 2417, 3058);
	append(10, 2375, 3150);
	append(10, 2387, 3183);
	append(10, 2283, 3149);
	append(10, 2329, 3108);
	append(10, 2334, 3109);
	append(10, 2287, 3075);
	append(10, 2329, 3067);
	append(10, 2198, 3118);
	append(10, 1894, 2945);
	append(10, 1913, 2962);
	append(10, 1927, 2929);
	append(10, 1919, 2914);
	append(10, 1909, 2874);
	append(10, 1889, 2880);
	append(10, 1852, 2898);
	append(10, 1875, 2853);
	append(10, 1811, 2820);
	append(10, 1834, 2819);
	append(10, 1805, 2786);
	append(10, 1780, 2776);
	append(10, 1778, 2781);
	append(10, 1781, 2787);
	append(10, 1763, 2736);
	append(10, 1763, 2685);
	append(10, 1781, 2669);
	append(10, 1796, 2647);
	append(10, 1807, 2658);
	append(10, 1792, 2608);
	append(10, 1742, 2500);
	append(10, 1763, 2506);
	append(10, 1812, 2538);
	append(10, 1849, 2557);
	append(10, 1763, 2439);
	append(10, 1768, 2352);
	append(10, 1812, 2443);
	append(10, 1850, 2435);
	append(10, 1889, 2521);
	append(10, 1924, 2520);
	append(10, 1963, 2478);
	append(10, 1991, 2511);
	append(10, 2097, 2475);
	append(10, 2108, 2479);
	append(10, 2059, 2509);
	append(10, 1953, 2407);
	append(10, 1877, 2402);
	append(10, 2082, 2394);
	append(10, 2132, 2410);
	append(10, 2162, 2386);
	append(10, 2158, 2377);
	append(10, 2126, 2376);
	append(10, 1828, 2521);
	append(10, 1905, 2517);

}

void ATM_ObjectLists::append(int i, int x, int y)
{
	if (i >= _objectListsNumber)
	{
		throw"Lists Full";
	}
	_objList[i].append(x, y);
}

void ATM_ObjectLists::reAppendFlag()
{
	_objFlag.clear();

	for (int ii = 0; ii < _collectionStateFlag.row(); ii++)
	{
		_objFlag.append(_collectionStateFlag[0][ii], _collectionStateFlag[1][ii]);
	}
}

void ATM_ObjectLists::reDeleteFlag()
{
}


