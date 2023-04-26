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
			std::shared_ptr<std::string> msg(new std::string("yo"));
			sendMessage(msg);
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

void CustomChat::shiftPressVk(short vk)
{
	INPUT inputs[4];
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_SHIFT;

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = vk;

	inputs[2].type = INPUT_KEYBOARD;
	inputs[2].ki.wVk = vk;
	inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

	inputs[3].type = INPUT_KEYBOARD;
	inputs[3].ki.wVk = VK_SHIFT;
	inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}

void CustomChat::pressKey(char c)
{
	auto inputLocale = GetKeyboardLayout(0);
	auto virtualKey = VkKeyScanExA(c, inputLocale);
	if (virtualKey & 0x100)
	{
		shiftPressVk(virtualKey);
	} else
	{
		pressVk(virtualKey);
	}
}

void CustomChat::sendMessage(const std::shared_ptr<std::string>& msg, int index)
{
	pressKey('t'); //Change based on keybind
	gameWrapper->SetTimeout([=](GameWrapper* gw)
		{
			sendMessageR(msg, index);
		}, 0.01F);
}

void CustomChat::sendMessageR(const std::shared_ptr<std::string>& msg, int index)
{
	for (int i = index; i < index + 20; ++i)
	{
		if (i == msg->length())
		{
			pressVk(VK_RETURN);
			return;
		}
		pressKey((*msg)[i]);

		if (i % 120 == 119)
		{
			pressVk(VK_RETURN);
			gameWrapper->SetTimeout([=](GameWrapper* gw)
				{
					sendMessage(msg, i + 1);
				}, 0.001F);
			return;
		}
	}
	gameWrapper->SetTimeout([=](GameWrapper* gw)
		{
			sendMessageR(msg, index + 20);
		}, 0.001F);
}

void CustomChat::onUnload()
{
}