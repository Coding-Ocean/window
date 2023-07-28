#if 0
#include<windows.h>
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
    MessageBox(0, "AKB", "48", 0);
}
#endif

#if 0
#include<windows.h>
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
    HWND hWnd = CreateWindow(
        "edit",                     //�E�B���h�E�N���X��
        "Coding Ocean",             //�E�B���h�E��
        WS_SYSMENU | WS_VISIBLE,    //�E�B���h�E�X�^�C��
        0, 0,                       //�E�B���h�E�\��XY���W
        256, 128,                   //�E�B���h�E�̕��ƍ���
        NULL,                       //�e�E�B���h�E
        NULL,                       //�E�B���h�E�����j���[
        NULL,                       //�C���X�^���X�n���h��
        NULL                        //�A�v���ɒǉ�����f�[�^
    );
    //���b�Z�[�W�擾�E���o���[�v.
    MSG msg{};
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_NCLBUTTONDOWN &&
            msg.wParam == HTCLOSE) {
            return 0;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
#endif

#if 0
#include <windows.h>
LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
    //�E�B���h�E�N���X�̓o�^
    WNDCLASS wc{};
    wc.lpszClassName = "GameWindow";//�E�B���h�E�N���X��
    wc.hInstance = hInstance;       //�n�r�����߂����̃A�v�������[�h����A�h���X
    wc.lpfnWndProc = WinProc;       //���̃E�B���h�E�ɔ����������b�Z�[�W����������֐��̃A�h���X
    RegisterClass(&wc);

    //�u�E�B���h�E�N���X�̏��v�Ɓu���̃p�����[�^�v�����ƂɃE�B���h�E������
    HWND hWnd = CreateWindow(
        "GameWindow",               //�E�B���h�E�N���X��
        "Coding Ocean",             //�E�B���h�E��
        WS_OVERLAPPEDWINDOW,        //�E�B���h�E�X�^�C��
        0, 0,                       //�E�B���h�E�\��XY���W
        256, 256,                   //�E�B���h�E�̕��ƍ���
        NULL,                       //�e�E�B���h�E
        NULL,                       //�E�B���h�E�����j���[
        hInstance,                  //�C���X�^���X�n���h��
        NULL                        //�A�v���ɒǉ�����f�[�^
    );

    ShowWindow(hWnd, SW_SHOW);

    //���b�Z�[�W�擾�E���o���[�v.
    MSG msg{};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

#endif

#if 0
#include<windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, uMsg, wp, lp);
    }
}

int APIENTRY WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ INT)
{
    const char* appName = "Coding Ocean";
    int windowWidth = 800;
    int windowHeight = 450;

    //�u�E�B���h�E�N���X�\���́v�̒l��ݒ肵�āA�E�B���h�E�N���X��o�^����
    HINSTANCE hInstance = GetModuleHandle(0);
    HBRUSH hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WNDCLASSA wc{};
    wc.lpszClassName = "GameWindow";            //�E�C���h�E�N���X�����w��
    wc.hInstance = hInstance;                   //�C���X�^���X�n���h�����w��
    wc.lpfnWndProc = WndProc;                   //�R�[���o�b�N�֐��������|�C���^���w��
    wc.hbrBackground = hBrush;                  //�w�i�p�̃u���V�n���h�����w��
    RegisterClass(&wc);//�����œo�^�I�I�I

    //�E�B���h�E�N���X�����ƂɃE�B���h�E�����
    HWND hWnd = CreateWindow(
        "GameWindow",               //��œo�^�����E�B���h�E�N���X�����w��
        appName,                    //�E�B���h�E�^�C�g����
        WS_SYSMENU,                 //�E�B���h�E�X�^�C��
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

    //�Q�[���p���C�����[�v
    MSG msg{};
    while (true){
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
            if (msg.message == WM_QUIT){
                return 0;
            }
            DispatchMessage(&msg);
        }

        if (GetAsyncKeyState(VK_ESCAPE)){
            PostMessage(hWnd, WM_CLOSE, 0, 0);
        }

        Sleep(1);
    }

    return 0;
}
#endif 

#if 0
#include<windows.h>
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
    switch (uMsg){
    case WM_DESTROY:
        PostQuitMessage(0);
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
    HWND hWnd = FindWindow("GameWindow", NULL);
    PostMessage(hWnd, WM_CLOSE, 0, 0);
}
void createWindow(const char* appName, int windowWidth, int windowHeight)
{
    //�u�E�B���h�E�N���X�\���́v�̒l��ݒ肵�āA�E�B���h�E�N���X��o�^����
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HBRUSH hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WNDCLASSA wc{};
    wc.style = CS_BYTEALIGNCLIENT;              //�������̒萔��g�ݍ��킹�ăN���X�X�^�C�����w��
    wc.lpfnWndProc = WndProc;                   //�R�[���o�b�N�֐��������|�C���^���w��
    wc.hInstance = hInstance;                   //�C���X�^���X�n���h�����w��
    wc.hIcon = LoadIcon(hInstance, IDC_ICON);   //�A�C�R���n���h�����w��
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�J�[�\���n���h�����w��
    wc.hbrBackground = hBrush;                  //�w�i�p�̃u���V�n���h�����w��
    wc.lpszClassName = "GameWindow";            //�E�C���h�E�N���X�����w��
    RegisterClass(&wc);//�����œo�^�I�I�I

    //�E�B���h�E�X�^�C�������肷��
    unsigned windowStyle = WS_SYSMENU;//�g����
    if (windowWidth == 1920 && windowHeight == 1080) {
        windowStyle = WS_POPUP;//�g��
    }

    //�E�B���h�E�N���X�����ƂɃE�B���h�E�����
    HWND hWnd = CreateWindow(
        "GameWindow",               //��œo�^�����E�B���h�E�N���X�����w��
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
    createWindow("Coding Ocean", 1920/2, 1080/2);

    while (!quit()){
        if (escKeyPressed()) {
            closeWindow();
        }

        Sleep(1);
    }

    return 0;
}
#endif 