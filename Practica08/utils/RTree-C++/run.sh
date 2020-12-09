# /bin/bash
g++ --std c++11 -c Main.cpp
g++ Main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app
dot datos.dot -o ejemplo.png -Tpng -Gcharset=utf8