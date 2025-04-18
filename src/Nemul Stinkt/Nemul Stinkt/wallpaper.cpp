#include "wallpaper.h"


std::wstring GetExecutablePath();
void SetWallpaperStyle();
void SetWallpaper(const std::wstring& imagePath);
std::string WStringToString(const std::wstring& wstr);
std::wstring CopyImageToTemp(const std::wstring& filename);
