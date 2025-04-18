#pragma once

#include <memory>

class Sound
{
public:
	Sound();

private:
	const std::weak_ptr<Launcher> launcher;
	const std::weak_ptr<Wallpaper> wallpaper;
};