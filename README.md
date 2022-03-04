# tetris

Competitive tetris. Can be played at https://games.freppan.com/tetris


To compile with emscripten
em++ -std=c++17 -O2 -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 -s FETCH=1 src/*.cpp -o index.html
