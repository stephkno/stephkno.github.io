all:
	em++ \
	src/main.cpp \
	src/mazegen.cpp	\
	src/mazesolver.cpp \
	src/js.cpp \
	-I src/disjoint_set.h \
	-I src/mazegen.h \
	-I src/mazesolver.h \
	-I src/queue.h \
	-I src/js.h \
	-g \
	-o index.html \
	-s WASM=1 \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s EXIT_RUNTIME \
	-s NO_DISABLE_EXCEPTION_CATCHING \
	-Oz \
	--shell-file template/index.html

run:
	emrun --no_browser --port 8080 .