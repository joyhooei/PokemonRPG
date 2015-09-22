LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2djs_shared

LOCAL_MODULE_FILENAME := libcocos2djs

LOCAL_SRC_FILES := entrance/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/extensions/actions/UIProgressActions.cpp \
                   ../../Classes/extensions/audio/GameAudioEngine.cpp \
                   ../../Classes/extensions/bindings/auto/js_game_ext_auto.cpp \
				   ../../Framework/base/FrameworkErrors.cpp \
				   ../../Framework/base/MWArrayList.cpp \
				   ../../Framework/base/MWBinaryData.cpp \
				   ../../Framework/base/MWDictionary.cpp \
				   ../../Framework/base/MWException.cpp \
				   ../../Framework/base/MWObject.cpp \
				   ../../Framework/base/MWQueue.cpp \
				   ../../Framework/base/MWStack.cpp \
				   ../../Framework/compression/minizip/ioapi.c \
				   ../../Framework/compression/minizip/mztools.c \
				   ../../Framework/compression/minizip/unzip.c \
				   ../../Framework/compression/minizip/zip.c \
				   ../../Framework/compression/MWZipData.cpp \
				   ../../Framework/db/sqlite/libsqlite/sqlite3.c \
				   ../../Framework/db/sqlite/MWSqliteDb.cpp \
				   ../../Framework/json/libjson/Source/internalJSONNode.cpp \
				   ../../Framework/json/libjson/Source/JSONAllocator.cpp \
				   ../../Framework/json/libjson/Source/JSONChildren.cpp \
				   ../../Framework/json/libjson/Source/JSONDebug.cpp \
				   ../../Framework/json/libjson/Source/JSONIterators.cpp \
				   ../../Framework/json/libjson/Source/JSONMemory.cpp \
				   ../../Framework/json/libjson/Source/JSONNode.cpp \
				   ../../Framework/json/libjson/Source/JSONNode_Mutex.cpp \
				   ../../Framework/json/libjson/Source/JSONPreparse.cpp \
				   ../../Framework/json/libjson/Source/JSONStream.cpp \
				   ../../Framework/json/libjson/Source/JSONValidator.cpp \
				   ../../Framework/json/libjson/Source/JSONWorker.cpp \
				   ../../Framework/json/libjson/Source/JSONWriter.cpp \
				   ../../Framework/json/libjson/Source/libjson.cpp \
				   ../../Framework/json/MWJsonElement.cpp \
				   ../../Framework/json/MWJsonFormatter.cpp \
				   ../../Framework/json/MWJsonParser.cpp \
				   ../../Framework/json/MWJsonStructure.cpp \
				   ../../Framework/js/MWJsUtils.cpp \
				   ../../Framework/js/auto/js_mwframework_auto.cpp \
				   ../../Framework/js/manual/js_mwframework_manual.cpp \
				   ../../Framework/net/MWNetCenter.cpp \
				   ../../Framework/net/MWNetFilter.cpp \
				   ../../Framework/net/MWNetHandler.cpp \
				   ../../Framework/net/MWNetProtocol.cpp \
				   ../../Framework/net/MWNetRequest.cpp \
				   ../../Framework/net/MWNetResponse.cpp \
				   ../../Framework/net/http/MWHttpDownloader.cpp \
				   ../../Framework/net/http/MWHttpForm.cpp \
				   ../../Framework/net/http/MWHttpGetService.cpp \
				   ../../Framework/net/http/MWHttpPostService.cpp \
				   ../../Framework/platform/android/MWIOUtilsStrategyAndroid.cpp \
				   ../../Framework/platform/android/MWSystemHelperStrategyAndroid.cpp \
				   ../../Framework/platform/MWIOUtils.cpp \
				   ../../Framework/platform/MWSystemHelper.cpp \
				   ../../Framework/scheme/MWGameScene.cpp \
				   ../../Framework/scheme/MWGameView.cpp \
				   ../../Framework/scheme/MWViewController.cpp \
				   ../../Framework/scheme/MWViewSegue.cpp \
				   ../../Framework/texture/gif/gif_lib/dgif_lib.c \
				   ../../Framework/texture/gif/gif_lib/egif_lib.c \
				   ../../Framework/texture/gif/gif_lib/gif_err.c \
				   ../../Framework/texture/gif/gif_lib/gif_font.c \
				   ../../Framework/texture/gif/gif_lib/gif_hash.c \
				   ../../Framework/texture/gif/gif_lib/gifalloc.c \
				   ../../Framework/texture/gif/gif_lib/quantize.c \
				   ../../Framework/texture/gif/MWGifFrame.cpp \
				   ../../Framework/texture/gif/MWGifSprite.cpp \
				   ../../Framework/texture/gif/MWGifFramesCache.cpp \
				   ../../Framework/texture/svg/MWSvgSprite.cpp \
				   ../../Framework/utils/MWAssetManager.cpp \
				   ../../Framework/utils/MWUUIDGenerator-android.cpp \
				   ../../Framework/encryption/base64/libbase64.c \
				   ../../Framework/encryption/md5/md5.cpp \
				   ../../Framework/encryption/MWCrypto.cpp \
				   ../../Framework/encryption/MWCrypto-android.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/extensions \
					$(LOCAL_PATH)/../../Classes/extensions/actions \
					$(LOCAL_PATH)/../../Classes/extensions/audio \
					$(LOCAL_PATH)/../../Classes/extensions/bindings \
					$(LOCAL_PATH)/../../Classes/extensions/bindings/auto \
					$(LOCAL_PATH)/../../Framework \
					$(LOCAL_PATH)/../../Framework/base \
					$(LOCAL_PATH)/../../Framework/compression \
					$(LOCAL_PATH)/../../Framework/compression/minizip \
					$(LOCAL_PATH)/../../Framework/db \
					$(LOCAL_PATH)/../../Framework/db/sqlite \
					$(LOCAL_PATH)/../../Framework/db/sqlite/libsqlite \
					$(LOCAL_PATH)/../../Framework/json \
					$(LOCAL_PATH)/../../Framework/json/libjson \
					$(LOCAL_PATH)/../../Framework/json/libjson/Dependencies \
					$(LOCAL_PATH)/../../Framework/json/libjson/Dependencies/libbase64++ \
					$(LOCAL_PATH)/../../Framework/json/libjson/Dependencies/mempool++ \
					$(LOCAL_PATH)/../../Framework/json/libjson/Source \
					$(LOCAL_PATH)/../../Framework/json/libjson/Source/JSONDefs \
					$(LOCAL_PATH)/../../Framework/js \
					$(LOCAL_PATH)/../../Framework/js/auto \
					$(LOCAL_PATH)/../../Framework/js/manual \
					$(LOCAL_PATH)/../../Framework/net \
					$(LOCAL_PATH)/../../Framework/net/http \
					$(LOCAL_PATH)/../../Framework/platform \
					$(LOCAL_PATH)/../../Framework/platform/android \
					$(LOCAL_PATH)/../../Framework/scheme \
					$(LOCAL_PATH)/../../Framework/texture \
					$(LOCAL_PATH)/../../Framework/texture/gif \
					$(LOCAL_PATH)/../../Framework/texture/gif/gif_lib \
					$(LOCAL_PATH)/../../Framework/texture/svg \
					$(LOCAL_PATH)/../../Framework/texture/svg/nanosvg \
					$(LOCAL_PATH)/../../Framework/utils \
					$(LOCAL_PATH)/../../../cocos2d-x/cocos/network \
					$(LOCAL_PATH)/../../../cocos2d-x/external
					
LOCAL_LDFLAGS += -L$(LOCAL_PATH)/../../../cocos2d-x/external/curl/prebuilt/android/armeabi/libcurl.a

LOCAL_CFLAGS += -DMW_ENABLE_SCRIPT_BINDING \
				-DNDEBUG \
				-DJSON_ISO_STRICT

LOCAL_STATIC_LIBRARIES := cocos2d_js_static

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_DEBUG=2 -DCOCOS2D_JAVASCRIPT

include $(BUILD_SHARED_LIBRARY)


$(call import-module, scripting/js-bindings/proj.android)
