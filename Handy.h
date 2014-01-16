#define _1PI 3.1415926535897932384f
#define _2PI 6.2831853071795864769f

extern "C" 
{

	unsigned int randNext;

	int _fltused;

	inline float sin(float i)
    {
		__asm fld i;
		__asm fsin;
		__asm fstp i;

		return i;
	}

    inline float cos(float i)
    {
		__asm fld i;
		__asm fcos;
		__asm fstp i;

		return i;
    }

    inline float sqrtf(float i)
    {
		__asm fld i;
		__asm fsqrt;
		__asm fstp i;

		return i;
    }

	inline float pow(float i, float j)
	{
		__asm fld j;
		__asm fld i;
		__asm fyl2x;
		__asm fld1;
		__asm fld st(1);
		__asm fprem;
		__asm f2xm1;
		__asm faddp st(1), st;
		__asm fscale;
		__asm fxch;
		__asm fstp st;
		__asm fstp i;

		return i;
	}

	int rand()
	{
		int value;

		__asm push edx;
		__asm imul edx, [randNext], 0x41c64e6d;
		__asm add  edx, 0x3093;
		__asm mov  [randNext], edx;
		__asm mov  eax, edx;
		__asm shr  eax, 16
		__asm and  eax, 0x7fff;
		__asm mov  [value], eax
		__asm pop  edx;

		return value;
	}

	void rj_memcpy(void* target, void* source, int count)
	{
		__asm mov  esi, [source];
		__asm mov  edi, [target];
		__asm mov  ecx, [count];
		__asm mov  eax, ecx;
		__asm shr  ecx, 2;
		__asm mov  ebx, ecx;
		__asm shl  ebx, 2;
		__asm sub  eax, ebx;
		__asm rep  movsd;
		__asm mov  ecx, eax;
		__asm rep  movsb;
	}
/*
	DWORD rj_getprocaddress(HMODULE module, unsigned long hash)
	{
		DWORD address;

		__asm
		{
//			pushad 
			push esi
			push edi
			push ebp

			// search procedure with hash ebx in module ebp
			mov     ebx, dword ptr [hash]
			mov     ebp, dword ptr [module]

			mov		eax, [ebp + 0x3c]		// eax = PE header offset
			mov		edx, [ebp + eax + 0x78]	// edx = exports directory table offset
			add		edx, ebp			    // edx = exports directory table address
			push	edx
			mov		edx, [edx + 0x20]		// edx = name pointers table offset
			add		edx, ebp			    // edx = name pointers table address

			// check all names of procedure for the right hash
			xor		eax, eax
			xor		ecx, ecx
	
		ScanProcedureNamesLoop:
			inc		ecx
			mov		esi, [edx + ecx*4]		// esi = name pointer offset
			add		esi, ebp				// esi = name pointer address
			xor		edi, edi
	
		CalculateHashLoop:
			ror		edi, 0x13
			lodsb
			add		edi, eax
			test	eax, eax
			jnz		CalculateHashLoop

			cmp		edi, ebx				// check computed hash
			jnz		ScanProcedureNamesLoop

			// found, get the address from the table
			pop		edx
			mov		ebx, [edx + 0x24]		// ebx = ordinals table RNA offset
			add		ebx, ebp				// ebx = ordinals table RNA address
			mov		cx, [ebx + ecx*2]		// ecx = function ordinal
			mov		ebx, [edx + 0x1c]		// ebx = address table RVA offset
			add		ebx, ebp				// ebx = address table RVA address
			mov		eax, [ebx + ecx*4]		// eax = address of function RVA offset
			add		eax, ebp

			pop ebp
			pop edi
			pop esi

			mov     dword ptr [address], eax
		}

		return (DWORD) address;
	}
*/

	void rj_memset(void* target, unsigned char value, int count)
	{
		__asm push edi;
		__asm mov  edi, [target];
		__asm mov  ecx, [count];
		__asm mov  al, [value];
		__asm rep  stosb;
		__asm pop  edi;
	}
	
//
//	void* rj_getprocaddress(char* dll, DWORD hashcode)
//	{
//		void* address = NULL;
//
//		HMODULE mod = LoadLibrary(dll);
//
//		address = GetProcAddress(mod, (LPCSTR) "waveOutOpen");
//
///*
////		__asm push ebp
//  //      __asm mov  ebp, eax
//    //    __asm mov  ebx, [hashcode]
//*/
//
///*
//		__asm 
//		{
////			user32    db "user32",0
//
//			lea  ebx, [kernel32]
//			push ebx
//			call hallo
//
//		}
//		*/
////		push offset "LoadLibraryA"push eax                               ; this is the handle for kernel32.dllcall GetProcAddressmov  ebx, eax    
//
//
////		__asm mov  ebx, [dll];
//  //      __asm push ebx;
//	//	__asm call LoadLibraryA;
////		__asm mov  ebx, hashcode;
////		__asm push ebx;
////		__asm push eax;
//  //      __asm call GetProcAddress;
//	//	__asm mov  [address], eax;
////		__asm pop  ebp
//
//		return address;
//	}
}
