#ifndef SPAG_KERNEL_H
#define SPAG_KERNEL_H

// Window management
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "Scene.h"
#include "Common.h"
#include "Camera.h"
#include "PBDSolver.h"

namespace spag{

struct SDL_state{

    SDL_state(uint _windowWidth = 1920, 
              uint _windowHeight = 1080,
              std::string _windowName = "Spaghetti engine");
    ~SDL_state();

    bool init(uint windowWidth, uint windowHeight, std::string windowName);
    bool teardown();

    uint m_windowWidth;
    uint m_windowHeight;
    std::string m_windowName;

    SDL_Window * m_window = nullptr;
    SDL_GLContext * m_context = nullptr;
};


struct Kernel{

    static Kernel* get(){
        if(!m_instance)
            m_instance = new Kernel();
        return m_instance;
    }

//=====================================Main kernel functionality===============================
public:
    bool quit = false;

    bool init();
    void runMainLoop();

private:
    Kernel() = default;
    static Kernel * m_instance;

//=====================================SDL functionality=======================================
public:

private:
    SDL_state m_sdl_state;

//=====================================Opengl functionality====================================
public:
    bool initGL();

    std::vector<std::shared_ptr<Shader>> m_shaders;
    std::vector<std::shared_ptr<Drawable>> m_drawables;
private:
//=====================================Scene functionality=====================================
public:
    // Get viewer Camera
    std::shared_ptr<Camera> getViewerCamera();

    // Set viewer Camera
    void setViewerCamera(std::shared_ptr<Camera> _viewerCamera);    

    // Get scene
    std::shared_ptr<Scene> getScene();
private:
    // Camera to draw everything from
    std::shared_ptr<Camera> m_viewerCamera;

    // Pointer to current scene
    std::shared_ptr<Scene> m_scene;
};

Kernel* Kernel::m_instance = 0;

static auto & kernel = Kernel::get();

}

#endif /* SPAG_KERNEL_H */