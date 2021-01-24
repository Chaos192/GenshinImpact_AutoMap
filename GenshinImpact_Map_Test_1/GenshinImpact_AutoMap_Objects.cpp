#include "GenshinImpact_AutoMap_Objects.h"

inline Location2d::Location2d() :Location2d(0, 0) {}

inline Location2d::Location2d(int _x, int _y) : x(_x), y(_y) {}

GenshinImpact_AutoMap_Object::GenshinImpact_AutoMap_Object()
{
	throw"No Klass Funcation.";
}

GenshinImpact_AutoMap_Object::~GenshinImpact_AutoMap_Object()
{
	delete p;
}

GenshinImpact_AutoMap_Object::GenshinImpact_AutoMap_Object(std::string str, int k,int max)
{
	if (k == 0)throw "Object Klass cannot be Zero.";
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
	
}

GenshinImpact_AutoMap_Objects::~GenshinImpact_AutoMap_Objects()
{
}

void GenshinImpact_AutoMap_Objects::initCSD()
{
	if (isLock)throw"Cann't Change!";
	object = new GenshinImpact_AutoMap_Object("传送点", 1, 73);
	{
		add(1519, 547);
		add(3000, 603);
		add(1801, 650);
		add(2728, 697);
		add(3005, 734);
		add(1637, 753);
		add(1449, 800);
		add(2063, 814);
		add(1688, 969);
		add(2906, 1034);
		add(2026, 1044);
		add(2405, 1048);
		add(2311, 1067);
		add(2625, 1105);
		add(2138, 1123);
		add(2405, 1273);
		add(2935, 1283);
		add(1885, 1362);
		add(2443, 1419);
		add(1102, 1428);
		add(1295, 1447);
		add(1501, 1522);
		add(2611, 1578);
		add(1571, 1592);
		add(732, 1597);
		add(1079, 1625);
		add(2171, 1681);
		add(2846, 1681);
		add(1346, 1690);
		add(3291, 1704);
		add(2518, 1775);
		add(2382, 1831);
		add(2157, 1859);
		add(859, 1887);
		add(1847, 1911);
		add(2044, 1920);
		add(1154, 1990);
		add(474, 2004);
		add(2344, 2014);
		add(2513, 2018);
		add(587, 2018);
		add(1871, 2056);
		add(906, 2089);
		add(2279, 2103);
		add(1477, 2136);
		add(2513, 2154);
		add(2105, 2154);
		add(610, 2159);
		add(2766, 2173);
		add(325, 2257);
		add(1763, 2309);
		add(802, 2332);
		add(1023, 2370);
		add(1463, 2403);
		add(643, 2417);
		add(2091, 2482);
		add(423, 2510);
		add(1074, 2632);
		add(1351, 2670);
		add(831, 2717);
		add(1683, 2721);
		add(737, 2871);
		add(2246, 2890);
		add(1712, 2942);
		add(1501, 3012);
		add(1248, 3035);
		add(1430, 3213);
		add(915, 3256);
		add(1079, 3279);
		add(1318, 3307);
		add(1515, 3340);
		add(1173, 3415);
		add(840, 3598);
	}
	isLock = true;
}

void GenshinImpact_AutoMap_Objects::initFST()
{
	if (isLock)throw"Cann't Change!";
	object = new GenshinImpact_AutoMap_Object("风神瞳", 2, 80);//66+14

	{

	}

	isLock = true;
}

void GenshinImpact_AutoMap_Objects::initFHYS()
{
	if (isLock)throw"Cann't Change!";
	object = new GenshinImpact_AutoMap_Object("绯红玉髓", 10, 80);//66+14

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
