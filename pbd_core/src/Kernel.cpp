#include "Kernel.h"

namespace spag{

//=====================================SDL State===============================================

SDL_state::SDL_state(uint _windowWidth,
                     uint _windowHeight,
                     std::string _windowName) :
    m_windowWidth(_windowWidth),
    m_windowHeight(_windowHeight),
    m_windowName(_windowName)
{
    init(m_windowWidth, m_windowHeight, m_windowName);
}

SDL_state::~SDL_state(){
    teardown();
}

bool SDL_state::init(uint windowWidth, uint windowHeight, std::string windowName){

    std::atexit(SDL_Quit);

    if (SDL_Init(SDL_INIT_VIDEO)<0 ){
        std::cout<<"Failed to init SDL: "<<SDL_GetError()<<std::endl;
        return false;
    }

    //SDL_GL_LoadLibrary(0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
               SDL_GL_CONTEXT_PROFILE_CORE);

    //SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    //SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    //SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    m_window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(!m_window){
        std::cout<<"Failed to create window: "<<SDL_GetError()<<std::endl;
        return false;
    }

    m_context = new SDL_GLContext(SDL_GL_CreateContext(m_window));
    if(!m_context){
        std::cout<<"Failed to create GL context: "<<SDL_GetError()<<std::endl;
        return false;
    }
    return true;
}

bool SDL_state::teardown(){
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return true;
}


//=====================================Kernel==================================================

//=====================================Main kernel functionality===============================

bool init(){
    
}

void Kernel::runMainLoop(){
    while(!quit)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event) != 0){
            switch (event.type){
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                    case SDLK_LEFT:
                        m_viewerCamera->moveCamera(Camera::ORBIT_LEFT);
                        std::cout<<"SDLK_LEFT"<<std::endl;
                        break;
                    case SDLK_RIGHT:
                        m_viewerCamera->moveCamera(Camera::ORBIT_RIGHT);
                        std::cout<<"SDLK_RIGHT"<<std::endl;
                        break;
                    case SDLK_UP:
                        m_viewerCamera->moveCamera(Camera::ORBIT_UP);
                        std::cout<<"SDLK_UP"<<std::endl;
                        break;
                    case SDLK_DOWN:
                        m_viewerCamera->moveCamera(Camera::ORBIT_DOWN);
                        std::cout<<"SDLK_DOWN"<<std::endl;
                        break;
                    }
                    break;

                case SDL_MOUSEWHEEL:
                    if(event.wheel.y < 0)       // scroll up
                        m_viewerCamera->moveCamera(Camera::ZOOM_IN);
                    else if(event.wheel.y > 0)  // scroll down
                        m_viewerCamera->moveCamera(Camera::ZOOM_OUT);
                    break;
            }
        }

        glClearColor(.5f, 0.5f, 0.5f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(auto & sbg : m_scene->m_SBGs)
            advanceStep(*sbg, *m_scene->m_pa, 1.f/24.f);

        m_viewerCamera->update();
        Eigen::Matrix4f cameraVP = m_viewerCamera->m_projMat * m_viewerCamera->m_viewMat;

        for(auto & drawable : m_drawables)
            drawable->draw(cameraVP);

        SDL_GL_SwapWindow(m_sdl_state.m_window);
    }
}

//=====================================SDL functionality=======================================

//=====================================Opengl functionality====================================

bool Kernel::initGL(){
    GLenum err = glewInit();
    if (GLEW_OK != err){
        // GLEW failed!
        std::cout<<"Failed to unit GLEW: "<<glewGetErrorString(err)<<std::endl;
        return false;
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(m_sdl_state.m_window && m_sdl_state.m_context)
        SDL_GL_SwapWindow(m_sdl_state.m_window);
    return true;
}


std::shared_ptr<Camera> Kernel::getViewerCamera(){
    return m_viewerCamera;
}

void Kernel::setViewerCamera(std::shared_ptr<Camera> _viewerCamera){
    m_viewerCamera = _viewerCamera;
}

std::shared_ptr<Scene> Kernel::getScene(){
    return m_scene;
}


//=====================================Scene functionality=====================================


}