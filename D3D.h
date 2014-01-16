IDirect3D9*	d3dInterface;
IDirect3DDevice9* d3dDevice;

void initD3D(HWND windowHandle)
{
	d3dInterface = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dPP;
	DWORD d3dBehaviorFlags;
	D3DDEVTYPE d3dDeviceType;
	DWORD d3dAdapter;

	d3dPP.hDeviceWindow = windowHandle;

	d3dPP.BackBufferCount  = 1;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferWidth  = 800;
	d3dPP.BackBufferHeight = 600;

	d3dPP.SwapEffect           = D3DSWAPEFFECT_DISCARD;
	//d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;//D3DPRESENT_INTERVAL_ONE;//D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_ONE;//D3DPRESENT_INTERVAL_IMMEDIATE;

	d3dPP.AutoDepthStencilFormat = D3DFMT_D16;
	d3dPP.EnableAutoDepthStencil = true;

	d3dPP.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
	d3dPP.MultiSampleQuality = 2;

	d3dPP.Flags = 0;

	d3dPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

    d3dPP.Windowed = false;

	d3dBehaviorFlags = D3DCREATE_MULTITHREADED | D3DCREATE_HARDWARE_VERTEXPROCESSING;
	d3dAdapter       = D3DADAPTER_DEFAULT;
	d3dDeviceType    = D3DDEVTYPE_HAL;

	d3dInterface->CreateDevice(d3dAdapter, 
			                   d3dDeviceType, 
							   windowHandle, 
							   d3dBehaviorFlags, 
							   &d3dPP, 
							   &d3dDevice);
/*
	D3DVIEWPORT9 viewportRender;

	viewportRender.X = 0;
	viewportRender.Y = 100;

	viewportRender.Width  = 800;
	viewportRender.Height = 400;

	viewportRender.MinZ = 0;
	viewportRender.MaxZ = 1;

	d3dDevice->SetViewport(&viewportRender);
*/

	d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
//	d3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
}

void deinitD3D()
{
	if (d3dDevice != NULL)
	{
		d3dDevice->Release();
	}

	if (d3dInterface != NULL)
	{
		d3dInterface->Release();
	}
}