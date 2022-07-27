OBJ_UFT=uft.o
DEPS = utf.h
CXXFLAGS=-O3 -Wall -std=c++11 $(EXTRA_CXXFLAGS)
TARGET_UFT=uft
INSTALL_DIR ?= "${HOME}/bin/"
LIBS=
STATIC_LIBGIT2=build/libgit2.a
LIBGIT2=-lgit2
LIBCURL=-lcurl

ifeq ($(BUILD_LIBGIT2), 1)
  LIBGIT2=$(STATIC_LIBGIT2)
  CXXFLAGS+=-I./libgit2/include/
  LIBS=-lpthread -lssl -lcrypto -lz -lpcre
endif

ifeq ($(DEBUG), 1)
  CXXFLAGS+=-g
endif

all: $(TARGET_UFT)

$(TARGET_UFT): $(OBJ_UFT) $(DEPS)
	g++ -o $@ $+ $(LIBGIT2) $(LIBS) $(LIBCURL)

%.o: %.cc $(LIBGIT2) $(DEPS)
	g++ -c $(CXXFLAGS) $<

$(STATIC_LIBGIT2):
	git submodule init
	git submodule update
	mkdir -p build
	(cd build;cmake -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DBUILD_CLAR=OFF -DUSE_SSH=OFF ../libgit2;cmake --build .)

install: $(TARGET_UFT)
	install -b -D -m 755 $(TARGET_UFT) $(INSTALL_DIR)

clean:
	rm -f $(OBJ_UFT)
	rm -f $(TARGET_UFT)
	rm -rf build