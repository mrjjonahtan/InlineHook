#include "stdafx.h"
//#include "HookDemo.h"
//
//
//typedef struct _REGISTER
//{
//	DWORD Eax;
//	DWORD Ecx;
//	DWORD Edx;
//	DWORD Ebx;
//	DWORD Esp;
//	DWORD Ebp;
//	DWORD Esi;
//	DWORD Edi;
//}Register;
//DWORD dwParax;
//DWORD dwParay;
//Register reg = { 0 };
//TCHAR szBuffer[100] = { 0 };
//
//extern "C" _declspec(naked)void HookProc()
//{
//	//����Ĵ���
//	_asm
//	{
//		pushad
//		pushfd
//	}
//	//��ȡ����
//	_asm
//	{
//		mov reg.Eax,eax
//		mov reg.Ecx,ecx
//		mov reg.Edx,edx
//		mov reg.Ebx,ebx
//		mov reg.Esp,esp
//		mov reg.Ebp,ebp
//		mov reg.Esi,esi
//		mov reg.Edi,edi
//
//		mov eax,dword ptr ss:[esp+0x28]
//		mov dwParax,EAX
//		mov eax,dword ptr ss:[esp+0x2c]
//		mov dwParay,EAX
//	}
//
//	swprintf_s(szBuffer, 100, L"EAX:%x\Ecx:%x\Edx:%x\Ebx:%x\n", reg.Eax, reg.Ecx, reg.Edx, reg.Ebx);
//	MessageBox(NULL, szBuffer, L"[Hook �Ĵ�������]", MB_OK);
//	memset(szBuffer, 0, 100);
//	swprintf_s(szBuffer, 100, L"����x:%x\n����y:%x", dwParax,dwParay);
//	MessageBox(NULL, szBuffer, L"[Hook ����]", MB_OK);
//
//	//�ָ��Ĵ���
//	_asm
//	{
//		popfd
//		popad
//	}
//
//	//ִ�и��ǵĴ���
//	_asm
//	{
//		push	ebp
//		mov		ebp,esp
//		sub		esp,40h
//	}
//
//	//����hook��ַ
//	_asm
//	{
//		jmp g_dwRetAddr
//	}
//
//}
