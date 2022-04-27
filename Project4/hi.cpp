#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//入口函数
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
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//这是图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//这是光标
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//背景
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;//窗口类的名字，上面已经赋值了szAppName


	//上面窗口的基本信息填写完毕，接下来开始注册了，注册论坛，注册信息的道理一样。
	if (!RegisterClass(&wndclass))//传入wndclass指针，相当于把上面的所有信息都传进注册类了，进行注册
	{
		MessageBox(NULL, TEXT("这个程序要在Windows API才能执行！"), szAppName, MB_ICONERROR);
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


	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);//相当于F5刷新窗口

	//从消息队列中检索消息
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//发送消息
		DispatchMessage(&msg);//分发消息
	}
	return msg.wParam;

}

//窗口过程代码：
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
		//DrawText(hdc, TEXT("大家好，这是我的第一个窗口"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		//改用TextOut：
		TextOut(hdc,400,300,TEXT("I love you"), 10);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd,TEXT("哎呀，我丫的被按了"), TEXT("好舒服"), MB_OK);
		return 0;

	case WM_CLOSE:
		if (MessageBox(hwnd, TEXT("请问是否真的要关闭我？"), TEXT("请确认"), MB_YESNO) == IDYES)
			DestroyWindow(hwnd);
		else
			return 0;

	case WM_DESTROY://退出消息
		PostQuitMessage(0);//退出返回代码
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);//
}