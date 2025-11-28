CXX = g++
CXXFLAGS = -std=c++17 -I/app/lib/SFML-2.5.1/include -I./JukkyJung-Adventure
LDFLAGS = -L/app/lib/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
SRCS = $(wildcard JukkyJung-Adventure/*.cpp)
OBJS = $(SRCS:.cpp=.o)
EXEC = JukkyJung-Adventure.out

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
