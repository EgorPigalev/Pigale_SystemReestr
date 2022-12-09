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
	if (RegSetValueW(hKey, L"MyKey", REG_SZ, L"Значение по умолчанию", 22 * sizeof(WCHAR)) == ERROR_SUCCESS)
	{
		MessageBoxA(NULL, "Ключ успешно создан и ему присвоено значение по умолчанию", "Информация", MB_OK);
	}
	LPDWORD DataType1 = NULL;
	LPDWORD Datalen1 = 512;
	LPWSTR StrValue1 = malloc(512);
	if (RegGetValueW(HKEY_CURRENT_USER, NULL, L"MyKey", RRF_RT_ANY, &DataType1, StrValue1, &Datalen1) == ERROR_SUCCESS)
	{
		MessageBox(NULL, StrValue1, L"Значение параметра", MB_OK);
	}
	else
	{
		MessageBox(NULL, L"Что-то пошло не так", L"Информация", MB_OK);
	}
	/*time_t mytime = time(NULL);
	char* time_str = ctime(&mytime);
	time_str[strlen(time_str) - 1] = '\0';
	LPSTR str = time_str;*/
	LPWSTR str = L"time_str";
	DWORD StrParamLen = wcslen(str);
	if (RegSetValueExW(tmp, L"MyStrParam", NULL, REG_SZ, str, StrParamLen * sizeof(WCHAR)) == ERROR_SUCCESS)
	{
		MessageBoxA(NULL, "Числовой параметр успешно создан и ему присвоено значение", "Информация", MB_OK);
	}
	LPDWORD DataType = NULL;
	LPDWORD Datalen = 512;
	LPWSTR StrValue = malloc(512);
	if (RegGetValueW(hKey, L"MyKey", L"MyStrParam", RRF_RT_ANY, &DataType, StrValue, &Datalen) == ERROR_SUCCESS)
	{
		//LPWSTR OutputString = malloc(512);
		//sprinf(OutputString, 512, TEXT("%d"), StrValue);
		MessageBox(NULL, StrValue, L"Значение параметра", MB_OK);
	}
	else
	{
		MessageBoxA(NULL, "Что-то пошло не так", "Информация", MB_OK);
	}
	if (RegDeleteKey(hKey, L"MyKey") == ERROR_SUCCESS)
	{
		MessageBoxA(NULL, "Ключ успешно удалён", "Информация", MB_OK);
	}
	else
	{
		MessageBoxA(NULL, "При удаление ключа возникла ошибка", "Информация", MB_OK);
	}
	RegCloseKey(tmp);
	RegCloseKey(hKey);
	return 0;
}