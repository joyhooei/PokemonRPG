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
#endif

