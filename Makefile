# Nome do compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -g

# Nome do executável
EXEC = poly_program

# Diretórios e arquivos
SRCS = Poly.cpp teste1.cpp
OBJS = $(SRCS:.cpp=.o)

# Regra padrão: compilar o executável
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

# Regra para compilar arquivos .cpp em .o
%.o: %.cpp Poly.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos arquivos objeto e executável
clean:
	rm -f $(OBJS) 
