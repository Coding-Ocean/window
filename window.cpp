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
        "edit",                     //ウィンドウクラス名
        "Coding Ocean",             //ウィンドウ名
        WS_SYSMENU | WS_VISIBLE,    //ウィンドウスタイル
        0, 0,                       //ウィンドウ表示XY座標
        256, 128,                   //ウィンドウの幅と高さ
        NULL,                       //親ウィンドウ
        NULL,                       //ウィンドウメメニュー
        NULL,                       //インスタンスハンドル
        NULL                        //アプリに追加するデータ
    );
    //メッセージ取得・送出ループ.
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
    //ウィンドウクラスの登録
    WNDCLASS wc{};
    wc.lpszClassName = "GameWindow";//ウィンドウクラス名
    wc.hInstance = hInstance;       //ＯＳが決めたこのアプリをロードするアドレス
    wc.lpfnWndProc = WinProc;       //このウィンドウに発生したメッセージを処理する関数のアドレス
    RegisterClass(&wc);

    //「ウィンドウクラスの情報」と「次のパラメータ」をもとにウィンドウをつくる
    HWND hWnd = CreateWindow(
        "GameWindow",               //ウィンドウクラス名
        "Coding Ocean",             //ウィンドウ名
        WS_OVERLAPPEDWINDOW,        //ウィンドウスタイル
        0, 0,                       //ウィンドウ表示XY座標
        256, 256,                   //ウィンドウの幅と高さ
        NULL,                       //親ウィンドウ
        NULL,                       //ウィンドウメメニュー
        hInstance,                  //インスタンスハンドル
        NULL                        //アプリに追加するデータ
    );

    ShowWindow(hWnd, SW_SHOW);

    //メッセージ取得・送出ループ.
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

    //「ウィンドウクラス構造体」の値を設定して、ウィンドウクラスを登録する
    HINSTANCE hInstance = GetModuleHandle(0);
    HBRUSH hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WNDCLASSA wc{};
    wc.lpszClassName = "GameWindow";            //ウインドウクラス名を指定
    wc.hInstance = hInstance;                   //インスタンスハンドルを指定
    wc.lpfnWndProc = WndProc;                   //コールバック関数を示すポインタを指定
    wc.hbrBackground = hBrush;                  //背景用のブラシハンドルを指定
    RegisterClass(&wc);//ここで登録！！！

    //ウィンドウクラスをもとにウィンドウを作る
    HWND hWnd = CreateWindow(
        "GameWindow",               //上で登録したウィンドウクラス名を指定
        appName,                    //ウィンドウタイトル名
        WS_SYSMENU,                 //ウィンドウスタイル
        0,                          //ウィンドウ表示位置x
        0,                          //ウィンドウ表示位置y
        windowWidth,                //ウィンドウの幅（ウィンドウ枠の幅を含む）
        windowHeight,               //ウィンドウの高さ（タイトルバーとウィンドウ枠の高さを含む）
        NULL,                       //親ウィンドウまたはオーナーウィンドウのハンドル
        NULL,                       //メニューハンドルまたは子ウィンドウID
        hInstance,                  //アプリケーションインスタンスのハンドル
        NULL                        //ウィンドウに関連付けるモジュールハンドル
    );

    //ウィンドウの大きさと位置を再計算する。
    RECT rect;
    GetClientRect(hWnd, &rect);    //直前で作ったクライアント領域の大きさを取得
    windowWidth += (windowWidth - rect.right);   //ウィンドウ枠の幅を加算
    windowHeight += (windowHeight - rect.bottom); //タイトルバーおよびウィンドウ枠の高さを加算
    //ウィンドウが中央に表示されるような表示位置を計算する。
    int windowPosX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
    int windowPosY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;
    //ウィンドウの位置と大きさを再設定
    SetWindowPos(hWnd, 0, windowPosX, windowPosY, windowWidth, windowHeight, 0);

    //ウィンドウを表示する
    ShowWindow(hWnd, SW_SHOW);

    //ゲーム用メインループ
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
        DispatchMessage(&msg); //この関数が（ＯＳ経由で） WndProc()を呼び出す
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
    //「ウィンドウクラス構造体」の値を設定して、ウィンドウクラスを登録する
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HBRUSH hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WNDCLASSA wc{};
    wc.style = CS_BYTEALIGNCLIENT;              //いくつかの定数を組み合わせてクラススタイルを指定
    wc.lpfnWndProc = WndProc;                   //コールバック関数を示すポインタを指定
    wc.hInstance = hInstance;                   //インスタンスハンドルを指定
    wc.hIcon = LoadIcon(hInstance, IDC_ICON);   //アイコンハンドルを指定
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //カーソルハンドルを指定
    wc.hbrBackground = hBrush;                  //背景用のブラシハンドルを指定
    wc.lpszClassName = "GameWindow";            //ウインドウクラス名を指定
    RegisterClass(&wc);//ここで登録！！！

    //ウィンドウスタイルを決定する
    unsigned windowStyle = WS_SYSMENU;//枠あり
    if (windowWidth == 1920 && windowHeight == 1080) {
        windowStyle = WS_POPUP;//枠無
    }

    //ウィンドウクラスをもとにウィンドウを作る
    HWND hWnd = CreateWindow(
        "GameWindow",               //上で登録したウィンドウクラス名を指定
        appName,                    //ウィンドウタイトル名
        windowStyle,                //ウィンドウスタイル
        0,                          //ウィンドウ表示位置x
        0,                          //ウィンドウ表示位置y
        windowWidth,                //ウィンドウの幅（ウィンドウ枠の幅を含む）
        windowHeight,               //ウィンドウの高さ（タイトルバーとウィンドウ枠の高さを含む）
        NULL,                       //親ウィンドウまたはオーナーウィンドウのハンドル
        NULL,                       //メニューハンドルまたは子ウィンドウID
        hInstance,                  //アプリケーションインスタンスのハンドル
        NULL                        //ウィンドウに関連付けるモジュールハンドル
    );

    //ウィンドウの大きさと位置を再計算する。
    RECT rect;
    GetClientRect(hWnd, &rect);    //直前で作ったクライアント領域の大きさを取得
    windowWidth += (windowWidth - rect.right);   //ウィンドウ枠の幅を加算
    windowHeight += (windowHeight - rect.bottom); //タイトルバーおよびウィンドウ枠の高さを加算
    //ウィンドウが中央に表示されるような表示位置を計算する。
    int windowPosX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
    int windowPosY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;
    //ウィンドウの位置と大きさを再設定
    SetWindowPos(hWnd, 0, windowPosX, windowPosY, windowWidth, windowHeight, 0);

    //ウィンドウを表示する
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