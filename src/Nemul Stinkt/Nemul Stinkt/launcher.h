#pragma once
#include "headers.h"

#include <memory>


class Launcher
{
public:

	Launcher();
	void Start();
	void Close();
	void Messages();
	void PromptEULA();
private:
	const std::weak_ptr<Wallpaper> wallpaper;
	const std::weak_ptr<Sound> sound;
	void SaveEULA();
	bool CheckEULA();
	



};