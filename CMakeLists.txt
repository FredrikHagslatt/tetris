cmake_minimum_required(VERSION 3.15)

project(empge CXX)

add_executable(
    main
    src/main.cpp
    src/olcPixelGameEngine.h
    src/MultiplayerTetris.cpp
    src/MultiplayerTetris.h
    src/Constants.h
    src/Tetrominoes.h
    src/Tetrominoes.cpp
    src/TetrisPlayer.h
    src/TetrisPlayer.cpp
    src/Scene.h
    src/Scene.cpp
    src/LeaderboardScene.h
    src/LeaderboardScene.cpp
    src/OnlineGameScene.h
    src/OnlineGameScene.cpp
    src/SplitScreenGameScene.h
    src/SplitScreenGameScene.cpp
    src/MenuScene.cpp
    src/MenuScene.h
    src/EnterNameScene.h
    src/EnterNameScene.cpp
    src/ServerConnectionEmscripten.h
    src/ServerConnectionEmscripten.cpp
    src/SoloGameScene.h
    src/SoloGameScene.cpp
    src/SceneManager.h
    src/SceneManager.cpp
)

include(cmake/PGE.cmake)
pge_set_emscripten_options(main)
