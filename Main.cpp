// heb lopen editen in: d3dx9math.inl !!! (disabled math.h include)

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "Handy.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>

#include <mmsystem.h>
#include <mmreg.h>

#define APP_WIDTH  800
#define APP_HEIGHT 600

int timer = 0;

#define MAINCOLOR 0xFFF4AB78
//#define OVERLAY_COLOR 0xff4C0610

DWORD OVERLAY_COLOR = 0xFFF4AB78;

			// 0xFFCFB898


			// F4AB78
			// 4C0610

struct OVERLAY_VERTEX
{
    float	x, y, z;
	float	rhw;
	DWORD	diffuse;   
};

#include "Synth.h"
#include "D3D.h"
#include "Tubes.h"



// D3DFVF_XYZRHW D3DFVF_DIFFUSE

//int mainCRTStartup(void)
int WinMainCRTStartup(void)


{
	int i;

	// create window
	HWND window = CreateWindowEx(WS_EX_TOPMOST, 
                                 "STATIC", 
                                 0, 
							     WS_POPUP | WS_VISIBLE, 
                                 0, 0, 
                                 APP_WIDTH, APP_HEIGHT, 
                                 0, 0, 0, 0);

	ShowCursor(false);

	initD3D(window);

	initEffect06();

	synthInit();

	MSG msg;
	while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
//	while (true)
    {
		//Sleep(25);

        // Just remove the message
        PeekMessage(&msg, window, 0, 0, PM_REMOVE);

		// synth
		synthMainLoop();

		// render

		//timer += 70000;

		if (timer >= 0)
		{
			// 0xFFCFB898

			// F4AB78
			// 4C0610
			d3dDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 0xffffffff, 1.0f, 0);
/*
			radTarget = 0.f;
			radLocation = 10.f;
			heightLocation = 14.f;
			heightTarget   = 6.f;
*/
			// overlay color calculation
			// F4AB78
			// 4C0610



			if (timer >= 8000)
			{
				radTarget   = 20.f + cos((timer - 8000) * 0.00039269908169872415480783042290994f) * 20.f;
				radLocation = 25.f + cos((timer - 8000) * 0.00039269908169872415480783042290994f) *  5.f;
			}

			if (timer >= 16000)
			{
				radTarget = 0.f;
				radLocation = 3.f;
				heightLocation = 10.f;
				heightTarget = 6.f;
				offsetX        =  5.f;
				offsetZ        = -7.f;
			}

			if (timer >= 20000)
			{
				heightLocation =  7.f;
				heightTarget   =  8.f;				
				offsetX        = 14.f;
				offsetZ        =  2.f;
			}

			if (timer >= 20000)
			{
				radLocation = 6.f - cos((timer - 20000) * 0.00015f) * 3.f;
			}

			if (timer >= 28000)				// low to up
			{
				heightLocation =  1.f;
				heightTarget   = 11.f;				
				offsetX        =  9.5f;
				offsetZ        =  6.f;
				radLocation    =  3.f;
			}

			if (timer >= 32000)				// line coming from far
			{
				offsetX        =  -7.0f;
				offsetZ        =  8.f;
				heightLocation =  8.1f;
				heightTarget   =  8.f;
			}

			if ((timer >= 36000) && (timer < 40000))
			{
				heightLocation =  14.1f;
				offsetX        =  -8.0f;
				offsetZ        =  6.f;
			}

			if (timer >= 40000)
			{
				speed = 0.000306f;
				offsetX = 0;
				offsetZ = 0;
				heightLocation =  9.f;
				radLocation = 4.f;
			}

			int rr = 0xF4;
			int gg = 0xAB;
			int bb = 0x78;

			if (timer > 44000)
			{
				heightLocation =  11.f;
				heightTarget   = 12.f;
				radLocation = 6.f;

				rr -= ((float)(0xF4 - 0x4C) / 16000.f) * (timer - 44000.f);
				gg -= ((float)(0xAB - 0x06) / 16000.f) * (timer - 44000.f);
				bb -= ((float)(0x78 - 0x10) / 16000.f) * (timer - 44000.f);

				if (rr < 0x4C) rr = 0x4C;
				if (gg < 0x06) gg = 0x06;
				if (bb < 0x10) bb = 0x10;

				OVERLAY_COLOR = 0xff000000 | (rr << 16) | (gg << 8) | (bb);
			}

			if (timer >= 48000)
			{
				heightLocation = 18.f;
				radLocation = 1.f;
			}

			if (timer >= 56000)
			{ // from -3
				radLocation    =  11.f - cos((timer - 56000) * 0.00015f) * 10.f;
				heightLocation =  14.f + cos((timer - 56000) * 0.00015f) *  4.f;
				heightTarget   =  12.5f - cos((timer - 56000) * 0.00015f) * 0.5f;
			}

			doEffect06();

			if (timer > 72000)
			{
				d3dDevice->BeginScene();

				d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

				int color = 255 - ((timer - 72000) * 0.1f);

				if (color < 0) color = 0;

				color = (0xff000000) | (color << 16) | (color << 8) | color;

				OVERLAY_VERTEX vertices[4] =
				{
					{ -1,  -1, 0.1f, 0.5f, color},
					{800,  -1, 0.1f, 0.5f, color},
					{ -1, 600, 0.1f, 0.5f, color},
					{800, 600, 0.1f, 0.5f, color}
				};

				d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
				d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
				d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);

//				d3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
				d3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
				d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(OVERLAY_VERTEX));
//				d3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
				d3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

				d3dDevice->EndScene();
			}

			if (timer > 76000)
			{
				break;
			}

			d3dDevice->Present(NULL, NULL, NULL, NULL);    
		}
	}

	// fuck it :)

	synthShutdown();

//	deinitD3D();

	ExitProcess(0);

	return 0;
}

