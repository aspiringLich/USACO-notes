CXX = g++
CXXFLAGS = -DLOCAL -fdiagnostics-color=always -g -std=c++17 -Wall
OBJDIR = build
SRC = $(wildcard boilerplate/*.cpp finished/*/*.cpp finished/*/*/*.cpp workspace/*.cpp)
OBJS = $(SRC:%.cpp=$(OBJDIR)/%.o)
EXE = $(OBJS:%.o=%)

all: $(EXE)

$(OBJDIR)/%: $(OBJDIR)/%.o
	@nm $< | grep -q " T main" && $(CXX) $(CXXFLAGS) $< -o $@ || echo "Skipping $^ (no main function)"

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(OBJDIR)/*
