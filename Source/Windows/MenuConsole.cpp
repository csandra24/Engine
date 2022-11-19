#include "MenuConsole.h"
#include "../Application.h"
#include "../ModuleWindow.h"

#include "../Globals.h"

MenuConsole::MenuConsole(char* name) : Menu(name) {}

MenuConsole::~MenuConsole()
{
	Clear();
}

bool MenuConsole::Draw()
{
	ImGuiWindowFlags consoleFlags = 0;
	consoleFlags |= ImGuiWindowFlags_NoFocusOnAppearing;

	if (ImGui::Begin(name, &enabled, consoleFlags))
	{
		if (ImGui::SmallButton("Clear"))
		{
			Clear();
		}
		ImGui::SameLine();
		ImGui::Checkbox("Auto Scroll", &scrollToBottom);
		ImGui::SameLine();
		filter.Draw("Filter", -100.0f);

		ImGui::Separator();

		ImGuiWindowFlags scrollFlags = 0;
		scrollFlags |= ImGuiWindowFlags_HorizontalScrollbar;
		scrollFlags |= ImGuiWindowFlags_AlwaysVerticalScrollbar;

		if (ImGui::BeginChild("scroll", ImVec2(0, 0), false, scrollFlags))
		{
			// Display logs
			if (filter.IsActive())
			{
				const char* line = buf.begin();

				for (int lineIndex = 0; line != nullptr; ++lineIndex)
				{
					const char* lineEnd;

					if (lineIndex < lineOffsets.Size)
						lineEnd = buf.begin() + lineOffsets[lineIndex];
					else
						lineEnd = nullptr;

					// Print filtered text
					if (filter.PassFilter(line, lineEnd))
						ImGui::TextUnformatted(line, lineEnd);

					if (lineEnd != nullptr && lineEnd[1] != '\0')
						line = lineEnd + 1;
					else
						line = nullptr;
				}
			}
			else
				// Print text
				ImGui::TextUnformatted(buf.begin());
		}

		if (scrollToBottom)
			ImGui::SetScrollHereY(1.0f);

		ImGui::EndChild();
	}
	ImGui::End();

	return true;
}

void MenuConsole::AddLog(const char* log)
{
	int oldSize = buf.size();

	buf.appendf(log);

	for (int newSize = buf.size(); oldSize < newSize; ++oldSize)
	{
		if (buf[oldSize] == '\n')
			lineOffsets.push_back(oldSize);
	}
}

void MenuConsole::Clear()
{
	buf.clear();
	lineOffsets.clear();
}