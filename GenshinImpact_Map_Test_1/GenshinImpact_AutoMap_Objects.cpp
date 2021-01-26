#include "GenshinImpact_AutoMap_Objects.h"

inline Location2d::Location2d() :Location2d(0, 0) {}

inline Location2d::Location2d(int _x, int _y) : x(_x), y(_y) {}

GenshinImpact_AutoMap_Object::GenshinImpact_AutoMap_Object()
{
	//throw"No Klass Funcation.";
	
}

GenshinImpact_AutoMap_Object::~GenshinImpact_AutoMap_Object()
{
	delete[] p;
}

GenshinImpact_AutoMap_Object::GenshinImpact_AutoMap_Object(std::string str, int k,int max)
{
	//if (k == 0)throw "Object Klass cannot be Zero.";
	if (max <= 0)throw "Object Number must not be less than or equal to Zero.";

	name = str;
	klass = k;
	number = max;
	p = new Location2d[max];
}

void GenshinImpact_AutoMap_Object::add(Location2d p0)
{
	p[order] = p0;
	order++;
}

void GenshinImpact_AutoMap_Object::add(int x, int y)
{
	p[order] = Location2d(x, y);
	order++;
}

//void GenshinImpact_AutoMap_Object::del(int n){}

Location2d GenshinImpact_AutoMap_Object::at(int n)
{
	if (n < 0)throw "The serial number shall not be less than Zero.";
	if (n >= number||n>=order)
	{
		throw"Out of range.";
	}
	else
	{
		return p[n];
	}
}

int GenshinImpact_AutoMap_Object::size()
{
	return order;
}

GenshinImpact_AutoMap_Objects::GenshinImpact_AutoMap_Objects()
{
	std::string type[4] = { "风神瞳", "岩神瞳","风地灵龛","岩地灵龛"};
	int num[4] = { 65,131,10,10 };
	objptr = new GenshinImpact_AutoMap_Object[4];
	GenshinImpact_AutoMap_Object list0(type[0], 0, num[0]);
	GenshinImpact_AutoMap_Object list1(type[1], 1, num[1]);
	GenshinImpact_AutoMap_Object list2(type[2], 2, num[2]);
	GenshinImpact_AutoMap_Object list3(type[3], 3, num[3]);
	objptr[0] = list0;
	objptr[1] = list1;
	objptr[2] = list2;
	objptr[3] = list3;
	//for (int i = 0; i < 4; i++)
	//{
	//	objptr[i] = new GenshinImpact_AutoMap_Object(type[i],i,num[i]);
	//}
}

GenshinImpact_AutoMap_Objects::~GenshinImpact_AutoMap_Objects()
{
	delete object;
	delete[] objptr;
}

void GenshinImpact_AutoMap_Objects::initALL()
{
	if (isLock)throw"Cann't Change!";

	{
		fun(1, 0, 1626, 756);
		fun(2, 0, 1752, 533);
		fun(3, 0, 1492, 570);
		fun(4, 0, 1658, 584);
		fun(5, 0, 1876, 770);
		fun(6, 0, 1747, 623);
		fun(7, 0, 1589, 734);
		fun(8, 0, 1548, 717);
		fun(9, 0, 1590, 685);
		fun(10, 0, 1423, 832);
		fun(11, 0, 1466, 805);
		fun(12, 0, 1520, 901);
		fun(13, 0, 1776, 1029);
		fun(14, 0, 1888, 939);
		fun(15, 0, 1709, 1131);
		fun(16, 0, 1985, 972);
		fun(17, 0, 2003, 862);
		fun(18, 0, 2062, 899);
		fun(19, 0, 2067, 839);
		fun(20, 0, 2028, 775);
		fun(21, 0, 2021, 728);
		fun(22, 0, 2112, 770);
		fun(23, 0, 2060, 1007);
		fun(24, 0, 2109, 1066);
		fun(25, 0, 2056, 1123);
		fun(26, 0, 2088, 1204);
		fun(27, 0, 2156, 1283);
		fun(28, 0, 2310, 1207);
		fun(29, 0, 2271, 1386);
		fun(30, 0, 2043, 1441);
		fun(31, 0, 1946, 1515);
		fun(32, 0, 2074, 1552);
		fun(33, 0, 2387, 1327);
		fun(34, 0, 2471, 1325);
		fun(35, 0, 2533, 1449);
		fun(36, 0, 2598, 1472);
		fun(37, 0, 2603, 1512);
		fun(38, 0, 2646, 1594);
		fun(39, 0, 2681, 1402);
		fun(40, 0, 2798, 1474);
		fun(41, 0, 2838, 1549);
		fun(42, 0, 2810, 1622);
		fun(43, 0, 2975, 1658);
		fun(44, 0, 2863, 1838);
		fun(45, 0, 3046, 1757);
		fun(46, 0, 2954, 1728);
		fun(47, 0, 3225, 1649);
		fun(48, 0, 2590, 1329);
		fun(49, 0, 2709, 1352);
		fun(50, 0, 2777, 1377);
		fun(51, 0, 2719, 1304);
		fun(52, 0, 2819, 1264);
		fun(53, 0, 2716, 1222);
		fun(54, 0, 2715, 1031);
		fun(55, 0, 2947, 1085);
		fun(56, 0, 3111, 1012);
		fun(57, 0, 3007, 879);
		fun(58, 0, 2662, 664);
		fun(59, 0, 2588, 548);
		fun(60, 0, 2964, 625);
		fun(61, 0, 3137, 505);
		fun(62, 0, 3588, 780);
		fun(63, 0, 3786, 1541);
		fun(64, 0, 2256, 758);
		fun(65, 0, 2293, 808);
		fun(101, 1, 1138, 1174);
		fun(102, 1, 1080, 1355);
		fun(103, 1, 1066, 1307);
		fun(104, 1, 1242, 1314);
		fun(105, 1, 1157, 1387);
		fun(106, 1, 1308, 1427);
		fun(107, 1, 1364, 1401);
		fun(108, 1, 1193, 1435);
		fun(109, 1, 1044, 1465);
		fun(110, 1, 1128, 1495);
		fun(111, 1, 1276, 1486);
		fun(112, 1, 1305, 1502);
		fun(113, 1, 1387, 1508);
		fun(114, 1, 1252, 1576);
		fun(115, 1, 1034, 1559);
		fun(116, 1, 1112, 1631);
		fun(117, 1, 1141, 1614);
		fun(118, 1, 1239, 1670);
		fun(119, 1, 1221, 1738);
		fun(120, 1, 1269, 1631);
		fun(121, 1, 1438, 1605);
		fun(122, 1, 1371, 1655);
		fun(123, 1, 1363, 1703);
		fun(124, 1, 1380, 1778);
		fun(125, 1, 1436, 1685);
		fun(126, 1, 1574, 1586);
		fun(127, 1, 1493, 1735);
		fun(128, 1, 1569, 1796);
		fun(129, 1, 1389, 1943);
		fun(130, 1, 1276, 1889);
		fun(131, 1, 1831, 1836);
		fun(132, 1, 1464, 2048);
		fun(133, 1, 1439, 2043);
		fun(134, 1, 1511, 2084);
		fun(135, 1, 1603, 2013);
		fun(136, 1, 1911, 2015);
		fun(137, 1, 1836, 2055);
		fun(138, 1, 1914, 2082);
		fun(139, 1, 1793, 2092);
		fun(140, 1, 1785, 2143);
		fun(141, 1, 1950, 2149);
		fun(142, 1, 2058, 2320);
		fun(143, 1, 1899, 2250);
		fun(144, 1, 2080, 2189);
		fun(145, 1, 2119, 2221);
		fun(146, 1, 2080, 2306);
		fun(147, 1, 1879, 2371);
		fun(148, 1, 2321, 2355);
		fun(149, 1, 2171, 2645);
		fun(150, 1, 2427, 2636);
		fun(151, 1, 2516, 2693);
		fun(152, 1, 2301, 2759);
		fun(153, 1, 1709, 2200);
		fun(154, 1, 1677, 2265);
		fun(155, 1, 1354, 2323);
		fun(156, 1, 1559, 2394);
		fun(157, 1, 1364, 2432);
		fun(158, 1, 1562, 2428);
		fun(159, 1, 1619, 2447);
		fun(160, 1, 1808, 2432);
		fun(161, 1, 1457, 2511);
		fun(162, 1, 1553, 2567);
		fun(163, 1, 1833, 2557);
		fun(164, 1, 1752, 2611);
		fun(165, 1, 1358, 2699);
		fun(166, 1, 1462, 2667);
		fun(167, 1, 1532, 2648);
		fun(168, 1, 1162, 2521);
		fun(169, 1, 1159, 2388);
		fun(170, 1, 917, 2665);
		fun(171, 1, 988, 2673);
		fun(172, 1, 1029, 2663);
		fun(173, 1, 757, 2708);
		fun(174, 1, 835, 2756);
		fun(175, 1, 735, 2841);
		fun(176, 1, 880, 2860);
		fun(177, 1, 724, 2905);
		fun(178, 1, 1041, 2838);
		fun(179, 1, 1266, 2794);
		fun(180, 1, 1232, 2806);
		fun(181, 1, 1235, 2849);
		fun(182, 1, 1182, 2881);
		fun(183, 1, 1303, 2922);
		fun(184, 1, 1331, 2961);
		fun(185, 1, 1114, 3001);
		fun(186, 1, 995, 3000);
		fun(187, 1, 735, 3013);
		fun(188, 1, 609, 2494);
		fun(189, 1, 603, 2416);
		fun(190, 1, 819, 1565);
		fun(191, 1, 708, 1684);
		fun(192, 1, 756, 1715);
		fun(193, 1, 923, 1700);
		fun(194, 1, 715, 1831);
		fun(195, 1, 1025, 1873);
		fun(196, 1, 1316, 2121);
		fun(197, 1, 1213, 2094);
		fun(198, 1, 1085, 2349);
		fun(199, 1, 1053, 2220);
		fun(200, 1, 1866, 2916);
		fun(201, 1, 986, 2121);
		fun(202, 1, 887, 2207);
		fun(203, 1, 810, 2253);
		fun(204, 1, 746, 2201);
		fun(205, 1, 777, 2148);
		fun(206, 1, 719, 2155);
		fun(207, 1, 703, 2131);
		fun(208, 1, 642, 2216);
		fun(209, 1, 612, 2086);
		fun(210, 1, 752, 2015);
		fun(211, 1, 789, 1964);
		fun(212, 1, 696, 1987);
		fun(213, 1, 485, 1819);
		fun(214, 1, 443, 1914);
		fun(215, 1, 466, 1999);
		fun(216, 1, 367, 2008);
		fun(217, 1, 439, 2021);
		fun(218, 1, 471, 2036);
		fun(219, 1, 522, 2052);
		fun(220, 1, 355, 2145);
		fun(221, 1, 286, 2123);
		fun(222, 1, 279, 2197);
		fun(223, 1, 318, 2187);
		fun(224, 1, 409, 2161);
		fun(225, 1, 429, 2161);
		fun(226, 1, 1449, 1823);
		fun(227, 1, 1936, 2237);
		fun(228, 1, 1197, 2147);
		fun(229, 1, 978, 1748);
		fun(230, 1, 2617, 2789);
		fun(231, 1, 1294, 2040);
		fun(1, 2, 2147, 676);
		fun(2, 2, 1940, 1163);
		fun(3, 2, 1885, 1589);
		fun(4, 2, 2215, 1286);
		fun(5, 2, 2504, 1286);
		fun(6, 2, 2657, 1488);
		fun(7, 2, 2735, 1729);
		fun(8, 2, 2906, 1576);
		fun(9, 2, 3036, 805);
		fun(10, 2, 2669, 572);
		fun(1, 3, 1664, 1615);
		fun(2, 3, 1315, 1524);
		fun(3, 3, 1967, 1969);
		fun(4, 3, 706, 1673);
		fun(5, 3, 706, 1837);
		fun(6, 3, 628, 1947);
		fun(7, 3, 498, 2321);
		fun(8, 3, 882, 2606);
		fun(9, 3, 1026, 2905);
		fun(10, 3, 2259, 2889);
	}

	isLock = true;
}

void GenshinImpact_AutoMap_Objects::initFST()
{
	if (isLock)throw"Cann't Change!";
	object = new GenshinImpact_AutoMap_Object("风神瞳", 1, 65);

	{
		add(1626, 756);
		add(1752, 533);
		add(1492, 570);
		add(1658, 584);
		add(1876, 770);
		add(1747, 623);
		add(1589, 734);
		add(1548, 717);
		add(1590, 685);
		add(1423, 832);
		add(1466, 805);
		add(1520, 901);
		add(1776, 1029);
		add(1888, 939);
		add(1709, 1131);
		add(1985, 972);
		add(2003, 862);
		add(2062, 899);
		add(2067, 839);
		add(2028, 775);
		add(2021, 728);
		add(2112, 770);
		add(2060, 1007);
		add(2109, 1066);
		add(2056, 1123);
		add(2088, 1204);
		add(2156, 1283);
		add(2310, 1207);
		add(2271, 1386);
		add(2043, 1441);
		add(1946, 1515);
		add(2074, 1552);
		add(2387, 1327);
		add(2471, 1325);
		add(2533, 1449);
		add(2598, 1472);
		add(2603, 1512);
		add(2646, 1594);
		add(2681, 1402);
		add(2798, 1474);
		add(2838, 1549);
		add(2810, 1622);
		add(2975, 1658);
		add(2863, 1838);
		add(3046, 1757);
		add(2954, 1728);
		add(3225, 1649);
		add(2590, 1329);
		add(2709, 1352);
		add(2777, 1377);
		add(2719, 1304);
		add(2819, 1264);
		add(2716, 1222);
		add(2715, 1031);
		add(2947, 1085);
		add(3111, 1012);
		add(3007, 879);
		add(2662, 664);
		add(2588, 548);
		add(2964, 625);
		add(3137, 505);
		add(3588, 780);
		add(3786, 1541);
		add(2256, 758);
		add(2293, 808);
	}
	
	isLock = true;
}

void GenshinImpact_AutoMap_Objects::initYST()
{
	if (isLock)throw"Cann't Change!";
	object = new GenshinImpact_AutoMap_Object("岩神瞳", 2, 131);//66+14

	{
		add(1138, 1174);
		add(1080, 1355);
		add(1066, 1307);
		add(1242, 1314);
		add(1157, 1387);
		add(1308, 1427);
		add(1364, 1401);
		add(1193, 1435);
		add(1044, 1465);
		add(1128, 1495);
		add(1276, 1486);
		add(1305, 1502);
		add(1387, 1508);
		add(1252, 1576);
		add(1034, 1559);
		add(1112, 1631);
		add(1141, 1614);
		add(1239, 1670);
		add(1221, 1738);
		add(1269, 1631);
		add(1438, 1605);
		add(1371, 1655);
		add(1363, 1703);
		add(1380, 1778);
		add(1436, 1685);
		add(1574, 1586);
		add(1493, 1735);
		add(1569, 1796);
		add(1389, 1943);
		add(1276, 1889);
		add(1831, 1836);
		add(1464, 2048);
		add(1439, 2043);
		add(1511, 2084);
		add(1603, 2013);
		add(1911, 2015);
		add(1836, 2055);
		add(1914, 2082);
		add(1793, 2092);
		add(1785, 2143);
		add(1950, 2149);
		add(2058, 2320);
		add(1899, 2250);
		add(2080, 2189);
		add(2119, 2221);
		add(2080, 2306);
		add(1879, 2371);
		add(2321, 2355);
		add(2171, 2645);
		add(2427, 2636);
		add(2516, 2693);
		add(2301, 2759);
		add(1709, 2200);
		add(1677, 2265);
		add(1354, 2323);
		add(1559, 2394);
		add(1364, 2432);
		add(1562, 2428);
		add(1619, 2447);
		add(1808, 2432);
		add(1457, 2511);
		add(1553, 2567);
		add(1833, 2557);
		add(1752, 2611);
		add(1358, 2699);
		add(1462, 2667);
		add(1532, 2648);
		add(1162, 2521);
		add(1159, 2388);
		add(917, 2665);
		add(988, 2673);
		add(1029, 2663);
		add(757, 2708);
		add(835, 2756);
		add(735, 2841);
		add(880, 2860);
		add(724, 2905);
		add(1041, 2838);
		add(1266, 2794);
		add(1232, 2806);
		add(1235, 2849);
		add(1182, 2881);
		add(1303, 2922);
		add(1331, 2961);
		add(1114, 3001);
		add(995, 3000);
		add(735, 3013);
		add(609, 2494);
		add(603, 2416);
		add(819, 1565);
		add(708, 1684);
		add(756, 1715);
		add(923, 1700);
		add(715, 1831);
		add(1025, 1873);
		add(1316, 2121);
		add(1213, 2094);
		add(1085, 2349);
		add(1053, 2220);
		add(1866, 2916);
		add(986, 2121);
		add(887, 2207);
		add(810, 2253);
		add(746, 2201);
		add(777, 2148);
		add(719, 2155);
		add(703, 2131);
		add(642, 2216);
		add(612, 2086);
		add(752, 2015);
		add(789, 1964);
		add(696, 1987);
		add(485, 1819);
		add(443, 1914);
		add(466, 1999);
		add(367, 2008);
		add(439, 2021);
		add(471, 2036);
		add(522, 2052);
		add(355, 2145);
		add(286, 2123);
		add(279, 2197);
		add(318, 2187);
		add(409, 2161);
		add(429, 2161);
		add(1449, 1823);
		add(1936, 2237);
		add(1197, 2147);
		add(978, 1748);
		add(2617, 2789);
		add(1294, 2040);
	}

	isLock = true;
}

void GenshinImpact_AutoMap_Objects::initFHYS()
{
	if (isLock)throw"Cann't Change!";
	object = new GenshinImpact_AutoMap_Object("绯红玉髓", 3, 80);//66+14

	{
		add(2442, 1953);
		add(2625, 2089);
		add(2438, 2183);
		add(2400, 2085);
		add(2447, 2056);
		add(2405, 2024);
		add(2363, 2005);
		add(2625, 2113);
		add(2114, 2005);
		add(2152, 1906);
		add(2105, 1841);
		add(2419, 1911);
		add(2386, 1930);
		add(2353, 1953);
		add(2452, 2052);
		add(2438, 2033);
		add(2428, 2042);
		add(2405, 2047);
		add(2339, 2005);
		add(2372, 2010);
		add(2021, 1855);
		add(2133, 1958);
		add(2293, 1930);
		add(2278, 1967);
		add(2264, 1930);
		add(2161, 1874);
		add(2161, 1902);
		add(2016, 1977);
		add(2002, 1977);
		add(2063, 1977);
		add(2035, 2047);
		add(2180, 2070);
		add(2171, 2085);
		add(2147, 2103);
		add(2161, 2117);
		add(2203, 2253);
		add(2236, 2183);
		add(2307, 2094);
		add(2307, 2122);
		add(2424, 2014);
		add(2419, 1986);
		add(2410, 1991);
		add(2433, 2094);
		add(2466, 2085);
		add(2461, 2089);
		add(2339, 2141);
		add(2564, 2000);
		add(2635, 2010);
		add(2597, 2038);
		add(2522, 2038);
		add(2428, 2117);
		add(2536, 2094);
		add(2438, 2178);
		add(2410, 2300);
		add(2635, 2342);
		add(2588, 2258);
		add(2588, 2234);
		add(2789, 2164);
		add(2649, 2117);
		add(2742, 2113);
		add(2860, 2033);
		add(2681, 1981);
		add(2653, 1958);
		add(2714, 1972);
		add(2480, 1897);
		add(2485, 1958);
		add(2499, 1921);
		add(2546, 1878);
		add(2686, 1813);
		add(2616, 1888);
		add(2588, 1846);
		add(2541, 1813);
		add(2358, 1789);
		add(2480, 1794);
		add(2457, 1757);
		add(2372, 1710);
		add(2288, 1742);
		add(2138, 1719);
		add(2105, 1733);
		add(2222, 1630);
	}

	isLock = true;
}

Location2d GenshinImpact_AutoMap_Objects::at(int n)
{
	return (*object).at(n);
}

void GenshinImpact_AutoMap_Objects::add(int x, int y)
{
	(*object).add(x, y);
}

int GenshinImpact_AutoMap_Objects::size()
{
	if (!isLock)return 0;
	return object->size();
}

int GenshinImpact_AutoMap_Objects::size(int i)
{
	return objptr[i].size();
}

void GenshinImpact_AutoMap_Objects::fun(int absID, int numID, int TypeID, std::string Type, int X, int Y, std::string Info)
{

}

void GenshinImpact_AutoMap_Objects::fun(int numID, int TypeID, int X, int Y)
{
	if (numID <= objptr[TypeID].size())
	{
		objptr[TypeID].add(X, Y);

	}
}
