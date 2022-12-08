#include "../Application.h"
#include "../Globals.h"
#include "PanelConfiguration.h"
#include "../Modules/ModuleEditor.h"
#include "../Modules/ModuleWindow.h"
#include "../Modules/ModuleRender.h"
#include "../Modules/ModuleCamera.h"

#include "../lib/SDL/include/SDL.h"
#include "../lib/imgui-docking/imgui.h"
#include "../lib/imgui-docking/imgui_impl_sdl.h"
#include "../lib/imgui-docking/imgui_impl_opengl3.h"
#include "../lib/glew-2.1.0/include/GL/glew.h"


static ImVec4 pink = ImVec4(1.0f, 0.0f, 0.40f, 1.0f);


PanelConfiguration::PanelConfiguration()
{

}

PanelConfiguration::~PanelConfiguration()
{

}

void PanelConfiguration::Draw()
{

	if (App->Editor->configurationEnabled) {

		ImGui::SetNextWindowSize(ImVec2(300, 550), ImGuiCond_Once);
		ImGui::SetNextWindowPos(ImVec2(0, 20), ImGuiCond_Once);

		if (ImGui::Begin("Configuration"))
		{
			if (ImGui::CollapsingHeader("Application"))
			{
                ImGui::Text(TITLE);

                std::vector<float> fpsLog = App->Editor->GetFps();
                std::vector<float> msLog = App->Editor->GetMs();

                char title[25];
                sprintf_s(title, 25, "Framerate %.1f", fpsLog[fpsLog.size() - 1]);
                ImGui::PlotHistogram("##framerate", &fpsLog[0], 100, 0, title, 0.0f, 200.0f, ImVec2(310.0f, 100.0f));
                sprintf_s(title, 25, "Miliseconds %.1f", msLog[msLog.size() - 1]);
                ImGui::PlotHistogram("##framerate", &msLog[0], 100, 0, title, 0.0f, 200.0f, ImVec2(310.0f, 100.0f));

                if (ImGui::Checkbox("VSync", &App->vsync))
                {
                    App->renderer->SetVSync(App->vsync);
                }
			}
            
            if (ImGui::CollapsingHeader("Window"))
            {
                static bool Fullscreen = FULLSCREEN;
                static bool Resizable = RESIZABLE;
                static bool Borderless = BORDERLESS;

				if (ImGui::Checkbox("FULLSCREEN   ", &Fullscreen))
				{
					App->window->SetWindowFullscreen(Fullscreen);
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("RESIZABLE   ", &Resizable))
				{
					App->window->SetWindowResizable(Resizable);
				}

				if (ImGui::Checkbox("BORDERLESS   ", &Borderless))
				{
					App->window->SetWindowBorderless(Borderless);
				}

                if (Resizable || Borderless)
                {
                    bool resizable = App->window->GetResizable();
                    if (ImGui::Checkbox("Resizable", &resizable))
                    {
                        App->window->SetResizable(resizable);
                    }
                    if (resizable)
                    {
                        bool size_changed = false;
                        bool size_changing = false;
                        ImGui::SliderInt("Width", &windowWidth, 640, 4096);
                        if (ImGui::IsItemDeactivatedAfterEdit())
                        {
                            size_changed = true;
                        }
                        if (ImGui::IsItemActive())
                        {
                            size_changing = true;
                        }
                        ImGui::SliderInt("Height", &windowHeight, 480, 2160);
                        if (ImGui::IsItemDeactivatedAfterEdit())
                        {
                            size_changed = true;
                        }
                        if (ImGui::IsItemActive())
                        {
                            size_changing = true;
                        }

                        if (size_changed)
                        {
                            App->window->SetSize(windowWidth, windowHeight);
                        }
                        else if (!size_changing)
                        {
                            windowWidth = App->window->GetWidth();
                            windowHeight = App->window->GetHeight();
                        }
                    }
                }

                float brightness = App->window->GetBrightness();
                if (ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f))
                {
                    App->window->SetBrightness(brightness);
                }

               
            }

            if (ImGui::CollapsingHeader("Camera")) 
            {
                vec front = App->camera->GetFront();
                vec up = App->camera->GetUp();
                ImGui::InputFloat3("Front", front.ptr(), "%.3f", ImGuiInputTextFlags_ReadOnly);
                ImGui::InputFloat3("Up", up.ptr(), "%.3f", ImGuiInputTextFlags_ReadOnly);
                vec position = App->camera->GetPosition();
                if (ImGui::InputFloat3("Position", position.ptr()))
                {
                    App->camera->SetPosition(position);
                }

                ImGui::Separator();

                float mSpeed = App->camera->GetMoveSpeed();
                float mrotation = App->camera->GetRotateSpeed();

                if (ImGui::SliderFloat("Movement Speed", &mSpeed, 0.0f, 60.0f))
                {
                    App->camera->SetMoveSpeed(mSpeed);
                }

                if (ImGui::SliderFloat("Rotation Speed", &mrotation, 0.0f, 60.0f))
                {
                    App->camera->SetRotSpeed(mrotation);
                }

                float nearPlane = App->camera->GetNearPlane();
                float farPlane = App->camera->GetFarPlane();

                if (ImGui::InputFloat("Near Plane", &nearPlane))
                {
                    App->camera->SetPlaneDistance(nearPlane, farPlane);
                }
                if (ImGui::InputFloat("Far Plane", &farPlane))
                {
                    App->camera->SetPlaneDistance(nearPlane, farPlane);
                }
                float fov = App->camera->GetVerticalFOV();
                if (ImGui::InputFloat("Field of View", &fov))
                {
                    App->camera->SetVerticalFOV(fov);
                }

            }

            if (ImGui::CollapsingHeader("Hardware")) 
            {
                OpenlGlVersion = (const char*)glGetString(GL_VERSION);
                ImGui::Text("Using OpenGl");
                ImGui::SameLine();
                ImGui::TextColored(pink, OpenlGlVersion);

 
                ImGui::Text("Using SDL");
                ImGui::SameLine();
                ImGui::TextColored(pink, "2.0");

                ImGui::Text("");
                ImGui::Separator();
                ImGui::Text("");

                gpu_vendor = (const char*)glGetString(GL_VENDOR);
                ImGui::Text("Vendor: %s");
                ImGui::SameLine();
                ImGui::TextColored(pink, gpu_vendor);

                rendererS = (const char*)glGetString(GL_RENDERER);
                ImGui::Text("Graphic: %s");
                ImGui::SameLine();
                ImGui::TextColored(pink, rendererS);

                ImGui::Text("CPUs:");
                ImGui::SameLine();
                ImGui::TextColored(pink, "%d", SDL_GetCPUCount);
                ImGui::SameLine();
                ImGui::TextColored(pink, "%i (Cache: %i kb)", SDL_GetCPUCacheLineSize);

                ImGui::Text("System RAM:");
                ImGui::SameLine();
                ImGui::TextColored(pink, "%.1f Gb", SDL_GetSystemRAM);

                ImGui::Text("");
                ImGui::Separator();
                ImGui::Text("");

                ImGui::Text("VRAM Budget:");
                ImGui::SameLine();
                ImGui::TextColored(pink, "%.1f Mb", local_video_memory_info.Budget * 0.00000001f);
                ImGui::Text("VRAM Usage:");
                ImGui::SameLine();
                ImGui::TextColored(pink, "%.1f Mb", local_video_memory_info.CurrentUsage * 0.00000001f);
                ImGui::Text("VRAM Available:");
                ImGui::SameLine();
                ImGui::TextColored(pink, "%.1f Mb", local_video_memory_info.AvailableForReservation * 0.00000001f);
                ImGui::Text("VRAM Reserved:");
                ImGui::SameLine();
                ImGui::TextColored(pink, "%.1f Mb", local_video_memory_info.CurrentReservation * 0.00000001f);

            }
        }

        ImGui::End();
		
	}

}

