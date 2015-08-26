#ifndef __mwframework_h__
#define __mwframework_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_mwframework_MWObject_class;
extern JSObject *jsb_mwframework_MWObject_prototype;

bool js_mwframework_MWObject_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWObject_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWObject(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWObject_toString(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWBinaryData_class;
extern JSObject *jsb_mwframework_MWBinaryData_prototype;

bool js_mwframework_MWBinaryData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWBinaryData_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWBinaryData(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWBinaryData_isValid(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWException_class;
extern JSObject *jsb_mwframework_MWException_prototype;

bool js_mwframework_MWException_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWException_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWException(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWException_errorCode(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWException_what(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWException_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWException_MWException(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWDictionary_class;
extern JSObject *jsb_mwframework_MWDictionary_prototype;

bool js_mwframework_MWDictionary_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWDictionary_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWDictionary(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWDictionary_count(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWDictionary_removeObjectForKey(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWDictionary_clear(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWDictionary_setObjectForKey(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWDictionary_objectForKey(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWDictionary_empty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWDictionary_hasKey(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWDictionary_clone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWDictionary_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWDictionary_MWDictionary(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWArrayList_class;
extern JSObject *jsb_mwframework_MWArrayList_prototype;

bool js_mwframework_MWArrayList_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWArrayList_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWArrayList(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWArrayList_count(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWArrayList_setObjectAtIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWArrayList_removeObjectAtIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWArrayList_appendObject(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWArrayList_lastIndexOfObject(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWArrayList_indexOfObject(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWArrayList_insertObjectAtIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWArrayList_removeObject(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWArrayList_clone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWArrayList_clear(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWArrayList_empty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWArrayList_objectAtIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWArrayList_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWArrayList_MWArrayList(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWQueue_class;
extern JSObject *jsb_mwframework_MWQueue_prototype;

bool js_mwframework_MWQueue_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWQueue_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWQueue(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWQueue_count(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWQueue_dequeue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWQueue_clear(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWQueue_enqueue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWQueue_front(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWQueue_clone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWQueue_empty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWQueue_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWQueue_MWQueue(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWStack_class;
extern JSObject *jsb_mwframework_MWStack_prototype;

bool js_mwframework_MWStack_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWStack_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWStack(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWStack_count(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWStack_top(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWStack_pop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWStack_push(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWStack_clone(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWStack_clear(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWStack_empty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWStack_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWStack_MWStack(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWSystemHelper_class;
extern JSObject *jsb_mwframework_MWSystemHelper_prototype;

bool js_mwframework_MWSystemHelper_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWSystemHelper_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWSystemHelper(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWSystemHelper_checkNetStatus(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWSystemHelper_getCurrentUsedMemory(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWSystemHelper_millisecondsNow(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWSystemHelper_copyToPasteBoard(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWSystemHelper_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWIOUtils_class;
extern JSObject *jsb_mwframework_MWIOUtils_prototype;

bool js_mwframework_MWIOUtils_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWIOUtils_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWIOUtils(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWIOUtils_fileExists(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWIOUtils_copyFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWIOUtils_writeDataToFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWIOUtils_getDataFromFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWIOUtils_splicePath(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWIOUtils_createFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWIOUtils_resourcePath(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWIOUtils_directoryExists(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWIOUtils_removeFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWIOUtils_moveFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWIOUtils_removeDirectory(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWIOUtils_createDirectory(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWIOUtils_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWGameScene_class;
extern JSObject *jsb_mwframework_MWGameScene_prototype;

bool js_mwframework_MWGameScene_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWGameScene_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWGameScene(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWGameScene_getViewControllers(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGameScene_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGameScene_unloadViewController(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGameScene_loadViewController(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGameScene_getViewControllerByIdentifier(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGameScene_getParameter(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGameScene_unloadAllViewControllers(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGameScene_addParameter(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGameScene_getMemoryWarningLine(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGameScene_setMemoryWarningLine(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGameScene_unloadViewControllerByIdentifier(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGameScene_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGameScene_MWGameScene(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWViewController_class;
extern JSObject *jsb_mwframework_MWViewController_prototype;

bool js_mwframework_MWViewController_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWViewController_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWViewController(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWViewController_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWViewController_segue(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWViewController_scene(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWViewController_getIdentifier(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWViewController_view(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWViewController_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWViewController_MWViewController(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWGameView_class;
extern JSObject *jsb_mwframework_MWGameView_prototype;

bool js_mwframework_MWGameView_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWGameView_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWGameView(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWGameView_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWViewSegue_class;
extern JSObject *jsb_mwframework_MWViewSegue_prototype;

bool js_mwframework_MWViewSegue_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWViewSegue_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWViewSegue(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWViewSegue_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWViewSegue_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWViewSegue_MWViewSegue(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWSqliteDb_class;
extern JSObject *jsb_mwframework_MWSqliteDb_prototype;

bool js_mwframework_MWSqliteDb_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWSqliteDb_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWSqliteDb(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWSqliteDb_executeNonQuery(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWSqliteDb_endTransaction(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWSqliteDb_beginTransaction(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWSqliteDb_openDb(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWSqliteDb_clearConnectionCache(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWZipData_class;
extern JSObject *jsb_mwframework_MWZipData_prototype;

bool js_mwframework_MWZipData_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWZipData_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWZipData(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWZipData_getCompressedFileData(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWZipData_zipNewFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWZipData_beginUnzip(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWZipData_endUnzip(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWZipData_beginZip(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWZipData_endZip(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWZipData_createWithExistingFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWZipData_createWithNewFile(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWGifFrame_class;
extern JSObject *jsb_mwframework_MWGifFrame_prototype;

bool js_mwframework_MWGifFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWGifFrame_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWGifFrame(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWGifFrame_setSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGifFrame_setDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGifFrame_getSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGifFrame_getDuration(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGifFrame_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWGifSprite_class;
extern JSObject *jsb_mwframework_MWGifSprite_prototype;

bool js_mwframework_MWGifSprite_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWGifSprite_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWGifSprite(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWGifSprite_play(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGifSprite_pause(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGifSprite_setSpeedRatio(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGifSprite_getSpriteFrameAtIndex(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGifSprite_resume(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGifSprite_getSpeedRatio(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGifSprite_stop(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGifSprite_createWithFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGifSprite_createWithFrames(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGifSprite_createWithRawData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWGifFramesCache_class;
extern JSObject *jsb_mwframework_MWGifFramesCache_prototype;

bool js_mwframework_MWGifFramesCache_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWGifFramesCache_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWGifFramesCache(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWGifFramesCache_removeAll(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGifFramesCache_addGifFramesCache(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGifFramesCache_getGifSprite(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGifFramesCache_removeGifFramesCache(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWGifFramesCache_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWSvgSprite_class;
extern JSObject *jsb_mwframework_MWSvgSprite_prototype;

bool js_mwframework_MWSvgSprite_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWSvgSprite_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWSvgSprite(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWSvgSprite_setVectorScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWSvgSprite_getVectorScale(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWSvgSprite_createWithFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWSvgSprite_createWithRawData(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWJsonObject_class;
extern JSObject *jsb_mwframework_MWJsonObject_prototype;

bool js_mwframework_MWJsonObject_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWJsonObject_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWJsonObject(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWJsonObject_count(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_getJsonArray(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_getBoolean(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_putBoolean(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_getString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_getNumber(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_putJsonArray(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_putJsonObject(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_clear(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_putNumber(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_remove(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_putString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_getJsonObject(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_toJsString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_toPrettyString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_hasKey(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_getObject(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_createWithFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonObject_createWithString(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWJsonArray_class;
extern JSObject *jsb_mwframework_MWJsonArray_prototype;

bool js_mwframework_MWJsonArray_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWJsonArray_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWJsonArray(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWJsonArray_count(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_getObjectAt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_toPrettyString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_getStringAt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_insertJsonArray(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_appendJsonArray(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_insertJsonObject(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_clear(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_appendJsonObject(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_insertNumber(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_removeAt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_appendNumber(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_appendBoolean(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_getBooleanAt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_insertString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_getJsonArrayAt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_appendString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_insertBoolean(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_getNumberAt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_toJsString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_getJsonObjectAt(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_createWithFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWJsonArray_createWithString(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWCrypto_class;
extern JSObject *jsb_mwframework_MWCrypto_prototype;

bool js_mwframework_MWCrypto_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWCrypto_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWCrypto(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWCrypto_encipherAes256(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWCrypto_decodeBase64(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWCrypto_md5String(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWCrypto_md5File(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWCrypto_getAes256KeyLength(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWCrypto_decipherAes256(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWCrypto_encodeBase64(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWCrypto_md5(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWCrypto_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWUUIDGenerator_class;
extern JSObject *jsb_mwframework_MWUUIDGenerator_prototype;

bool js_mwframework_MWUUIDGenerator_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWUUIDGenerator_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWUUIDGenerator(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWUUIDGenerator_generateUUID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWUUIDGenerator_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWNetHandler_class;
extern JSObject *jsb_mwframework_MWNetHandler_prototype;

bool js_mwframework_MWNetHandler_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWNetHandler_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWNetHandler(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWNetHandler_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWNetRequest_class;
extern JSObject *jsb_mwframework_MWNetRequest_prototype;

bool js_mwframework_MWNetRequest_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWNetRequest_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWNetRequest(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWNetRequest_getProtocolId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetRequest_setBody(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetRequest_setProtocolId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetRequest_getBody(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetRequest_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWNetResponse_class;
extern JSObject *jsb_mwframework_MWNetResponse_prototype;

bool js_mwframework_MWNetResponse_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWNetResponse_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWNetResponse(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWNetResponse_getRelatedRequest(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetResponse_getProtocolId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetResponse_setBody(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetResponse_setProtocolId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetResponse_getBody(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetResponse_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWNetProtocol_class;
extern JSObject *jsb_mwframework_MWNetProtocol_prototype;

bool js_mwframework_MWNetProtocol_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWNetProtocol_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWNetProtocol(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWNetProtocol_getRelatedHandler(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetProtocol_getServiceId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetProtocol_getProtocolId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetProtocol_setServiceId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetProtocol_setProtocolId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetProtocol_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_mwframework_MWNetCenter_class;
extern JSObject *jsb_mwframework_MWNetCenter_prototype;

bool js_mwframework_MWNetCenter_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_mwframework_MWNetCenter_finalize(JSContext *cx, JSObject *obj);
void js_register_mwframework_MWNetCenter(JSContext *cx, JS::HandleObject global);
void register_all_mwframework(JSContext* cx, JS::HandleObject obj);
bool js_mwframework_MWNetCenter_addNetService(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetCenter_removeAllNetFilters(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetCenter_addNetFilter(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetCenter_removeNetProtocol(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetCenter_removeNetFilter(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetCenter_removeNetService(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetCenter_sendMessage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetCenter_addNetProtocol(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetCenter_dispatchFailedMessage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetCenter_dispatchSuccessfulMessage(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetCenter_sendCommand(JSContext *cx, uint32_t argc, jsval *vp);
bool js_mwframework_MWNetCenter_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
#endif

