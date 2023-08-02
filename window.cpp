#include<windows.h>
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
    HDC hDC;
    PAINTSTRUCT ps;
    RECT rect;
    HFONT hFont;
    HGDIOBJ hGDI;
    const WCHAR* str = L"コーディングオーシャン";

    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT: //ウィンドウの描画
        GetClientRect(hWnd, &rect);
        hDC = BeginPaint(hWnd, &ps);

        //何も設定しない状態で出力してみる
        rect.top += DrawText(hDC, str, -1, &rect, DT_WORDBREAK);

        hFont = CreateFont(
            60, 0,					//高さ, 幅
            0, 0,					//角度1, 角度2
            FW_DONTCARE,			//太さ
            FALSE, FALSE, FALSE,	//斜体, 下線, 打消し線
            ANSI_CHARSET,		//文字セット
            OUT_DEFAULT_PRECIS,		//精度
            CLIP_DEFAULT_PRECIS,	//精度
            DEFAULT_QUALITY,		//品質
            DEFAULT_PITCH | FF_DONTCARE, //ピッチとファミリ
            L"あずきフォントB");			//フォント名
        
        hGDI = SelectObject(hDC, hFont);

        SetBkMode(hDC, TRANSPARENT);
        SetTextColor(hDC, RGB(200, 200, 0));
        rect.top += DrawText(hDC, str, -1, &rect, DT_WORDBREAK);

        SetTextColor(hDC, RGB(0, 200, 200));

        WCHAR str[64];
        wsprintf(str, L"乃木坂46");
        for (int i = 0; i < 5; i++) {
            TextOut(hDC, 10, 100 + 60 * i, &str[i], 1);
        }



        SelectObject(hDC, hGDI); //フォントを元に戻す
        DeleteObject(hFont);	//オブジェクト削除

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
    HWND hWnd = FindWindow(L"GameWindow", NULL);
    PostMessage(hWnd, WM_CLOSE, 0, 0);
}
void createWindow(const WCHAR* appName, int windowWidth, int windowHeight)
{
    //「ウィンドウクラス構造体」の値を設定して、ウィンドウクラスを登録する
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HBRUSH hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WNDCLASS wc{};
    wc.style = CS_BYTEALIGNCLIENT;              //いくつかの定数を組み合わせてクラススタイルを指定
    wc.lpfnWndProc = WndProc;                   //コールバック関数を示すポインタを指定
    wc.hInstance = hInstance;                   //インスタンスハンドルを指定
    wc.hIcon = LoadIcon(hInstance, IDC_ICON);   //アイコンハンドルを指定
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //カーソルハンドルを指定
    wc.hbrBackground = hBrush;                  //背景用のブラシハンドルを指定
    wc.lpszClassName = L"GameWindow";            //ウインドウクラス名を指定
    RegisterClass(&wc);//ここで登録！！！

    //ウィンドウスタイルを決定する
    unsigned windowStyle = WS_SYSMENU;//枠あり
    if (windowWidth == 1920 && windowHeight == 1080) {
        windowStyle = WS_POPUP;//枠無
    }

    //ウィンドウクラスをもとにウィンドウを作る
    HWND hWnd = CreateWindow(
        L"GameWindow",               //上で登録したウィンドウクラス名を指定
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
