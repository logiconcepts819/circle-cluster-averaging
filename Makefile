# Specific dependencies

CXX = g++
CFLAGS = -W -Wall -O3
LDFLAGS = -lm
EXEC_NAME = test

RM = rm
RMFLAGS = -Rf

OBJS = \
	3rd-party/INIParser/src/INIConfig.o  \
	3rd-party/INIParser/src/INIParser.o \
	3rd-party/INIParser/src/Utilities.o \
	algorithms/BentleyOttmann.o         \
	config/SetupConfig.o                \
	reporter/ClusterReporter.o          \
	shapes/Circle.o                     \
	ClusterAverage.o                    \
	test.o

.PHONY: all
all: $(EXEC_NAME)

$(EXEC_NAME): $(OBJS)
	@$(CXX) -o $(EXEC_NAME) $(OBJS) $(LDFLAGS)
	@echo "CXXLD $@"

%.o: %.cpp
	@$(CXX) $(CFLAGS) -c -o $@ $<
	@echo "CXX   $@"

.PHONY: clean
clean:
	$(RM) $(RMFLAGS) $(EXEC_NAME) $(OBJS)
