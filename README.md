# 原神自动地图（Genshin Impact Auto Map）
原神自动地图，基于原神小地图的自动标记资源地图

目前做成了原神的PC端悬浮窗地图工具……（但也实现了自动跟踪的功能），Qt重写了之后可以做的很好看，融合的毫无违和感

甚至可以做成圆的盖在原版上，一点问题没有。太赞了

目前实现了与“「空荧酒馆」原神地图”的通信和调用，发送定位、朝向与UID到“「空荧酒馆」原神地图”。

## 分支的新效果

![完美嵌入](https://github.com/GengGode/GenshinImpact_AutoMap/blob/master/Image/Snipaste_2021-02-23_20-51-30.png)

## 主分支效果

![完美嵌入](https://github.com/GengGode/GenshinImpact_AutoMap/blob/master/Image/Snipaste_2021-02-19_20-27-21.png)

![完美嵌入](https://github.com/GengGode/GenshinImpact_AutoMap/blob/master/Image/Snipaste_2021-02-19_20-30-23.png)

![完美嵌入](https://github.com/GengGode/GenshinImpact_AutoMap/blob/master/Image/Snipaste_2021-02-19_20-32-53.png)

# Qt重构中，已实现追踪+隐现，待添加标记+UI设计+启动绑定+优化
 
使用要点，设置原神窗口为无边框，关掉原神启动器，无了。

## 官服打开窗口弹不上去就闪以下的话，目前的解决方案是修改游戏的快捷方式，在目标栏添加` -popupwindow`，注意`-`号前面有个空格，如图：

![修改快捷方式](https://github.com/GengGode/GenshinImpact_AutoMap/blob/master/GenshinImpact_Map_Test_1/Img/Snipaste_2021-01-31_22-57-14.png)

启动之后按`Alt + Enter`即可切换为无边框模式

详见 https://www.bilibili.com/video/BV1u54y1W7Dg

有一点，目前只对1920x1080及1680x1050分辨率的有边框和无边框（无论是否全屏）进行了处理，关于其他分辨率还正在收集匹配的图片资源。

## 开发环境

Visual Studio 2017 

Qt5.12

opencv4.5.0

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

之后的开发中将会涉及到数据文件的保存与读取，目前会在Temp（目前版本应该会改到My Game目录下，Temp下容易被删除）目录中建立名为GenshinImpactAutoMap的文件夹，并在该文件夹中建立数据存档。

（说不定会改到AppData下的LocalLow里）

如：`C:\Users\%USERNAME%\AppData\Local\Temp\GenshinImpactAutoMap`

日后可能会开发GPU加速图像处理的功能，需要使用GPU运算。

目前为了与“「空荧酒馆」原神地图”客户端通信还使用了本机的6666端口用来发送原神角色的位置、朝向以及UID。

还有读写文件存档。

除此之外不存在其他系统资源的使用，也没有获取系统权限的需求。

## 运行画面

![运行画面](https://github.com/GengGode/GenshinImpact_AutoMap/blob/master/GenshinImpact_Map_Test_1/Img/Snipaste_2021-01-31_23-13-55.png)


### 自动跟踪与搜索神瞳

![自动跟踪](https://github.com/GengGode/GenshinImpact_AutoMap/blob/master/GenshinImpact_Map_Test_1/Img/2021-01-27%2000-27-55_5.gif)


![搜索神瞳](https://github.com/GengGode/GenshinImpact_AutoMap/blob/master/GenshinImpact_Map_Test_1/Img/2021-01-27%2000-27-55_3.gif)

## 目前实现

全局快捷键 `Alt + T` 开启关闭自动追踪

全局快捷键 `Alt + F` 添加自定义标记

全局快捷键 `Alt + M` 激活或反激活“「空荧酒馆」原神地图”客户端的大地图覆盖模式

左键拖动以及滚轮缩放地图显示

中键移动窗口位置

左键双击左上角派蒙退出

通过游戏内小地图，自动识别角色所在位置以及角色朝向

地图任意位置左键双击开启关闭自动追踪，右下角图标会有反应，根据电脑性能，3至60秒即可加载完成，悬浮窗会自动显示角色所在位置的地图，很吃性能，有时候会飘，还在调整

检测游戏状态（有时候原神和悬浮窗都显示不出来，多点两下原神就好了）

自动追踪下在某些情况下自动隐藏悬浮窗，如传送时，打开大地图时，释放大招时……这么讲，原神内置小地图什么时候可见，悬浮窗就什么时候可见

可以添加标记（只有一种自定义类型，而且还删不掉，另外还没有存档）

-- 自动发现小地图上出现的神瞳并记录 --

修复了悬浮窗自动复位时，键鼠焦点转移，导致弹出输入法的问题

添加了自动识别UID

-- 并在Temp文件夹下保存存档 --

## 计划实现

缩放改为以指针为中心（还没改，主要是映射算法问题）

添加标记改为自动（emmm，很不准）

根据数据库显示周围资源分布（以后慢慢添加）

自动记忆神瞳是否收集，判断显示哪些神瞳没被发现（正在做）

优化UI（慢慢来）

## 一些已知的问题

游戏全屏时，因为悬浮窗处于置顶状态，悬浮窗和原神会争抢顶层窗口的位置，以至于游戏来回全屏和最小化。

目前的解决方案是修改快捷方式，在目标栏添加` -popupwindow`，注意`-`号前面有个空格，如图：

![修改快捷方式](https://github.com/GengGode/GenshinImpact_AutoMap/blob/master/GenshinImpact_Map_Test_1/Img/Snipaste_2021-01-31_22-57-14.png)

启动之后按`Alt + Enter`即可切换为无边框模式（我不知道这是怎么做到的，但事实是它可以用）。

此时启动悬浮窗将不会再导致原神最小化
