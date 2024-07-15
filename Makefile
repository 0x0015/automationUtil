OBJS	= main.cpp.o\
	  compositor/Client.cpp.o \
	  compositor/Compositor.cpp.o \
	  compositor/Output.cpp.o \
	  compositor/SessionLockManager.cpp.o \
	  compositor/Surface.cpp.o \
	  compositor/input/Clipboard.cpp.o \
	  compositor/input/DND.cpp.o \
	  compositor/input/Keyboard.cpp.o \
	  compositor/input/Pointer.cpp.o \
	  compositor/input/Seat.cpp.o \
	  compositor/input/Touch.cpp.o \
	  compositor/roles/CursorRole.cpp.o \
	  compositor/roles/DNDIconRole.cpp.o \
	  compositor/roles/LayerRole.cpp.o \
	  compositor/roles/PopupRole.cpp.o \
	  compositor/roles/SessionLockRole.cpp.o \
	  compositor/roles/SubsurfaceRole.cpp.o \
	  compositor/roles/ToplevelRole.cpp.o \
	  compositor/scene/LayerView.cpp.o \
	  compositor/scene/Scene.cpp.o \
	  compositor/scene/SSD.cpp.o \
	  compositor/scene/SSDTouchable.cpp.o \
	  compositor/scene/SurfaceView.cpp.o \
	  compositor/utils/Assets.cpp.o \
	  compositor/utils/Global.cpp.o \
	  compositor/utils/Settings.cpp.o \
	  compositor/utils/Systemd.cpp.o

OUT	= main
CXX	= g++
CC      = gcc
CC_ACCEL = ccache
BUILD_CXX_FLAGS	 = -Wall -std=c++20 -g -I/usr/include/Louvre -I/usr/include/pixman-1 -I/usr/include/libdrm
BULID_CC_FLAGS   =
LINK_OPTS	 = -lLouvre -lpixman-1 -lsystemd -linput

all: $(OBJS)
	$(CC_ACCEL) $(CXX) $(OBJS) -o $(OUT) $(LINK_OPTS)

%.cpp.o: %.cpp
	$(CC_ACCEL) $(CXX) $< $(BUILD_CXX_FLAGS) -g -c -o $@

%.c.o: %.c
	$(CC_ACCEL) $(CXX) $< $(BUILD_CXX_FLAGS) -g -c -o $@

clean:
	rm -f $(OBJS) $(OUT)
