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

void register_all_game_ext(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "ex", &ns);

    js_register_game_ext_UIProgressBy(cx, ns);
    js_register_game_ext_UIProgressTo(cx, ns);
}

