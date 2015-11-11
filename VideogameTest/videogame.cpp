#include <Windows.h>
#include <d3d11.h>
#include "ContextManager.h"
#include "DebugRender.h"
#include "Application.h"

//#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"winmm.lib")
//#pragma comment(lib,"dxerr.lib")
//#pragma comment(lib,"dxguid.lib")

#define APPLICATION_NAME	"VIDEOGAME TEST"
#define WIDTH_APPLICATION	800
#define HEIGHT_APPLICATION	600

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{

  switch( msg )
  {
  case WM_DESTROY:
    {
      PostQuitMessage( 0 );
      return 0;
    }
    break;
  case WM_KEYDOWN:
    {
      switch( wParam )
      {
      case VK_ESCAPE:
        //Cleanup();
        PostQuitMessage( 0 );
        return 0;
        break;
      }
    }
    break;
  }//end switch( msg )

  return DefWindowProc( hWnd, msg, wParam, lParam );
}

//-----------------------------------------------------------------------
// WinMain
//-----------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
	CContextManager l_context;
	DWORD l_CurrentTime = 0;
	float l_ElapsedTime = 0;
	float l_PreviousTime = 0;

	// Register the window class
	WNDCLASSEX wc = {	sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, APPLICATION_NAME, NULL };

	RegisterClassEx( &wc );

	RECT rc = {
		0, 0, WIDTH_APPLICATION, HEIGHT_APPLICATION
	};
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE);

	// Create the application's window
	HWND hWnd = CreateWindow( APPLICATION_NAME, APPLICATION_NAME, WS_OVERLAPPEDWINDOW, 100, 100, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, wc.hInstance, NULL);
	
	l_context.CreateContext(hWnd, WIDTH_APPLICATION, HEIGHT_APPLICATION);

	ShowWindow( hWnd, SW_SHOWDEFAULT );
	l_context.CreateBackBuffer(hWnd, WIDTH_APPLICATION, HEIGHT_APPLICATION);
	l_context.InitStates();
	CDebugRender l_DebugRender(l_context.GetDevice());

	CApplication application(&l_DebugRender, &l_context);

	UpdateWindow( hWnd );
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );

	// Añadir en el while la condición de salida del programa de la aplicación

	while( msg.message != WM_QUIT )
	{
	if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
	else
	{
		// Main loop: Añadir aquí el Update y Render de la aplicación principal
		l_CurrentTime = timeGetTime();
		l_ElapsedTime = (float)(l_CurrentTime - l_PreviousTime)*0.001f;
		l_PreviousTime = l_CurrentTime;
		application.Update(l_ElapsedTime);
		application.Render();
	}
	}
	UnregisterClass( APPLICATION_NAME, wc.hInstance );

	// Añadir una llamada a la alicación para finalizar/liberar memoria de todos sus datos

	return 0;
}