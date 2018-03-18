# Source for the game
set(TESTGAME_SRC
	Animation.hpp
	ParallaxingBackground.hpp
	Player.hpp
    TestGame.hpp
    TestGame.cpp
    main.cpp
	TileSheet.cpp
	TileSheet.hpp
	Enemy.hpp
	Projectile.hpp
)

# Define an executable
add_executable(test_game
    ${TESTGAME_SRC})
        
# Define the libraries this project depends upon
target_link_libraries(test_game gl_engine SDL2::SDL2main)

add_custom_command(TARGET test_game PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/test_game/Fonts $<TARGET_FILE_DIR:test_game>/Fonts)

add_custom_command(TARGET test_game PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/test_game/Shaders $<TARGET_FILE_DIR:test_game>/Shaders)

add_custom_command(TARGET test_game PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/test_game/Textures $<TARGET_FILE_DIR:test_game>/Textures)