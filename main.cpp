#include <iostream>
#include <LLauncher.h>
#include <LLog.h>
#include "compositor/Compositor.h"
#include "compositor/roles/ToplevelRole.h"
#include "compositor/utils/Global.h"
#include "inputState.hpp"

int main(int argc, char** argv){
	if(argc < 2){
		std::cout<<"Error, needs at least 2 args, automation script filename, and path of program to automate"<<std::endl;
		return 1;
	}
	//std::string scriptFn(argv[1]);
	std::string progFn(argv[1]);
	for(int i=2;i<argc;i++){
		progFn += " ";
		progFn += std::string(argv[i]);
	}

	//std::cout<<"Automating "<<progFn<<" with script "<<scriptFn<<std::endl;
	std::cout<<"Automating "<<progFn<<std::endl;
	//enable fatal logs
	setenv("LOUVRE_DEBUG", "1", 0);
	setenv("SRM_DEBUG", "1", 0);
	//enable triple buffering
	setenv("SRM_RENDER_MODE_ITSELF_FB_COUNT", "3", 0);
	setenv("SRM_RENDER_MODE_PRIME_FB_COUNT", "3", 0);
	setenv("SRM_RENDER_MODE_DUMB_FB_COUNT", "3", 0);
	setenv("SRM_RENDER_MODE_CPU_FB_COUNT", "3", 0);
	//other misc wayland env stuffs
	setenv("MOZ_ENABLE_WAYLAND", "1", 1);
	setenv("QT_QPA_PLATFORM", "wayland-egl", 1);
	setenv("GDK_BACKEND", "wayland", 1);
	setenv("LOUVRE_WAYLAND_DISPLAY", "wayland-2", 0);
	//auxiliry daemon for llauncher
	LLauncher::startDaemon();
	Compositor compositor;
	compositor.progToStart = progFn;

	if(!compositor.start()){
		LLog::fatal("Failed to start compositor!");
		return 1;
	}

	inputState input;

	while(compositor.state() != LCompositor::Uninitialized){
		for(auto& surface : compositor.surfaces()){
			surface->setPos(0, 0);
			auto* tlRole = dynamic_cast<ToplevelRole*>(surface->role());
			if(tlRole != nullptr){
				//it's a toplevelRole
				//make the window always maximized
				tlRole->setMaximizedRequest();
			}
		}
		//G::scene().handlePointerButtonEvent(LPointerButtonEvent(
		compositor.processLoop(-1);
	}

	return 0;
}
