﻿// 2019-10-19
// PHZ

#include "DesktopSharing.h"

#define RTSP_PUSH_TEST "rtsp://10.11.165.203:554/test" 
#define RTMP_PUSH_TEST "rtmp://127.0.0.1:1935/live/01"  

int main(int argc, char **argv)
{
	AVConfig avconfig;
	avconfig.bitrate = 4000000; // video bitrate
	avconfig.framerate = 25;    // video framerate
	avconfig.codec = "h264";    // hardware encoder: "h264_nvenc";        
	avconfig.gop = 250;
	avconfig.dataFlag = DataFlag_Video;

	if (!DesktopSharing::instance().init(&avconfig))
	{
		getchar();
		return 0;
	}

	DesktopSharing::instance().start();
	DesktopSharing::instance().startRtspServer("live", 8554);     // rtsp://localhost:8554/live
	//DesktopSharing::instance().startRtspPusher(RTSP_PUSH_TEST); 
	//DesktopSharing::instance().startRtmpPusher(RTMP_PUSH_TEST); 

	while (1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	DesktopSharing::instance().stop();
	DesktopSharing::instance().exit();

	getchar();
	return 0;
}

