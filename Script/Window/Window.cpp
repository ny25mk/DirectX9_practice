#include "Window.h"

Window::Window()
	:widthSize(640), heightSize(480), nCmdShow(SW_SHOW){

	hInstance = GetModuleHandle(NULL);
	SetWindowName(Default_WindowName);

}

Window::~Window(){

	DestroyWindow(hWnd);		//Windowの破棄
	MessageBox(NULL, _T("デストローイ"), _T("メッセージ"), MB_OK);

}

/// <summary>
/// @brief ウィンドウを生成するクラス
/// </summary>
/// <returns>true 生成</returns>
/// <returns>false 生成失敗</returns>
bool Window::WindowInit(){

#pragma region どのようなウィンドウを作成するか
	wc.cbClsExtra = 0;											//構造体のサイズを拡張するバイト数
	wc.cbWndExtra = 0;											//ウィンドウのサイズを拡張するバイト数
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);		//ウィンドウの背景を塗りつぶすブラシ
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);				//ウィンドウ上にマウスカーソルが来た場合のマウスの形状
	wc.hIcon = NULL;											//ウィンドウのアイコン（LoadImage()でつけてもよい）
	wc.hInstance = hInstance;									//ウィンドウを作るためのインスタンスハンドルを指定
	wc.lpfnWndProc = WndProc;									//ウィンドウから通知されたイベントを処理するための関数を指定
	wc.lpszClassName = _T("WindowsAPI");						//登録するウィンドウのクラス名
	wc.lpszMenuName = NULL;										//メニューのリソースID
	wc.style = NULL;											//ウィンドウクラスのスタイル

	//ウィンドウの登録に失敗した場合終了させる
	if(!RegisterClass(&wc)){
		MessageBox(NULL, _T("ウィンドウの登録に失敗しました"), _T("エラー"), MB_OK);
		return false;
	}
#pragma endregion

#pragma region ウィンドウの作成
	hWnd = CreateWindow(
		wc.lpszClassName,								//登録されているクラス名
		windowName,										//ウィンドウのタイトル
		(WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),		//ウィンドウのスタイル(タイトル、システム、最小化使用)
		CW_USEDEFAULT,									//ウィンドウのx位置(システム標準値を使用)
		CW_USEDEFAULT,									//ウィンドウのy位置
		widthSize,										//ウィンドウの幅
		heightSize,										//ウィンドウの高さ
		NULL,											//親ウィンドウのハンドル
		NULL,											//メニューハンドル
		hInstance,
		NULL											//ウィンドウ作成時のイベントへ渡すデータのポインタ
		);

	if(!hWnd){
		MessageBox(NULL, _T("ウィンドウの生成に失敗しました"), _T("エラー"), MB_OK);
		return false;
	}

	//ウィンドウサイズの調整
	RECT r1, r2;

	GetClientRect(hWnd, &r1);
	GetWindowRect(hWnd, &r2);
	MoveWindow(
		hWnd, r2.left, r2.top,
		widthSize + ((r2.right - r2.left) - (r1.right - r1.left)),
		heightSize + ((r2.bottom - r2.top) - (r1.bottom - r1.top)),
		false
	);
#pragma endregion

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);

	MessageBox(NULL, _T("ショーウインドー"), _T("メッセージ"), MB_OK);

	return true;
}

/// <summary>
/// @brief ウィンドウの処理を行う
/// </summary>
/// <returns>true それ以外</returns>
/// <returns>false QUITメッセージ</returns>
bool Window::Process() const{

	MSG msg;

	//ウィンドウに通達されようとしているイベントを取得
	if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
		if(msg.message == WM_QUIT){
			return false;
		}

		TranslateMessage(&msg);	//仮想キーメッセージを文字メッセージへ変換
		DispatchMessage(&msg);	//ウィンドウイベントを通達
	}

	return true;
}