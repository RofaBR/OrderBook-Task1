CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCDIR = src
OBJDIR = obj
BINDIR = bin

EXECUTABLE = orderbook
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

$(BINDIR)/$(EXECUTABLE): $(OBJECTS) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: clean
