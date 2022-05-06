#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
	HINSTANCE hInstace,//����ֱ�Ӹ�ֵ������
	HINSTANCE hPreInstance,
	LPSTR szCmdLine,
	int iCmdShow
)
{
	//���崰��������֣�MyWindows
	static TCHAR szAppName[] = TEXT("MyWindows");
	HWND hwnd;//���ھ��=����ָ�룬windowsͨ������ҵ�����
	MSG msg;
	WNDCLASS wndclass;//������ṹWNDCLASS������Ϊwndclass

	//���ڵĿ�ȸ߶ȶ�̬�ػ棬ȱһ����
	wndclass.style = CS_HREDRAW | CS_VREDRAW;//�߶ȡ����
	//wndclass.style = CS_HREDRAW ;

	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstace;//��ֵ�����˹�
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//����ͼ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//���ǹ��
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//����
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;//����������֣������Ѿ���ֵ��szAppName


	//���洰�ڵĻ�����Ϣ��д��ϣ���������ʼע���ˣ�ע����̳��ע����Ϣ�ĵ���һ����
	if (!RegisterClass(&wndclass))//����wndclassָ�룬�൱�ڰ������������Ϣ������ע�����ˣ�����ע��
	{
		MessageBox(NULL, TEXT("�������Ҫ��Windows API����ִ�У�"), szAppName, MB_ICONERROR);
		return 0;
	}

	//����ע�ắ�����жϣ������жϣ��������dos��ִ�У��ͻ�������������Ҫ��Windows API����ִ�У���
	//�����Windowsϵͳ�£�����ִ�гɹ��ˣ�������ִ�����к�����CreateWindow�����������hwnd��hwndץס�˰ѱ����൱�ڷ���һ�����
	hwnd = CreateWindow(//�ḻ���ڸ��Ի��Ĳ��������涨�崰����ṹ�����︺��ḻ��������Ի�
		szAppName,//����������
		TEXT("��C������"),//���ڱ���
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,//Ĭ��ֵ
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstace,
		NULL
	);//������ڷḻ��Ϣ�������˺ܶ�


	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);//�൱��F5ˢ�´���

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;

}

//���ڹ��̣�
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
	int i;

	switch (message)
	{
	case WM_PAINT://���ڻ���
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);

		for (i = rect.left; i <= rect.right; i++)//�ѵ����ѭ�����Ϳ��Եõ�һ����
			SetPixel(hdc, i, 100, RGB(255, 0, 0));

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY://�˳���Ϣ
		PostQuitMessage(0);//�˳����ش���
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);//
}