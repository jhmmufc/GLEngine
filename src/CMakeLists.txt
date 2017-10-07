# Source for the library
set(GLENGINE_SRC
    AudioEngineWrapper.cpp
    AudioManager.cpp
    Camera.cpp
    Clock.cpp
    GameContext.cpp
    GameEngine.cpp
    GLSLProgram.cpp
    InputManager.cpp
    ParticleBatch2D.cpp
    ParticleEngine.cpp
    ResourceManager.cpp
    Sprite.cpp
    SpriteBatch.cpp
    SpriteFont.cpp
    TextureManager.cpp
    Time.cpp
    Utility.cpp
    Window.cpp
    Game.cpp
)

# Define library. Only source files here!
add_library(gl_engine
    ${GLENGINE_SRC})
   
# Link to the libs we need
target_link_libraries(gl_engine
    glew::glew
    SDL2::SDL2
    glm
    --coverage
)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(gl_engine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS gl_engine EXPORT GLEngineConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT GLEngineConfig DESTINATION share/gl_engine/cmake)

# This makes the project importable from the build directory
export(TARGETS gl_engine FILE GLEngineConfig.cmake)