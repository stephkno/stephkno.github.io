native:
	g++ \
	src/main.cpp \
	src/mazegen.cpp	\
	src/mazesolver.cpp \
	-I src \
	-g \
	-o maze

wasm:
	em++ \
	src/main_wasm.cpp \
	src/mazegen.cpp	\
	src/mazesolver.cpp \
	src/js.cpp \
	-I src \
	-g \
	-o index.html \
	-s WASM=1 \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s EXIT_RUNTIME \
	-s NO_DISABLE_EXCEPTION_CATCHING \
	-sASYNCIFY \
	-DWASM \
	--shell-file template/index.html \
	--profiling

run:
	emrun --no_browser --port 8080 .