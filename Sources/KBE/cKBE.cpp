//file      cKBE.cpp
//date      09-12-2018
//project   Kubbler
//author    Warkerings

#include <KBE/cKBE.h>

int KBE::Run() {
    if (Init(1024, 600, false))
        return 1;
    
    unsigned int VBO, VAO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    mChunk = new cChunk();
    
    glClearColor(0.2, 0.3, 0.3, 1.0);
    
    while(!glfwWindowShouldClose(mWindow)){
        mCurrentTime = (float)glfwGetTime();
        mDeltaTime = mCurrentTime - mLastFrame;
        mLastFrame = mCurrentTime;
        
        ProcessInput();
        
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        mTextures.Use();
        mShaders.Use();
        mShaders.SetMat4("projection", glm::perspective(glm::radians(45.0f), (float)mWinWidth / (float)mWinHeight, 0.1f, 100.0f));
        mShaders.SetMat4("view", mCamera.GetViewMatrix());
        mShaders.SetMat4("model", glm::mat4(1));
        glBindVertexArray(VAO);
        mChunk->Draw();
        
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
    glfwSetWindowUserPointer(mWindow, this);
    glfwSetFramebufferSizeCallback(mWindow, CallBackWindowSize);
    glfwSetCursorPosCallback(mWindow, CallBackCursor);
    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    LogInfo("Initializing GLAD...");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LogError("Can't initialize GLAD");
        return 1;
    }
    
    glViewport(0, 0, mWinWidth, mWinHeight);
    glEnable(GL_DEPTH_TEST);
    
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
    mFirstLoop = true;
    mCurrentTime = 0.0f;
    mDeltaTime = 0.0f;
    mLastFrame = 0.0f;
}

KBE::~KBE() {
    Release();
}

void KBE::ProcessResize(int width, int height){
    mWinWidth = width;
    mWinHeight = height;
    glViewport(0, 0, width, height);
}

void KBE::ProcessCursor(double cursorX, double cursorY){
    if(mFirstLoop){
        mLastX = (float)cursorX;
        mLastY = (float)cursorY;
        mFirstLoop = false;
    }
    mOffsetX = (float)cursorX - mLastX;
    mOffsetY = mLastY - (float)cursorY;
    mLastX = (float)cursorX;
    mLastY = (float)cursorY;
    
    mCamera.Look(mOffsetX, mOffsetY);
}

void KBE::ProcessInput() {
    if(glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
    if(glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
        mCamera.Move(CAM_FORWARD, mDeltaTime);
    if(glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
        mCamera.Move(CAM_BACKWARD, mDeltaTime);
    if(glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
        mCamera.Move(CAM_LEFT, mDeltaTime);
    if(glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
        mCamera.Move(CAM_RIGHT, mDeltaTime);
}
