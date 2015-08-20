#include "js_mwframework_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "mwframework.h"

using namespace mwframework;

extern JSClass *jsb_mwframework_MWDictionary_class;
extern JSObject *jsb_mwframework_MWDictionary_prototype;

bool js_mwframework_MWDictionary_allKeys(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWDictionary * cobj = (mwframework::MWDictionary *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2(cobj, cx, false, "js_mwframework_MWDictionary_allKeys : Invalid Native Object");
    if (argc == 0) {
        std::vector<std::string> ret = cobj->allKeys();
        JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0));
        
        int i = 0;
        for (auto & str :ret)
        {
            JS::RootedValue arrElement(cx, std_string_to_jsval(cx, str));
            if (!JS_SetElement(cx, jsretArr, i, arrElement)) {
                break;
            }
            ++i;
        }
        args.rval().set(OBJECT_TO_JSVAL(jsretArr));
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWDictionary_allKeys : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

extern JSClass *jsb_mwframework_MWSqliteDb_class;
extern JSObject *jsb_mwframework_MWSqliteDb_prototype;

bool js_mwframework_MWSqliteDb_executeQuery(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWSqliteDb * cobj = (mwframework::MWSqliteDb *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2(cobj, cx, false, "js_mwframework_MWSqliteDb_executeQuery : Invalid Native Object");
    bool ok = true;
    if (argc == 1) {
        std::string sql;
        ok &= jsval_to_std_string(cx, args.get(0), &sql);
        JSB_PRECONDITION2(ok, cx, false, "js_mwframework_MWSqliteDb_executeQuery : Error processing arguments");
        MWArrayList *ret = cobj->executeQuery(sql);
        
        JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0));
        for (int i = 0; i < ret->count(); ++i) {
            JS::RootedObject jsRet(cx, JS_NewObject(cx, nullptr, JS::NullPtr(), JS::NullPtr()));
            
            MWDictionary * pDict = static_cast<MWDictionary *>(ret->objectAtIndex(i));
            auto allKeys = pDict->allKeys();
            for (auto &key : allKeys) {
                cocos2d::Ref *pVal = pDict->objectForKey(key);
                cocos2d::__Double *pNum = nullptr;
                cocos2d::__Integer *pInt = nullptr;
                cocos2d::__String *pStr = nullptr;
                if ((pNum = dynamic_cast<cocos2d::__Double *>(pVal))) {
                    JS::RootedValue val(cx);
                    val.setDouble(pNum->getValue());
                    JS_SetProperty(cx, jsRet, key.c_str(), val);
                } else if ((pInt = dynamic_cast<cocos2d::__Integer *>(pVal))) {
                    JS::RootedValue val(cx);
                    val.setInt32(pInt->getValue());
                    JS_SetProperty(cx, jsRet, key.c_str(), val);
                } else if ((pStr = dynamic_cast<cocos2d::__String *>(pVal))) {
                    JS::RootedValue val(cx, std_string_to_jsval(cx, pStr->getCString()));
                    JS_SetProperty(cx, jsRet, key.c_str(), val);
                }
            }
            
            if (!JS_SetElement(cx, jsretArr, i, jsRet)) {
                break;
            }
        }
        args.rval().set(OBJECT_TO_JSVAL(jsretArr));
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWSqliteDb_executeQuery : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

extern JSClass *jsb_mwframework_MWGifSprite_class;
extern JSObject *jsb_mwframework_MWGifSprite_prototype;

bool js_mwframework_MWGifSprite_getFrames(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWGifSprite * cobj = (mwframework::MWGifSprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2(cobj, cx, false, "js_mwframework_MWGifSprite_getFrames : Invalid Native Object");
    if (argc == 0) {
        MWArrayList *ret = cobj->getFrames();
        JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0));
        
        for (int i = 0; i < ret->count(); ++i) {
            JS::RootedValue arrElement(cx);
            
            MWGifFrame *frame = static_cast<MWGifFrame *>(ret->objectAtIndex(i));
            js_proxy_t *jsProxy = js_get_or_create_proxy<MWGifFrame>(cx, frame);
            if (jsProxy) {
                arrElement = OBJECT_TO_JSVAL(jsProxy->obj);
            }
            if (!JS_SetElement(cx, jsretArr, i, arrElement)) {
                break;
            }
        }
        args.rval().set(OBJECT_TO_JSVAL(jsretArr));
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWGifSprite_getFrames : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

extern JSClass *jsb_mwframework_MWJsonObject_class;
extern JSObject *jsb_mwframework_MWJsonObject_prototype;

bool js_mwframework_MWJsonObject_allKeys(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    mwframework::MWJsonObject * cobj = (mwframework::MWJsonObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2(cobj, cx, false, "js_mwframework_MWJsonObject_allKeys : Invalid Native Object");
    if (argc == 0) {
        std::vector<std::string> ret = cobj->allKeys();
        JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0));
        
        int i = 0;
        for (auto & str :ret)
        {
            JS::RootedValue arrElement(cx, std_string_to_jsval(cx, str));
            if (!JS_SetElement(cx, jsretArr, i, arrElement)) {
                break;
            }
            ++i;
        }
        args.rval().set(OBJECT_TO_JSVAL(jsretArr));
        return true;
    }
    JS_ReportError(cx, "js_mwframework_MWJsonObject_allKeys : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

//extern JSClass *jsb_mwframework_MWGameScene_class;
//extern JSObject *jsb_mwframework_MWGameScene_prototype;
//
//bool js_mwframework_MWGameScene_createWithParams(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    if (argc == 1) {
//        JS::RootedObject tmp(cx, args.get(0).toObjectOrNull());
//        JSB_PRECONDITION2(tmp, cx, false, "js_mwframework_MWGameScene_createWithParams: the param is not an object.");
//        
//        mwframework::MWDictionary * params = MWDictionary::create();
//        
//        JS::RootedObject iter(cx, JS_NewPropertyIterator(cx, tmp));
//        while (true) {
//            JS::RootedId idp(cx);
//            JS::RootedValue key(cx);
//            if (!JS_NextProperty(cx, iter, idp.address()) || !JS_IdToValue(cx, idp, &key)) {
//                CCLOGERROR("js_mwframework_MWGameScene_createWithParams: Error processing arguments.");
//                return false;
//            }
//            if (key == JSVAL_VOID) {
//                break;      // end of the iteration.
//            }
//            if (!key.isString()) {
//                continue;
//            }
//            
//            std::string stdKey;
//            jsval_to_std_string(cx, key, &stdKey);
//            
//            JS::RootedValue value(cx);
//            JS_GetPropertyById(cx, tmp, idp, &value);
//            if (value.isNumber()) {
//                params->setObjectForKey(stdKey, cocos2d::__Double::create(value.toNumber()));
//            } else if (value.isBoolean()) {
//                params->setObjectForKey(stdKey, cocos2d::__Bool::create(value.toBoolean()));
//            } else if (value.isString()) {
//                std::string strVal;
//                jsval_to_std_string(cx, value, &strVal);
//                params->setObjectForKey(stdKey, cocos2d::__String::create(strVal));
//            } else if (value.isObject()) {
//                js_proxy_t *jsProxy;
//                JSObject *tmpObj = value.toObjectOrNull();
//                jsProxy = jsb_get_js_proxy(tmpObj);
//                cocos2d::Ref * pVal = (cocos2d::Ref *)(jsProxy ? jsProxy->ptr : nullptr);
//                JSB_PRECONDITION2(pVal, cx, false, "js_mwframework_MWGameScene_createWithParams: Error processing arguments.");
//                params->setObjectForKey(stdKey, pVal);
//            }
//        }
//        
//        auto ret = MWGameScene::createWithParams(params);
//        jsval jsret = JSVAL_NULL;
//        if (ret) {
//            js_proxy_t *jsProxy = js_get_or_create_proxy<mwframework::MWGameScene>(cx, ret);
//            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
//        }
//        args.rval().set(jsret);
//        return true;
//    }
//    JS_ReportError(cx, "js_mwframework_MWGameScene_createWithParams : wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}

void register_all_mwframework_manual(JSContext* cx, JS::HandleObject global)
{
    // extend mw.Dictionary
    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_mwframework_MWDictionary_prototype), "allKeys", js_mwframework_MWDictionary_allKeys, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    // extend mw.SqliteDb
    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_mwframework_MWSqliteDb_prototype), "executeQuery", js_mwframework_MWSqliteDb_executeQuery, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    // extend mw.GifSprite
    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_mwframework_MWGifSprite_prototype), "getFrames", js_mwframework_MWGifSprite_getFrames, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    // extend mw.JsonObject
    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_mwframework_MWJsonObject_prototype), "allKeys", js_mwframework_MWJsonObject_allKeys, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    // extend mw.GameScene
//    JS::RootedObject mwObj(cx);
//    JS::RootedValue tmpVal(cx);
//    JS::RootedObject tmpObj(cx);
//    get_or_create_js_obj(cx, global, "mw", &mwObj);
//    JS_GetProperty(cx, mwObj, "GameScene", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", js_mwframework_MWGameScene_createWithParams, 1, JSPROP_READONLY | JSPROP_PERMANENT);
}