#include<windows.h>
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
    HDC hDC;
    PAINTSTRUCT ps;
    RECT rect;
    HFONT hFont;
    HGDIOBJ hGDI;
    const WCHAR* str = L"�R�[�f�B���O�I�[�V����";

    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT: //�E�B���h�E�̕`��
        GetClientRect(hWnd, &rect);
        hDC = BeginPaint(hWnd, &ps);

        //�����ݒ肵�Ȃ���Ԃŏo�͂��Ă݂�
        rect.top += DrawText(hDC, str, -1, &rect, DT_WORDBREAK);

        hFont = CreateFont(
            60, 0,					//����, ��
            0, 0,					//�p�x1, �p�x2
            FW_DONTCARE,			//����
            FALSE, FALSE, FALSE,	//�Α�, ����, �ŏ�����
            ANSI_CHARSET,		//�����Z�b�g
            OUT_DEFAULT_PRECIS,		//���x
            CLIP_DEFAULT_PRECIS,	//���x
            DEFAULT_QUALITY,		//�i��
            DEFAULT_PITCH | FF_DONTCARE, //�s�b�`�ƃt�@�~��
            L"�������t�H���gB");			//�t�H���g��
        
        hGDI = SelectObject(hDC, hFont);

        SetBkMode(hDC, TRANSPARENT);
        SetTextColor(hDC, RGB(200, 200, 0));
        rect.top += DrawText(hDC, str, -1, &rect, DT_WORDBREAK);

        SetTextColor(hDC, RGB(0, 200, 200));

        WCHAR str[64];
        wsprintf(str, L"�T�؍�46");
        for (int i = 0; i < 5; i++) {
            TextOut(hDC, 10, 100 + 60 * i, &str[i], 1);
        }



        SelectObject(hDC, hGDI); //�t�H���g�����ɖ߂�
        DeleteObject(hFont);	//�I�u�W�F�N�g�폜

        EndPaint(hWnd, &ps);

        return 0;
    default:
        return DefWindowProc(hWnd, uMsg, wp, lp);
    }
}
bool quit()
{
    MSG msg;
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
        DispatchMessage(&msg); //���̊֐����i�n�r�o�R�Łj WndProc()���Ăяo��
    }
    return msg.message == WM_QUIT;
}
bool escKeyPressed()
{
    return GetAsyncKeyState(VK_ESCAPE) & 0x8000;
}
void closeWindow()
{
    HWND hWnd = FindWindow(L"GameWindow", NULL);
    PostMessage(hWnd, WM_CLOSE, 0, 0);
}
void createWindow(const WCHAR* appName, int windowWidth, int windowHeight)
{
    //�u�E�B���h�E�N���X�\���́v�̒l��ݒ肵�āA�E�B���h�E�N���X��o�^����
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HBRUSH hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WNDCLASS wc{};
    wc.style = CS_BYTEALIGNCLIENT;              //�������̒萔��g�ݍ��킹�ăN���X�X�^�C�����w��
    wc.lpfnWndProc = WndProc;                   //�R�[���o�b�N�֐��������|�C���^���w��
    wc.hInstance = hInstance;                   //�C���X�^���X�n���h�����w��
    wc.hIcon = LoadIcon(hInstance, IDC_ICON);   //�A�C�R���n���h�����w��
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�J�[�\���n���h�����w��
    wc.hbrBackground = hBrush;                  //�w�i�p�̃u���V�n���h�����w��
    wc.lpszClassName = L"GameWindow";            //�E�C���h�E�N���X�����w��
    RegisterClass(&wc);//�����œo�^�I�I�I

    //�E�B���h�E�X�^�C�������肷��
    unsigned windowStyle = WS_SYSMENU;//�g����
    if (windowWidth == 1920 && windowHeight == 1080) {
        windowStyle = WS_POPUP;//�g��
    }

    //�E�B���h�E�N���X�����ƂɃE�B���h�E�����
    HWND hWnd = CreateWindow(
        L"GameWindow",               //��œo�^�����E�B���h�E�N���X�����w��
        appName,                    //�E�B���h�E�^�C�g����
        windowStyle,                //�E�B���h�E�X�^�C��
        0,                          //�E�B���h�E�\���ʒux
        0,                          //�E�B���h�E�\���ʒuy
        windowWidth,                //�E�B���h�E�̕��i�E�B���h�E�g�̕����܂ށj
        windowHeight,               //�E�B���h�E�̍����i�^�C�g���o�[�ƃE�B���h�E�g�̍������܂ށj
        NULL,                       //�e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
        NULL,                       //���j���[�n���h���܂��͎q�E�B���h�EID
        hInstance,                  //�A�v���P�[�V�����C���X�^���X�̃n���h��
        NULL                        //�E�B���h�E�Ɋ֘A�t���郂�W���[���n���h��
    );

    //�E�B���h�E�̑傫���ƈʒu���Čv�Z����B
    RECT rect;
    GetClientRect(hWnd, &rect);    //���O�ō�����N���C�A���g�̈�̑傫�����擾
    windowWidth += (windowWidth - rect.right);   //�E�B���h�E�g�̕������Z
    windowHeight += (windowHeight - rect.bottom); //�^�C�g���o�[����уE�B���h�E�g�̍��������Z
    //�E�B���h�E�������ɕ\�������悤�ȕ\���ʒu���v�Z����B
    int windowPosX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
    int windowPosY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;
    //�E�B���h�E�̈ʒu�Ƒ傫�����Đݒ�
    SetWindowPos(hWnd, 0, windowPosX, windowPosY, windowWidth, windowHeight, 0);

    //�E�B���h�E��\������
    ShowWindow(hWnd, SW_SHOW);
}
int APIENTRY WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ INT)
{
    createWindow(L"Coding Ocean", 1920 / 2, 1080 / 2);

    bool loopFlag = true;
    while (loopFlag) {
        if (quit()) {
            loopFlag = false;
            continue;
        }

        HWND hWnd = GetActiveWindow();

        if (hWnd == NULL) {
            continue;
        }

        if (escKeyPressed()) {
            closeWindow();
        }

        HDC hDC = GetDC(hWnd);
        SetBkMode(hDC, TRANSPARENT);

        ReleaseDC(hWnd, hDC);

        Sleep(1);
    }

    return 0;
}
