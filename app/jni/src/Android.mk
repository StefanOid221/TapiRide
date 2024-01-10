LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(LOCAL_PATH)/../SDL2_image/ $(LOCAL_PATH)/../SDL2_mixer/ $(LOCAL_PATH)/../SDL2_ttf/ $(LOCAL_PATH)/../src/headers

# Add your application source files here...
LOCAL_SRC_FILES := main.cpp Globals.cpp Util.cpp LTexture.cpp LButton.cpp Player.cpp Obstacle.cpp Cola.cpp GameManager.cpp LTimer.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer SDL2_ttf

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -lOpenSLES -llog -landroid

include $(BUILD_SHARED_LIBRARY)
