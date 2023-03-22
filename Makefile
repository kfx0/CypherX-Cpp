CXX = g++
CXXFLAGS = -std=c++20 -Wall -c
LXXFLAGS = -std=c++20
OBJECTS = CypherX.o RSAInt.o RSACrypt.o
TARGET = CypherX


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) $(OBJECTS) -o $(TARGET)
CypherX.o: CypherX.cpp
	$(CXX) $(CXXFLAGS) CypherX.cpp
RSAInt.o:RSAInt.cpp RSAInt.h
	$(CXX) $(CXXFLAGS) RSAInt.cpp
RSACrypt.o: RSACrypt.cpp RSACrypt.h
	$(CXX) $(CXXFLAGS) RSACrypt.cpp
clean:
	rm -f $(TARGET) $(OBJECTS)
