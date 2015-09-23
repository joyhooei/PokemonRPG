#include "js_game_ext_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "game-ext.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && initializing.toBoolean();
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JS::RootedObject proto(cx, typeClass->proto.get());
        JS::RootedObject parent(cx, typeClass->parentProto.get());
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
        
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}
JSClass  *jsb_game_UIProgressBy_class;
JSObject *jsb_game_UIProgressBy_prototype;

bool js_game_ext_UIProgressBy_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        double arg0;
        double arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_UIProgressBy_create : Error processing arguments");
        game::UIProgressBy* ret = game::UIProgressBy::create(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<game::UIProgressBy>(cx, (game::UIProgressBy*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_ext_UIProgressBy_create : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_ActionInterval_prototype;

void js_game_UIProgressBy_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (UIProgressBy)", obj);
}

void js_register_game_ext_UIProgressBy(JSContext *cx, JS::HandleObject global) {
    jsb_game_UIProgressBy_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_game_UIProgressBy_class->name = "UIProgressBy";
    jsb_game_UIProgressBy_class->addProperty = JS_PropertyStub;
    jsb_game_UIProgressBy_class->delProperty = JS_DeletePropertyStub;
    jsb_game_UIProgressBy_class->getProperty = JS_PropertyStub;
    jsb_game_UIProgressBy_class->setProperty = JS_StrictPropertyStub;
    jsb_game_UIProgressBy_class->enumerate = JS_EnumerateStub;
    jsb_game_UIProgressBy_class->resolve = JS_ResolveStub;
    jsb_game_UIProgressBy_class->convert = JS_ConvertStub;
    jsb_game_UIProgressBy_class->finalize = js_game_UIProgressBy_finalize;
    jsb_game_UIProgressBy_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_game_ext_UIProgressBy_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_game_UIProgressBy_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ActionInterval_prototype),
        jsb_game_UIProgressBy_class,
        dummy_constructor<game::UIProgressBy>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "UIProgressBy", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<game::UIProgressBy> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_game_UIProgressBy_class;
        p->proto = jsb_game_UIProgressBy_prototype;
        p->parentProto = jsb_cocos2d_ActionInterval_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_game_UIProgressTo_class;
JSObject *jsb_game_UIProgressTo_prototype;

bool js_game_ext_UIProgressTo_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        double arg0;
        double arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_UIProgressTo_create : Error processing arguments");
        game::UIProgressTo* ret = game::UIProgressTo::create(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<game::UIProgressTo>(cx, (game::UIProgressTo*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_ext_UIProgressTo_create : wrong number of arguments");
    return false;
}


extern JSObject *jsb_game_UIProgressBy_prototype;

void js_game_UIProgressTo_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (UIProgressTo)", obj);
}

void js_register_game_ext_UIProgressTo(JSContext *cx, JS::HandleObject global) {
    jsb_game_UIProgressTo_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_game_UIProgressTo_class->name = "UIProgressTo";
    jsb_game_UIProgressTo_class->addProperty = JS_PropertyStub;
    jsb_game_UIProgressTo_class->delProperty = JS_DeletePropertyStub;
    jsb_game_UIProgressTo_class->getProperty = JS_PropertyStub;
    jsb_game_UIProgressTo_class->setProperty = JS_StrictPropertyStub;
    jsb_game_UIProgressTo_class->enumerate = JS_EnumerateStub;
    jsb_game_UIProgressTo_class->resolve = JS_ResolveStub;
    jsb_game_UIProgressTo_class->convert = JS_ConvertStub;
    jsb_game_UIProgressTo_class->finalize = js_game_UIProgressTo_finalize;
    jsb_game_UIProgressTo_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_game_ext_UIProgressTo_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_game_UIProgressTo_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_game_UIProgressBy_prototype),
        jsb_game_UIProgressTo_class,
        dummy_constructor<game::UIProgressTo>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "UIProgressTo", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<game::UIProgressTo> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_game_UIProgressTo_class;
        p->proto = jsb_game_UIProgressTo_prototype;
        p->parentProto = jsb_game_UIProgressBy_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_game_UITextOneByOne_class;
JSObject *jsb_game_UITextOneByOne_prototype;


extern JSObject *jsb_cocos2d_ActionInterval_prototype;

void js_game_UITextOneByOne_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (UITextOneByOne)", obj);
}

void js_register_game_ext_UITextOneByOne(JSContext *cx, JS::HandleObject global) {
    jsb_game_UITextOneByOne_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_game_UITextOneByOne_class->name = "UITextOneByOne";
    jsb_game_UITextOneByOne_class->addProperty = JS_PropertyStub;
    jsb_game_UITextOneByOne_class->delProperty = JS_DeletePropertyStub;
    jsb_game_UITextOneByOne_class->getProperty = JS_PropertyStub;
    jsb_game_UITextOneByOne_class->setProperty = JS_StrictPropertyStub;
    jsb_game_UITextOneByOne_class->enumerate = JS_EnumerateStub;
    jsb_game_UITextOneByOne_class->resolve = JS_ResolveStub;
    jsb_game_UITextOneByOne_class->convert = JS_ConvertStub;
    jsb_game_UITextOneByOne_class->finalize = js_game_UITextOneByOne_finalize;
    jsb_game_UITextOneByOne_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_game_UITextOneByOne_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ActionInterval_prototype),
        jsb_game_UITextOneByOne_class,
        dummy_constructor<game::UITextOneByOne>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "UITextOneByOne", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<game::UITextOneByOne> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_game_UITextOneByOne_class;
        p->proto = jsb_game_UITextOneByOne_prototype;
        p->parentProto = jsb_cocos2d_ActionInterval_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_game_GameAudioEngine_class;
JSObject *jsb_game_GameAudioEngine_prototype;

bool js_game_ext_GameAudioEngine_play2d(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_play2d : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_GameAudioEngine_play2d : Error processing arguments");
        int ret = cobj->play2d(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_GameAudioEngine_play2d : Error processing arguments");
        int ret = cobj->play2d(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        bool arg1;
        double arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_GameAudioEngine_play2d : Error processing arguments");
        int ret = cobj->play2d(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_play2d : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_ext_GameAudioEngine_pause(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_pause : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_GameAudioEngine_pause : Error processing arguments");
        cobj->pause(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_pause : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_ext_GameAudioEngine_getMaxAudioInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_getMaxAudioInstance : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getMaxAudioInstance();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_getMaxAudioInstance : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_ext_GameAudioEngine_resume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_resume : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_GameAudioEngine_resume : Error processing arguments");
        cobj->resume(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_resume : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_ext_GameAudioEngine_setFinishCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_setFinishCallback : Invalid Native Object");
    if (argc == 2) {
        int arg0;
        std::function<void (int, std::basic_string<char>)> arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        do {
		    if(JS_TypeOfValue(cx, args.get(1)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(1)));
		        auto lambda = [=](int larg0, std::basic_string<char> larg1) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[2];
		            largv[0] = int32_to_jsval(cx, larg0);
		            largv[1] = std_string_to_jsval(cx, larg1);
		            JS::RootedValue rval(cx);
		            bool ok = func->invoke(2, &largv[0], &rval);
		            if (!ok && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg1 = lambda;
		    }
		    else
		    {
		        arg1 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_GameAudioEngine_setFinishCallback : Error processing arguments");
        cobj->setFinishCallback(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_setFinishCallback : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_game_ext_GameAudioEngine_uncache(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_uncache : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_GameAudioEngine_uncache : Error processing arguments");
        cobj->uncache(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_uncache : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_ext_GameAudioEngine_stop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_stop : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_GameAudioEngine_stop : Error processing arguments");
        cobj->stop(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_stop : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_ext_GameAudioEngine_setCurrentTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_setCurrentTime : Invalid Native Object");
    if (argc == 2) {
        int arg0;
        double arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_GameAudioEngine_setCurrentTime : Error processing arguments");
        bool ret = cobj->setCurrentTime(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_setCurrentTime : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_game_ext_GameAudioEngine_getCurrentTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_getCurrentTime : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_GameAudioEngine_getCurrentTime : Error processing arguments");
        double ret = cobj->getCurrentTime(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_getCurrentTime : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_ext_GameAudioEngine_resumeAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_resumeAll : Invalid Native Object");
    if (argc == 0) {
        cobj->resumeAll();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_resumeAll : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_ext_GameAudioEngine_setMaxAudioInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_setMaxAudioInstance : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_GameAudioEngine_setMaxAudioInstance : Error processing arguments");
        bool ret = cobj->setMaxAudioInstance(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_setMaxAudioInstance : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_ext_GameAudioEngine_getVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_getVolume : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_GameAudioEngine_getVolume : Error processing arguments");
        double ret = cobj->getVolume(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_getVolume : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_ext_GameAudioEngine_isLoop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_isLoop : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_GameAudioEngine_isLoop : Error processing arguments");
        bool ret = cobj->isLoop(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_isLoop : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_ext_GameAudioEngine_getDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_getDuration : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_GameAudioEngine_getDuration : Error processing arguments");
        double ret = cobj->getDuration(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_getDuration : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_game_ext_GameAudioEngine_pauseAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_pauseAll : Invalid Native Object");
    if (argc == 0) {
        cobj->pauseAll();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_pauseAll : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_ext_GameAudioEngine_uncacheAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_uncacheAll : Invalid Native Object");
    if (argc == 0) {
        cobj->uncacheAll();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_uncacheAll : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_ext_GameAudioEngine_setLoop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_setLoop : Invalid Native Object");
    if (argc == 2) {
        int arg0;
        bool arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_GameAudioEngine_setLoop : Error processing arguments");
        cobj->setLoop(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_setLoop : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_game_ext_GameAudioEngine_stopAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_stopAll : Invalid Native Object");
    if (argc == 0) {
        cobj->stopAll();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_stopAll : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_game_ext_GameAudioEngine_setVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    game::GameAudioEngine* cobj = (game::GameAudioEngine *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_game_ext_GameAudioEngine_setVolume : Invalid Native Object");
    if (argc == 2) {
        int arg0;
        double arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_game_ext_GameAudioEngine_setVolume : Error processing arguments");
        cobj->setVolume(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_game_ext_GameAudioEngine_setVolume : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_game_ext_GameAudioEngine_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        game::GameAudioEngine* ret = game::GameAudioEngine::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<game::GameAudioEngine>(cx, (game::GameAudioEngine*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_game_ext_GameAudioEngine_getInstance : wrong number of arguments");
    return false;
}



void js_game_GameAudioEngine_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (GameAudioEngine)", obj);
}

void js_register_game_ext_GameAudioEngine(JSContext *cx, JS::HandleObject global) {
    jsb_game_GameAudioEngine_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_game_GameAudioEngine_class->name = "GameAudioEngine";
    jsb_game_GameAudioEngine_class->addProperty = JS_PropertyStub;
    jsb_game_GameAudioEngine_class->delProperty = JS_DeletePropertyStub;
    jsb_game_GameAudioEngine_class->getProperty = JS_PropertyStub;
    jsb_game_GameAudioEngine_class->setProperty = JS_StrictPropertyStub;
    jsb_game_GameAudioEngine_class->enumerate = JS_EnumerateStub;
    jsb_game_GameAudioEngine_class->resolve = JS_ResolveStub;
    jsb_game_GameAudioEngine_class->convert = JS_ConvertStub;
    jsb_game_GameAudioEngine_class->finalize = js_game_GameAudioEngine_finalize;
    jsb_game_GameAudioEngine_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("play2d", js_game_ext_GameAudioEngine_play2d, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pause", js_game_ext_GameAudioEngine_pause, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaxAudioInstance", js_game_ext_GameAudioEngine_getMaxAudioInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resume", js_game_ext_GameAudioEngine_resume, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFinishCallback", js_game_ext_GameAudioEngine_setFinishCallback, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("uncache", js_game_ext_GameAudioEngine_uncache, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stop", js_game_ext_GameAudioEngine_stop, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCurrentTime", js_game_ext_GameAudioEngine_setCurrentTime, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentTime", js_game_ext_GameAudioEngine_getCurrentTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resumeAll", js_game_ext_GameAudioEngine_resumeAll, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxAudioInstance", js_game_ext_GameAudioEngine_setMaxAudioInstance, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVolume", js_game_ext_GameAudioEngine_getVolume, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLoop", js_game_ext_GameAudioEngine_isLoop, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDuration", js_game_ext_GameAudioEngine_getDuration, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pauseAll", js_game_ext_GameAudioEngine_pauseAll, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("uncacheAll", js_game_ext_GameAudioEngine_uncacheAll, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLoop", js_game_ext_GameAudioEngine_setLoop, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopAll", js_game_ext_GameAudioEngine_stopAll, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVolume", js_game_ext_GameAudioEngine_setVolume, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getInstance", js_game_ext_GameAudioEngine_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_game_GameAudioEngine_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_game_GameAudioEngine_class,
        dummy_constructor<game::GameAudioEngine>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "GameAudioEngine", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<game::GameAudioEngine> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_game_GameAudioEngine_class;
        p->proto = jsb_game_GameAudioEngine_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_game_ext(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "ex", &ns);

    js_register_game_ext_UIProgressBy(cx, ns);
    js_register_game_ext_UIProgressTo(cx, ns);
    js_register_game_ext_UITextOneByOne(cx, ns);
    js_register_game_ext_GameAudioEngine(cx, ns);
}

