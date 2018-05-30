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
//	//保存寄存器
//	_asm
//	{
//		pushad
//		pushfd
//	}
//	//获取数据
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
//	MessageBox(NULL, szBuffer, L"[Hook 寄存器数据]", MB_OK);
//	memset(szBuffer, 0, 100);
//	swprintf_s(szBuffer, 100, L"参数x:%x\n参数y:%x", dwParax,dwParay);
//	MessageBox(NULL, szBuffer, L"[Hook 参数]", MB_OK);
//
//	//恢复寄存器
//	_asm
//	{
//		popfd
//		popad
//	}
//
//	//执行覆盖的代码
//	_asm
//	{
//		push	ebp
//		mov		ebp,esp
//		sub		esp,40h
//	}
//
//	//跳回hook地址
//	_asm
//	{
//		jmp g_dwRetAddr
//	}
//
//}
