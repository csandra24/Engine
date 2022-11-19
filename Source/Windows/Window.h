#include "../lib/imgui-docking/imgui.h"

class Window
{
public:
	Window();
	~Window();

	virtual void Draw() { }

	bool IsEnabled() const {
		return enabled;
	}

	bool IsFocused() const {
		return focused;
	}

	void ToggleEnabled() {
		enabled = !enabled;
	}

protected:
	bool enabled = true;
	bool focused = false;
};

