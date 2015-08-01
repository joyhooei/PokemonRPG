/**
 * @module mwframework
 */
var mw = mw || {};

/**
 * @class MWObject
 */
mw.MWObject = {

/**
 * @method toString
 * @return {String}
 */
toString : function (
)
{
    return ;
},

};

/**
 * @class MWBinaryData
 */
mw.MWBinaryData = {

/**
 * @method isValid
 * @return {bool}
 */
isValid : function (
)
{
    return false;
},

};

/**
 * @class MWException
 */
mw.MWException = {

/**
 * @method errorCode
 * @return {int}
 */
errorCode : function (
)
{
    return 0;
},

/**
 * @method what
 * @return {char}
 */
what : function (
)
{
    return 0;
},

/**
 * @method create
 * @param {int} arg0
 * @param {char} arg1
 * @return {mw.MWException}
 */
create : function (
int, 
char 
)
{
    return mw.MWException;
},

/**
 * @method MWException
 * @constructor
 * @param {int} arg0
 * @param {char} arg1
 */
MWException : function (
int, 
char 
)
{
},

};

/**
 * @class MWDictionary
 */
mw.MWDictionary = {

/**
 * @method count
 * @return {unsigned int}
 */
count : function (
)
{
    return 0;
},

/**
 * @method removeObjectForKey
 * @param {String} arg0
 * @return {bool}
 */
removeObjectForKey : function (
str 
)
{
    return false;
},

/**
 * @method clear
 */
clear : function (
)
{
},

/**
 * @method setObjectForKey
 * @param {String} arg0
 * @param {cc.Ref} arg1
 */
setObjectForKey : function (
str, 
ref 
)
{
},

/**
 * @method objectForKey
 * @param {String} arg0
 * @return {cc.Ref}
 */
objectForKey : function (
str 
)
{
    return cc.Ref;
},

/**
 * @method empty
 * @return {bool}
 */
empty : function (
)
{
    return false;
},

/**
 * @method hasKey
 * @param {String} arg0
 * @return {bool}
 */
hasKey : function (
str 
)
{
    return false;
},

/**
 * @method clone
 * @return {mw.MWDictionary}
 */
clone : function (
)
{
    return mw.MWDictionary;
},

/**
 * @method create
 * @return {mw.MWDictionary}
 */
create : function (
)
{
    return mw.MWDictionary;
},

/**
 * @method MWDictionary
 * @constructor
 */
MWDictionary : function (
)
{
},

};

/**
 * @class MWArrayList
 */
mw.MWArrayList = {

/**
 * @method count
 * @return {unsigned int}
 */
count : function (
)
{
    return 0;
},

/**
 * @method setObjectAtIndex
 * @param {cc.Ref} arg0
 * @param {unsigned int} arg1
 */
setObjectAtIndex : function (
ref, 
int 
)
{
},

/**
 * @method removeObjectAtIndex
 * @param {unsigned int} arg0
 * @return {bool}
 */
removeObjectAtIndex : function (
int 
)
{
    return false;
},

/**
 * @method appendObject
 * @param {cc.Ref} arg0
 */
appendObject : function (
ref 
)
{
},

/**
 * @method lastIndexOfObject
 * @param {cc.Ref} arg0
 * @return {unsigned int}
 */
lastIndexOfObject : function (
ref 
)
{
    return 0;
},

/**
 * @method indexOfObject
 * @param {cc.Ref} arg0
 * @return {unsigned int}
 */
indexOfObject : function (
ref 
)
{
    return 0;
},

/**
 * @method insertObjectAtIndex
 * @param {cc.Ref} arg0
 * @param {unsigned int} arg1
 */
insertObjectAtIndex : function (
ref, 
int 
)
{
},

/**
 * @method removeObject
 * @param {cc.Ref} arg0
 * @return {bool}
 */
removeObject : function (
ref 
)
{
    return false;
},

/**
 * @method clone
 * @return {mw.MWArrayList}
 */
clone : function (
)
{
    return mw.MWArrayList;
},

/**
 * @method clear
 */
clear : function (
)
{
},

/**
 * @method empty
 * @return {bool}
 */
empty : function (
)
{
    return false;
},

/**
 * @method objectAtIndex
 * @param {unsigned int} arg0
 * @return {cc.Ref}
 */
objectAtIndex : function (
int 
)
{
    return cc.Ref;
},

/**
 * @method create
 * @return {mw.MWArrayList}
 */
create : function (
)
{
    return mw.MWArrayList;
},

/**
 * @method MWArrayList
 * @constructor
 */
MWArrayList : function (
)
{
},

};

/**
 * @class MWQueue
 */
mw.MWQueue = {

/**
 * @method count
 * @return {unsigned int}
 */
count : function (
)
{
    return 0;
},

/**
 * @method dequeue
 * @return {bool}
 */
dequeue : function (
)
{
    return false;
},

/**
 * @method clear
 */
clear : function (
)
{
},

/**
 * @method enqueue
 * @param {cc.Ref} arg0
 */
enqueue : function (
ref 
)
{
},

/**
 * @method front
 * @return {cc.Ref}
 */
front : function (
)
{
    return cc.Ref;
},

/**
 * @method clone
 * @return {mw.MWQueue}
 */
clone : function (
)
{
    return mw.MWQueue;
},

/**
 * @method empty
 * @return {bool}
 */
empty : function (
)
{
    return false;
},

/**
 * @method create
 * @return {mw.MWQueue}
 */
create : function (
)
{
    return mw.MWQueue;
},

/**
 * @method MWQueue
 * @constructor
 */
MWQueue : function (
)
{
},

};

/**
 * @class MWStack
 */
mw.MWStack = {

/**
 * @method count
 * @return {unsigned int}
 */
count : function (
)
{
    return 0;
},

/**
 * @method top
 * @return {cc.Ref}
 */
top : function (
)
{
    return cc.Ref;
},

/**
 * @method pop
 * @return {bool}
 */
pop : function (
)
{
    return false;
},

/**
 * @method push
 * @param {cc.Ref} arg0
 */
push : function (
ref 
)
{
},

/**
 * @method clone
 * @return {mw.MWStack}
 */
clone : function (
)
{
    return mw.MWStack;
},

/**
 * @method clear
 */
clear : function (
)
{
},

/**
 * @method empty
 * @return {bool}
 */
empty : function (
)
{
    return false;
},

/**
 * @method create
 * @return {mw.MWStack}
 */
create : function (
)
{
    return mw.MWStack;
},

/**
 * @method MWStack
 * @constructor
 */
MWStack : function (
)
{
},

};

/**
 * @class MWSystemHelper
 */
mw.MWSystemHelper = {

/**
 * @method checkNetStatus
 * @return {mw.ENetStatus}
 */
checkNetStatus : function (
)
{
    return 0;
},

/**
 * @method getCurrentUsedMemory
 * @return {double}
 */
getCurrentUsedMemory : function (
)
{
    return 0;
},

/**
 * @method millisecondsNow
 * @return {unsigned long}
 */
millisecondsNow : function (
)
{
    return 0;
},

/**
 * @method copyToPasteBoard
 * @param {String} arg0
 */
copyToPasteBoard : function (
str 
)
{
},

/**
 * @method getInstance
 * @return {mw.MWSystemHelper}
 */
getInstance : function (
)
{
    return mw.MWSystemHelper;
},

};

/**
 * @class MWIOUtils
 */
mw.MWIOUtils = {

/**
 * @method fileExists
 * @param {String} arg0
 * @return {bool}
 */
fileExists : function (
str 
)
{
    return false;
},

/**
 * @method copyFile
 * @param {String} arg0
 * @param {String} arg1
 * @return {bool}
 */
copyFile : function (
str, 
str 
)
{
    return false;
},

/**
 * @method writeDataToFile
 * @param {void} arg0
 * @param {unsigned long} arg1
 * @param {String} arg2
 * @param {bool} arg3
 * @return {bool}
 */
writeDataToFile : function (
void, 
long, 
str, 
bool 
)
{
    return false;
},

/**
 * @method getDataFromFile
 * @param {String} arg0
 * @return {mw.MWBinaryData}
 */
getDataFromFile : function (
str 
)
{
    return mw.MWBinaryData;
},

/**
 * @method splicePath
 * @param {String} arg0
 * @param {String} arg1
 * @return {String}
 */
splicePath : function (
str, 
str 
)
{
    return ;
},

/**
 * @method createFile
 * @param {String} arg0
 * @return {bool}
 */
createFile : function (
str 
)
{
    return false;
},

/**
 * @method resourcePath
 * @param {String} arg0
 * @return {String}
 */
resourcePath : function (
str 
)
{
    return ;
},

/**
 * @method removeFile
 * @param {String} arg0
 * @return {bool}
 */
removeFile : function (
str 
)
{
    return false;
},

/**
 * @method moveFile
 * @param {String} arg0
 * @param {String} arg1
 * @return {bool}
 */
moveFile : function (
str, 
str 
)
{
    return false;
},

/**
 * @method createDirectory
 * @param {String} arg0
 * @return {bool}
 */
createDirectory : function (
str 
)
{
    return false;
},

/**
 * @method getInstance
 * @return {mw.MWIOUtils}
 */
getInstance : function (
)
{
    return mw.MWIOUtils;
},

};

/**
 * @class MWGameScene
 */
mw.MWGameScene = {

/**
 * @method getViewControllers
 * @return {mw.MWDictionary}
 */
getViewControllers : function (
)
{
    return mw.MWDictionary;
},

/**
 * @method unloadViewController
 * @param {mw.MWViewController} arg0
 */
unloadViewController : function (
mwviewcontroller 
)
{
},

/**
 * @method loadViewController
 * @param {mw.MWViewController} arg0
 * @param {String} arg1
 */
loadViewController : function (
mwviewcontroller, 
str 
)
{
},

/**
 * @method getViewControllerByIdentifier
 * @param {String} arg0
 * @return {mw.MWViewController}
 */
getViewControllerByIdentifier : function (
str 
)
{
    return mw.MWViewController;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method getBooleanParameter
 * @param {String} arg0
 * @return {bool}
 */
getBooleanParameter : function (
str 
)
{
    return false;
},

/**
 * @method unloadAllViewControllers
 */
unloadAllViewControllers : function (
)
{
},

/**
 * @method addParameter
* @param {String|String|String|String} str
* @param {bool|double|String|cc.Ref} bool
*/
addParameter : function(
str,
ref 
)
{
},

/**
 * @method getRefParameter
 * @param {String} arg0
 * @return {cc.Ref}
 */
getRefParameter : function (
str 
)
{
    return cc.Ref;
},

/**
 * @method getMemoryWarningLine
 * @return {double}
 */
getMemoryWarningLine : function (
)
{
    return 0;
},

/**
 * @method setMemoryWarningLine
 * @param {double} arg0
 */
setMemoryWarningLine : function (
double 
)
{
},

/**
 * @method getStringParameter
 * @param {String} arg0
 * @return {String}
 */
getStringParameter : function (
str 
)
{
    return ;
},

/**
 * @method unloadViewControllerByIdentifier
 * @param {String} arg0
 */
unloadViewControllerByIdentifier : function (
str 
)
{
},

/**
 * @method getNumberParameter
 * @param {String} arg0
 * @return {double}
 */
getNumberParameter : function (
str 
)
{
    return 0;
},

/**
 * @method create
 * @return {mw.MWGameScene}
 */
create : function (
)
{
    return mw.MWGameScene;
},

/**
 * @method MWGameScene
 * @constructor
 */
MWGameScene : function (
)
{
},

};

/**
 * @class MWViewController
 */
mw.MWViewController = {

/**
 * @method init
 * @param {mw.MWViewSegue} arg0
 * @return {bool}
 */
init : function (
mwviewsegue 
)
{
    return false;
},

/**
 * @method segue
 * @return {mw.MWViewSegue}
 */
segue : function (
)
{
    return mw.MWViewSegue;
},

/**
 * @method scene
 * @return {mw.MWGameScene}
 */
scene : function (
)
{
    return mw.MWGameScene;
},

/**
 * @method getIdentifier
 * @return {String}
 */
getIdentifier : function (
)
{
    return ;
},

/**
 * @method view
 * @return {mw.MWGameView}
 */
view : function (
)
{
    return mw.MWGameView;
},

/**
 * @method create
 * @return {mw.MWViewController}
 */
create : function (
)
{
    return mw.MWViewController;
},

/**
 * @method MWViewController
 * @constructor
 */
MWViewController : function (
)
{
},

};

/**
 * @class MWGameView
 */
mw.MWGameView = {

/**
 * @method create
 * @return {mw.MWGameView}
 */
create : function (
)
{
    return mw.MWGameView;
},

};

/**
 * @class MWViewSegue
 */
mw.MWViewSegue = {

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method create
 * @return {mw.MWViewSegue}
 */
create : function (
)
{
    return mw.MWViewSegue;
},

/**
 * @method MWViewSegue
 * @constructor
 */
MWViewSegue : function (
)
{
},

};

/**
 * @class MWSqliteDb
 */
mw.MWSqliteDb = {

/**
 * @method executeNonQuery
 * @param {String} arg0
 * @return {bool}
 */
executeNonQuery : function (
str 
)
{
    return false;
},

/**
 * @method endTransaction
 * @param {bool} arg0
 * @return {bool}
 */
endTransaction : function (
bool 
)
{
    return false;
},

/**
 * @method beginTransaction
 * @return {bool}
 */
beginTransaction : function (
)
{
    return false;
},

/**
 * @method openDb
 * @param {String} arg0
 * @return {mw.MWSqliteDb}
 */
openDb : function (
str 
)
{
    return mw.MWSqliteDb;
},

/**
 * @method clearConnectionCache
 */
clearConnectionCache : function (
)
{
},

};

/**
 * @class MWZipData
 */
mw.MWZipData = {

/**
 * @method getCompressedFileData
 * @param {String} arg0
 * @param {String} arg1
 * @return {mw.MWBinaryData}
 */
getCompressedFileData : function (
str, 
str 
)
{
    return mw.MWBinaryData;
},

/**
 * @method zipNewFile
 * @param {String} arg0
 * @param {mw.MWBinaryData} arg1
 * @param {String} arg2
 * @param {int} arg3
 * @return {bool}
 */
zipNewFile : function (
str, 
mwbinarydata, 
str, 
int 
)
{
    return false;
},

/**
 * @method beginUnzip
 */
beginUnzip : function (
)
{
},

/**
 * @method endUnzip
 */
endUnzip : function (
)
{
},

/**
 * @method beginZip
 */
beginZip : function (
)
{
},

/**
 * @method endZip
 */
endZip : function (
)
{
},

/**
 * @method createWithExistingFile
 * @param {String} arg0
 * @return {mw.MWZipData}
 */
createWithExistingFile : function (
str 
)
{
    return mw.MWZipData;
},

/**
 * @method createWithNewFile
 * @param {String} arg0
 * @return {mw.MWZipData}
 */
createWithNewFile : function (
str 
)
{
    return mw.MWZipData;
},

};

/**
 * @class MWGifFrame
 */
mw.MWGifFrame = {

/**
 * @method setSpriteFrame
 * @param {cc.SpriteFrame} arg0
 */
setSpriteFrame : function (
spriteframe 
)
{
},

/**
 * @method setDuration
 * @param {unsigned int} arg0
 */
setDuration : function (
int 
)
{
},

/**
 * @method getSpriteFrame
 * @return {cc.SpriteFrame}
 */
getSpriteFrame : function (
)
{
    return cc.SpriteFrame;
},

/**
 * @method getDuration
 * @return {unsigned int}
 */
getDuration : function (
)
{
    return 0;
},

/**
 * @method create
 * @param {cc.SpriteFrame} arg0
 * @param {unsigned int} arg1
 * @return {mw.MWGifFrame}
 */
create : function (
spriteframe, 
int 
)
{
    return mw.MWGifFrame;
},

};

/**
 * @class MWGifSprite
 */
mw.MWGifSprite = {

/**
 * @method play
 */
play : function (
)
{
},

/**
 * @method pause
 */
pause : function (
)
{
},

/**
 * @method setSpeedRatio
 * @param {float} arg0
 */
setSpeedRatio : function (
float 
)
{
},

/**
 * @method getSpriteFrameAtIndex
 * @param {int} arg0
 * @return {cc.SpriteFrame}
 */
getSpriteFrameAtIndex : function (
int 
)
{
    return cc.SpriteFrame;
},

/**
 * @method resume
 */
resume : function (
)
{
},

/**
 * @method getSpeedRatio
 * @return {float}
 */
getSpeedRatio : function (
)
{
    return 0;
},

/**
 * @method stop
 */
stop : function (
)
{
},

/**
 * @method createWithFile
 * @param {String} arg0
 * @return {mw.MWGifSprite}
 */
createWithFile : function (
str 
)
{
    return mw.MWGifSprite;
},

/**
 * @method createWithFrames
 * @param {mw.MWArrayList} arg0
 * @return {mw.MWGifSprite}
 */
createWithFrames : function (
mwarraylist 
)
{
    return mw.MWGifSprite;
},

/**
 * @method createWithRawData
 * @param {mw.MWBinaryData} arg0
 * @return {mw.MWGifSprite}
 */
createWithRawData : function (
mwbinarydata 
)
{
    return mw.MWGifSprite;
},

};

/**
 * @class MWGifFramesCache
 */
mw.MWGifFramesCache = {

/**
 * @method removeAll
 */
removeAll : function (
)
{
},

/**
 * @method addGifFramesCache
* @param {mw.MWBinaryData|String|mw.MWGifSprite|mw.MWArrayList} mwbinarydata
* @param {String|String|String} str
*/
addGifFramesCache : function(
mwarraylist,
str 
)
{
},

/**
 * @method getGifSprite
 * @param {String} arg0
 * @return {mw.MWGifSprite}
 */
getGifSprite : function (
str 
)
{
    return mw.MWGifSprite;
},

/**
 * @method removeGifFramesCache
 * @param {String} arg0
 */
removeGifFramesCache : function (
str 
)
{
},

/**
 * @method getInstance
 * @return {mw.MWGifFramesCache}
 */
getInstance : function (
)
{
    return mw.MWGifFramesCache;
},

};

/**
 * @class MWSvgSprite
 */
mw.MWSvgSprite = {

/**
 * @method setVectorScale
 * @param {float} arg0
 */
setVectorScale : function (
float 
)
{
},

/**
 * @method getVectorScale
 * @return {float}
 */
getVectorScale : function (
)
{
    return 0;
},

/**
 * @method createWithFile
 * @param {String} arg0
 * @param {float} arg1
 * @return {mw.MWSvgSprite}
 */
createWithFile : function (
str, 
float 
)
{
    return mw.MWSvgSprite;
},

/**
 * @method createWithRawData
 * @param {mw.MWBinaryData} arg0
 * @param {float} arg1
 * @return {mw.MWSvgSprite}
 */
createWithRawData : function (
mwbinarydata, 
float 
)
{
    return mw.MWSvgSprite;
},

};

/**
 * @class MWJsonObject
 */
mw.MWJsonObject = {

/**
 * @method count
 * @return {unsigned int}
 */
count : function (
)
{
    return 0;
},

/**
 * @method getJsonArray
 * @param {String} arg0
 * @return {mw.MWJsonArray}
 */
getJsonArray : function (
str 
)
{
    return mw.MWJsonArray;
},

/**
 * @method getBoolean
 * @param {String} arg0
 * @return {bool}
 */
getBoolean : function (
str 
)
{
    return false;
},

/**
 * @method putBoolean
 * @param {String} arg0
 * @param {bool} arg1
 */
putBoolean : function (
str, 
bool 
)
{
},

/**
 * @method getString
 * @param {String} arg0
 * @return {char}
 */
getString : function (
str 
)
{
    return 0;
},

/**
 * @method getNumber
 * @param {String} arg0
 * @return {double}
 */
getNumber : function (
str 
)
{
    return 0;
},

/**
 * @method putJsonArray
 * @param {String} arg0
 * @param {mw.MWJsonArray} arg1
 */
putJsonArray : function (
str, 
mwjsonarray 
)
{
},

/**
 * @method putJsonObject
 * @param {String} arg0
 * @param {mw.MWJsonObject} arg1
 */
putJsonObject : function (
str, 
mwjsonobject 
)
{
},

/**
 * @method clear
 */
clear : function (
)
{
},

/**
 * @method toLuaString
 * @return {String}
 */
toLuaString : function (
)
{
    return ;
},

/**
 * @method putNumber
 * @param {String} arg0
 * @param {double} arg1
 */
putNumber : function (
str, 
double 
)
{
},

/**
 * @method remove
 * @param {String} arg0
 */
remove : function (
str 
)
{
},

/**
 * @method putString
 * @param {String} arg0
 * @param {String} arg1
 */
putString : function (
str, 
str 
)
{
},

/**
 * @method getJsonObject
 * @param {String} arg0
 * @return {mw.MWJsonObject}
 */
getJsonObject : function (
str 
)
{
    return mw.MWJsonObject;
},

/**
 * @method toPrettyString
 * @return {String}
 */
toPrettyString : function (
)
{
    return ;
},

/**
 * @method hasKey
 * @param {String} arg0
 * @return {bool}
 */
hasKey : function (
str 
)
{
    return false;
},

/**
 * @method getObject
 * @param {String} arg0
 * @return {mw.MWObject}
 */
getObject : function (
str 
)
{
    return mw.MWObject;
},

/**
 * @method createWithFile
 * @param {String} arg0
 * @return {mw.MWJsonObject}
 */
createWithFile : function (
str 
)
{
    return mw.MWJsonObject;
},

/**
 * @method create
 * @return {mw.MWJsonObject}
 */
create : function (
)
{
    return mw.MWJsonObject;
},

/**
 * @method createWithString
 * @param {String} arg0
 * @return {mw.MWJsonObject}
 */
createWithString : function (
str 
)
{
    return mw.MWJsonObject;
},

};

/**
 * @class MWJsonArray
 */
mw.MWJsonArray = {

/**
 * @method count
 * @return {unsigned int}
 */
count : function (
)
{
    return 0;
},

/**
 * @method getObjectAt
 * @param {unsigned int} arg0
 * @return {mw.MWObject}
 */
getObjectAt : function (
int 
)
{
    return mw.MWObject;
},

/**
 * @method toPrettyString
 * @return {String}
 */
toPrettyString : function (
)
{
    return ;
},

/**
 * @method getStringAt
 * @param {unsigned int} arg0
 * @return {char}
 */
getStringAt : function (
int 
)
{
    return 0;
},

/**
 * @method insertJsonArray
 * @param {mw.MWJsonArray} arg0
 * @param {unsigned int} arg1
 */
insertJsonArray : function (
mwjsonarray, 
int 
)
{
},

/**
 * @method appendJsonArray
 * @param {mw.MWJsonArray} arg0
 */
appendJsonArray : function (
mwjsonarray 
)
{
},

/**
 * @method insertJsonObject
 * @param {mw.MWJsonObject} arg0
 * @param {unsigned int} arg1
 */
insertJsonObject : function (
mwjsonobject, 
int 
)
{
},

/**
 * @method clear
 */
clear : function (
)
{
},

/**
 * @method appendJsonObject
 * @param {mw.MWJsonObject} arg0
 */
appendJsonObject : function (
mwjsonobject 
)
{
},

/**
 * @method insertNumber
 * @param {double} arg0
 * @param {unsigned int} arg1
 */
insertNumber : function (
double, 
int 
)
{
},

/**
 * @method removeAt
 * @param {unsigned int} arg0
 */
removeAt : function (
int 
)
{
},

/**
 * @method appendNumber
 * @param {double} arg0
 */
appendNumber : function (
double 
)
{
},

/**
 * @method appendBoolean
 * @param {bool} arg0
 */
appendBoolean : function (
bool 
)
{
},

/**
 * @method toLuaString
 * @return {String}
 */
toLuaString : function (
)
{
    return ;
},

/**
 * @method getBooleanAt
 * @param {int} arg0
 * @return {bool}
 */
getBooleanAt : function (
int 
)
{
    return false;
},

/**
 * @method insertString
 * @param {String} arg0
 * @param {int} arg1
 */
insertString : function (
str, 
int 
)
{
},

/**
 * @method getJsonArrayAt
 * @param {unsigned int} arg0
 * @return {mw.MWJsonArray}
 */
getJsonArrayAt : function (
int 
)
{
    return mw.MWJsonArray;
},

/**
 * @method appendString
 * @param {String} arg0
 */
appendString : function (
str 
)
{
},

/**
 * @method insertBoolean
 * @param {bool} arg0
 * @param {unsigned int} arg1
 */
insertBoolean : function (
bool, 
int 
)
{
},

/**
 * @method getNumberAt
 * @param {unsigned int} arg0
 * @return {double}
 */
getNumberAt : function (
int 
)
{
    return 0;
},

/**
 * @method getJsonObjectAt
 * @param {unsigned int} arg0
 * @return {mw.MWJsonObject}
 */
getJsonObjectAt : function (
int 
)
{
    return mw.MWJsonObject;
},

/**
 * @method createWithFile
 * @param {String} arg0
 * @return {mw.MWJsonArray}
 */
createWithFile : function (
str 
)
{
    return mw.MWJsonArray;
},

/**
 * @method create
 * @return {mw.MWJsonArray}
 */
create : function (
)
{
    return mw.MWJsonArray;
},

/**
 * @method createWithString
 * @param {String} arg0
 * @return {mw.MWJsonArray}
 */
createWithString : function (
str 
)
{
    return mw.MWJsonArray;
},

};

/**
 * @class MWUUIDGenerator
 */
mw.MWUUIDGenerator = {

/**
 * @method generateUUID
 * @return {String}
 */
generateUUID : function (
)
{
    return ;
},

/**
 * @method getInstance
 * @return {mw.MWUUIDGenerator}
 */
getInstance : function (
)
{
    return mw.MWUUIDGenerator;
},

};

/**
 * @class MWNetHandler
 */
mw.MWNetHandler = {

/**
 * @method create
 * @return {mw.MWNetHandler}
 */
create : function (
)
{
    return mw.MWNetHandler;
},

};

/**
 * @class MWNetRequest
 */
mw.MWNetRequest = {

/**
 * @method getProtocolId
 * @return {String}
 */
getProtocolId : function (
)
{
    return ;
},

/**
 * @method setBody
 * @param {String} arg0
 */
setBody : function (
str 
)
{
},

/**
 * @method setProtocolId
 * @param {String} arg0
 */
setProtocolId : function (
str 
)
{
},

/**
 * @method getBody
 * @return {String}
 */
getBody : function (
)
{
    return ;
},

/**
 * @method create
 * @param {String} arg0
 * @param {String} arg1
 * @return {mw.MWNetRequest}
 */
create : function (
str, 
str 
)
{
    return mw.MWNetRequest;
},

};

/**
 * @class MWNetResponse
 */
mw.MWNetResponse = {

/**
 * @method getRelatedRequest
 * @return {mw.MWNetRequest}
 */
getRelatedRequest : function (
)
{
    return mw.MWNetRequest;
},

/**
 * @method getProtocolId
 * @return {String}
 */
getProtocolId : function (
)
{
    return ;
},

/**
 * @method setBody
 * @param {String} arg0
 */
setBody : function (
str 
)
{
},

/**
 * @method setProtocolId
 * @param {String} arg0
 */
setProtocolId : function (
str 
)
{
},

/**
 * @method getBody
 * @return {String}
 */
getBody : function (
)
{
    return ;
},

/**
 * @method create
 * @param {String} arg0
 * @param {String} arg1
 * @param {mw.MWNetRequest} arg2
 * @return {mw.MWNetResponse}
 */
create : function (
str, 
str, 
mwnetrequest 
)
{
    return mw.MWNetResponse;
},

};

/**
 * @class MWNetProtocol
 */
mw.MWNetProtocol = {

/**
 * @method getRelatedHandler
 * @return {mw.MWNetHandler}
 */
getRelatedHandler : function (
)
{
    return mw.MWNetHandler;
},

/**
 * @method getServiceId
 * @return {String}
 */
getServiceId : function (
)
{
    return ;
},

/**
 * @method getProtocolId
 * @return {String}
 */
getProtocolId : function (
)
{
    return ;
},

/**
 * @method setServiceId
 * @param {String} arg0
 */
setServiceId : function (
str 
)
{
},

/**
 * @method setProtocolId
 * @param {String} arg0
 */
setProtocolId : function (
str 
)
{
},

/**
 * @method create
 * @param {String} arg0
 * @param {String} arg1
 * @param {mw.MWNetHandler} arg2
 * @return {mw.MWNetProtocol}
 */
create : function (
str, 
str, 
mwnethandler 
)
{
    return mw.MWNetProtocol;
},

};

/**
 * @class MWNetCenter
 */
mw.MWNetCenter = {

/**
 * @method addNetService
 * @param {String} arg0
 * @param {mw.MWNetService} arg1
 */
addNetService : function (
str, 
mwnetservice 
)
{
},

/**
 * @method removeAllNetFilters
 */
removeAllNetFilters : function (
)
{
},

/**
 * @method addNetFilter
 * @param {mw.MWNetFilter} arg0
 */
addNetFilter : function (
mwnetfilter 
)
{
},

/**
 * @method removeNetProtocol
 * @param {String} arg0
 */
removeNetProtocol : function (
str 
)
{
},

/**
 * @method removeNetFilter
 * @param {mw.MWNetFilter} arg0
 */
removeNetFilter : function (
mwnetfilter 
)
{
},

/**
 * @method removeNetService
 * @param {String} arg0
 */
removeNetService : function (
str 
)
{
},

/**
 * @method sendMessage
 * @param {mw.MWNetRequest} arg0
 */
sendMessage : function (
mwnetrequest 
)
{
},

/**
 * @method addNetProtocol
* @param {mw.MWNetProtocol|String} mwnetprotocol
* @param {String} str
* @param {mw.MWNetHandler} mwnethandler
*/
addNetProtocol : function(
str,
str,
mwnethandler 
)
{
},

/**
 * @method dispatchFailedMessage
 * @param {mw.MWNetResponse} arg0
 */
dispatchFailedMessage : function (
mwnetresponse 
)
{
},

/**
 * @method dispatchSuccessfulMessage
 * @param {mw.MWNetResponse} arg0
 */
dispatchSuccessfulMessage : function (
mwnetresponse 
)
{
},

/**
 * @method sendCommand
 * @param {String} arg0
 * @param {String} arg1
 * @param {cc.Ref} arg2
 */
sendCommand : function (
str, 
str, 
ref 
)
{
},

/**
 * @method getInstance
 * @return {mw.MWNetCenter}
 */
getInstance : function (
)
{
    return mw.MWNetCenter;
},

};
