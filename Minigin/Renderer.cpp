#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	SceneManager::GetInstance().Render();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	
	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}

}


void dae::Renderer::RenderTexture(const Texture2D& texture, float x, float y, float rotationAngle) const
{
	SDL_Rect dstRect{};
	dstRect.x = static_cast<int>(x);
	dstRect.y = static_cast<int>(y);

	// Get the size of the texture
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dstRect.w, &dstRect.h);

	// Use SDL_RenderCopyEx to apply rotation
	SDL_RenderCopyEx(
		m_renderer,
		texture.GetSDLTexture(),
		nullptr,   // No source rect (full texture)
		&dstRect,  // Destination rectangle
		rotationAngle,  // Rotation angle
		nullptr,  // Rotation around the center of the texture
		SDL_FLIP_NONE // No flip
	);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, float x, float y, float width, float height, float rotationAngle) const
{
	SDL_Rect dstRect{};
	dstRect.x = static_cast<int>(x);
	dstRect.y = static_cast<int>(y);
	dstRect.w = static_cast<int>(width);
	dstRect.h = static_cast<int>(height);

	// Use SDL_RenderCopyEx to apply rotation with custom width/height
	SDL_RenderCopyEx(
		m_renderer,
		texture.GetSDLTexture(),
		nullptr,   // No source rect (full texture)
		&dstRect,  // Destination rectangle
		rotationAngle,  // Rotation angle
		nullptr,  // Rotation around the center of the texture
		SDL_FLIP_NONE // No flip
	);
}

SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }
