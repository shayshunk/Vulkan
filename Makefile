# Variables
CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

# create list of all spv files and set as dependency
vertSources = $(shell find ./shaders -type f -name "*.vert")
vertObjFiles = $(patsubst %.vert, %.vert.spv, $(vertSources))
fragSources = $(shell find ./shaders -type f -name "*.frag")
fragObjFiles = $(patsubst %.frag, %.frag.spv, $(fragSources))

# Compiling
Vulkan: *.cpp *.h
	g++ $(CFLAGS) -o Vulkan *.cpp $(LDFLAGS)

# Rules
.PHONY: test clean

test: Vulkan
	./Vulkan

clean:
	rm Vulkan
	make
	./Vulkan