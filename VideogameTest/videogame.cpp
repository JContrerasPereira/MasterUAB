#include <Windows.h>
#include <d3d11.h>
#include "ContextManager.h"
#include "DebugRender.h"
#include "Application.h"
#include "InputManagerImplementation.h"
#include "SphericalCameraController.h"

//#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"winmm.lib")
//#pragma comment(lib,"dxerr.lib")
//#pragma comment(lib,"dxguid.lib")

#define APPLICATION_NAME	"VIDEOGAME TEST"
#define WIDTH_APPLICATION	800
#define HEIGHT_APPLICATION	600

CContextManager l_context;

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
  case WM_SIZE:
	  if (wParam != SIZE_MINIMIZED)
	  {
		  l_context.Resize(hWnd, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam));
	  }
	  return 0;
    break;
  }//end switch( msg )

  return DefWindowProc( hWnd, msg, wParam, lParam );
}

//-----------------------------------------------------------------------
// WinMain
//-----------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
	DWORD l_CurrentTime = 0;
	float l_ElapsedTime = 0;
	float l_PreviousTime = 0;
	CInputManagerImplementation l_InputManager;

	CInputManager::SetCurrentInputManager(&l_InputManager);

	l_InputManager.LoadCommandsFromFile("Data\\input.xml");

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
	CSphericalCameraController l_Camera;

	CApplication application(&l_DebugRender, &l_context, l_Camera);

	UpdateWindow( hWnd );
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );

	// Añadir en el while la condición de salida del programa de la aplicación

	while( msg.message != WM_QUIT )
	{
		l_CurrentTime = timeGetTime();
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			switch (msg.message)
			{
				case WM_SYSKEYDOWN:
				case WM_SYSKEYUP:
				case WM_KEYDOWN:
				case WM_KEYUP:
					if (!l_InputManager.KeyEventReceived(msg.wParam, msg.lParam))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
					break;
				default:
					TranslateMessage(&msg);
					DispatchMessage(&msg);
			}
		}
		else
		{
			l_InputManager.BeginFrame();
			l_ElapsedTime = (float)(l_CurrentTime - l_PreviousTime)*0.1f;
			l_PreviousTime = l_CurrentTime;
			application.Update(l_ElapsedTime);
			application.Render();
			l_InputManager.EndFrame();
		}
	}
	UnregisterClass( APPLICATION_NAME, wc.hInstance );

	// Añadir una llamada a la alicación para finalizar/liberar memoria de todos sus datos

	return 0;
}