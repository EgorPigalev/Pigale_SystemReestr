#include <Windows.h>
#include <stdio.h>
#include <malloc.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	HKEY hKey = NULL;
	if (RegOpenKeyW(HKEY_CURRENT_USER, NULL, &hKey) != ERROR_SUCCESS)
	{
		MessageBox(NULL, L"� ������ ��������� �������� ��������", L"����������", MB_OK);
		return 0;
	}
	HKEY tmp = NULL;
	if (RegCreateKey(hKey, L"MyKey", &tmp) == ERROR_SUCCESS)
	{
		MessageBox(NULL, L"���� ������� ������", L"����������", MB_OK);
	}
	if (RegSetValueW(hKey, L"MyKey", REG_SZ, L"�������� �� ���������", 22 * sizeof(WCHAR)) == ERROR_SUCCESS)
	{
		MessageBoxA(NULL, "���� ������� ������ � ��� ��������� �������� �� ���������", "����������", MB_OK);
	}
	LPDWORD DataType1 = NULL;
	LPDWORD Datalen1 = 512;
	LPWSTR StrValue1 = malloc(512);
	if (RegGetValueW(HKEY_CURRENT_USER, NULL, L"MyKey", RRF_RT_ANY, &DataType1, StrValue1, &Datalen1) == ERROR_SUCCESS)
	{
		MessageBox(NULL, StrValue1, L"�������� ���������", MB_OK);
	}
	else
	{
		MessageBox(NULL, L"���-�� ����� �� ���", L"����������", MB_OK);
	}
	/*time_t mytime = time(NULL);
	char* time_str = ctime(&mytime);
	time_str[strlen(time_str) - 1] = '\0';
	LPSTR str = time_str;*/
	LPWSTR str = L"time_str";
	DWORD StrParamLen = wcslen(str);
	if (RegSetValueExW(tmp, L"MyStrParam", NULL, REG_SZ, str, StrParamLen * sizeof(WCHAR)) == ERROR_SUCCESS)
	{
		MessageBoxA(NULL, "�������� �������� ������� ������ � ��� ��������� ��������", "����������", MB_OK);
	}
	LPDWORD DataType = NULL;
	LPDWORD Datalen = 512;
	LPWSTR StrValue = malloc(512);
	if (RegGetValueW(hKey, L"MyKey", L"MyStrParam", RRF_RT_ANY, &DataType, StrValue, &Datalen) == ERROR_SUCCESS)
	{
		//LPWSTR OutputString = malloc(512);
		//sprinf(OutputString, 512, TEXT("%d"), StrValue);
		MessageBox(NULL, StrValue, L"�������� ���������", MB_OK);
	}
	else
	{
		MessageBoxA(NULL, "���-�� ����� �� ���", "����������", MB_OK);
	}
	if (RegDeleteKey(hKey, L"MyKey") == ERROR_SUCCESS)
	{
		MessageBoxA(NULL, "���� ������� �����", "����������", MB_OK);
	}
	else
	{
		MessageBoxA(NULL, "��� �������� ����� �������� ������", "����������", MB_OK);
	}
	RegCloseKey(tmp);
	RegCloseKey(hKey);
	return 0;
}