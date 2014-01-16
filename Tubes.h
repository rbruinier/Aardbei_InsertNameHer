struct FX06_OBJECT_VERTEX
{
	D3DXVECTOR3 pos;
	DWORD color;
};

#define FX06_OBJECT_VERTEX_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

#define FX06_NRTOWERS    8

#define FX06_ROWLENGTH	30
#define FX06_NRSIDES	16
#define FX06_NRPRIMS    (FX06_NRTOWERS * FX06_ROWLENGTH * FX06_NRSIDES * 2 * 2)
#define FX06_NRVERTS    (FX06_NRPRIMS * 3)

IDirect3DVertexBuffer9* fx06_VertexBuffer;

float fx06_Position[8][2] =
{
	{  0,   0},
	{ -2,  10},
	{ -8,  -9},
	{-16,   3},
	{  5,  -7},
	{  9,  10},
	{ 10, -12},
	{ 14,   2}
};

FX06_OBJECT_VERTEX fx06_Tower[FX06_NRVERTS];

// lines
#define FX07_NRBOXES1  390
#define FX07_BOXSIZE1   95
#define FX07_NRVERTS1 (FX07_NRBOXES1 * FX07_BOXSIZE1)

#define FX07_NRBOXES2  195
#define FX07_BOXSIZE2   95
#define FX07_NRVERTS2 (FX07_NRBOXES2 * FX07_BOXSIZE2)

IDirect3DVertexBuffer9* fx07_VertexBuffer;

FX06_OBJECT_VERTEX fx07_Lines[FX07_NRVERTS1 + FX07_NRVERTS2];

// pyramids
#define FX08_NRPYRAMIDS	140

#define FX08_NRPRIMS    (FX08_NRPYRAMIDS * 4)
#define FX08_NRVERTS    (FX08_NRPRIMS * 3)

IDirect3DVertexBuffer9* fx08_VertexBuffer;

FX06_OBJECT_VERTEX fx08_Pyramid[FX08_NRVERTS];

float radLocation    = 30.f;
float radTarget      = 40.f;
float speed          = 0.000306f;
int   difference     = 2000;
float heightLocation = 4.f;
float heightTarget   = 4.f;
float offsetX        = 0.f;
float offsetZ        = 0.f;

D3DXVECTOR4 points[46] =
{
	D3DXVECTOR4(    5,    0,   -7,    0),						// 1

	D3DXVECTOR4(    5,    0,   -7,   15), // 1					// 2
	D3DXVECTOR4(    5,  3.f,   -7,   25), // 1.1				// 3
	D3DXVECTOR4(    5,  6.6f,  -7,   40), // 1.1				// 4
	D3DXVECTOR4( 7.5f,   10,-9.5f,   54), // 1.5				// 5
	
	D3DXVECTOR4(   10,    6.6f,  -12, 68), // 1.9				// 6
	D3DXVECTOR4(   10,    6.4f,  -12,  69), // 2				// 7
	D3DXVECTOR4(   10,    6.6f,  -12, 70), // 2.1				// 8
	D3DXVECTOR4(   12,   10,   -5,    99), // 2.5				// 9

	D3DXVECTOR4(   14,    6.6f,    2,  128), // 2.9				// 10
	D3DXVECTOR4(   14,    6.4f,    2,  129), // 3				// 11
	D3DXVECTOR4(   14,    6.6f,    2,  130), // 3.1				// 12
	D3DXVECTOR4(11.5f,   10,    6,     149), // 3.5				// 13

	D3DXVECTOR4(    9,    6.6f,   10,  168), // 3.9				// 14
	D3DXVECTOR4(    9,    6.4f,   10,  169), // 4				// 15
	D3DXVECTOR4(    9,    6.6f,   10,  170), // 4.1				// 16
	D3DXVECTOR4( 3.5f,   10,   10,  192), // 4.5				// 17

	D3DXVECTOR4(   -2,    6.6f,   10,  214), // 4.9				// 18
	D3DXVECTOR4(   -2,    6.4f,   10,  215), // 5				// 19
	D3DXVECTOR4(   -2,    6.6f,   10,  216), // 5.1				// 20
	D3DXVECTOR4(   -9,   10, 6.5f,  247), // 5.5				// 21

	D3DXVECTOR4(  -16,    6.6f,    3,  278), // 5.9				// 22
	D3DXVECTOR4(  -16,    6.4f,    3,  279), // 6				// 23
	D3DXVECTOR4(  -16,    6.6f,    3,  280), // 6.1				// 24
	D3DXVECTOR4(  -12,   10,   -3,  309), // 6.5				// 25

	D3DXVECTOR4(   -8,    6.6f,  -9,   338), // 6.9				// 26
	D3DXVECTOR4(   -8,    6.4f,  -9,   339), // 7				// 27
	D3DXVECTOR4(   -8,    6.6f,  -9,   340), // 7.1				// 28
	D3DXVECTOR4(-1.5f,   10,  -8,   367), // 7.5				// 29

	D3DXVECTOR4(    5,    6.6f,  -7,   394), // 0.9				// 30
	D3DXVECTOR4(    5,    3,  -7,   395), // 1					// 31
	D3DXVECTOR4(    5,    4,  -7,   396),						// 32
	D3DXVECTOR4(    5,    0,  -7,   397),						// 33
	D3DXVECTOR4(    5,    0,  -7,   398),						// 34
/*
	D3DXVECTOR4( 0,  4,  0, 400), // not used
	D3DXVECTOR4( 0,  5,  0, 405),
	D3DXVECTOR4( 0,  9,  0, 460),
	D3DXVECTOR4(-3, 13,  0, 520),
	D3DXVECTOR4(-1, 15,  0, 540),
	D3DXVECTOR4( 0, 14,  0, 570),
	D3DXVECTOR4( 1, 15,  0, 600),
	D3DXVECTOR4( 3, 13,  0, 640),
	D3DXVECTOR4( 0,  8,  0, 700),
	D3DXVECTOR4( 0,  5,  0, 730),
	D3DXVECTOR4( 0,  6,  0, 800),  // not used
	D3DXVECTOR4( 0,  6,  0, 840)  // not used
*/
	// heart
	D3DXVECTOR4( 0,  4,  0, 400), // not used
	D3DXVECTOR4( 0,  5,  0, 405), 
	D3DXVECTOR4( 0,  9,  0, 420), 
	D3DXVECTOR4(-3, 13,  0, 470), 
	D3DXVECTOR4(-1, 15,  0, 500), 
	D3DXVECTOR4( 0, 14,  0, 510), 
	D3DXVECTOR4( 1, 15,  0, 520),
	D3DXVECTOR4( 3, 13,  0, 550),
	D3DXVECTOR4( 0,  9,  0, 600),
	D3DXVECTOR4( 0,  5,  0, 730),
	D3DXVECTOR4( 0,  6,  0, 800),  // not used
	D3DXVECTOR4( 0,  6,  0, 840)  // not used
};


void FillVertexBuffer(IDirect3DVertexBuffer9* vb, void* data, int size)
{	
	VOID* pVertices;
	vb->Lock(0, size, (void**)&pVertices, 0);
	rj_memcpy(pVertices, data, size);
	vb->Unlock();
}

void initEffect06()
{
	int x, y;

	// object
	FX06_OBJECT_VERTEX* vertex = fx06_Tower;

	for (int i = 0; i < FX06_NRTOWERS; i++)
	{

		float random2 = rand();

		for (y = 0; y < FX06_ROWLENGTH * 2; y++)
		{
			int rowY = y;

			if (y >= FX06_ROWLENGTH)
			{
				rowY = ((FX06_ROWLENGTH * 2) - y) - 1;
			}

			float random = random2 + rowY;

			float r  = 1.5f + sin(random * 0.3f) * 0.1f;

			float xo = (sin(random * 0.2f) * 0.1f) + fx06_Position[i][0];
			float zo = (cos(random * 0.3f) * 0.1f) + fx06_Position[i][1];

			for (x = 0; x < FX06_NRSIDES; x++)
			{
				float r1Diff = 0.f;

				float x1 = sin(x * _2PI / FX06_NRSIDES) + ((sin(x * _2PI * 2.f / FX06_NRSIDES) * 0.2f));
				float x2 = sin((x + 1) * _2PI / FX06_NRSIDES) + ((sin((x + 1) * _2PI * 2.f / FX06_NRSIDES) * 0.2f));

				float z1 = cos(x * _2PI / FX06_NRSIDES);
				float z2 = cos((x + 1) * _2PI / FX06_NRSIDES);

				float ystep = 0.25f;

				float y1 = rowY * ystep;

				float rr;

				// top
				if (rowY > (FX06_ROWLENGTH - 4))
				{
					int pos = 3 - (FX06_ROWLENGTH - rowY);

					r1Diff = (0.25f / 3.f) * (pos);

					y1 -= (0.15f * (pos));
				}

				if (y >= FX06_ROWLENGTH)
				{
					rr = r * (r1Diff + 0.5f);
				}
				else
				{
					rr = r * (1.f - r1Diff);
				}

				// color
				float tint = ((rand()%1000) / 1200.f);

				if (rowY < 15) tint += ((15 - rowY) / 15.f);
				if (tint > 1.f) tint = 1.f;


				DWORD c1 = (0xFF000000) |
   						   ((DWORD)(0xFF * tint) << 16) |
						   ((DWORD)(0xFF * tint) <<  8) |
						   ((DWORD)(0xFF * tint));

/*
				DWORD c1 = (0xFF000000) |
   						   ((DWORD)(0xCF * tint) << 16) |
						   ((DWORD)(0xB8 * tint) <<  8) |
						   ((DWORD)(0x98 * tint));
*/
				FX06_OBJECT_VERTEX vertex1, vertex2;

				vertex1.pos   = D3DXVECTOR3(xo + x1 * rr, y1, zo + z1 * rr);
				vertex2.pos   = D3DXVECTOR3(xo + x2 * rr, y1, zo + z2 * rr);
					
				vertex[0].color = 
					vertex[1].color =
					vertex[2].color =
					vertex[3].color =
					vertex[4].color =
					vertex[5].color = c1;
					
				if (y == 0)
				{
					vertex[0].pos = vertex1.pos;
					vertex[1].pos = vertex2.pos;
					vertex[5].pos = vertex2.pos;
				}
				else if (y == ((FX06_ROWLENGTH * 2) - 1))
				{
					vertex[(-(FX06_NRSIDES * 2 * 3)) + 2].pos = 
						vertex[(-(FX06_NRSIDES * 2 * 3)) + 3].pos = vertex1.pos;

					vertex[(-(FX06_NRSIDES * 2 * 3)) + 4].pos = vertex2.pos;
				}
				else
				{
					vertex[0].pos = 
						vertex[(-(FX06_NRSIDES * 2 * 3)) + 2].pos =
						vertex[(-(FX06_NRSIDES * 2 * 3)) + 4].pos =
						vertex1.pos;

					vertex[1].pos = 
						vertex[5].pos =
						vertex[(-(FX06_NRSIDES * 2 * 3)) + 3].pos =						
						vertex2.pos;
				}

				vertex += 6;
			}
		}
	}

	d3dDevice->CreateVertexBuffer(sizeof(FX06_OBJECT_VERTEX) * FX06_NRVERTS,
								  0, 
								  FX06_OBJECT_VERTEX_FVF, 
								  D3DPOOL_DEFAULT, 
								  &fx06_VertexBuffer,
								  NULL);

	FillVertexBuffer(fx06_VertexBuffer, fx06_Tower, sizeof(FX06_OBJECT_VERTEX) * FX06_NRVERTS);


	// lines	
	FX06_OBJECT_VERTEX* line = fx07_Lines;

	for (x = 0; x < FX07_NRBOXES1 + FX07_NRBOXES2; x++)
	{		
		int box = x + points[1].w;

		int start = 1;

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
				           (D3DXVECTOR3*) &points[start],
					       (D3DXVECTOR3*) &points[start + 1],
						   (D3DXVECTOR3*) &points[start + 2],
						   (float) (box - points[start].w) / (float) (points[start + 1].w - points[start].w));

		for (y = 0; y < FX07_BOXSIZE1; y++)
		{
			float xx = (rand() * 0.0000060119638079778759731866414164187f) - 0.1f;
			float yy = (rand() * 0.0000060119638079778759731866414164187f) - 0.1f;
			float zz = (rand() * 0.0000060119638079778759731866414164187f) - 0.1f;

			float ll = 0.25f / sqrtf((xx * xx) + (yy * yy) + (zz * zz));

			line->pos.x = r.x + xx * ll;
			line->pos.y = r.y + yy * ll;
			line->pos.z = r.z + zz * ll;

			DWORD fade  = (rand() % 255);
			line->color = 0xff000000 | (fade << 16) | (fade << 8) + fade;

			line++;
		}
		
	}

	d3dDevice->CreateVertexBuffer(sizeof(FX06_OBJECT_VERTEX) * (FX07_NRVERTS1 + FX07_NRVERTS2),
								  0, 
								  FX06_OBJECT_VERTEX_FVF, 
								  D3DPOOL_DEFAULT, 
								  &fx07_VertexBuffer,
								  NULL);

	FillVertexBuffer(fx07_VertexBuffer, fx07_Lines, sizeof(FX06_OBJECT_VERTEX) * (FX07_NRVERTS1 + FX07_NRVERTS2));

	// pyramids
	FX06_OBJECT_VERTEX* pyramid = fx08_Pyramid;
	for (x = 0; x < FX08_NRPYRAMIDS; x++)
	{
		float r = x + ((rand()%100) / 200.f);

		float xx = sin(r) * (20.f + (float) x);
 		float zz = cos(r) * (20.f + (float) x);

		float x1 = -2.f + xx; float x2 = 2.f + xx;
		float z1 = -2.f + zz; float z2 = 2.f + zz;

		pyramid[0].color = pyramid[8].color = pyramid[2].color = 
			pyramid[9].color = pyramid[3].color = pyramid[11].color = pyramid[5].color =
			pyramid[6].color = 0x00FFFF80;

		pyramid[1].color = pyramid[4].color = pyramid[7].color = 
			pyramid[10].color = 0xFFFFFF80;

		pyramid[0].pos = pyramid[8].pos = D3DXVECTOR3(x1, 0.f, z1); 

		pyramid[2].pos = pyramid[9].pos = D3DXVECTOR3(x2, 0.f, z1); 

		pyramid[1].pos = pyramid[4].pos = pyramid[7].pos =
			pyramid[10].pos = D3DXVECTOR3(xx, 3.f, zz);

		pyramid[3].pos = pyramid[11].pos = D3DXVECTOR3(x2, 0.f, z2); 

		pyramid[5].pos = pyramid[6].pos = D3DXVECTOR3(x1, 0.f, z2); 

		pyramid += 12;
	}

	d3dDevice->CreateVertexBuffer(sizeof(FX06_OBJECT_VERTEX) * FX08_NRVERTS,
								0, 
								FX06_OBJECT_VERTEX_FVF, 
								D3DPOOL_DEFAULT, 
								&fx08_VertexBuffer,
								NULL);

	FillVertexBuffer(fx08_VertexBuffer, fx08_Pyramid, sizeof(FX06_OBJECT_VERTEX) * FX08_NRVERTS);
}

void doEffect06()
{
	// lines update

	__asm
	{
		// FX06_OBJECT_VERTEX* line = &fx07_Lines[0][0];
		// for (int i = 0; i < FX07_NRVERTS; i++)
		// {
		//	int fade = (timer / 10.f) - (i * 0.2f);
		//	if (fade < 0)   fade = 0;
		//	if (fade > 150) fade = 150;
		//	line[i].color = (fade << 24) | (line[i].color & 0xffffff);
		// }

		lea		edi, [fx07_Lines];
		add     edi, 12

		xor     ebx, ebx;
	lineloop:
		mov		eax, timer;

		shr     eax, 2
		cmp     ebx, FX07_NRVERTS1;
		jle     hihihi;
//		add     eax, 3250 - 4000;
//		jmp     justkidding
		add     eax, 3250
	hihihi:
//		cmp     timer, 16000
//		jge     dofadeout
		sub     eax, 4000;
//	justkidding:

		mov     ecx, ebx;
		shr     ecx, 2;

		sub     eax, ecx;

		jge		blabla1;
		xor     eax, eax
	blabla1:
		cmp     eax, 150;
		jle		blabla2;
		mov     eax, 150;
	blabla2:

		shl     eax, 24;

		mov     ecx, dword ptr [edi];
		and     ecx, 0x00ffffff;
		add     eax, ecx;
		mov     dword ptr [edi], eax;

		add     edi, 16

		inc     ebx;
		cmp     ebx, (FX07_NRVERTS1 + FX07_NRVERTS2)
		jne		lineloop;
	}

/*
	 FX06_OBJECT_VERTEX* line = &fx07_Lines[0][0];

	 for (int i = 0; i < FX07_NRVERTS; i++)
	 {
		int fade = (timer / 10.f) - (i * 0.2f);
		if (fade < 0)   fade = 0;
		if (fade > 150) fade = 150;
		line[i].color = (fade << 24) | (line[i].color & 0xffffff);
	}
*/
	FillVertexBuffer(fx07_VertexBuffer, fx07_Lines, sizeof(FX06_OBJECT_VERTEX) * (FX07_NRVERTS1 + FX07_NRVERTS2));

	// matrices
	D3DXMATRIX matTemp1, matTemp2, matTemp3;

	float rad = 0;

	D3DXVECTOR3 v1, v2, v3;

	__asm
	{
		// v1.x = sin(timer * speed) * radLocation;
		// v1.y = heightLocation;
		// v1.z = cos(timer * speed) * radLocation;
		lea     edx, [v1]
		fild	dword ptr [timer]
		fmul	dword ptr [speed]
		fsincos
		fmul    [radLocation]
		fadd    [offsetZ]
		fstp    dword ptr [edx + 8]
		fmul    [radLocation]
		fadd    [offsetX]
		fstp    dword ptr [edx]
		mov     eax, dword ptr [heightLocation]
		mov     dword ptr [edx + 4], eax

		// v2.x = sin((timer + difference) * speed) * radTarget;
		// v2.y = heightTarget;
		// v2.z = cos((timer + difference) * speed) * radTarget;
		lea     edx, [v2]
		fild		dword ptr [timer]
		fiadd    dword ptr [difference]
		fmul	dword ptr [speed]
		fsincos
		fmul    dword ptr [radTarget]
		fadd    [offsetZ]
		fstp    dword ptr [edx + 8]
		fmul    dword ptr [radTarget]
		fadd    [offsetX]
		fstp    dword ptr [edx]
		mov     eax, dword ptr [heightTarget]
		mov     dword ptr [edx + 4], eax

		// v3.x = v3.z = 0.f;
		// v3.y = 1.f;
		lea     edx, [v3]
		fldz
		fst     dword ptr [v3]
		fstp    dword ptr [v3 + 8]
		fld1
		fstp    dword ptr [v3 + 4]	
	}

//	v1.x = sin(timer * 0.0004f) * 17.f;
//	v1.y = 12;
//	v1.z = -cos(timer * 0.0004f) * 7.f;

	D3DXMatrixLookAtLH(&matTemp1,
					   &v1,
					   &v2,
					   &v3);

	D3DXMatrixPerspectiveFovLH(&matTemp2,
		                       1.1f,
							   1.50f,
							   0.9f,
							   100.f);

	d3dDevice->SetTransform(D3DTS_VIEW,       &matTemp1);
	d3dDevice->SetTransform(D3DTS_PROJECTION, &matTemp2);

	// begin rendering
	d3dDevice->BeginScene();

	float fogDens  = 0.04f;

	d3dDevice->SetRenderState(D3DRS_CULLMODE,         D3DCULL_CCW);
	d3dDevice->SetRenderState(D3DRS_LIGHTING,         false);
	d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	d3dDevice->SetRenderState(D3DRS_FOGCOLOR,         0xffffffff);
	d3dDevice->SetRenderState(D3DRS_FOGTABLEMODE,     D3DFOG_EXP);
	d3dDevice->SetRenderState(D3DRS_FOGDENSITY,       *(DWORD*) (&fogDens));
	d3dDevice->SetRenderState(D3DRS_FOGENABLE,        true);
	
	d3dDevice->SetTransform(D3DTS_WORLD, D3DXMatrixIdentity(&matTemp3));

	// towers
	d3dDevice->SetStreamSource(0, fx06_VertexBuffer, 0, sizeof(FX06_OBJECT_VERTEX));
	d3dDevice->SetFVF(FX06_OBJECT_VERTEX_FVF);
	d3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, FX06_NRPRIMS);

	// draw color overlay
	d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	OVERLAY_VERTEX vertices[4] =
	{
		{ -1,  -1, 0.1f, 0.5f, OVERLAY_COLOR},
		{800,  -1, 0.1f, 0.5f, OVERLAY_COLOR},
		{ -1, 600, 0.1f, 0.5f, OVERLAY_COLOR},
		{800, 600, 0.1f, 0.5f, OVERLAY_COLOR}
	};

	d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
	d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);

	d3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(OVERLAY_VERTEX));
	d3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	// render pyramids
	d3dDevice->SetRenderState(D3DRS_FOGCOLOR, OVERLAY_COLOR);

	d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	d3dDevice->SetFVF(FX06_OBJECT_VERTEX_FVF);
	d3dDevice->SetStreamSource(0, fx08_VertexBuffer, 0, sizeof(FX06_OBJECT_VERTEX));
	d3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, FX08_NRPRIMS);

	// render lines
	d3dDevice->SetStreamSource(0, fx07_VertexBuffer, 0, sizeof(FX06_OBJECT_VERTEX));
	d3dDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, FX07_NRVERTS1 - 1 - 800);
	d3dDevice->DrawPrimitive(D3DPT_LINESTRIP, FX07_NRVERTS1, FX07_NRVERTS2 - 10);

	// finish rendering
	d3dDevice->EndScene();
}
