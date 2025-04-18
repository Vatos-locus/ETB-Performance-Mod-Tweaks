#pragma once
#include "headers.h"

#include <memory>
#include <string>

class Wallpaper
{
public:
	Wallpaper(std::shared_ptr<Launcher> launcherINIT, const std::shared_ptr<Sound> soundINIT);
	void SetWallpaperFromExecutable();


private:
	const std::weak_ptr<Launcher> launcher;
	const std::weak_ptr<Sound> sound;

	std::wstring GetExecutablePath();
	void SetWallpaperStyle();
	void SetWallpaper(const std::wstring& imagePath);
	std::string WStringToString(const std::wstring& wstr);
	std::wstring CopyImageToTemp(const std::wstring& filename);

	
};