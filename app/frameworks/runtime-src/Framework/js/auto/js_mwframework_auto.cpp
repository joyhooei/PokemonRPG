#include "js_mwframework_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "mwframework.h"

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
JSClass  *jsb_mwframework_MWObject_class;
JSObject *jsb_mwframework_MWObject_prototype;

bool js_mwframework_MWObject_toString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWObject* cobj = (mwframework::MWObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWObject_toString : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->toString();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWObject_toString : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}


void js_mwframework_MWObject_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWObject)", obj);
}

void js_register_mwframework_MWObject(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWObject_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWObject_class->name = "Object";
    jsb_mwframework_MWObject_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWObject_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWObject_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWObject_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWObject_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWObject_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWObject_class->convert = JS_ConvertStub;
    jsb_mwframework_MWObject_class->finalize = js_mwframework_MWObject_finalize;
    jsb_mwframework_MWObject_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("toString", js_mwframework_MWObject_toString, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_mwframework_MWObject_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_mwframework_MWObject_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Object", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWObject> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWObject_class;
        p->proto = jsb_mwframework_MWObject_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWBinaryData_class;
JSObject *jsb_mwframework_MWBinaryData_prototype;

bool js_mwframework_MWBinaryData_isValid(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWBinaryData* cobj = (mwframework::MWBinaryData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWBinaryData_isValid : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isValid();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWBinaryData_isValid : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWBinaryData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWBinaryData)", obj);
}

void js_register_mwframework_MWBinaryData(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWBinaryData_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWBinaryData_class->name = "BinaryData";
    jsb_mwframework_MWBinaryData_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWBinaryData_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWBinaryData_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWBinaryData_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWBinaryData_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWBinaryData_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWBinaryData_class->convert = JS_ConvertStub;
    jsb_mwframework_MWBinaryData_class->finalize = js_mwframework_MWBinaryData_finalize;
    jsb_mwframework_MWBinaryData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("isValid", js_mwframework_MWBinaryData_isValid, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_mwframework_MWBinaryData_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWBinaryData_class,
        dummy_constructor<mwframework::MWBinaryData>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "BinaryData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWBinaryData> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWBinaryData_class;
        p->proto = jsb_mwframework_MWBinaryData_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWException_class;
JSObject *jsb_mwframework_MWException_prototype;

bool js_mwframework_MWException_errorCode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWException* cobj = (mwframework::MWException *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWException_errorCode : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->errorCode();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWException_errorCode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWException_what(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWException* cobj = (mwframework::MWException *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWException_what : Invalid Native Object");
    if (argc == 0) {
        const char* ret = cobj->what();
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWException_what : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWException_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0;
        const char* arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWException_create : Error processing arguments");
        mwframework::MWException* ret = mwframework::MWException::create(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWException>(cx, (mwframework::MWException*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWException_create : wrong number of arguments");
    return false;
}

bool js_mwframework_MWException_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    int arg0;
    const char* arg1;
    ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
    std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
    JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWException_constructor : Error processing arguments");
    mwframework::MWException* cobj = new (std::nothrow) mwframework::MWException(arg0, arg1);
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<mwframework::MWException> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "mwframework::MWException");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWException_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWException)", obj);
}

void js_register_mwframework_MWException(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWException_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWException_class->name = "Exception";
    jsb_mwframework_MWException_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWException_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWException_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWException_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWException_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWException_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWException_class->convert = JS_ConvertStub;
    jsb_mwframework_MWException_class->finalize = js_mwframework_MWException_finalize;
    jsb_mwframework_MWException_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("errorCode", js_mwframework_MWException_errorCode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("what", js_mwframework_MWException_what, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_mwframework_MWException_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWException_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWException_class,
        js_mwframework_MWException_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Exception", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWException> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWException_class;
        p->proto = jsb_mwframework_MWException_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWDictionary_class;
JSObject *jsb_mwframework_MWDictionary_prototype;

bool js_mwframework_MWDictionary_count(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWDictionary* cobj = (mwframework::MWDictionary *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWDictionary_count : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->count();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWDictionary_count : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWDictionary_removeObjectForKey(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWDictionary* cobj = (mwframework::MWDictionary *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWDictionary_removeObjectForKey : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWDictionary_removeObjectForKey : Error processing arguments");
        bool ret = cobj->removeObjectForKey(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWDictionary_removeObjectForKey : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWDictionary_clear(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWDictionary* cobj = (mwframework::MWDictionary *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWDictionary_clear : Invalid Native Object");
    if (argc == 0) {
        cobj->clear();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWDictionary_clear : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWDictionary_setObjectForKey(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWDictionary* cobj = (mwframework::MWDictionary *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWDictionary_setObjectForKey : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        cocos2d::Ref* arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWDictionary_setObjectForKey : Error processing arguments");
        cobj->setObjectForKey(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWDictionary_setObjectForKey : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWDictionary_objectForKey(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWDictionary* cobj = (mwframework::MWDictionary *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWDictionary_objectForKey : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWDictionary_objectForKey : Error processing arguments");
        cocos2d::Ref* ret = cobj->objectForKey(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWDictionary_objectForKey : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWDictionary_empty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWDictionary* cobj = (mwframework::MWDictionary *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWDictionary_empty : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->empty();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWDictionary_empty : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWDictionary_hasKey(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWDictionary* cobj = (mwframework::MWDictionary *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWDictionary_hasKey : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWDictionary_hasKey : Error processing arguments");
        bool ret = cobj->hasKey(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWDictionary_hasKey : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWDictionary_clone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWDictionary* cobj = (mwframework::MWDictionary *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWDictionary_clone : Invalid Native Object");
    if (argc == 0) {
        mwframework::MWDictionary* ret = cobj->clone();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWDictionary>(cx, (mwframework::MWDictionary*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWDictionary_clone : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWDictionary_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        mwframework::MWDictionary* ret = mwframework::MWDictionary::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWDictionary>(cx, (mwframework::MWDictionary*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWDictionary_create : wrong number of arguments");
    return false;
}

bool js_mwframework_MWDictionary_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    mwframework::MWDictionary* cobj = new (std::nothrow) mwframework::MWDictionary();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<mwframework::MWDictionary> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "mwframework::MWDictionary");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWDictionary_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWDictionary)", obj);
}

void js_register_mwframework_MWDictionary(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWDictionary_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWDictionary_class->name = "Dictionary";
    jsb_mwframework_MWDictionary_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWDictionary_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWDictionary_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWDictionary_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWDictionary_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWDictionary_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWDictionary_class->convert = JS_ConvertStub;
    jsb_mwframework_MWDictionary_class->finalize = js_mwframework_MWDictionary_finalize;
    jsb_mwframework_MWDictionary_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("count", js_mwframework_MWDictionary_count, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeObjectForKey", js_mwframework_MWDictionary_removeObjectForKey, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clear", js_mwframework_MWDictionary_clear, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setObjectForKey", js_mwframework_MWDictionary_setObjectForKey, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("objectForKey", js_mwframework_MWDictionary_objectForKey, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("empty", js_mwframework_MWDictionary_empty, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("hasKey", js_mwframework_MWDictionary_hasKey, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clone", js_mwframework_MWDictionary_clone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_mwframework_MWDictionary_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWDictionary_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWDictionary_class,
        js_mwframework_MWDictionary_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Dictionary", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWDictionary> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWDictionary_class;
        p->proto = jsb_mwframework_MWDictionary_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWArrayList_class;
JSObject *jsb_mwframework_MWArrayList_prototype;

bool js_mwframework_MWArrayList_count(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWArrayList* cobj = (mwframework::MWArrayList *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWArrayList_count : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->count();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWArrayList_count : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWArrayList_setObjectAtIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWArrayList* cobj = (mwframework::MWArrayList *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWArrayList_setObjectAtIndex : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Ref* arg0;
        unsigned int arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWArrayList_setObjectAtIndex : Error processing arguments");
        cobj->setObjectAtIndex(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWArrayList_setObjectAtIndex : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWArrayList_removeObjectAtIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWArrayList* cobj = (mwframework::MWArrayList *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWArrayList_removeObjectAtIndex : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWArrayList_removeObjectAtIndex : Error processing arguments");
        bool ret = cobj->removeObjectAtIndex(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWArrayList_removeObjectAtIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWArrayList_appendObject(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWArrayList* cobj = (mwframework::MWArrayList *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWArrayList_appendObject : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Ref* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWArrayList_appendObject : Error processing arguments");
        cobj->appendObject(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWArrayList_appendObject : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWArrayList_lastIndexOfObject(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWArrayList* cobj = (mwframework::MWArrayList *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWArrayList_lastIndexOfObject : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Ref* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWArrayList_lastIndexOfObject : Error processing arguments");
        unsigned int ret = cobj->lastIndexOfObject(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWArrayList_lastIndexOfObject : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWArrayList_indexOfObject(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWArrayList* cobj = (mwframework::MWArrayList *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWArrayList_indexOfObject : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Ref* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWArrayList_indexOfObject : Error processing arguments");
        unsigned int ret = cobj->indexOfObject(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWArrayList_indexOfObject : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWArrayList_insertObjectAtIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWArrayList* cobj = (mwframework::MWArrayList *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWArrayList_insertObjectAtIndex : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Ref* arg0;
        unsigned int arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWArrayList_insertObjectAtIndex : Error processing arguments");
        cobj->insertObjectAtIndex(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWArrayList_insertObjectAtIndex : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWArrayList_removeObject(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWArrayList* cobj = (mwframework::MWArrayList *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWArrayList_removeObject : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Ref* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWArrayList_removeObject : Error processing arguments");
        bool ret = cobj->removeObject(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWArrayList_removeObject : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWArrayList_clone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWArrayList* cobj = (mwframework::MWArrayList *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWArrayList_clone : Invalid Native Object");
    if (argc == 0) {
        mwframework::MWArrayList* ret = cobj->clone();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWArrayList>(cx, (mwframework::MWArrayList*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWArrayList_clone : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWArrayList_clear(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWArrayList* cobj = (mwframework::MWArrayList *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWArrayList_clear : Invalid Native Object");
    if (argc == 0) {
        cobj->clear();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWArrayList_clear : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWArrayList_empty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWArrayList* cobj = (mwframework::MWArrayList *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWArrayList_empty : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->empty();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWArrayList_empty : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWArrayList_objectAtIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWArrayList* cobj = (mwframework::MWArrayList *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWArrayList_objectAtIndex : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWArrayList_objectAtIndex : Error processing arguments");
        cocos2d::Ref* ret = cobj->objectAtIndex(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWArrayList_objectAtIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWArrayList_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        mwframework::MWArrayList* ret = mwframework::MWArrayList::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWArrayList>(cx, (mwframework::MWArrayList*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWArrayList_create : wrong number of arguments");
    return false;
}

bool js_mwframework_MWArrayList_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    mwframework::MWArrayList* cobj = new (std::nothrow) mwframework::MWArrayList();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<mwframework::MWArrayList> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "mwframework::MWArrayList");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWArrayList_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWArrayList)", obj);
}

void js_register_mwframework_MWArrayList(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWArrayList_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWArrayList_class->name = "ArrayList";
    jsb_mwframework_MWArrayList_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWArrayList_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWArrayList_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWArrayList_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWArrayList_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWArrayList_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWArrayList_class->convert = JS_ConvertStub;
    jsb_mwframework_MWArrayList_class->finalize = js_mwframework_MWArrayList_finalize;
    jsb_mwframework_MWArrayList_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("count", js_mwframework_MWArrayList_count, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setObjectAtIndex", js_mwframework_MWArrayList_setObjectAtIndex, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeObjectAtIndex", js_mwframework_MWArrayList_removeObjectAtIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("appendObject", js_mwframework_MWArrayList_appendObject, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("lastIndexOfObject", js_mwframework_MWArrayList_lastIndexOfObject, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("indexOfObject", js_mwframework_MWArrayList_indexOfObject, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("insertObjectAtIndex", js_mwframework_MWArrayList_insertObjectAtIndex, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeObject", js_mwframework_MWArrayList_removeObject, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clone", js_mwframework_MWArrayList_clone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clear", js_mwframework_MWArrayList_clear, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("empty", js_mwframework_MWArrayList_empty, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("objectAtIndex", js_mwframework_MWArrayList_objectAtIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_mwframework_MWArrayList_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWArrayList_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWArrayList_class,
        js_mwframework_MWArrayList_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ArrayList", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWArrayList> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWArrayList_class;
        p->proto = jsb_mwframework_MWArrayList_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWQueue_class;
JSObject *jsb_mwframework_MWQueue_prototype;

bool js_mwframework_MWQueue_count(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWQueue* cobj = (mwframework::MWQueue *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWQueue_count : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->count();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWQueue_count : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWQueue_dequeue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWQueue* cobj = (mwframework::MWQueue *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWQueue_dequeue : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->dequeue();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWQueue_dequeue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWQueue_clear(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWQueue* cobj = (mwframework::MWQueue *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWQueue_clear : Invalid Native Object");
    if (argc == 0) {
        cobj->clear();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWQueue_clear : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWQueue_enqueue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWQueue* cobj = (mwframework::MWQueue *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWQueue_enqueue : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Ref* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWQueue_enqueue : Error processing arguments");
        cobj->enqueue(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWQueue_enqueue : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWQueue_front(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWQueue* cobj = (mwframework::MWQueue *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWQueue_front : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Ref* ret = cobj->front();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWQueue_front : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWQueue_clone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWQueue* cobj = (mwframework::MWQueue *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWQueue_clone : Invalid Native Object");
    if (argc == 0) {
        mwframework::MWQueue* ret = cobj->clone();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWQueue>(cx, (mwframework::MWQueue*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWQueue_clone : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWQueue_empty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWQueue* cobj = (mwframework::MWQueue *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWQueue_empty : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->empty();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWQueue_empty : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWQueue_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        mwframework::MWQueue* ret = mwframework::MWQueue::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWQueue>(cx, (mwframework::MWQueue*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWQueue_create : wrong number of arguments");
    return false;
}

bool js_mwframework_MWQueue_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    mwframework::MWQueue* cobj = new (std::nothrow) mwframework::MWQueue();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<mwframework::MWQueue> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "mwframework::MWQueue");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWQueue_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWQueue)", obj);
}

void js_register_mwframework_MWQueue(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWQueue_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWQueue_class->name = "Queue";
    jsb_mwframework_MWQueue_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWQueue_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWQueue_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWQueue_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWQueue_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWQueue_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWQueue_class->convert = JS_ConvertStub;
    jsb_mwframework_MWQueue_class->finalize = js_mwframework_MWQueue_finalize;
    jsb_mwframework_MWQueue_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("count", js_mwframework_MWQueue_count, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("dequeue", js_mwframework_MWQueue_dequeue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clear", js_mwframework_MWQueue_clear, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("enqueue", js_mwframework_MWQueue_enqueue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("front", js_mwframework_MWQueue_front, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clone", js_mwframework_MWQueue_clone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("empty", js_mwframework_MWQueue_empty, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_mwframework_MWQueue_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWQueue_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWQueue_class,
        js_mwframework_MWQueue_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Queue", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWQueue> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWQueue_class;
        p->proto = jsb_mwframework_MWQueue_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWStack_class;
JSObject *jsb_mwframework_MWStack_prototype;

bool js_mwframework_MWStack_count(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWStack* cobj = (mwframework::MWStack *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWStack_count : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->count();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWStack_count : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWStack_top(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWStack* cobj = (mwframework::MWStack *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWStack_top : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Ref* ret = cobj->top();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWStack_top : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWStack_pop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWStack* cobj = (mwframework::MWStack *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWStack_pop : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->pop();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWStack_pop : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWStack_push(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWStack* cobj = (mwframework::MWStack *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWStack_push : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Ref* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWStack_push : Error processing arguments");
        cobj->push(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWStack_push : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWStack_clone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWStack* cobj = (mwframework::MWStack *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWStack_clone : Invalid Native Object");
    if (argc == 0) {
        mwframework::MWStack* ret = cobj->clone();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWStack>(cx, (mwframework::MWStack*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWStack_clone : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWStack_clear(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWStack* cobj = (mwframework::MWStack *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWStack_clear : Invalid Native Object");
    if (argc == 0) {
        cobj->clear();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWStack_clear : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWStack_empty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWStack* cobj = (mwframework::MWStack *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWStack_empty : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->empty();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWStack_empty : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWStack_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        mwframework::MWStack* ret = mwframework::MWStack::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWStack>(cx, (mwframework::MWStack*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWStack_create : wrong number of arguments");
    return false;
}

bool js_mwframework_MWStack_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    mwframework::MWStack* cobj = new (std::nothrow) mwframework::MWStack();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<mwframework::MWStack> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "mwframework::MWStack");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWStack_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWStack)", obj);
}

void js_register_mwframework_MWStack(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWStack_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWStack_class->name = "Stack";
    jsb_mwframework_MWStack_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWStack_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWStack_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWStack_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWStack_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWStack_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWStack_class->convert = JS_ConvertStub;
    jsb_mwframework_MWStack_class->finalize = js_mwframework_MWStack_finalize;
    jsb_mwframework_MWStack_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("count", js_mwframework_MWStack_count, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("top", js_mwframework_MWStack_top, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pop", js_mwframework_MWStack_pop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("push", js_mwframework_MWStack_push, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clone", js_mwframework_MWStack_clone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clear", js_mwframework_MWStack_clear, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("empty", js_mwframework_MWStack_empty, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_mwframework_MWStack_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWStack_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWStack_class,
        js_mwframework_MWStack_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Stack", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWStack> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWStack_class;
        p->proto = jsb_mwframework_MWStack_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWSystemHelper_class;
JSObject *jsb_mwframework_MWSystemHelper_prototype;

bool js_mwframework_MWSystemHelper_checkNetStatus(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWSystemHelper* cobj = (mwframework::MWSystemHelper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWSystemHelper_checkNetStatus : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->checkNetStatus();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWSystemHelper_checkNetStatus : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWSystemHelper_getCurrentUsedMemory(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWSystemHelper* cobj = (mwframework::MWSystemHelper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWSystemHelper_getCurrentUsedMemory : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getCurrentUsedMemory();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWSystemHelper_getCurrentUsedMemory : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWSystemHelper_millisecondsNow(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWSystemHelper* cobj = (mwframework::MWSystemHelper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWSystemHelper_millisecondsNow : Invalid Native Object");
    if (argc == 0) {
        unsigned long ret = cobj->millisecondsNow();
        jsval jsret = JSVAL_NULL;
        jsret = ulong_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWSystemHelper_millisecondsNow : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWSystemHelper_copyToPasteBoard(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWSystemHelper* cobj = (mwframework::MWSystemHelper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWSystemHelper_copyToPasteBoard : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWSystemHelper_copyToPasteBoard : Error processing arguments");
        cobj->copyToPasteBoard(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWSystemHelper_copyToPasteBoard : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWSystemHelper_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        mwframework::MWSystemHelper* ret = mwframework::MWSystemHelper::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWSystemHelper>(cx, (mwframework::MWSystemHelper*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWSystemHelper_getInstance : wrong number of arguments");
    return false;
}



void js_mwframework_MWSystemHelper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWSystemHelper)", obj);
}

void js_register_mwframework_MWSystemHelper(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWSystemHelper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWSystemHelper_class->name = "SystemHelper";
    jsb_mwframework_MWSystemHelper_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWSystemHelper_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWSystemHelper_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWSystemHelper_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWSystemHelper_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWSystemHelper_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWSystemHelper_class->convert = JS_ConvertStub;
    jsb_mwframework_MWSystemHelper_class->finalize = js_mwframework_MWSystemHelper_finalize;
    jsb_mwframework_MWSystemHelper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("checkNetStatus", js_mwframework_MWSystemHelper_checkNetStatus, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentUsedMemory", js_mwframework_MWSystemHelper_getCurrentUsedMemory, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("millisecondsNow", js_mwframework_MWSystemHelper_millisecondsNow, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("copyToPasteBoard", js_mwframework_MWSystemHelper_copyToPasteBoard, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getInstance", js_mwframework_MWSystemHelper_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWSystemHelper_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_mwframework_MWSystemHelper_class,
        dummy_constructor<mwframework::MWSystemHelper>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "SystemHelper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWSystemHelper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWSystemHelper_class;
        p->proto = jsb_mwframework_MWSystemHelper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWIOUtils_class;
JSObject *jsb_mwframework_MWIOUtils_prototype;

bool js_mwframework_MWIOUtils_fileExists(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWIOUtils* cobj = (mwframework::MWIOUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWIOUtils_fileExists : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWIOUtils_fileExists : Error processing arguments");
        bool ret = cobj->fileExists(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWIOUtils_fileExists : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWIOUtils_copyFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWIOUtils* cobj = (mwframework::MWIOUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWIOUtils_copyFile : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWIOUtils_copyFile : Error processing arguments");
        bool ret = cobj->copyFile(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWIOUtils_copyFile : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWIOUtils_writeDataToFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWIOUtils* cobj = (mwframework::MWIOUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWIOUtils_writeDataToFile : Invalid Native Object");
    if (argc == 3) {
        const void* arg0;
        unsigned long arg1;
        std::string arg2;
        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        ok &= jsval_to_ulong(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWIOUtils_writeDataToFile : Error processing arguments");
        bool ret = cobj->writeDataToFile(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 4) {
        const void* arg0;
        unsigned long arg1;
        std::string arg2;
        bool arg3;
        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        ok &= jsval_to_ulong(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        arg3 = JS::ToBoolean(args.get(3));
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWIOUtils_writeDataToFile : Error processing arguments");
        bool ret = cobj->writeDataToFile(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWIOUtils_writeDataToFile : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_mwframework_MWIOUtils_getDataFromFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWIOUtils* cobj = (mwframework::MWIOUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWIOUtils_getDataFromFile : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWIOUtils_getDataFromFile : Error processing arguments");
        mwframework::MWBinaryData* ret = cobj->getDataFromFile(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWBinaryData>(cx, (mwframework::MWBinaryData*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWIOUtils_getDataFromFile : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWIOUtils_splicePath(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWIOUtils* cobj = (mwframework::MWIOUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWIOUtils_splicePath : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWIOUtils_splicePath : Error processing arguments");
        std::string ret = cobj->splicePath(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWIOUtils_splicePath : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWIOUtils_createFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWIOUtils* cobj = (mwframework::MWIOUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWIOUtils_createFile : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWIOUtils_createFile : Error processing arguments");
        bool ret = cobj->createFile(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWIOUtils_createFile : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWIOUtils_resourcePath(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWIOUtils* cobj = (mwframework::MWIOUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWIOUtils_resourcePath : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWIOUtils_resourcePath : Error processing arguments");
        std::string ret = cobj->resourcePath(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWIOUtils_resourcePath : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWIOUtils_removeFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWIOUtils* cobj = (mwframework::MWIOUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWIOUtils_removeFile : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWIOUtils_removeFile : Error processing arguments");
        bool ret = cobj->removeFile(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWIOUtils_removeFile : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWIOUtils_moveFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWIOUtils* cobj = (mwframework::MWIOUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWIOUtils_moveFile : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWIOUtils_moveFile : Error processing arguments");
        bool ret = cobj->moveFile(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWIOUtils_moveFile : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWIOUtils_createDirectory(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWIOUtils* cobj = (mwframework::MWIOUtils *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWIOUtils_createDirectory : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWIOUtils_createDirectory : Error processing arguments");
        bool ret = cobj->createDirectory(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWIOUtils_createDirectory : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWIOUtils_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        mwframework::MWIOUtils* ret = mwframework::MWIOUtils::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWIOUtils>(cx, (mwframework::MWIOUtils*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWIOUtils_getInstance : wrong number of arguments");
    return false;
}



void js_mwframework_MWIOUtils_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWIOUtils)", obj);
}

void js_register_mwframework_MWIOUtils(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWIOUtils_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWIOUtils_class->name = "IOUtils";
    jsb_mwframework_MWIOUtils_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWIOUtils_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWIOUtils_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWIOUtils_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWIOUtils_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWIOUtils_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWIOUtils_class->convert = JS_ConvertStub;
    jsb_mwframework_MWIOUtils_class->finalize = js_mwframework_MWIOUtils_finalize;
    jsb_mwframework_MWIOUtils_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("fileExists", js_mwframework_MWIOUtils_fileExists, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("copyFile", js_mwframework_MWIOUtils_copyFile, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("writeDataToFile", js_mwframework_MWIOUtils_writeDataToFile, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDataFromFile", js_mwframework_MWIOUtils_getDataFromFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("splicePath", js_mwframework_MWIOUtils_splicePath, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createFile", js_mwframework_MWIOUtils_createFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resourcePath", js_mwframework_MWIOUtils_resourcePath, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeFile", js_mwframework_MWIOUtils_removeFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("moveFile", js_mwframework_MWIOUtils_moveFile, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createDirectory", js_mwframework_MWIOUtils_createDirectory, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getInstance", js_mwframework_MWIOUtils_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWIOUtils_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_mwframework_MWIOUtils_class,
        dummy_constructor<mwframework::MWIOUtils>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "IOUtils", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWIOUtils> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWIOUtils_class;
        p->proto = jsb_mwframework_MWIOUtils_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWGameScene_class;
JSObject *jsb_mwframework_MWGameScene_prototype;

bool js_mwframework_MWGameScene_getViewControllers(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGameScene* cobj = (mwframework::MWGameScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGameScene_getViewControllers : Invalid Native Object");
    if (argc == 0) {
        mwframework::MWDictionary* ret = cobj->getViewControllers();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWDictionary>(cx, (mwframework::MWDictionary*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGameScene_getViewControllers : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWGameScene_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGameScene* cobj = (mwframework::MWGameScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGameScene_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 1) {
        mwframework::MWDictionary* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWDictionary*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGameScene_init : Error processing arguments");
        bool ret = cobj->init(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGameScene_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWGameScene_unloadViewController(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGameScene* cobj = (mwframework::MWGameScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGameScene_unloadViewController : Invalid Native Object");
    if (argc == 1) {
        mwframework::MWViewController* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWViewController*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGameScene_unloadViewController : Error processing arguments");
        cobj->unloadViewController(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGameScene_unloadViewController : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWGameScene_loadViewController(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGameScene* cobj = (mwframework::MWGameScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGameScene_loadViewController : Invalid Native Object");
    if (argc == 2) {
        mwframework::MWViewController* arg0;
        std::string arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWViewController*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGameScene_loadViewController : Error processing arguments");
        cobj->loadViewController(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGameScene_loadViewController : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWGameScene_getViewControllerByIdentifier(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGameScene* cobj = (mwframework::MWGameScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGameScene_getViewControllerByIdentifier : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGameScene_getViewControllerByIdentifier : Error processing arguments");
        mwframework::MWViewController* ret = cobj->getViewControllerByIdentifier(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWViewController>(cx, (mwframework::MWViewController*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGameScene_getViewControllerByIdentifier : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWGameScene_getParameter(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGameScene* cobj = (mwframework::MWGameScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGameScene_getParameter : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGameScene_getParameter : Error processing arguments");
        std::string ret = cobj->getParameter(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGameScene_getParameter : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWGameScene_unloadAllViewControllers(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGameScene* cobj = (mwframework::MWGameScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGameScene_unloadAllViewControllers : Invalid Native Object");
    if (argc == 0) {
        cobj->unloadAllViewControllers();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGameScene_unloadAllViewControllers : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWGameScene_addParameter(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGameScene* cobj = (mwframework::MWGameScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGameScene_addParameter : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGameScene_addParameter : Error processing arguments");
        cobj->addParameter(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGameScene_addParameter : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWGameScene_getMemoryWarningLine(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGameScene* cobj = (mwframework::MWGameScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGameScene_getMemoryWarningLine : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMemoryWarningLine();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGameScene_getMemoryWarningLine : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWGameScene_setMemoryWarningLine(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGameScene* cobj = (mwframework::MWGameScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGameScene_setMemoryWarningLine : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGameScene_setMemoryWarningLine : Error processing arguments");
        cobj->setMemoryWarningLine(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGameScene_setMemoryWarningLine : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWGameScene_unloadViewControllerByIdentifier(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGameScene* cobj = (mwframework::MWGameScene *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGameScene_unloadViewControllerByIdentifier : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGameScene_unloadViewControllerByIdentifier : Error processing arguments");
        cobj->unloadViewControllerByIdentifier(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGameScene_unloadViewControllerByIdentifier : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWGameScene_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        mwframework::MWGameScene* ret = mwframework::MWGameScene::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWGameScene>(cx, (mwframework::MWGameScene*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWGameScene_create : wrong number of arguments");
    return false;
}

bool js_mwframework_MWGameScene_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    mwframework::MWGameScene* cobj = new (std::nothrow) mwframework::MWGameScene();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<mwframework::MWGameScene> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "mwframework::MWGameScene");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Scene_prototype;

void js_mwframework_MWGameScene_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWGameScene)", obj);
}

static bool js_mwframework_MWGameScene_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    mwframework::MWGameScene *nobj = new (std::nothrow) mwframework::MWGameScene();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "mwframework::MWGameScene");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_mwframework_MWGameScene(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWGameScene_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWGameScene_class->name = "GameScene";
    jsb_mwframework_MWGameScene_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWGameScene_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWGameScene_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWGameScene_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWGameScene_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWGameScene_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWGameScene_class->convert = JS_ConvertStub;
    jsb_mwframework_MWGameScene_class->finalize = js_mwframework_MWGameScene_finalize;
    jsb_mwframework_MWGameScene_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getViewControllers", js_mwframework_MWGameScene_getViewControllers, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_mwframework_MWGameScene_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("unloadViewController", js_mwframework_MWGameScene_unloadViewController, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadViewController", js_mwframework_MWGameScene_loadViewController, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getViewControllerByIdentifier", js_mwframework_MWGameScene_getViewControllerByIdentifier, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getParameter", js_mwframework_MWGameScene_getParameter, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("unloadAllViewControllers", js_mwframework_MWGameScene_unloadAllViewControllers, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addParameter", js_mwframework_MWGameScene_addParameter, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMemoryWarningLine", js_mwframework_MWGameScene_getMemoryWarningLine, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMemoryWarningLine", js_mwframework_MWGameScene_setMemoryWarningLine, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("unloadViewControllerByIdentifier", js_mwframework_MWGameScene_unloadViewControllerByIdentifier, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_mwframework_MWGameScene_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_mwframework_MWGameScene_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWGameScene_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Scene_prototype),
        jsb_mwframework_MWGameScene_class,
        js_mwframework_MWGameScene_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "GameScene", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWGameScene> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWGameScene_class;
        p->proto = jsb_mwframework_MWGameScene_prototype;
        p->parentProto = jsb_cocos2d_Scene_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWViewController_class;
JSObject *jsb_mwframework_MWViewController_prototype;

bool js_mwframework_MWViewController_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWViewController* cobj = (mwframework::MWViewController *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWViewController_init : Invalid Native Object");
    if (argc == 1) {
        mwframework::MWViewSegue* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWViewSegue*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWViewController_init : Error processing arguments");
        bool ret = cobj->init(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWViewController_init : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWViewController_segue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWViewController* cobj = (mwframework::MWViewController *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWViewController_segue : Invalid Native Object");
    if (argc == 0) {
        mwframework::MWViewSegue* ret = cobj->segue();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWViewSegue>(cx, (mwframework::MWViewSegue*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWViewController_segue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWViewController_scene(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWViewController* cobj = (mwframework::MWViewController *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWViewController_scene : Invalid Native Object");
    if (argc == 0) {
        mwframework::MWGameScene* ret = cobj->scene();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWGameScene>(cx, (mwframework::MWGameScene*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWViewController_scene : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWViewController_getIdentifier(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWViewController* cobj = (mwframework::MWViewController *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWViewController_getIdentifier : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getIdentifier();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWViewController_getIdentifier : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWViewController_view(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWViewController* cobj = (mwframework::MWViewController *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWViewController_view : Invalid Native Object");
    if (argc == 0) {
        mwframework::MWGameView* ret = cobj->view();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWGameView>(cx, (mwframework::MWGameView*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWViewController_view : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWViewController_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 0) {
        mwframework::MWViewController* ret = mwframework::MWViewController::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWViewController>(cx, (mwframework::MWViewController*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 1) {
        mwframework::MWViewSegue* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWViewSegue*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWViewController_create : Error processing arguments");
        mwframework::MWViewController* ret = mwframework::MWViewController::create(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWViewController>(cx, (mwframework::MWViewController*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWViewController_create : wrong number of arguments");
    return false;
}

bool js_mwframework_MWViewController_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    mwframework::MWViewController* cobj = new (std::nothrow) mwframework::MWViewController();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<mwframework::MWViewController> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "mwframework::MWViewController");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWViewController_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWViewController)", obj);
}

static bool js_mwframework_MWViewController_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    mwframework::MWViewController *nobj = new (std::nothrow) mwframework::MWViewController();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "mwframework::MWViewController");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_mwframework_MWViewController(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWViewController_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWViewController_class->name = "ViewController";
    jsb_mwframework_MWViewController_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWViewController_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWViewController_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWViewController_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWViewController_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWViewController_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWViewController_class->convert = JS_ConvertStub;
    jsb_mwframework_MWViewController_class->finalize = js_mwframework_MWViewController_finalize;
    jsb_mwframework_MWViewController_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("init", js_mwframework_MWViewController_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("segue", js_mwframework_MWViewController_segue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("scene", js_mwframework_MWViewController_scene, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIdentifier", js_mwframework_MWViewController_getIdentifier, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("view", js_mwframework_MWViewController_view, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_mwframework_MWViewController_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_mwframework_MWViewController_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWViewController_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWViewController_class,
        js_mwframework_MWViewController_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ViewController", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWViewController> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWViewController_class;
        p->proto = jsb_mwframework_MWViewController_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWGameView_class;
JSObject *jsb_mwframework_MWGameView_prototype;

bool js_mwframework_MWGameView_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        mwframework::MWGameView* ret = mwframework::MWGameView::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWGameView>(cx, (mwframework::MWGameView*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWGameView_create : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Layer_prototype;

void js_mwframework_MWGameView_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWGameView)", obj);
}

void js_register_mwframework_MWGameView(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWGameView_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWGameView_class->name = "GameView";
    jsb_mwframework_MWGameView_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWGameView_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWGameView_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWGameView_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWGameView_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWGameView_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWGameView_class->convert = JS_ConvertStub;
    jsb_mwframework_MWGameView_class->finalize = js_mwframework_MWGameView_finalize;
    jsb_mwframework_MWGameView_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_mwframework_MWGameView_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWGameView_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Layer_prototype),
        jsb_mwframework_MWGameView_class,
        dummy_constructor<mwframework::MWGameView>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "GameView", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWGameView> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWGameView_class;
        p->proto = jsb_mwframework_MWGameView_prototype;
        p->parentProto = jsb_cocos2d_Layer_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWViewSegue_class;
JSObject *jsb_mwframework_MWViewSegue_prototype;

bool js_mwframework_MWViewSegue_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWViewSegue* cobj = (mwframework::MWViewSegue *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWViewSegue_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWViewSegue_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWViewSegue_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        mwframework::MWViewSegue* ret = mwframework::MWViewSegue::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWViewSegue>(cx, (mwframework::MWViewSegue*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWViewSegue_create : wrong number of arguments");
    return false;
}

bool js_mwframework_MWViewSegue_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    mwframework::MWViewSegue* cobj = new (std::nothrow) mwframework::MWViewSegue();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<mwframework::MWViewSegue> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "mwframework::MWViewSegue");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWViewSegue_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWViewSegue)", obj);
}

static bool js_mwframework_MWViewSegue_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    mwframework::MWViewSegue *nobj = new (std::nothrow) mwframework::MWViewSegue();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "mwframework::MWViewSegue");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_mwframework_MWViewSegue(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWViewSegue_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWViewSegue_class->name = "ViewSegue";
    jsb_mwframework_MWViewSegue_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWViewSegue_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWViewSegue_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWViewSegue_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWViewSegue_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWViewSegue_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWViewSegue_class->convert = JS_ConvertStub;
    jsb_mwframework_MWViewSegue_class->finalize = js_mwframework_MWViewSegue_finalize;
    jsb_mwframework_MWViewSegue_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("init", js_mwframework_MWViewSegue_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_mwframework_MWViewSegue_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_mwframework_MWViewSegue_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWViewSegue_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWViewSegue_class,
        js_mwframework_MWViewSegue_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ViewSegue", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWViewSegue> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWViewSegue_class;
        p->proto = jsb_mwframework_MWViewSegue_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWSqliteDb_class;
JSObject *jsb_mwframework_MWSqliteDb_prototype;

bool js_mwframework_MWSqliteDb_executeNonQuery(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWSqliteDb* cobj = (mwframework::MWSqliteDb *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWSqliteDb_executeNonQuery : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWSqliteDb_executeNonQuery : Error processing arguments");
        bool ret = cobj->executeNonQuery(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWSqliteDb_executeNonQuery : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWSqliteDb_endTransaction(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWSqliteDb* cobj = (mwframework::MWSqliteDb *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWSqliteDb_endTransaction : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWSqliteDb_endTransaction : Error processing arguments");
        bool ret = cobj->endTransaction(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWSqliteDb_endTransaction : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWSqliteDb_beginTransaction(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWSqliteDb* cobj = (mwframework::MWSqliteDb *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWSqliteDb_beginTransaction : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->beginTransaction();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWSqliteDb_beginTransaction : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWSqliteDb_openDb(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWSqliteDb_openDb : Error processing arguments");
        mwframework::MWSqliteDb* ret = mwframework::MWSqliteDb::openDb(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWSqliteDb>(cx, (mwframework::MWSqliteDb*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWSqliteDb_openDb : wrong number of arguments");
    return false;
}

bool js_mwframework_MWSqliteDb_clearConnectionCache(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        mwframework::MWSqliteDb::clearConnectionCache();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWSqliteDb_clearConnectionCache : wrong number of arguments");
    return false;
}


extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWSqliteDb_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWSqliteDb)", obj);
}

void js_register_mwframework_MWSqliteDb(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWSqliteDb_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWSqliteDb_class->name = "SqliteDb";
    jsb_mwframework_MWSqliteDb_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWSqliteDb_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWSqliteDb_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWSqliteDb_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWSqliteDb_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWSqliteDb_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWSqliteDb_class->convert = JS_ConvertStub;
    jsb_mwframework_MWSqliteDb_class->finalize = js_mwframework_MWSqliteDb_finalize;
    jsb_mwframework_MWSqliteDb_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("executeNonQuery", js_mwframework_MWSqliteDb_executeNonQuery, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("endTransaction", js_mwframework_MWSqliteDb_endTransaction, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("beginTransaction", js_mwframework_MWSqliteDb_beginTransaction, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("openDb", js_mwframework_MWSqliteDb_openDb, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clearConnectionCache", js_mwframework_MWSqliteDb_clearConnectionCache, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWSqliteDb_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWSqliteDb_class,
        dummy_constructor<mwframework::MWSqliteDb>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "SqliteDb", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWSqliteDb> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWSqliteDb_class;
        p->proto = jsb_mwframework_MWSqliteDb_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWZipData_class;
JSObject *jsb_mwframework_MWZipData_prototype;

bool js_mwframework_MWZipData_getCompressedFileData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWZipData* cobj = (mwframework::MWZipData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWZipData_getCompressedFileData : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWZipData_getCompressedFileData : Error processing arguments");
        mwframework::MWBinaryData* ret = cobj->getCompressedFileData(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWBinaryData>(cx, (mwframework::MWBinaryData*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWZipData_getCompressedFileData : Error processing arguments");
        mwframework::MWBinaryData* ret = cobj->getCompressedFileData(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWBinaryData>(cx, (mwframework::MWBinaryData*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWZipData_getCompressedFileData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWZipData_zipNewFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWZipData* cobj = (mwframework::MWZipData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWZipData_zipNewFile : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        mwframework::MWBinaryData* arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (mwframework::MWBinaryData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWZipData_zipNewFile : Error processing arguments");
        bool ret = cobj->zipNewFile(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        mwframework::MWBinaryData* arg1;
        std::string arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (mwframework::MWBinaryData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWZipData_zipNewFile : Error processing arguments");
        bool ret = cobj->zipNewFile(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 4) {
        std::string arg0;
        mwframework::MWBinaryData* arg1;
        std::string arg2;
        int arg3;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (mwframework::MWBinaryData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWZipData_zipNewFile : Error processing arguments");
        bool ret = cobj->zipNewFile(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWZipData_zipNewFile : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWZipData_beginUnzip(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWZipData* cobj = (mwframework::MWZipData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWZipData_beginUnzip : Invalid Native Object");
    if (argc == 0) {
        cobj->beginUnzip();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWZipData_beginUnzip : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWZipData_endUnzip(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWZipData* cobj = (mwframework::MWZipData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWZipData_endUnzip : Invalid Native Object");
    if (argc == 0) {
        cobj->endUnzip();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWZipData_endUnzip : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWZipData_beginZip(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWZipData* cobj = (mwframework::MWZipData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWZipData_beginZip : Invalid Native Object");
    if (argc == 0) {
        cobj->beginZip();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWZipData_beginZip : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWZipData_endZip(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWZipData* cobj = (mwframework::MWZipData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWZipData_endZip : Invalid Native Object");
    if (argc == 0) {
        cobj->endZip();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWZipData_endZip : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWZipData_createWithExistingFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWZipData_createWithExistingFile : Error processing arguments");
        mwframework::MWZipData* ret = mwframework::MWZipData::createWithExistingFile(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWZipData>(cx, (mwframework::MWZipData*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWZipData_createWithExistingFile : wrong number of arguments");
    return false;
}

bool js_mwframework_MWZipData_createWithNewFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWZipData_createWithNewFile : Error processing arguments");
        mwframework::MWZipData* ret = mwframework::MWZipData::createWithNewFile(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWZipData>(cx, (mwframework::MWZipData*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWZipData_createWithNewFile : wrong number of arguments");
    return false;
}


extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWZipData_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWZipData)", obj);
}

void js_register_mwframework_MWZipData(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWZipData_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWZipData_class->name = "ZipData";
    jsb_mwframework_MWZipData_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWZipData_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWZipData_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWZipData_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWZipData_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWZipData_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWZipData_class->convert = JS_ConvertStub;
    jsb_mwframework_MWZipData_class->finalize = js_mwframework_MWZipData_finalize;
    jsb_mwframework_MWZipData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getCompressedFileData", js_mwframework_MWZipData_getCompressedFileData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("zipNewFile", js_mwframework_MWZipData_zipNewFile, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("beginUnzip", js_mwframework_MWZipData_beginUnzip, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("endUnzip", js_mwframework_MWZipData_endUnzip, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("beginZip", js_mwframework_MWZipData_beginZip, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("endZip", js_mwframework_MWZipData_endZip, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("createWithExistingFile", js_mwframework_MWZipData_createWithExistingFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithNewFile", js_mwframework_MWZipData_createWithNewFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWZipData_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWZipData_class,
        dummy_constructor<mwframework::MWZipData>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ZipData", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWZipData> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWZipData_class;
        p->proto = jsb_mwframework_MWZipData_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWGifFrame_class;
JSObject *jsb_mwframework_MWGifFrame_prototype;

bool js_mwframework_MWGifFrame_setSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGifFrame* cobj = (mwframework::MWGifFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGifFrame_setSpriteFrame : Invalid Native Object");
    if (argc == 1) {
        cocos2d::SpriteFrame* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::SpriteFrame*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGifFrame_setSpriteFrame : Error processing arguments");
        cobj->setSpriteFrame(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGifFrame_setSpriteFrame : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWGifFrame_setDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGifFrame* cobj = (mwframework::MWGifFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGifFrame_setDuration : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGifFrame_setDuration : Error processing arguments");
        cobj->setDuration(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGifFrame_setDuration : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWGifFrame_getSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGifFrame* cobj = (mwframework::MWGifFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGifFrame_getSpriteFrame : Invalid Native Object");
    if (argc == 0) {
        cocos2d::SpriteFrame* ret = cobj->getSpriteFrame();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::SpriteFrame>(cx, (cocos2d::SpriteFrame*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGifFrame_getSpriteFrame : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWGifFrame_getDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGifFrame* cobj = (mwframework::MWGifFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGifFrame_getDuration : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getDuration();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGifFrame_getDuration : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWGifFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        cocos2d::SpriteFrame* arg0;
        unsigned int arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::SpriteFrame*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGifFrame_create : Error processing arguments");
        mwframework::MWGifFrame* ret = mwframework::MWGifFrame::create(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWGifFrame>(cx, (mwframework::MWGifFrame*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWGifFrame_create : wrong number of arguments");
    return false;
}


extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWGifFrame_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWGifFrame)", obj);
}

void js_register_mwframework_MWGifFrame(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWGifFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWGifFrame_class->name = "GifFrame";
    jsb_mwframework_MWGifFrame_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWGifFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWGifFrame_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWGifFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWGifFrame_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWGifFrame_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWGifFrame_class->convert = JS_ConvertStub;
    jsb_mwframework_MWGifFrame_class->finalize = js_mwframework_MWGifFrame_finalize;
    jsb_mwframework_MWGifFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setSpriteFrame", js_mwframework_MWGifFrame_setSpriteFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDuration", js_mwframework_MWGifFrame_setDuration, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSpriteFrame", js_mwframework_MWGifFrame_getSpriteFrame, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDuration", js_mwframework_MWGifFrame_getDuration, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_mwframework_MWGifFrame_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWGifFrame_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWGifFrame_class,
        dummy_constructor<mwframework::MWGifFrame>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "GifFrame", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWGifFrame> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWGifFrame_class;
        p->proto = jsb_mwframework_MWGifFrame_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWGifSprite_class;
JSObject *jsb_mwframework_MWGifSprite_prototype;

bool js_mwframework_MWGifSprite_play(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGifSprite* cobj = (mwframework::MWGifSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGifSprite_play : Invalid Native Object");
    if (argc == 0) {
        cobj->play();
        args.rval().setUndefined();
        return true;
    }
    if (argc == 1) {
        unsigned int arg0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGifSprite_play : Error processing arguments");
        cobj->play(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGifSprite_play : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWGifSprite_pause(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGifSprite* cobj = (mwframework::MWGifSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGifSprite_pause : Invalid Native Object");
    if (argc == 0) {
        cobj->pause();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGifSprite_pause : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWGifSprite_setSpeedRatio(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGifSprite* cobj = (mwframework::MWGifSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGifSprite_setSpeedRatio : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGifSprite_setSpeedRatio : Error processing arguments");
        cobj->setSpeedRatio(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGifSprite_setSpeedRatio : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWGifSprite_getSpriteFrameAtIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGifSprite* cobj = (mwframework::MWGifSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGifSprite_getSpriteFrameAtIndex : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGifSprite_getSpriteFrameAtIndex : Error processing arguments");
        cocos2d::SpriteFrame* ret = cobj->getSpriteFrameAtIndex(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::SpriteFrame>(cx, (cocos2d::SpriteFrame*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGifSprite_getSpriteFrameAtIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWGifSprite_resume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGifSprite* cobj = (mwframework::MWGifSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGifSprite_resume : Invalid Native Object");
    if (argc == 0) {
        cobj->resume();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGifSprite_resume : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWGifSprite_getSpeedRatio(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGifSprite* cobj = (mwframework::MWGifSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGifSprite_getSpeedRatio : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSpeedRatio();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGifSprite_getSpeedRatio : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWGifSprite_stop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGifSprite* cobj = (mwframework::MWGifSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGifSprite_stop : Invalid Native Object");
    if (argc == 0) {
        cobj->stop();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGifSprite_stop : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWGifSprite_createWithFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGifSprite_createWithFile : Error processing arguments");
        mwframework::MWGifSprite* ret = mwframework::MWGifSprite::createWithFile(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWGifSprite>(cx, (mwframework::MWGifSprite*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWGifSprite_createWithFile : wrong number of arguments");
    return false;
}

bool js_mwframework_MWGifSprite_createWithFrames(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        mwframework::MWArrayList* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWArrayList*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGifSprite_createWithFrames : Error processing arguments");
        mwframework::MWGifSprite* ret = mwframework::MWGifSprite::createWithFrames(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWGifSprite>(cx, (mwframework::MWGifSprite*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWGifSprite_createWithFrames : wrong number of arguments");
    return false;
}

bool js_mwframework_MWGifSprite_createWithRawData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        mwframework::MWBinaryData* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWBinaryData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGifSprite_createWithRawData : Error processing arguments");
        mwframework::MWGifSprite* ret = mwframework::MWGifSprite::createWithRawData(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWGifSprite>(cx, (mwframework::MWGifSprite*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWGifSprite_createWithRawData : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Sprite_prototype;

void js_mwframework_MWGifSprite_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWGifSprite)", obj);
}

void js_register_mwframework_MWGifSprite(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWGifSprite_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWGifSprite_class->name = "GifSprite";
    jsb_mwframework_MWGifSprite_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWGifSprite_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWGifSprite_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWGifSprite_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWGifSprite_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWGifSprite_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWGifSprite_class->convert = JS_ConvertStub;
    jsb_mwframework_MWGifSprite_class->finalize = js_mwframework_MWGifSprite_finalize;
    jsb_mwframework_MWGifSprite_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("play", js_mwframework_MWGifSprite_play, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pause", js_mwframework_MWGifSprite_pause, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSpeedRatio", js_mwframework_MWGifSprite_setSpeedRatio, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSpriteFrameAtIndex", js_mwframework_MWGifSprite_getSpriteFrameAtIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resume", js_mwframework_MWGifSprite_resume, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSpeedRatio", js_mwframework_MWGifSprite_getSpeedRatio, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stop", js_mwframework_MWGifSprite_stop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("createWithFile", js_mwframework_MWGifSprite_createWithFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithFrames", js_mwframework_MWGifSprite_createWithFrames, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithRawData", js_mwframework_MWGifSprite_createWithRawData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWGifSprite_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Sprite_prototype),
        jsb_mwframework_MWGifSprite_class,
        dummy_constructor<mwframework::MWGifSprite>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "GifSprite", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWGifSprite> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWGifSprite_class;
        p->proto = jsb_mwframework_MWGifSprite_prototype;
        p->parentProto = jsb_cocos2d_Sprite_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWGifFramesCache_class;
JSObject *jsb_mwframework_MWGifFramesCache_prototype;

bool js_mwframework_MWGifFramesCache_removeAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGifFramesCache* cobj = (mwframework::MWGifFramesCache *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGifFramesCache_removeAll : Invalid Native Object");
    if (argc == 0) {
        cobj->removeAll();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGifFramesCache_removeAll : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWGifFramesCache_addGifFramesCache(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    mwframework::MWGifFramesCache* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (mwframework::MWGifFramesCache *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGifFramesCache_addGifFramesCache : Invalid Native Object");
    do {
        if (argc == 2) {
            mwframework::MWBinaryData* arg0;
            do {
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (mwframework::MWBinaryData*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cobj->addGifFramesCache(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->addGifFramesCache(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            mwframework::MWGifSprite* arg0;
            do {
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (mwframework::MWGifSprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cobj->addGifFramesCache(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            mwframework::MWArrayList* arg0;
            do {
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (mwframework::MWArrayList*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cobj->addGifFramesCache(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_mwframework_MWGifFramesCache_addGifFramesCache : wrong number of arguments");
    return false;
}
bool js_mwframework_MWGifFramesCache_getGifSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGifFramesCache* cobj = (mwframework::MWGifFramesCache *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGifFramesCache_getGifSprite : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGifFramesCache_getGifSprite : Error processing arguments");
        mwframework::MWGifSprite* ret = cobj->getGifSprite(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWGifSprite>(cx, (mwframework::MWGifSprite*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGifFramesCache_getGifSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWGifFramesCache_removeGifFramesCache(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGifFramesCache* cobj = (mwframework::MWGifFramesCache *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWGifFramesCache_removeGifFramesCache : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWGifFramesCache_removeGifFramesCache : Error processing arguments");
        cobj->removeGifFramesCache(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWGifFramesCache_removeGifFramesCache : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWGifFramesCache_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        mwframework::MWGifFramesCache* ret = mwframework::MWGifFramesCache::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWGifFramesCache>(cx, (mwframework::MWGifFramesCache*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWGifFramesCache_getInstance : wrong number of arguments");
    return false;
}


extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWGifFramesCache_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWGifFramesCache)", obj);
}

void js_register_mwframework_MWGifFramesCache(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWGifFramesCache_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWGifFramesCache_class->name = "GifFramesCache";
    jsb_mwframework_MWGifFramesCache_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWGifFramesCache_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWGifFramesCache_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWGifFramesCache_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWGifFramesCache_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWGifFramesCache_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWGifFramesCache_class->convert = JS_ConvertStub;
    jsb_mwframework_MWGifFramesCache_class->finalize = js_mwframework_MWGifFramesCache_finalize;
    jsb_mwframework_MWGifFramesCache_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("removeAll", js_mwframework_MWGifFramesCache_removeAll, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addGifFramesCache", js_mwframework_MWGifFramesCache_addGifFramesCache, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getGifSprite", js_mwframework_MWGifFramesCache_getGifSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeGifFramesCache", js_mwframework_MWGifFramesCache_removeGifFramesCache, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getInstance", js_mwframework_MWGifFramesCache_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWGifFramesCache_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWGifFramesCache_class,
        dummy_constructor<mwframework::MWGifFramesCache>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "GifFramesCache", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWGifFramesCache> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWGifFramesCache_class;
        p->proto = jsb_mwframework_MWGifFramesCache_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWSvgSprite_class;
JSObject *jsb_mwframework_MWSvgSprite_prototype;

bool js_mwframework_MWSvgSprite_setVectorScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWSvgSprite* cobj = (mwframework::MWSvgSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWSvgSprite_setVectorScale : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWSvgSprite_setVectorScale : Error processing arguments");
        cobj->setVectorScale(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWSvgSprite_setVectorScale : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWSvgSprite_getVectorScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWSvgSprite* cobj = (mwframework::MWSvgSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWSvgSprite_getVectorScale : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getVectorScale();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWSvgSprite_getVectorScale : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWSvgSprite_createWithFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWSvgSprite_createWithFile : Error processing arguments");
        mwframework::MWSvgSprite* ret = mwframework::MWSvgSprite::createWithFile(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWSvgSprite>(cx, (mwframework::MWSvgSprite*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        double arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWSvgSprite_createWithFile : Error processing arguments");
        mwframework::MWSvgSprite* ret = mwframework::MWSvgSprite::createWithFile(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWSvgSprite>(cx, (mwframework::MWSvgSprite*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWSvgSprite_createWithFile : wrong number of arguments");
    return false;
}

bool js_mwframework_MWSvgSprite_createWithRawData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        mwframework::MWBinaryData* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWBinaryData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWSvgSprite_createWithRawData : Error processing arguments");
        mwframework::MWSvgSprite* ret = mwframework::MWSvgSprite::createWithRawData(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWSvgSprite>(cx, (mwframework::MWSvgSprite*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        mwframework::MWBinaryData* arg0;
        double arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWBinaryData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWSvgSprite_createWithRawData : Error processing arguments");
        mwframework::MWSvgSprite* ret = mwframework::MWSvgSprite::createWithRawData(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWSvgSprite>(cx, (mwframework::MWSvgSprite*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWSvgSprite_createWithRawData : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Sprite_prototype;

void js_mwframework_MWSvgSprite_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWSvgSprite)", obj);
}

void js_register_mwframework_MWSvgSprite(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWSvgSprite_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWSvgSprite_class->name = "SvgSprite";
    jsb_mwframework_MWSvgSprite_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWSvgSprite_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWSvgSprite_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWSvgSprite_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWSvgSprite_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWSvgSprite_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWSvgSprite_class->convert = JS_ConvertStub;
    jsb_mwframework_MWSvgSprite_class->finalize = js_mwframework_MWSvgSprite_finalize;
    jsb_mwframework_MWSvgSprite_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setVectorScale", js_mwframework_MWSvgSprite_setVectorScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVectorScale", js_mwframework_MWSvgSprite_getVectorScale, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("createWithFile", js_mwframework_MWSvgSprite_createWithFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithRawData", js_mwframework_MWSvgSprite_createWithRawData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWSvgSprite_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Sprite_prototype),
        jsb_mwframework_MWSvgSprite_class,
        dummy_constructor<mwframework::MWSvgSprite>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "SvgSprite", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWSvgSprite> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWSvgSprite_class;
        p->proto = jsb_mwframework_MWSvgSprite_prototype;
        p->parentProto = jsb_cocos2d_Sprite_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWJsonObject_class;
JSObject *jsb_mwframework_MWJsonObject_prototype;

bool js_mwframework_MWJsonObject_count(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject* cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonObject_count : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->count();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonObject_count : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWJsonObject_getJsonArray(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject* cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonObject_getJsonArray : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonObject_getJsonArray : Error processing arguments");
        mwframework::MWJsonArray* ret = cobj->getJsonArray(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWJsonArray>(cx, (mwframework::MWJsonArray*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonObject_getJsonArray : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonObject_getBoolean(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject* cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonObject_getBoolean : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonObject_getBoolean : Error processing arguments");
        bool ret = cobj->getBoolean(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonObject_getBoolean : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonObject_putBoolean(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject* cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonObject_putBoolean : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonObject_putBoolean : Error processing arguments");
        cobj->putBoolean(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonObject_putBoolean : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWJsonObject_getString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject* cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonObject_getString : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonObject_getString : Error processing arguments");
        const char* ret = cobj->getString(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonObject_getString : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonObject_getNumber(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject* cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonObject_getNumber : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonObject_getNumber : Error processing arguments");
        double ret = cobj->getNumber(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonObject_getNumber : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonObject_putJsonArray(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject* cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonObject_putJsonArray : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        mwframework::MWJsonArray* arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (mwframework::MWJsonArray*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonObject_putJsonArray : Error processing arguments");
        cobj->putJsonArray(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonObject_putJsonArray : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWJsonObject_putJsonObject(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject* cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonObject_putJsonObject : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        mwframework::MWJsonObject* arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (mwframework::MWJsonObject*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonObject_putJsonObject : Error processing arguments");
        cobj->putJsonObject(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonObject_putJsonObject : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWJsonObject_clear(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject* cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonObject_clear : Invalid Native Object");
    if (argc == 0) {
        cobj->clear();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonObject_clear : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWJsonObject_putNumber(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject* cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonObject_putNumber : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        double arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonObject_putNumber : Error processing arguments");
        cobj->putNumber(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonObject_putNumber : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWJsonObject_remove(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject* cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonObject_remove : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonObject_remove : Error processing arguments");
        cobj->remove(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonObject_remove : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonObject_putString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject* cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonObject_putString : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonObject_putString : Error processing arguments");
        cobj->putString(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonObject_putString : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWJsonObject_getJsonObject(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject* cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonObject_getJsonObject : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonObject_getJsonObject : Error processing arguments");
        mwframework::MWJsonObject* ret = cobj->getJsonObject(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWJsonObject>(cx, (mwframework::MWJsonObject*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonObject_getJsonObject : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonObject_toJsString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject* cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonObject_toJsString : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->toJsString();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonObject_toJsString : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWJsonObject_toPrettyString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject* cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonObject_toPrettyString : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->toPrettyString();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonObject_toPrettyString : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWJsonObject_hasKey(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject* cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonObject_hasKey : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonObject_hasKey : Error processing arguments");
        bool ret = cobj->hasKey(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonObject_hasKey : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonObject_getObject(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject* cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonObject_getObject : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonObject_getObject : Error processing arguments");
        mwframework::MWObject* ret = cobj->getObject(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWObject>(cx, (mwframework::MWObject*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonObject_getObject : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonObject_createWithFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonObject_createWithFile : Error processing arguments");
        mwframework::MWJsonObject* ret = mwframework::MWJsonObject::createWithFile(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWJsonObject>(cx, (mwframework::MWJsonObject*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWJsonObject_createWithFile : wrong number of arguments");
    return false;
}

bool js_mwframework_MWJsonObject_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        mwframework::MWJsonObject* ret = mwframework::MWJsonObject::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWJsonObject>(cx, (mwframework::MWJsonObject*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWJsonObject_create : wrong number of arguments");
    return false;
}

bool js_mwframework_MWJsonObject_createWithString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonObject_createWithString : Error processing arguments");
        mwframework::MWJsonObject* ret = mwframework::MWJsonObject::createWithString(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWJsonObject>(cx, (mwframework::MWJsonObject*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWJsonObject_createWithString : wrong number of arguments");
    return false;
}


extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWJsonObject_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWJsonObject)", obj);
}

void js_register_mwframework_MWJsonObject(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWJsonObject_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWJsonObject_class->name = "JsonObject";
    jsb_mwframework_MWJsonObject_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWJsonObject_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWJsonObject_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWJsonObject_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWJsonObject_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWJsonObject_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWJsonObject_class->convert = JS_ConvertStub;
    jsb_mwframework_MWJsonObject_class->finalize = js_mwframework_MWJsonObject_finalize;
    jsb_mwframework_MWJsonObject_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("count", js_mwframework_MWJsonObject_count, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getJsonArray", js_mwframework_MWJsonObject_getJsonArray, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBoolean", js_mwframework_MWJsonObject_getBoolean, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("putBoolean", js_mwframework_MWJsonObject_putBoolean, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getString", js_mwframework_MWJsonObject_getString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNumber", js_mwframework_MWJsonObject_getNumber, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("putJsonArray", js_mwframework_MWJsonObject_putJsonArray, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("putJsonObject", js_mwframework_MWJsonObject_putJsonObject, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clear", js_mwframework_MWJsonObject_clear, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("putNumber", js_mwframework_MWJsonObject_putNumber, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("remove", js_mwframework_MWJsonObject_remove, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("putString", js_mwframework_MWJsonObject_putString, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getJsonObject", js_mwframework_MWJsonObject_getJsonObject, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("toJsString", js_mwframework_MWJsonObject_toJsString, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("toPrettyString", js_mwframework_MWJsonObject_toPrettyString, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("hasKey", js_mwframework_MWJsonObject_hasKey, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getObject", js_mwframework_MWJsonObject_getObject, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("createWithFile", js_mwframework_MWJsonObject_createWithFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("create", js_mwframework_MWJsonObject_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithString", js_mwframework_MWJsonObject_createWithString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWJsonObject_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWJsonObject_class,
        dummy_constructor<mwframework::MWJsonObject>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "JsonObject", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWJsonObject> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWJsonObject_class;
        p->proto = jsb_mwframework_MWJsonObject_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWJsonArray_class;
JSObject *jsb_mwframework_MWJsonArray_prototype;

bool js_mwframework_MWJsonArray_count(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_count : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->count();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_count : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWJsonArray_getObjectAt(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_getObjectAt : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_getObjectAt : Error processing arguments");
        mwframework::MWObject* ret = cobj->getObjectAt(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWObject>(cx, (mwframework::MWObject*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_getObjectAt : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonArray_toPrettyString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_toPrettyString : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->toPrettyString();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_toPrettyString : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWJsonArray_getStringAt(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_getStringAt : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_getStringAt : Error processing arguments");
        const char* ret = cobj->getStringAt(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_getStringAt : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonArray_insertJsonArray(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_insertJsonArray : Invalid Native Object");
    if (argc == 2) {
        mwframework::MWJsonArray* arg0;
        unsigned int arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWJsonArray*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_insertJsonArray : Error processing arguments");
        cobj->insertJsonArray(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_insertJsonArray : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWJsonArray_appendJsonArray(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_appendJsonArray : Invalid Native Object");
    if (argc == 1) {
        mwframework::MWJsonArray* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWJsonArray*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_appendJsonArray : Error processing arguments");
        cobj->appendJsonArray(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_appendJsonArray : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonArray_insertJsonObject(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_insertJsonObject : Invalid Native Object");
    if (argc == 2) {
        mwframework::MWJsonObject* arg0;
        unsigned int arg1;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWJsonObject*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_insertJsonObject : Error processing arguments");
        cobj->insertJsonObject(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_insertJsonObject : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWJsonArray_clear(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_clear : Invalid Native Object");
    if (argc == 0) {
        cobj->clear();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_clear : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWJsonArray_appendJsonObject(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_appendJsonObject : Invalid Native Object");
    if (argc == 1) {
        mwframework::MWJsonObject* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWJsonObject*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_appendJsonObject : Error processing arguments");
        cobj->appendJsonObject(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_appendJsonObject : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonArray_insertNumber(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_insertNumber : Invalid Native Object");
    if (argc == 2) {
        double arg0;
        unsigned int arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_insertNumber : Error processing arguments");
        cobj->insertNumber(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_insertNumber : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWJsonArray_removeAt(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_removeAt : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_removeAt : Error processing arguments");
        cobj->removeAt(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_removeAt : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonArray_appendNumber(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_appendNumber : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_appendNumber : Error processing arguments");
        cobj->appendNumber(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_appendNumber : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonArray_appendBoolean(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_appendBoolean : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_appendBoolean : Error processing arguments");
        cobj->appendBoolean(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_appendBoolean : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonArray_getBooleanAt(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_getBooleanAt : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_getBooleanAt : Error processing arguments");
        bool ret = cobj->getBooleanAt(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_getBooleanAt : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonArray_insertString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_insertString : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        int arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_insertString : Error processing arguments");
        cobj->insertString(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_insertString : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWJsonArray_getJsonArrayAt(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_getJsonArrayAt : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_getJsonArrayAt : Error processing arguments");
        mwframework::MWJsonArray* ret = cobj->getJsonArrayAt(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWJsonArray>(cx, (mwframework::MWJsonArray*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_getJsonArrayAt : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonArray_appendString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_appendString : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_appendString : Error processing arguments");
        cobj->appendString(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_appendString : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonArray_insertBoolean(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_insertBoolean : Invalid Native Object");
    if (argc == 2) {
        bool arg0;
        unsigned int arg1;
        arg0 = JS::ToBoolean(args.get(0));
        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_insertBoolean : Error processing arguments");
        cobj->insertBoolean(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_insertBoolean : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWJsonArray_getNumberAt(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_getNumberAt : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_getNumberAt : Error processing arguments");
        double ret = cobj->getNumberAt(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_getNumberAt : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonArray_toJsString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_toJsString : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->toJsString();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_toJsString : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWJsonArray_getJsonObjectAt(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonArray* cobj = (mwframework::MWJsonArray *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWJsonArray_getJsonObjectAt : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_getJsonObjectAt : Error processing arguments");
        mwframework::MWJsonObject* ret = cobj->getJsonObjectAt(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWJsonObject>(cx, (mwframework::MWJsonObject*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWJsonArray_getJsonObjectAt : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWJsonArray_createWithFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_createWithFile : Error processing arguments");
        mwframework::MWJsonArray* ret = mwframework::MWJsonArray::createWithFile(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWJsonArray>(cx, (mwframework::MWJsonArray*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWJsonArray_createWithFile : wrong number of arguments");
    return false;
}

bool js_mwframework_MWJsonArray_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        mwframework::MWJsonArray* ret = mwframework::MWJsonArray::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWJsonArray>(cx, (mwframework::MWJsonArray*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWJsonArray_create : wrong number of arguments");
    return false;
}

bool js_mwframework_MWJsonArray_createWithString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWJsonArray_createWithString : Error processing arguments");
        mwframework::MWJsonArray* ret = mwframework::MWJsonArray::createWithString(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWJsonArray>(cx, (mwframework::MWJsonArray*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWJsonArray_createWithString : wrong number of arguments");
    return false;
}


extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWJsonArray_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWJsonArray)", obj);
}

void js_register_mwframework_MWJsonArray(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWJsonArray_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWJsonArray_class->name = "JsonArray";
    jsb_mwframework_MWJsonArray_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWJsonArray_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWJsonArray_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWJsonArray_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWJsonArray_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWJsonArray_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWJsonArray_class->convert = JS_ConvertStub;
    jsb_mwframework_MWJsonArray_class->finalize = js_mwframework_MWJsonArray_finalize;
    jsb_mwframework_MWJsonArray_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("count", js_mwframework_MWJsonArray_count, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getObjectAt", js_mwframework_MWJsonArray_getObjectAt, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("toPrettyString", js_mwframework_MWJsonArray_toPrettyString, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStringAt", js_mwframework_MWJsonArray_getStringAt, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("insertJsonArray", js_mwframework_MWJsonArray_insertJsonArray, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("appendJsonArray", js_mwframework_MWJsonArray_appendJsonArray, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("insertJsonObject", js_mwframework_MWJsonArray_insertJsonObject, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clear", js_mwframework_MWJsonArray_clear, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("appendJsonObject", js_mwframework_MWJsonArray_appendJsonObject, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("insertNumber", js_mwframework_MWJsonArray_insertNumber, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeAt", js_mwframework_MWJsonArray_removeAt, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("appendNumber", js_mwframework_MWJsonArray_appendNumber, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("appendBoolean", js_mwframework_MWJsonArray_appendBoolean, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBooleanAt", js_mwframework_MWJsonArray_getBooleanAt, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("insertString", js_mwframework_MWJsonArray_insertString, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getJsonArrayAt", js_mwframework_MWJsonArray_getJsonArrayAt, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("appendString", js_mwframework_MWJsonArray_appendString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("insertBoolean", js_mwframework_MWJsonArray_insertBoolean, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNumberAt", js_mwframework_MWJsonArray_getNumberAt, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("toJsString", js_mwframework_MWJsonArray_toJsString, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getJsonObjectAt", js_mwframework_MWJsonArray_getJsonObjectAt, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("createWithFile", js_mwframework_MWJsonArray_createWithFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("create", js_mwframework_MWJsonArray_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithString", js_mwframework_MWJsonArray_createWithString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWJsonArray_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWJsonArray_class,
        dummy_constructor<mwframework::MWJsonArray>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "JsonArray", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWJsonArray> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWJsonArray_class;
        p->proto = jsb_mwframework_MWJsonArray_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWUUIDGenerator_class;
JSObject *jsb_mwframework_MWUUIDGenerator_prototype;

bool js_mwframework_MWUUIDGenerator_generateUUID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWUUIDGenerator* cobj = (mwframework::MWUUIDGenerator *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWUUIDGenerator_generateUUID : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->generateUUID();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWUUIDGenerator_generateUUID : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWUUIDGenerator_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        mwframework::MWUUIDGenerator* ret = mwframework::MWUUIDGenerator::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWUUIDGenerator>(cx, (mwframework::MWUUIDGenerator*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWUUIDGenerator_getInstance : wrong number of arguments");
    return false;
}



void js_mwframework_MWUUIDGenerator_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWUUIDGenerator)", obj);
}

void js_register_mwframework_MWUUIDGenerator(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWUUIDGenerator_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWUUIDGenerator_class->name = "UUIDGenerator";
    jsb_mwframework_MWUUIDGenerator_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWUUIDGenerator_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWUUIDGenerator_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWUUIDGenerator_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWUUIDGenerator_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWUUIDGenerator_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWUUIDGenerator_class->convert = JS_ConvertStub;
    jsb_mwframework_MWUUIDGenerator_class->finalize = js_mwframework_MWUUIDGenerator_finalize;
    jsb_mwframework_MWUUIDGenerator_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("generateUUID", js_mwframework_MWUUIDGenerator_generateUUID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getInstance", js_mwframework_MWUUIDGenerator_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWUUIDGenerator_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_mwframework_MWUUIDGenerator_class,
        dummy_constructor<mwframework::MWUUIDGenerator>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "UUIDGenerator", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWUUIDGenerator> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWUUIDGenerator_class;
        p->proto = jsb_mwframework_MWUUIDGenerator_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWNetHandler_class;
JSObject *jsb_mwframework_MWNetHandler_prototype;

bool js_mwframework_MWNetHandler_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetHandler* cobj = (mwframework::MWNetHandler *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetHandler_create : Invalid Native Object");
    if (argc == 0) {
        mwframework::MWNetHandler* ret = cobj->create();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWNetHandler>(cx, (mwframework::MWNetHandler*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetHandler_create : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWNetHandler_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWNetHandler)", obj);
}

static bool js_mwframework_MWNetHandler_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    mwframework::MWNetHandler *nobj = new (std::nothrow) mwframework::MWNetHandler();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "mwframework::MWNetHandler");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_mwframework_MWNetHandler(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWNetHandler_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWNetHandler_class->name = "NetHandler";
    jsb_mwframework_MWNetHandler_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWNetHandler_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWNetHandler_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWNetHandler_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWNetHandler_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWNetHandler_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWNetHandler_class->convert = JS_ConvertStub;
    jsb_mwframework_MWNetHandler_class->finalize = js_mwframework_MWNetHandler_finalize;
    jsb_mwframework_MWNetHandler_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("create", js_mwframework_MWNetHandler_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_mwframework_MWNetHandler_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_mwframework_MWNetHandler_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWNetHandler_class,
        dummy_constructor<mwframework::MWNetHandler>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "NetHandler", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWNetHandler> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWNetHandler_class;
        p->proto = jsb_mwframework_MWNetHandler_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWNetRequest_class;
JSObject *jsb_mwframework_MWNetRequest_prototype;

bool js_mwframework_MWNetRequest_getProtocolId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetRequest* cobj = (mwframework::MWNetRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetRequest_getProtocolId : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getProtocolId();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetRequest_getProtocolId : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWNetRequest_setBody(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetRequest* cobj = (mwframework::MWNetRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetRequest_setBody : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetRequest_setBody : Error processing arguments");
        cobj->setBody(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetRequest_setBody : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWNetRequest_setProtocolId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetRequest* cobj = (mwframework::MWNetRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetRequest_setProtocolId : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetRequest_setProtocolId : Error processing arguments");
        cobj->setProtocolId(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetRequest_setProtocolId : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWNetRequest_getBody(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetRequest* cobj = (mwframework::MWNetRequest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetRequest_getBody : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getBody();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetRequest_getBody : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWNetRequest_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetRequest_create : Error processing arguments");
        mwframework::MWNetRequest* ret = mwframework::MWNetRequest::create(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWNetRequest>(cx, (mwframework::MWNetRequest*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWNetRequest_create : wrong number of arguments");
    return false;
}


extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWNetRequest_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWNetRequest)", obj);
}

void js_register_mwframework_MWNetRequest(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWNetRequest_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWNetRequest_class->name = "NetRequest";
    jsb_mwframework_MWNetRequest_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWNetRequest_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWNetRequest_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWNetRequest_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWNetRequest_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWNetRequest_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWNetRequest_class->convert = JS_ConvertStub;
    jsb_mwframework_MWNetRequest_class->finalize = js_mwframework_MWNetRequest_finalize;
    jsb_mwframework_MWNetRequest_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getProtocolId", js_mwframework_MWNetRequest_getProtocolId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBody", js_mwframework_MWNetRequest_setBody, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setProtocolId", js_mwframework_MWNetRequest_setProtocolId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBody", js_mwframework_MWNetRequest_getBody, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_mwframework_MWNetRequest_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWNetRequest_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWNetRequest_class,
        dummy_constructor<mwframework::MWNetRequest>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "NetRequest", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWNetRequest> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWNetRequest_class;
        p->proto = jsb_mwframework_MWNetRequest_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWNetResponse_class;
JSObject *jsb_mwframework_MWNetResponse_prototype;

bool js_mwframework_MWNetResponse_getRelatedRequest(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetResponse* cobj = (mwframework::MWNetResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetResponse_getRelatedRequest : Invalid Native Object");
    if (argc == 0) {
        mwframework::MWNetRequest* ret = cobj->getRelatedRequest();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWNetRequest>(cx, (mwframework::MWNetRequest*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetResponse_getRelatedRequest : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWNetResponse_getProtocolId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetResponse* cobj = (mwframework::MWNetResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetResponse_getProtocolId : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getProtocolId();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetResponse_getProtocolId : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWNetResponse_setBody(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetResponse* cobj = (mwframework::MWNetResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetResponse_setBody : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetResponse_setBody : Error processing arguments");
        cobj->setBody(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetResponse_setBody : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWNetResponse_setProtocolId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetResponse* cobj = (mwframework::MWNetResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetResponse_setProtocolId : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetResponse_setProtocolId : Error processing arguments");
        cobj->setProtocolId(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetResponse_setProtocolId : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWNetResponse_getBody(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetResponse* cobj = (mwframework::MWNetResponse *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetResponse_getBody : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getBody();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetResponse_getBody : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWNetResponse_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        mwframework::MWNetRequest* arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        do {
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (mwframework::MWNetRequest*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetResponse_create : Error processing arguments");
        mwframework::MWNetResponse* ret = mwframework::MWNetResponse::create(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWNetResponse>(cx, (mwframework::MWNetResponse*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWNetResponse_create : wrong number of arguments");
    return false;
}


extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWNetResponse_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWNetResponse)", obj);
}

void js_register_mwframework_MWNetResponse(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWNetResponse_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWNetResponse_class->name = "NetResponse";
    jsb_mwframework_MWNetResponse_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWNetResponse_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWNetResponse_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWNetResponse_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWNetResponse_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWNetResponse_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWNetResponse_class->convert = JS_ConvertStub;
    jsb_mwframework_MWNetResponse_class->finalize = js_mwframework_MWNetResponse_finalize;
    jsb_mwframework_MWNetResponse_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getRelatedRequest", js_mwframework_MWNetResponse_getRelatedRequest, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getProtocolId", js_mwframework_MWNetResponse_getProtocolId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBody", js_mwframework_MWNetResponse_setBody, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setProtocolId", js_mwframework_MWNetResponse_setProtocolId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBody", js_mwframework_MWNetResponse_getBody, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_mwframework_MWNetResponse_create, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWNetResponse_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWNetResponse_class,
        dummy_constructor<mwframework::MWNetResponse>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "NetResponse", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWNetResponse> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWNetResponse_class;
        p->proto = jsb_mwframework_MWNetResponse_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWNetProtocol_class;
JSObject *jsb_mwframework_MWNetProtocol_prototype;

bool js_mwframework_MWNetProtocol_getRelatedHandler(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetProtocol* cobj = (mwframework::MWNetProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetProtocol_getRelatedHandler : Invalid Native Object");
    if (argc == 0) {
        mwframework::MWNetHandler* ret = cobj->getRelatedHandler();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWNetHandler>(cx, (mwframework::MWNetHandler*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetProtocol_getRelatedHandler : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWNetProtocol_getServiceId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetProtocol* cobj = (mwframework::MWNetProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetProtocol_getServiceId : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getServiceId();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetProtocol_getServiceId : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWNetProtocol_getProtocolId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetProtocol* cobj = (mwframework::MWNetProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetProtocol_getProtocolId : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getProtocolId();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetProtocol_getProtocolId : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWNetProtocol_setServiceId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetProtocol* cobj = (mwframework::MWNetProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetProtocol_setServiceId : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetProtocol_setServiceId : Error processing arguments");
        cobj->setServiceId(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetProtocol_setServiceId : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWNetProtocol_setProtocolId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetProtocol* cobj = (mwframework::MWNetProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetProtocol_setProtocolId : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetProtocol_setProtocolId : Error processing arguments");
        cobj->setProtocolId(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetProtocol_setProtocolId : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWNetProtocol_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        mwframework::MWNetHandler* arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        do {
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (mwframework::MWNetHandler*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetProtocol_create : Error processing arguments");
        mwframework::MWNetProtocol* ret = mwframework::MWNetProtocol::create(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWNetProtocol>(cx, (mwframework::MWNetProtocol*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWNetProtocol_create : wrong number of arguments");
    return false;
}


extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWNetProtocol_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWNetProtocol)", obj);
}

void js_register_mwframework_MWNetProtocol(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWNetProtocol_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWNetProtocol_class->name = "NetProtocol";
    jsb_mwframework_MWNetProtocol_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWNetProtocol_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWNetProtocol_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWNetProtocol_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWNetProtocol_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWNetProtocol_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWNetProtocol_class->convert = JS_ConvertStub;
    jsb_mwframework_MWNetProtocol_class->finalize = js_mwframework_MWNetProtocol_finalize;
    jsb_mwframework_MWNetProtocol_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getRelatedHandler", js_mwframework_MWNetProtocol_getRelatedHandler, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getServiceId", js_mwframework_MWNetProtocol_getServiceId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getProtocolId", js_mwframework_MWNetProtocol_getProtocolId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setServiceId", js_mwframework_MWNetProtocol_setServiceId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setProtocolId", js_mwframework_MWNetProtocol_setProtocolId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_mwframework_MWNetProtocol_create, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWNetProtocol_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWNetProtocol_class,
        dummy_constructor<mwframework::MWNetProtocol>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "NetProtocol", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWNetProtocol> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWNetProtocol_class;
        p->proto = jsb_mwframework_MWNetProtocol_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_mwframework_MWNetCenter_class;
JSObject *jsb_mwframework_MWNetCenter_prototype;

bool js_mwframework_MWNetCenter_addNetService(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetCenter* cobj = (mwframework::MWNetCenter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetCenter_addNetService : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        mwframework::MWNetService* arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (mwframework::MWNetService*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetCenter_addNetService : Error processing arguments");
        cobj->addNetService(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetCenter_addNetService : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_mwframework_MWNetCenter_removeAllNetFilters(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetCenter* cobj = (mwframework::MWNetCenter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetCenter_removeAllNetFilters : Invalid Native Object");
    if (argc == 0) {
        cobj->removeAllNetFilters();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetCenter_removeAllNetFilters : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_mwframework_MWNetCenter_addNetFilter(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetCenter* cobj = (mwframework::MWNetCenter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetCenter_addNetFilter : Invalid Native Object");
    if (argc == 1) {
        mwframework::MWNetFilter* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWNetFilter*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetCenter_addNetFilter : Error processing arguments");
        cobj->addNetFilter(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetCenter_addNetFilter : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWNetCenter_removeNetProtocol(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetCenter* cobj = (mwframework::MWNetCenter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetCenter_removeNetProtocol : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetCenter_removeNetProtocol : Error processing arguments");
        cobj->removeNetProtocol(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetCenter_removeNetProtocol : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWNetCenter_removeNetFilter(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetCenter* cobj = (mwframework::MWNetCenter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetCenter_removeNetFilter : Invalid Native Object");
    if (argc == 1) {
        mwframework::MWNetFilter* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWNetFilter*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetCenter_removeNetFilter : Error processing arguments");
        cobj->removeNetFilter(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetCenter_removeNetFilter : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWNetCenter_removeNetService(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetCenter* cobj = (mwframework::MWNetCenter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetCenter_removeNetService : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetCenter_removeNetService : Error processing arguments");
        cobj->removeNetService(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetCenter_removeNetService : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWNetCenter_sendMessage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetCenter* cobj = (mwframework::MWNetCenter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetCenter_sendMessage : Invalid Native Object");
    if (argc == 1) {
        mwframework::MWNetRequest* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWNetRequest*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetCenter_sendMessage : Error processing arguments");
        cobj->sendMessage(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetCenter_sendMessage : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWNetCenter_addNetProtocol(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    mwframework::MWNetCenter* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (mwframework::MWNetCenter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetCenter_addNetProtocol : Invalid Native Object");
    do {
        if (argc == 1) {
            mwframework::MWNetProtocol* arg0;
            do {
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (mwframework::MWNetProtocol*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cobj->addNetProtocol(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 3) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            mwframework::MWNetHandler* arg2;
            do {
                if (!args.get(2).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(2).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg2 = (mwframework::MWNetHandler*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cobj->addNetProtocol(arg0, arg1, arg2);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_mwframework_MWNetCenter_addNetProtocol : wrong number of arguments");
    return false;
}
bool js_mwframework_MWNetCenter_dispatchFailedMessage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetCenter* cobj = (mwframework::MWNetCenter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetCenter_dispatchFailedMessage : Invalid Native Object");
    if (argc == 1) {
        mwframework::MWNetResponse* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWNetResponse*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetCenter_dispatchFailedMessage : Error processing arguments");
        cobj->dispatchFailedMessage(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetCenter_dispatchFailedMessage : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWNetCenter_dispatchSuccessfulMessage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetCenter* cobj = (mwframework::MWNetCenter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetCenter_dispatchSuccessfulMessage : Invalid Native Object");
    if (argc == 1) {
        mwframework::MWNetResponse* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (mwframework::MWNetResponse*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetCenter_dispatchSuccessfulMessage : Error processing arguments");
        cobj->dispatchSuccessfulMessage(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetCenter_dispatchSuccessfulMessage : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_mwframework_MWNetCenter_sendCommand(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWNetCenter* cobj = (mwframework::MWNetCenter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_mwframework_MWNetCenter_sendCommand : Invalid Native Object");
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        cocos2d::Ref* arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        do {
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWNetCenter_sendCommand : Error processing arguments");
        cobj->sendCommand(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_mwframework_MWNetCenter_sendCommand : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_mwframework_MWNetCenter_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        mwframework::MWNetCenter* ret = mwframework::MWNetCenter::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWNetCenter>(cx, (mwframework::MWNetCenter*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWNetCenter_getInstance : wrong number of arguments");
    return false;
}


extern JSObject *jsb_mwframework_MWObject_prototype;

void js_mwframework_MWNetCenter_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (MWNetCenter)", obj);
}

void js_register_mwframework_MWNetCenter(JSContext *cx, JS::HandleObject global) {
    jsb_mwframework_MWNetCenter_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_mwframework_MWNetCenter_class->name = "NetCenter";
    jsb_mwframework_MWNetCenter_class->addProperty = JS_PropertyStub;
    jsb_mwframework_MWNetCenter_class->delProperty = JS_DeletePropertyStub;
    jsb_mwframework_MWNetCenter_class->getProperty = JS_PropertyStub;
    jsb_mwframework_MWNetCenter_class->setProperty = JS_StrictPropertyStub;
    jsb_mwframework_MWNetCenter_class->enumerate = JS_EnumerateStub;
    jsb_mwframework_MWNetCenter_class->resolve = JS_ResolveStub;
    jsb_mwframework_MWNetCenter_class->convert = JS_ConvertStub;
    jsb_mwframework_MWNetCenter_class->finalize = js_mwframework_MWNetCenter_finalize;
    jsb_mwframework_MWNetCenter_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("addNetService", js_mwframework_MWNetCenter_addNetService, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeAllNetFilters", js_mwframework_MWNetCenter_removeAllNetFilters, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addNetFilter", js_mwframework_MWNetCenter_addNetFilter, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeNetProtocol", js_mwframework_MWNetCenter_removeNetProtocol, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeNetFilter", js_mwframework_MWNetCenter_removeNetFilter, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeNetService", js_mwframework_MWNetCenter_removeNetService, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("sendMessage", js_mwframework_MWNetCenter_sendMessage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addNetProtocol", js_mwframework_MWNetCenter_addNetProtocol, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("dispatchFailedMessage", js_mwframework_MWNetCenter_dispatchFailedMessage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("dispatchSuccessfulMessage", js_mwframework_MWNetCenter_dispatchSuccessfulMessage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("sendCommand", js_mwframework_MWNetCenter_sendCommand, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getInstance", js_mwframework_MWNetCenter_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_mwframework_MWNetCenter_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_mwframework_MWObject_prototype),
        jsb_mwframework_MWNetCenter_class,
        dummy_constructor<mwframework::MWNetCenter>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "NetCenter", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<mwframework::MWNetCenter> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_mwframework_MWNetCenter_class;
        p->proto = jsb_mwframework_MWNetCenter_prototype;
        p->parentProto = jsb_mwframework_MWObject_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_mwframework(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "mw", &ns);

    js_register_mwframework_MWObject(cx, ns);
    js_register_mwframework_MWViewSegue(cx, ns);
    js_register_mwframework_MWNetRequest(cx, ns);
    js_register_mwframework_MWGameView(cx, ns);
    js_register_mwframework_MWGifFrame(cx, ns);
    js_register_mwframework_MWException(cx, ns);
    js_register_mwframework_MWGifFramesCache(cx, ns);
    js_register_mwframework_MWUUIDGenerator(cx, ns);
    js_register_mwframework_MWGameScene(cx, ns);
    js_register_mwframework_MWSvgSprite(cx, ns);
    js_register_mwframework_MWDictionary(cx, ns);
    js_register_mwframework_MWSystemHelper(cx, ns);
    js_register_mwframework_MWGifSprite(cx, ns);
    js_register_mwframework_MWBinaryData(cx, ns);
    js_register_mwframework_MWSqliteDb(cx, ns);
    js_register_mwframework_MWQueue(cx, ns);
    js_register_mwframework_MWNetCenter(cx, ns);
    js_register_mwframework_MWViewController(cx, ns);
    js_register_mwframework_MWNetProtocol(cx, ns);
    js_register_mwframework_MWIOUtils(cx, ns);
    js_register_mwframework_MWStack(cx, ns);
    js_register_mwframework_MWArrayList(cx, ns);
    js_register_mwframework_MWJsonArray(cx, ns);
    js_register_mwframework_MWZipData(cx, ns);
    js_register_mwframework_MWNetHandler(cx, ns);
    js_register_mwframework_MWNetResponse(cx, ns);
    js_register_mwframework_MWJsonObject(cx, ns);
}

