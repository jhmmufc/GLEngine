# Source for the game
set(TESTGAME_SRC
    Game.hpp
    Game.cpp
    main.cpp
)

# Define an executable
add_executable(test_game
    ${TESTGAME_SRC})
    
target_compile_features(test_game PRIVATE cxx_lambda_init_captures)
    
# Define the libraries this project depends upon
target_link_libraries(test_game gl_engine)