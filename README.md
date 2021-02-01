# 原神自动地图（Genshin Impact Auto Map）
原神自动地图，基于原神小地图的自动标记资源地图

目前做成了原神的PC端悬浮窗地图工具……（但也实现了自动跟踪的功能）

 
原神悬浮窗v.0.8.2 修复了不能单独启动的bug，添加了绯红玉髓标记，但没有自动识别玉髓

迅雷网盘
链接：https://pan.xunlei.com/s/VMSSInYRm0g20pDRFCczyPIeA1
提取码：qeqp

原神悬浮窗v.0.8.1 修复了不能单独启动的bug

蓝奏云盘
链接：https://wws.lanzous.com/iip8el5y0te
密码:bwiv

使用要点，没啥要点，先开悬浮窗，再开原神，关掉启动器，无了

## 官服打开窗口弹不上去就闪以下的话，目前的解决方案是修改游戏的快捷方式，在目标栏添加` -popupwindow`，注意`-`号前面有个空格，如图：

![修改快捷方式](https://github.com/GengGode/GenshinImpact_AutoMap/blob/master/GenshinImpact_Map_Test_1/Img/Snipaste_2021-01-31_22-57-14.png)

启动之后按`Alt + Enter`即可切换为无边框模式

有一点，目前只对1920x1080分辨率进行了处理，包括全屏与窗口，但对其他分辨率，emmm可能能用，大概率会出问题。

有遇到Bug可以尝试自己解决下，我如果发现了会尽量处理，目前的重心在调整匹配精度上。

## 开发环境

Visual Studio 2017 

opencv4.5.0

控制台应用

在VS里配置好Opencv即可进行编译输出，选择项目GenshinImpact_Map_Test_1生成，所用资源文件均已上传至Res文件夹。

由于使用的是opencv的dll，以及程序中封装了一张较大的地图图片，所以最后生成的程序大概有37MB，发布版解压缩大致有92MB，以至于无法上传至GitHub，有需要的可以自己手动编译，或者点击上方链接下载。

链接版本只经过简单测试，如有任何问题可以提交反馈。

## 工作原理与系统权限

本地图是通过调用Windows Api来对原神的游戏窗口进行截屏，然后对画面进行图像处理，对地图与世界地图进行匹配来实现的自动追踪。

通过Api来设置地图为顶层窗口，使其保持在原神游戏窗口的上方。

目前所有涉及对原神窗口的操作如下：

`giHandle = FindWindowA(NULL, "原神");` 获取原神窗口句柄

`giIsDisplayFlag = !IsIconic(giHandle);` 判断原神是否处于最小化

`GetWindowRect(giHandle, &giRect);` 获取原神窗口区域

`HDC hScreen = GetDC(giHandle);` 获取原神窗口画面，作用是截屏获取原神画面

`SetForegroundWindow(giHandle);` 激活原神窗口为焦点

`if (giHandle != NULL)` 判断原神窗口句柄是否为空

之后的开发中将会涉及到数据文件的保存与读取，目前会在Temp目录中建立名为GenshinImpactAutoMap的文件夹，并在该文件夹中建立数据存档。

如：`C:\Users\%USERNAME%\AppData\Local\Temp\GenshinImpactAutoMap`

日后可能会开发GPU加速图像处理的功能，需要使用GPU运算。

除此之外不存在其他系统资源的使用，也没有获取系统权限的需求。

## 运行画面

![运行画面](https://github.com/GengGode/GenshinImpact_AutoMap/blob/master/GenshinImpact_Map_Test_1/Img/Snipaste_2021-01-31_23-13-55.png)


### 自动跟踪与搜索神瞳

![自动跟踪](https://github.com/GengGode/GenshinImpact_AutoMap/blob/master/GenshinImpact_Map_Test_1/Img/2021-01-27%2000-27-55_5.gif)


![搜索神瞳](https://github.com/GengGode/GenshinImpact_AutoMap/blob/master/GenshinImpact_Map_Test_1/Img/2021-01-27%2000-27-55_3.gif)

## 目前实现

左键拖动以及滚轮缩放地图显示

中键移动窗口位置（有Bug，会闪）

左键双击右上角❌退出

双击开启关闭自动追踪，悬浮窗会自动显示角色所在位置的地图，有点慢，有时候会飘，还在调整

检测游戏状态（有时候原神和悬浮窗都显示不出来，多点两下原神就好了）

可以添加标记（代码里，目前只做了两种神瞳）

通过游戏内小地图，自动识别角色所在位置

自动发现小地图上出现的神瞳并记录

自动追踪下在某些情况下自动隐藏悬浮窗，如传送时，打开大地图时，释放大招时……这么讲，原神内置小地图什么时候可见，悬浮窗就什么时候可见

修复了悬浮窗自动复位时，键鼠焦点转移，导致弹出输入法的问题

添加了自动识别UID，并在Temp文件夹下保存存档

## 计划实现

缩放改为以指针为中心（还没改，主要是映射算法问题）

添加标记改为自动（emmm，很不准）

根据数据库显示周围资源分布（以后慢慢添加）

自动记忆神瞳是否收集，判断显示哪些神瞳没被发现（正在做）

优化UI（可能会优化吧，或许吧）

## 更远的计划

利用MFC或者Qt重写一个窗口，不再使用OpenCV提供的窗口，以便实现不规则窗口和边缘半透明效果

根据另一个做的小地图自动识别来看，还得优化自动识别的速度

## 一些已知的问题

游戏全屏时，因为悬浮窗处于置顶状态，悬浮窗和原神会争抢顶层窗口的位置，以至于游戏来回全屏和最小化。

目前的解决方案是修改快捷方式，在目标栏添加` -popupwindow`，注意`-`号前面有个空格，如图：

![修改快捷方式](https://github.com/GengGode/GenshinImpact_AutoMap/blob/master/GenshinImpact_Map_Test_1/Img/Snipaste_2021-01-31_22-57-14.png)

启动之后按`Alt + Enter`即可切换为无边框模式（我不知道这是怎么做到的，但事实是它可以用）。

此时启动悬浮窗将不会再导致原神最小化

中键拖动窗口会闪烁，这个是由于OpenCV的鼠标回调返回的鼠标位置是基于窗口左上角的，拖动的话，在窗口移动时，鼠标的坐标是不变的，有点难以处理，用MFC或者Qt重写了可能会好些吧。
