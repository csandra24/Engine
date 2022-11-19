#include "Menu.h"

Menu::Menu(char* name) : name(name) {}

Menu::~Menu() {}

void Menu::OnOff()
{
	enabled = !enabled;
}

bool Menu::IsEnabled() const
{
	return enabled;
}