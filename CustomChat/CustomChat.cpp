#include "pch.h"
#include "CustomChat.h"
#include <Windows.h>


BAKKESMOD_PLUGIN(CustomChat, "Create custom chat messages", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void CustomChat::onLoad()
{
	_globalCvarManager = cvarManager;
	cvarManager->registerNotifier("sendChat", [this](std::vector<std::string> args)
		{
			sendMessage("thisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthisthis");
		}, "", PERMISSION_ALL);
}

void CustomChat::pressVk(short vk)
{
	INPUT inputs[2];
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = vk;

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = vk;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}

void CustomChat::pressKey(char c)
{
	auto inputLocale = GetKeyboardLayout(0);
	auto virtualKey = VkKeyScanExA(c, inputLocale);
	pressVk(virtualKey);
}

void CustomChat::sendMessage(const std::string& msg)
{
	pressKey('t'); //Change based on keybind
	/*
	gameWrapper->SetTimeout([=](GameWrapper* gw) 
		{
			for (char c : msg)
			{
				pressKey(c);
			}
			pressVk(VK_RETURN);
		}, 0.005);
		*/
}

void CustomChat::onUnload()
{
}