# Variables
CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

# Compiling
Vulkan: *.cpp *.h
	g++ $(CFLAGS) -o Vulkan *.cpp $(LDFLAGS)

# Rules
.PHONY: test clean

test: Vulkan
	./Vulkan

clean:
	rm -f Vulkan