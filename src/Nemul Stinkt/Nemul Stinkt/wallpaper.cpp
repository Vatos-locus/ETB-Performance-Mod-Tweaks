#include "wallpaper.h"
#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <string>
#include <fstream>
#include <iostream>
#include <codecvt>
#include <locale>

#pragma comment(lib, "Shlwapi.lib")

Wallpaper::Wallpaper(std::shared_ptr<Launcher> launcherINIT, const std::shared_ptr<Sound> soundINIT) : launcher(launcherINIT), sound(soundINIT)
{
	
}
void Wallpaper::SetWallpaperFromExecutable()
{
    std::wstring exePath = GetExecutablePath();

    // Bild sollte sich im selben Verzeichnis wie das Executable befinden
    std::wstring::size_type pos = exePath.find_last_of(L"\\/");
    std::wstring basePath = (pos != std::wstring::npos) ? exePath.substr(0, pos + 1) : L"";
    std::wstring imagePath = L"dmod.bmp"; // Hier der Name des Bildes

    // Setze den Wallpaper-Stil auf "Fit"
    SetWallpaperStyle();

    // Kopiere das Bild in das temporäre Verzeichnis und setze es als Wallpaper
    std::wstring tempImagePath = CopyImageToTemp(imagePath);
    if (!tempImagePath.empty()) {
        SetWallpaper(tempImagePath);
    }
}
std::wstring Wallpaper::GetExecutablePath()
{
	wchar_t buffer[MAX_PATH];
	GetModuleFileNameW(NULL, buffer, MAX_PATH);
	return std::wstring(buffer);
}
void Wallpaper::SetWallpaperStyle()
{
    HKEY hKey;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Control Panel\\Desktop", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        RegSetValueExW(hKey, L"WallpaperStyle", 0, REG_SZ, (const BYTE*)L"6", sizeof(wchar_t) * 2);  // Fit
        RegSetValueExW(hKey, L"TileWallpaper", 0, REG_SZ, (const BYTE*)L"0", sizeof(wchar_t) * 2);   // No tile
        RegCloseKey(hKey);
    }
}
void Wallpaper::SetWallpaper(const std::wstring& imagePath)
{
    SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (PVOID)imagePath.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
}
std::string Wallpaper::WStringToString(const std::wstring& wstr)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    return conv.to_bytes(wstr);
}
}
std::wstring Wallpaper::CopyImageToTemp(const std::wstring& filename)
{
        wchar_t tempPath[MAX_PATH];
        GetTempPathW(MAX_PATH, tempPath);
        std::wstring tempImagePath = std::wstring(tempPath) + L"temp_dmod.bmp";

        std::ifstream src(WStringToString(filename), std::ios::binary);
        std::ofstream dst(WStringToString(tempImagePath), std::ios::binary);

        if (!src.is_open() || !dst.is_open()) {
            std::wcerr << L"Failed to open source or destination image file." << std::endl;
            return L"";
        }

        dst << src.rdbuf();

        return tempImagePath;
}
