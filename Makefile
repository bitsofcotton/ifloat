CXX=	xcrun clang++

# compiler flags.
CXXFLAGS+=	-std=c++11
#CXXFLAGS+=	-Ofast -mtune=native -gfull
CXXFLAGS+=	-O0 -gfull
LDFLAGS+=	-lc++
