#define FX07_NRTOWERS    8

#define FX07_NRBOXES  265
#define FX07_BOXSIZE   40
#define FX07_NRVERTS (FX07_NRBOXES * FX07_BOXSIZE + 1)

IDirect3DVertexBuffer9* fx07_VertexBuffer[FX07_NRTOWERS];

FX06_OBJECT_VERTEX fx07_Lines[FX07_NRTOWERS][FX07_NRVERTS];

float FX07_Rand()
{
	return (rand() % 30000) / 30000.f;
}

D3DXVECTOR3 FX07_GetPosition(int box)
{
	D3DXVECTOR4 points[] =
	{
		D3DXVECTOR4( 0,  4,  0,   0), // not used
		D3DXVECTOR4( 0,  5,  0,  30),
		D3DXVECTOR4( 0,  9,  0,  60),
		D3DXVECTOR4(-3, 13,  0, 120),
		D3DXVECTOR4(-1, 15,  0, 140),
		D3DXVECTOR4( 0, 14,  0, 170),
		D3DXVECTOR4( 1, 15,  0, 200),
		D3DXVECTOR4( 3, 13,  0, 240),
		D3DXVECTOR4( 0,  8,  0, 300),
		D3DXVECTOR4( 0,  5,  0, 330),
		D3DXVECTOR4( 0,  6,  0, 400)  // not used
	};

	box += points[1].w;

	int start;

	for (int i = 1; i < (sizeof(points) / 16); i++)
	{
		if (box < points[i + 1].w)
		{
			start = i;
			break;
		}
	}

	D3DXVECTOR3 r;

	D3DXVec3CatmullRom(&r, 
		               (D3DXVECTOR3*) &points[start - 1],
		               (D3DXVECTOR3*) &points[start + 0],
			           (D3DXVECTOR3*) &points[start + 1],
			           (D3DXVECTOR3*) &points[start + 2],
			           (float) (box - points[start + 0].w) / (float) (points[start + 1].w - points[start + 0].w));

	return r;
}

void initEffect07()
{
	D3DXVECTOR3 r;

	FX06_OBJECT_VERTEX* line = &fx07_Lines[0][0];

	for (int i = 0; i < FX07_NRBOXES; i++)
	{
		r = FX07_GetPosition(i);

		for (int j = 0; j < FX07_BOXSIZE; j++)
		{
			float xx = (FX07_Rand() * 0.2f) - 0.1f;
			float yy = (FX07_Rand() * 0.2f) - 0.1f;
			float zz = (FX07_Rand() * 0.2f) - 0.1f;

			float ll = 0.25f / sqrt((xx * xx) + (yy * yy) + (zz * zz));

			line->pos.x = r.x + xx * ll;
			line->pos.y = r.y + yy * ll;
			line->pos.z = r.z + zz * ll;

			DWORD fade = (rand() % 255);

			line->color = (fade << 16) | (fade << 8) + fade;

			line++;
		}
	}

	d3dDevice->CreateVertexBuffer(sizeof(FX06_OBJECT_VERTEX) * FX07_NRVERTS,
								  0, 
								  FX06_OBJECT_VERTEX_FVF, 
								  D3DPOOL_DEFAULT, 
								  &fx07_VertexBuffer[0],
								  NULL);

	VOID* pVertices;

	fx07_VertexBuffer[0]->Lock(0, sizeof(FX06_OBJECT_VERTEX) * FX07_NRVERTS, (void**)&pVertices, 0);

	rj_memcpy(pVertices, line, sizeof(FX06_OBJECT_VERTEX) * FX07_NRVERTS);

	fx07_VertexBuffer[0]->Unlock();

}

void doEffect07()
{
	// update
	FX06_OBJECT_VERTEX* line = &fx07_Lines[0][0];

	for (int i = 0; i < FX07_NRVERTS; i++)
	{
		int fade = (timer / 10.f) - (i * 0.2f);

		if (fade < 0)   fade = 0;
		if (fade > 150) fade = 150;

		line[i].color = (fade << 24) | (line[i].color & 0xffffff);
	}

	VOID* pVertices;

	fx07_VertexBuffer[0]->Lock(0, sizeof(FX06_OBJECT_VERTEX) * FX07_NRVERTS, (void**)&pVertices, 0);

	rj_memcpy(pVertices, line, sizeof(FX06_OBJECT_VERTEX) * FX07_NRVERTS);

	fx07_VertexBuffer[0]->Unlock();

	// render
	D3DXMATRIX matRotX, matRotY, matRotZ, matLoc, matView, matProj;

	d3dDevice->SetTransform(D3DTS_WORLD, &(*D3DXMatrixIdentity(&matRotZ)));

	d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	d3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	d3dDevice->SetRenderState(D3DRS_LIGHTING, false);

	d3dDevice->SetStreamSource(0, fx07_VertexBuffer[0], 0, sizeof(FX06_OBJECT_VERTEX));

	d3dDevice->SetFVF(FX06_OBJECT_VERTEX_FVF);

	d3dDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, FX07_NRVERTS - 2);

	d3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}