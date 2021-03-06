// InlineHook.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

//全局变量
DWORD g_dwHookAddr;	//Hook开始地址
DWORD g_dwRetAddr;	//Hook返回地址
DWORD g_dwLength;	//Hook字节数
PBYTE g_pCodePatch;	//存储被Hook的内存的原来的硬编码
DWORD g_dwHookFlag;	//Hook 状态 1 hook成功 0 失败

BOOL SetInlineHook(DWORD dwHookAddr, DWORD dwProcAddr, DWORD dwLength);
BOOL UnInlineHook();
DWORD Pluse(DWORD x, DWORD y);

typedef struct _REGISTER
{
	DWORD Eax;
	DWORD Ecx;
	DWORD Edx;
	DWORD Ebx;
	DWORD Esp;
	DWORD Ebp;
	DWORD Esi;
	DWORD Edi;
}Register;
DWORD dwParax;
DWORD dwParay;
Register reg = { 0 };
TCHAR szBuffer[100] = { 0 };

extern "C" _declspec(naked)void HookProc()
{
	//保存寄存器
	_asm
	{
		pushad
		pushfd
	}
	//获取数据
	_asm
	{
		mov reg.Eax, eax
		mov reg.Ecx, ecx
		mov reg.Edx, edx
		mov reg.Ebx, ebx
		mov reg.Esp, esp
		mov reg.Ebp, ebp
		mov reg.Esi, esi
		mov reg.Edi, edi

		mov eax, dword ptr ss : [esp + 0x28]
		mov dwParax, EAX
		mov eax, dword ptr ss : [esp + 0x2c]
		mov dwParay, EAX
	}

	swprintf_s(szBuffer, 100, L"EAX:%x\nEcx:%x\nEdx:%x\nEbx:%x\n", reg.Eax, reg.Ecx, reg.Edx, reg.Ebx);
	MessageBox(NULL, szBuffer, L"[Hook 寄存器数据]", MB_OK);
	memset(szBuffer, 0, 100);
	swprintf_s(szBuffer, 100, L"参数x:%x\n参数y:%x", dwParax, dwParay);
	MessageBox(NULL, szBuffer, L"[Hook 参数]", MB_OK);

	//恢复寄存器
	_asm
	{
		popfd
		popad
	}

	//执行覆盖的代码
	_asm
	{
		 push        ebp
		 mov         ebp, esp
		 sub         esp, 0C0h
	}

	//跳回hook地址
	_asm
	{
		jmp g_dwRetAddr
	}

}


int main()
{
	//安装
	SetInlineHook(0x4513c0, (DWORD)HookProc, 9);

	Pluse(13, 16);

	//卸载
	UnInlineHook();

    return 0;
}

BOOL SetInlineHook(DWORD dwHookAddr,DWORD dwProcAddr,DWORD dwLength)
{
	BOOL bRet = FALSE;
	DWORD dwOldProtect;
	DWORD dwJmpCode;

	//参数校验
	if (dwHookAddr == NULL || dwProcAddr == NULL)
	{
		OutputDebugString(L"SetInlineHook失败，Hook地址/Hook函数地址填写错误.");
		return FALSE;
	}

	//长度不小于5
	if (dwLength < 5) {
		OutputDebugString(L"SetInlineHook失败，长度小于5.");
		return FALSE;
	}
	//将要Hook的内存修改为可写
	bRet = VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwHookAddr, dwLength, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	if (!bRet)
	{
		OutputDebugString(L"SetInlineHook失败，修改内存属性失败.");
		return FALSE;
	}
	//创建对内存空间，储存原来的硬编码
	g_pCodePatch = new BYTE[dwLength];
	memcpy(g_pCodePatch, (PDWORD)dwHookAddr, dwLength);
	//跳转到dwProcAddr
	//要跳转的地址 = E9的地址 + 5 + E9后面的值
	// --->E9后面的值 = 要跳转的值 - E9的地址 - 5
	dwJmpCode = dwProcAddr - dwHookAddr - 5;

	//将hook的内存全部初始化成nop(dwLength > 5)
	memset((PBYTE)dwHookAddr, 0x90, dwLength);
	//修改要hook的硬编码
	*(PBYTE)dwHookAddr = 0xE9;						//jmp
	*(PDWORD)((PBYTE)dwHookAddr + 1) = dwJmpCode;	//jmp后面跟着的硬编码

	//修改Hook状态
	g_dwHookFlag = 1;
	g_dwHookAddr = dwHookAddr;
	g_dwLength = dwLength;
	g_dwRetAddr = dwHookAddr + dwLength;

	return TRUE;
}

BOOL UnInlineHook()
{
	BOOL bRet = FALSE;
	DWORD dwOldProtect;

	//hook成功才能卸载
	if (!g_dwHookFlag)
	{
		OutputDebugString(L"卸载失败，hook没有成功，无法卸载.");
		return FALSE;
	}
	//修改内存为可写
	bRet = VirtualProtectEx(::GetCurrentProcess(), (LPVOID)g_dwHookAddr, g_dwLength, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	if (!bRet)
	{
		OutputDebugString(L"卸载失败失败，修改内存属性失败.");
		return FALSE;
	}

	//恢复原来的硬编码
	memcpy((PDWORD)g_dwHookAddr, g_pCodePatch, g_dwLength);

	//修改hook状态
	delete[] g_pCodePatch;
	g_dwHookFlag = 0;
	g_dwHookAddr = 0;
	g_dwLength = 0;
	g_pCodePatch = NULL;

	return TRUE;
}

DWORD Pluse(DWORD x,DWORD y)
{
	return x + y;
}
