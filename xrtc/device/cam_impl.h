﻿#ifndef XRTCSDK_XRTC_DEVICE_CAM_IMPL_H_
#define XRTCSDK_XRTC_DEVICE_CAM_IMPL_H_

#include <atomic>
#include <vector>

#include <rtc_base/thread.h>
#include <modules/video_capture/video_capture.h>

#include "xrtc/xrtc.h"

namespace xrtc {

class CamImpl : public IVideoSource,
                public rtc::VideoSinkInterface<webrtc::VideoFrame>
{
public:
    void Start() override;
    void Setup(const std::string& json_config) override;
    void Stop() override;
    void Destroy() override;
    void AddConsumer(IXRTCConsumer* consumer) override;
    void RemoveConsumer(IXRTCConsumer* consumer) override;

    // rtc::VideoSinkInterface
    void OnFrame(const webrtc::VideoFrame& frame) override;

private:
    CamImpl(const std::string& cam_id);
    ~CamImpl();

    friend class XRTCEngine;

private:
    std::string cam_id_;
    rtc::Thread* current_thread_;
    bool has_start_ = false;
    rtc::scoped_refptr<webrtc::VideoCaptureModule> video_capture_;
    webrtc::VideoCaptureModule::DeviceInfo* device_info_;
    std::atomic<int> fps_{ 0 };
    std::atomic<int64_t> last_frame_ts_{ 0 };
    std::atomic<int64_t> start_time_{ 0 };
    std::vector<IXRTCConsumer*> consumer_list_;
};

} // namespace xrtc


#endif // XRTCSDK_XRTC_DEVICE_CAM_IMPL_H_