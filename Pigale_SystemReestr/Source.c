#include <Windows.h>
#include <stdio.h>
#include <malloc.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	HKEY hKey = NULL;
	if (RegOpenKeyW(HKEY_CURRENT_USER, NULL, &hKey) != ERROR_SUCCESS)
	{
		MessageBox(NULL, L"В работе программы возникла проблема", L"Информация", MB_OK);
		return 0;
	}
	HKEY tmp = NULL;
	if (RegCreateKey(hKey, L"MyKey", &tmp) == ERROR_SUCCESS)
	{
		MessageBox(NULL, L"Ключ успешно создан", L"Информация", MB_OK);
	}
	LPDWORD DataType = NULL;
	LPDWORD Datalen = NULL;
	time_t mytime = time(NULL);
	char* time_str = ctime(&mytime);
	time_str[strlen(time_str) - 1] = '\0';
	LPSTR str = time_str;
	MessageBoxA(NULL, str, "Информация", MB_OK);
	if (RegSetValueExW(tmp, L"MyStrParam", NULL, REG_SZ, &str, 4) == ERROR_SUCCESS)
	{
		MessageBoxA(NULL, "Числовой параметр успешно создан и ему присвоено значение", "Информация", MB_OK);
	}
	LPSTR StrValue = "";
	if (RegGetValueW(hKey, L"MyKey", L"MyStrParam", RRF_RT_ANY, &DataType, &StrValue, &Datalen) == ERROR_SUCCESS)
	{
		LPWSTR OutputString = malloc(512);
		//swprinf(OutputString, 512, TEXT("%d"), StrValue);
		MessageBoxA(NULL, StrValue, L"Значение параметра", MB_OK);
	}
	else
	{
		MessageBoxA(NULL, "Что-то пошло не так", "Информация", MB_OK);
	}
	if (RegDeleteKey(hKey, L"MyKey") == ERROR_SUCCESS)
	{
		MessageBoxA(NULL, "Ключ успешно удалён", "Информация", MB_OK);
	}
	RegCloseKey(tmp);
	RegCloseKey(hKey);
	return 0;
}