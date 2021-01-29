#include "GenshinImpact_AutoMap_Objects.h"

inline Location2d::Location2d() :Location2d(0, 0) {}

inline Location2d::Location2d(int _x, int _y) : x(_x), y(_y) {}

GenshinImpact_AutoMap_Object::GenshinImpact_AutoMap_Object(): GenshinImpact_AutoMap_Object("NoName",0,3){}

GenshinImpact_AutoMap_Object::~GenshinImpact_AutoMap_Object()
{
	if (p != nullptr)
	{
		delete[] p;
		p = nullptr;
	}

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
	objptr = new GenshinImpact_AutoMap_Object*[4];
	GenshinImpact_AutoMap_Object list0(type[0], 0, num[0]);
	GenshinImpact_AutoMap_Object list1(type[1], 1, num[1]);
	GenshinImpact_AutoMap_Object list2(type[2], 2, num[2]);
	GenshinImpact_AutoMap_Object list3(type[3], 3, num[3]);
	objptr[0] = &list0;
	objptr[1] = &list1;
	objptr[2] = &list2;
	objptr[3] = &list3;
	//for (int i = 0; i < 4; i++)
	//{
	//	objptr[i] = new GenshinImpact_AutoMap_Object(type[i],i,num[i]);
	//}
}

GenshinImpact_AutoMap_Objects::~GenshinImpact_AutoMap_Objects()
{
	if (isLock)
	{
		delete object;
	}
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
		add(1628, 747);
		add(1754, 535);
		add(1494, 570);
		add(1660, 583);
		add(1878, 761);
		add(1749, 620);
		add(1591, 726);
		add(1549, 709);
		add(1592, 679);
		add(1425, 821);
		add(1468, 794);
		add(1522, 887);
		add(1778, 1014);
		add(1890, 925);
		add(1711, 1115);
		add(1988, 957);
		add(2006, 849);
		add(2064, 886);
		add(2069, 827);
		add(2030, 766);
		add(2023, 720);
		add(2114, 760);
		add(2063, 991);
		add(2112, 1050);
		add(2058, 1108);
		add(2090, 1190);
		add(2158, 1271);
		add(2312, 1192);
		add(2273, 1377);
		add(2046, 1435);
		add(1948, 1515);
		add(2076, 1555);
		add(2389, 1316);
		add(2474, 1314);
		add(2536, 1444);
		add(2601, 1468);
		add(2606, 1511);
		add(2649, 1601);
		add(2684, 1395);
		add(2802, 1471);
		add(2841, 1551);
		add(2813, 1631);
		add(2979, 1671);
		add(2867, 1874);
		add(3050, 1781);
		add(2958, 1749);
		add(3229, 1661);
		add(2593, 1318);
		add(2712, 1342);
		add(2780, 1368);
		add(2722, 1292);
		add(2822, 1251);
		add(2719, 1207);
		add(2718, 1015);
		add(2950, 1069);
		add(3115, 996);
		add(3010, 866);
		add(2665, 659);
		add(2591, 550);
		add(2967, 622);
		add(3141, 509);
		add(3592, 770);
		add(3790, 1543);
		add(2259, 749);
		add(2296, 797);
	}
	
	isLock = true;
}

void GenshinImpact_AutoMap_Objects::initYST()
{
	if (isLock)throw"Cann't Change!";
	object = new GenshinImpact_AutoMap_Object("岩神瞳", 2, 131);//66+14

	{
		add(1139, 1159);
		add(1081, 1345);
		add(1067, 1295);
		add(1243, 1303);
		add(1158, 1378);
		add(1310, 1421);
		add(1366, 1394);
		add(1194, 1429);
		add(1046, 1461);
		add(1129, 1493);
		add(1277, 1483);
		add(1307, 1501);
		add(1388, 1507);
		add(1254, 1580);
		add(1036, 1563);
		add(1114, 1641);
		add(1142, 1622);
		add(1240, 1684);
		add(1222, 1760);
		add(1270, 1641);
		add(1440, 1612);
		add(1372, 1667);
		add(1364, 1720);
		add(1381, 1805);
		add(1437, 1700);
		add(1576, 1592);
		add(1495, 1757);
		add(1571, 1826);
		add(1390, 1997);
		add(1278, 1933);
		add(1833, 1872);
		add(1466, 2122);
		add(1441, 2117);
		add(1513, 2167);
		add(1605, 2080);
		add(1913, 2082);
		add(1838, 2132);
		add(1917, 2164);
		add(1795, 2176);
		add(1788, 2239);
		add(1952, 2246);
		add(2060, 2466);
		add(1901, 2375);
		add(2082, 2297);
		add(2121, 2339);
		add(2082, 2448);
		add(1881, 2534);
		add(2324, 2512);
		add(2173, 2918);
		add(2430, 2905);
		add(2519, 2989);
		add(2304, 3090);
		add(1711, 2312);
		add(1679, 2395);
		add(1355, 2471);
		add(1561, 2564);
		add(1365, 2617);
		add(1564, 2611);
		add(1621, 2636);
		add(1810, 2617);
		add(1459, 2726);
		add(1555, 2805);
		add(1835, 2791);
		add(1754, 2869);
		add(1359, 2998);
		add(1464, 2950);
		add(1534, 2923);
		add(1164, 2740);
		add(1161, 2556);
		add(918, 2948);
		add(989, 2959);
		add(1030, 2945);
		add(758, 3012);
		add(836, 3086);
		add(736, 3218);
		add(881, 3248);
		add(725, 3322);
		add(1042, 3214);
		add(1267, 3144);
		add(1234, 3163);
		add(1237, 3232);
		add(1183, 3283);
		add(1304, 3349);
		add(1332, 3414);
		add(1115, 3483);
		add(996, 3480);
		add(735, 3504);
		add(609, 2702);
		add(603, 2595);
		add(820, 1569);
		add(709, 1699);
		add(756, 1734);
		add(924, 1717);
		add(715, 1866);
		add(1026, 1915);
		add(1317, 2212);
		add(1215, 2178);
		add(1087, 2505);
		add(1054, 2336);
		add(1868, 3340);
		add(988, 2212);
		add(888, 2320);
		add(811, 2378);
		add(747, 2312);
		add(778, 2246);
		add(720, 2255);
		add(704, 2225);
		add(643, 2332);
		add(612, 2169);
		add(753, 2082);
		add(790, 2022);
		add(697, 2049);
		add(486, 1852);
		add(444, 1962);
		add(467, 2063);
		add(367, 2074);
		add(439, 2089);
		add(471, 2107);
		add(523, 2128);
		add(355, 2242);
		add(286, 2214);
		add(280, 2308);
		add(318, 2295);
		add(410, 2262);
		add(429, 2262);
		add(1451, 1857);
		add(1938, 2358);
		add(1199, 2245);
		add(979, 1771);
		add(2620, 3136);
		add(1295, 2113);
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
	return objptr[i]->size();
}

void GenshinImpact_AutoMap_Objects::fun(int absID, int numID, int TypeID, std::string Type, int X, int Y, std::string Info)
{

}

void GenshinImpact_AutoMap_Objects::fun(int numID, int TypeID, int X, int Y)
{
	if (numID <= objptr[TypeID]->size())
	{
		objptr[TypeID]->add(X, Y);

	}
}
