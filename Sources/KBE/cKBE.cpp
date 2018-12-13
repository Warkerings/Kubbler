//file      cKBE.cpp
//date      09-12-2018
//project   Kubbler
//author    Warkerings

#include <KBE/cKBE.h>

int KBE::Run() {
    if ( Init(640, 480, false) )
        return 1;
    
    unsigned int VBO, VAO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    mBlock = new cBlock();
    
    glClearColor(0.2, 0.3, 0.3, 1.0);
    
    while(!glfwWindowShouldClose(mWindow)){
        glClear(GL_COLOR_BUFFER_BIT);
        
        mTextures.Use();
        mShaders.Use();
        glBindVertexArray(VAO);
        mBlock->Draw();
        
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
    
    LogInfo("Main loop exited. Closing...");
    return 0;
}

int KBE::Init(int Width, int Height, bool FullScreen) {
    mWinWidth = Width;
    mWinHeight = Height;
    mFullScreen = FullScreen;
    
    LogInfo("Initializing GLFW...");
    if(glfwInit() == GLFW_FALSE){
        LogError("Can't initialize GLFW");
        return 1;
    }
    
    LogInfo("Creating window...");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if(!mFullScreen) {
        mWindow = glfwCreateWindow(mWinWidth, mWinHeight, "Test", nullptr, nullptr);
    }else {
        mWindow = glfwCreateWindow(mWinWidth, mWinHeight, "Test", glfwGetPrimaryMonitor(), nullptr);
    }
    glfwMakeContextCurrent(mWindow);
    
    LogInfo("Initializing GLAD...");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LogError("Can't initialize GLAD");
        return 1;
    }
    
    glViewport(0, 0, mWinWidth, mWinHeight);
    
    mShaders.Load("../Data/Shaders/vertex.glsl", "../Data/Shaders/fragment.glsl");
    mTextures.Load("../Data/Textures/grass_diff.jpg");
    
    mShaders.Use();
    mShaders.SetInt("texture0", 0);
    
    LogInfo("Initializations successful. Entering main loop...");
    return 0;
}

void KBE::Release() {
    if(mWindow != nullptr){
        glfwDestroyWindow(mWindow);
        LogInfo("Window destroyed");
    }
    glfwTerminate();
    LogInfo("GLFW terminated");
}

KBE::KBE() {
    mWindow = nullptr;
    mWinWidth = 640;
    mWinHeight = 480;
    mFullScreen = false;
}

KBE::~KBE() {
    Release();
}
