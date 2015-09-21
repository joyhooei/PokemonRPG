#ifndef __game_ext_h__
#define __game_ext_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_game_UIProgressBy_class;
extern JSObject *jsb_game_UIProgressBy_prototype;

bool js_game_ext_UIProgressBy_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_game_ext_UIProgressBy_finalize(JSContext *cx, JSObject *obj);
void js_register_game_ext_UIProgressBy(JSContext *cx, JS::HandleObject global);
void register_all_game_ext(JSContext* cx, JS::HandleObject obj);
bool js_game_ext_UIProgressBy_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_game_UIProgressTo_class;
extern JSObject *jsb_game_UIProgressTo_prototype;

bool js_game_ext_UIProgressTo_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_game_ext_UIProgressTo_finalize(JSContext *cx, JSObject *obj);
void js_register_game_ext_UIProgressTo(JSContext *cx, JS::HandleObject global);
void register_all_game_ext(JSContext* cx, JS::HandleObject obj);
bool js_game_ext_UIProgressTo_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_game_GameAudioEngine_class;
extern JSObject *jsb_game_GameAudioEngine_prototype;

bool js_game_ext_GameAudioEngine_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_game_ext_GameAudioEngine_finalize(JSContext *cx, JSObject *obj);
void js_register_game_ext_GameAudioEngine(JSContext *cx, JS::HandleObject global);
void register_all_game_ext(JSContext* cx, JS::HandleObject obj);
bool js_game_ext_GameAudioEngine_play2d(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_pause(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_getMaxAudioInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_resume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_setFinishCallback(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_uncache(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_stop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_setCurrentTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_getCurrentTime(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_resumeAll(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_setMaxAudioInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_getVolume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_isLoop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_getDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_pauseAll(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_uncacheAll(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_setLoop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_stopAll(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_setVolume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_game_ext_GameAudioEngine_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
#endif

