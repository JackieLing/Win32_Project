# Windows基础=窗口编程

[TOC]



# 一、概念

> 先有编程后有OS，学习Windows编程主要是积累Windows API。
>
> Windows编程的游戏规则：在之前的编程中，我们都是用户来调用函数名进行相应函数的调用执行，Windows编程则是用户发送消息告诉Windows操作系统，由WIndows系统通过消息队列来间接调用我们的函数。

**Windows编程**是基于Windows系统环境下的编程，利用微软提供的`Windows API`调用接口实现用户与硬件的交互；这门课在大学期间没有接触过，大学接触的C语言、C++只是一种高级编程语言，相当于在背单词，而Windows编程相当于在写文章，进行自由创作；大学学习C和C++只是基于黑窗口Dos编程，进行简单的思维训练。

需要重新接触这门知识需要具备的基础：

+ C和C++
+ OS
+ 数据结构

以上基础都是我们在学校接触过的知识，所以入门并不算难，关键在于练。



## 1.1、第一个程序打招呼

```c++
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hprevInstance,
	PSTR szCmdLine,
	int icmdShow)
{
	MessageBox(NULL,TEXT("第一个程序"), TEXT("打招呼"), MB_OK);
	return 0;
}
```

![image-20220425171254227](https://gitee.com/jackieling/xp01/raw/master/202204261543973.png)

# 二、窗口(消息框、控制条、子窗口控件)

消息框是一个窗口，VS2013也是一个窗口，浏览器也是一个窗口，甚至我们的桌面也是一个窗口程序，还有一些看起来不明显的，例如各种按钮、单选按钮、复选按钮、列表框、滚动条这些其实也都是窗口。

```c++
#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
	HINSTANCE hInstace,//参数直接赋值到下列
	HINSTANCE hPreInstance,
	LPSTR szCmdLine,
	int iCmdShow
)
{
	//定义窗口类的名字：MyWindows
	static TCHAR szAppName[] = TEXT("MyWindows");
	HWND hwnd;//窗口句柄=特殊指针，windows通过句柄找到窗口
	MSG msg;
	WNDCLASS wndclass;//窗口类结构WNDCLASS，对象为wndclass

	//窗口的宽度高度动态重绘，缺一不可
	wndclass.style = CS_HREDRAW | CS_VREDRAW;//高度、宽度
	//wndclass.style = CS_HREDRAW ;

	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstace;//赋值，搬运工
	wndclass.hIcon= LoadIcon(NULL,IDI_APPLICATION);//这是图标
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);//这是光标
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//背景
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;//窗口类的名字，上面已经赋值了szAppName


	//上面窗口的基本信息填写完毕，接下来开始注册了，注册论坛，注册信息的道理一样。
	if (!RegisterClass(&wndclass))//传入wndclass指针，相当于把上面的所有信息都传进注册类了，进行注册
	{
		MessageBox(NULL,TEXT("这个程序要在Windows API才能执行！"), szAppName, MB_ICONERROR);
		return 0;
	}

	//以上注册函数的判断，在于判断，如果你在dos下执行，就会输出：这个程序要在Windows API才能执行！；
	//如果在Windows系统下，就算执行成功了，接下来执行下列函数：CreateWindow，句柄传给了hwnd，hwnd抓住了把柄，相当于返回一个句柄
	hwnd = CreateWindow(//丰富窗口个性化的参数，上面定义窗口类结构，这里负责丰富，负责个性化
		szAppName,//窗口类名称
		TEXT("鱼C工作室"),//窗口标题
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,//默认值
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstace,
		NULL
	);//以上填窗口丰富信息，个性了很多


	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);//相当于F5刷新窗口

	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;

}

//窗口过程：
LRESULT CALLBACK WndProc(
	HWND hwnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
	
)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	switch (message)
	{
	case WM_PAINT://窗口绘制
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);//获取客户区的填充信息rect
		DrawText(hdc,TEXT("大家好，这是我的第一个窗口"), -1, &rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY://退出消息
		PostQuitMessage(0);//退出返回代码
		return 0;
	}
	return DefWindowProc(hwnd,message,wParam,lParam);//
}
```

![image-20220425181500795](https://gitee.com/jackieling/xp01/raw/master/202204261543974.png)

## 2.1、窗口的诞生

窗口诞生的过程：

![image-20220427094957062](https://gitee.com/jackieling/xp01/raw/master/202204271120880.png)

## 2.2、事件驱动

> Windows是一个事件驱动，基于消息机制的操作系统。

## 2.3、窗口过程

客户区和非客户区：

![image-20220427103017422](https://gitee.com/jackieling/xp01/raw/master/202204271120882.png)



```c++
##加了一个模块：左键单击提醒
	case WM_LBUTTONDOWN:
		MessageBox(hwnd,TEXT("哎呀，我丫的被按了"), TEXT("好舒服"), MB_OK);
		return 0;
```



![image-20220427133819792](https://gitee.com/jackieling/xp01/raw/master/202204271432059.png)

![image-20220427135341241](https://gitee.com/jackieling/xp01/raw/master/202204271432060.png)

## 总结：

> ​		在之前的编程中，我们都是用户来调用函数名进行相应函数的调用执行，Windows编程则是用户发送消息告诉Windows操作系统，由WIndows系统通过消息队列来间接调用我们的函数。
>
> 我们写的代码包含两部分：
>
> + 入口函数WinMain：
>
>   + 注册窗口类
>   + 创建窗口
>   + 从消息队列中检索消息、分配消息
>
> + 窗口过程代码WndProc
>
>   + 三个case 响应操作
>
>     

# 三、文本输出

> Windows三大核心部件：
>
> 1. Kernel
> 2. GDI
> 3. user

GDI：图形设备接口，使应用程序能够在视频显示器和打印机上使用图形和格式化文本。

使用GDI之前需要设置设备环境句柄,这个设备环境句柄就是GDI函数的通行证，只有有了这个句柄，才能知道如何调用GDI函数：

```c++
方法一：
hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);//获取客户区的填充信息rect
		xxx;//使用GDI函数
EndPaint(hwnd, &ps);
```

```c++
方法二：
hdc=GetDC(hwnd);
	xxx;//使用GDI函数
ReleaseDC(hwnd,hdc);
```

![image-20220427142524099](https://gitee.com/jackieling/xp01/raw/master/202204271432061.png)

```c++
//实现上图代码：
case WM_PAINT://窗口绘制
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);//获取客户区的填充信息rect
		//DrawText(hdc, TEXT("大家好，这是我的第一个窗口"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		//改用TextOut：
		TextOut(hdc,400,300,TEXT("I love you"), 10);//自己用勾股定理计算

		EndPaint(hwnd, &ps);
		return 0;
```

# 四、使用字符串处理

![image-20220427142734573](https://gitee.com/jackieling/xp01/raw/master/202204271432062.png)

