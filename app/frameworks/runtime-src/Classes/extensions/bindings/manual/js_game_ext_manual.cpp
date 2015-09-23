#include "js_game_ext_manual.hpp"
#include "cocos2d_specifics.hpp"
#include "game-ext.h"
#include <string>
#include <vector>

using namespace std;
using namespace game;

extern JSClass  *jsb_game_UITextOneByOne_class;
extern JSObject *jsb_game_UITextOneByOne_prototype;

bool jsb_game_ext_UITextOneByOne_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        double duration;
        vector<string> array;
        
        ok &= JS::ToNumber(cx, args.get(0), &duration) && !isnan(duration);
        ok &= JS_IsArrayObject(cx, JS::RootedObject(cx, args.get(1).toObjectOrNull()));
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
        JS::RootedObject jsobj(cx);
        
        auto jsary = args.get(1);
        ok &= (jsary.isObject() && JS_ValueToObject(cx, jsary, &jsobj));
        JSB_PRECONDITION3(ok, cx, false, "Error converting value to object");
        JSB_PRECONDITION3(jsobj && JS_IsArrayObject(cx, jsobj), cx, false, "Object must be an array");
        
        uint32_t len = 0;
        JS_GetArrayLength(cx, jsobj, &len);
        
        for (uint32_t i = 0; i < len; i++)
        {
            JS::RootedValue value(cx);
            if (JS_GetElement(cx, jsobj, i, &value))
            {
                CCASSERT(value.isString(), "the element in array isn't a string.");
                string str;
                jsval_to_std_string(cx, value, &str);
                array.push_back(str);
            }
        }
        
        auto ret = UITextOneByOne::create(duration, array);
        jsval jsret;
        if (ret) {
            js_proxy_t *p = jsb_get_native_proxy(ret);
            if (p) {
                jsret = OBJECT_TO_JSVAL(p->obj);
            } else {
                // create a new js obj of that class
                js_proxy_t *proxy = js_get_or_create_proxy<UITextOneByOne>(cx, ret);
                jsret = OBJECT_TO_JSVAL(proxy->obj);
            }
        } else {
            jsret = JSVAL_NULL;
        }
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return false;
}

void register_all_game_ext_manual(JSContext* cx, JS::HandleObject global) {
    // extend ex.UITextOneByOne
    JS::RootedObject exObj(cx);
    JS::RootedValue tmpVal(cx);
    JS::RootedObject tmpObj(cx);
    get_or_create_js_obj(cx, global, "ex", &exObj);
    JS_GetProperty(cx, exObj, "UITextOneByOne", &tmpVal);
    tmpObj = tmpVal.toObjectOrNull();
    JS_DefineFunction(cx, tmpObj, "create", jsb_game_ext_UITextOneByOne_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);
}

