all:
	em++ \
	src/main.cpp \
	src/mazegen.cpp	\
	-I src/disjoint_set.h \
	-I src/mazegen.h \
	-I src/mazesolve.h \
	-I src/queue.h \
	-g \
	-o index.html \
	-s WASM=1 \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s EXIT_RUNTIME \
	-s NO_DISABLE_EXCEPTION_CATCHING \
	--shell-file template/index.html

run:
	emrun --no_browser --port 8080 .