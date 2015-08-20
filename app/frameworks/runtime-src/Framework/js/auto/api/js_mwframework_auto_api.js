/**
 * @module mwframework
 */
var mw = mw || {};

/**
 * @class MWObject
 */
mw.Object = {

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
mw.BinaryData = {

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
mw.Exception = {

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
 * @return {mw.Exception}
 */
create : function (
int, 
char 
)
{
    return mw.Exception;
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
mw.Dictionary = {

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
 * @return {mw.Dictionary}
 */
clone : function (
)
{
    return mw.Dictionary;
},

/**
 * @method create
 * @return {mw.Dictionary}
 */
create : function (
)
{
    return mw.Dictionary;
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
mw.ArrayList = {

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
 * @return {mw.ArrayList}
 */
clone : function (
)
{
    return mw.ArrayList;
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
 * @return {mw.ArrayList}
 */
create : function (
)
{
    return mw.ArrayList;
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
mw.Queue = {

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
 * @return {mw.Queue}
 */
clone : function (
)
{
    return mw.Queue;
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
 * @return {mw.Queue}
 */
create : function (
)
{
    return mw.Queue;
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
mw.Stack = {

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
 * @return {mw.Stack}
 */
clone : function (
)
{
    return mw.Stack;
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
 * @return {mw.Stack}
 */
create : function (
)
{
    return mw.Stack;
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
mw.SystemHelper = {

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
 * @return {mw.SystemHelper}
 */
getInstance : function (
)
{
    return mw.SystemHelper;
},

};

/**
 * @class MWIOUtils
 */
mw.IOUtils = {

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
 * @return {mw.BinaryData}
 */
getDataFromFile : function (
str 
)
{
    return mw.BinaryData;
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
 * @return {mw.IOUtils}
 */
getInstance : function (
)
{
    return mw.IOUtils;
},

};

/**
 * @class MWGameScene
 */
mw.GameScene = {

/**
 * @method getViewControllers
 * @return {mw.Dictionary}
 */
getViewControllers : function (
)
{
    return mw.Dictionary;
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
 * @method unloadViewController
 * @param {mw.ViewController} arg0
 */
unloadViewController : function (
mwviewcontroller 
)
{
},

/**
 * @method loadViewController
 * @param {mw.ViewController} arg0
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
 * @return {mw.ViewController}
 */
getViewControllerByIdentifier : function (
str 
)
{
    return mw.ViewController;
},

/**
 * @method getParameter
 * @param {String} arg0
 * @return {String}
 */
getParameter : function (
str 
)
{
    return ;
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
 * @param {String} arg0
 * @param {String} arg1
 */
addParameter : function (
str, 
str 
)
{
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
 * @method unloadViewControllerByIdentifier
 * @param {String} arg0
 */
unloadViewControllerByIdentifier : function (
str 
)
{
},

/**
 * @method create
 * @return {mw.GameScene}
 */
create : function (
)
{
    return mw.GameScene;
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
mw.ViewController = {

/**
 * @method init
 * @param {mw.ViewSegue} arg0
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
 * @return {mw.ViewSegue}
 */
segue : function (
)
{
    return mw.ViewSegue;
},

/**
 * @method scene
 * @return {mw.GameScene}
 */
scene : function (
)
{
    return mw.GameScene;
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
 * @return {mw.GameView}
 */
view : function (
)
{
    return mw.GameView;
},

/**
 * @method create
 * @return {mw.ViewController}
 */
create : function (
)
{
    return mw.ViewController;
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
mw.GameView = {

/**
 * @method create
 * @return {mw.GameView}
 */
create : function (
)
{
    return mw.GameView;
},

};

/**
 * @class MWViewSegue
 */
mw.ViewSegue = {

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
 * @return {mw.ViewSegue}
 */
create : function (
)
{
    return mw.ViewSegue;
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
mw.SqliteDb = {

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
 * @return {mw.SqliteDb}
 */
openDb : function (
str 
)
{
    return mw.SqliteDb;
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
mw.ZipData = {

/**
 * @method getCompressedFileData
 * @param {String} arg0
 * @param {String} arg1
 * @return {mw.BinaryData}
 */
getCompressedFileData : function (
str, 
str 
)
{
    return mw.BinaryData;
},

/**
 * @method zipNewFile
 * @param {String} arg0
 * @param {mw.BinaryData} arg1
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
 * @return {mw.ZipData}
 */
createWithExistingFile : function (
str 
)
{
    return mw.ZipData;
},

/**
 * @method createWithNewFile
 * @param {String} arg0
 * @return {mw.ZipData}
 */
createWithNewFile : function (
str 
)
{
    return mw.ZipData;
},

};

/**
 * @class MWGifFrame
 */
mw.GifFrame = {

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
 * @return {mw.GifFrame}
 */
create : function (
spriteframe, 
int 
)
{
    return mw.GifFrame;
},

};

/**
 * @class MWGifSprite
 */
mw.GifSprite = {

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
 * @return {mw.GifSprite}
 */
createWithFile : function (
str 
)
{
    return mw.GifSprite;
},

/**
 * @method createWithFrames
 * @param {mw.ArrayList} arg0
 * @return {mw.GifSprite}
 */
createWithFrames : function (
mwarraylist 
)
{
    return mw.GifSprite;
},

/**
 * @method createWithRawData
 * @param {mw.BinaryData} arg0
 * @return {mw.GifSprite}
 */
createWithRawData : function (
mwbinarydata 
)
{
    return mw.GifSprite;
},

};

/**
 * @class MWGifFramesCache
 */
mw.GifFramesCache = {

/**
 * @method removeAll
 */
removeAll : function (
)
{
},

/**
 * @method addGifFramesCache
* @param {mw.BinaryData|String|mw.GifSprite|mw.ArrayList} mwbinarydata
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
 * @return {mw.GifSprite}
 */
getGifSprite : function (
str 
)
{
    return mw.GifSprite;
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
 * @return {mw.GifFramesCache}
 */
getInstance : function (
)
{
    return mw.GifFramesCache;
},

};

/**
 * @class MWSvgSprite
 */
mw.SvgSprite = {

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
 * @return {mw.SvgSprite}
 */
createWithFile : function (
str, 
float 
)
{
    return mw.SvgSprite;
},

/**
 * @method createWithRawData
 * @param {mw.BinaryData} arg0
 * @param {float} arg1
 * @return {mw.SvgSprite}
 */
createWithRawData : function (
mwbinarydata, 
float 
)
{
    return mw.SvgSprite;
},

};

/**
 * @class MWJsonObject
 */
mw.JsonObject = {

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
 * @return {mw.JsonArray}
 */
getJsonArray : function (
str 
)
{
    return mw.JsonArray;
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
 * @param {mw.JsonArray} arg1
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
 * @param {mw.JsonObject} arg1
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
 * @return {mw.JsonObject}
 */
getJsonObject : function (
str 
)
{
    return mw.JsonObject;
},

/**
 * @method toJsString
 * @return {String}
 */
toJsString : function (
)
{
    return ;
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
 * @return {mw.Object}
 */
getObject : function (
str 
)
{
    return mw.Object;
},

/**
 * @method createWithFile
 * @param {String} arg0
 * @return {mw.JsonObject}
 */
createWithFile : function (
str 
)
{
    return mw.JsonObject;
},

/**
 * @method create
 * @return {mw.JsonObject}
 */
create : function (
)
{
    return mw.JsonObject;
},

/**
 * @method createWithString
 * @param {String} arg0
 * @return {mw.JsonObject}
 */
createWithString : function (
str 
)
{
    return mw.JsonObject;
},

};

/**
 * @class MWJsonArray
 */
mw.JsonArray = {

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
 * @return {mw.Object}
 */
getObjectAt : function (
int 
)
{
    return mw.Object;
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
 * @param {mw.JsonArray} arg0
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
 * @param {mw.JsonArray} arg0
 */
appendJsonArray : function (
mwjsonarray 
)
{
},

/**
 * @method insertJsonObject
 * @param {mw.JsonObject} arg0
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
 * @param {mw.JsonObject} arg0
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
 * @return {mw.JsonArray}
 */
getJsonArrayAt : function (
int 
)
{
    return mw.JsonArray;
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
 * @method toJsString
 * @return {String}
 */
toJsString : function (
)
{
    return ;
},

/**
 * @method getJsonObjectAt
 * @param {unsigned int} arg0
 * @return {mw.JsonObject}
 */
getJsonObjectAt : function (
int 
)
{
    return mw.JsonObject;
},

/**
 * @method createWithFile
 * @param {String} arg0
 * @return {mw.JsonArray}
 */
createWithFile : function (
str 
)
{
    return mw.JsonArray;
},

/**
 * @method create
 * @return {mw.JsonArray}
 */
create : function (
)
{
    return mw.JsonArray;
},

/**
 * @method createWithString
 * @param {String} arg0
 * @return {mw.JsonArray}
 */
createWithString : function (
str 
)
{
    return mw.JsonArray;
},

};

/**
 * @class MWUUIDGenerator
 */
mw.UUIDGenerator = {

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
 * @return {mw.UUIDGenerator}
 */
getInstance : function (
)
{
    return mw.UUIDGenerator;
},

};

/**
 * @class MWNetHandler
 */
mw.NetHandler = {

/**
 * @method create
 * @return {mw.NetHandler}
 */
create : function (
)
{
    return mw.NetHandler;
},

};

/**
 * @class MWNetRequest
 */
mw.NetRequest = {

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
 * @return {mw.NetRequest}
 */
create : function (
str, 
str 
)
{
    return mw.NetRequest;
},

};

/**
 * @class MWNetResponse
 */
mw.NetResponse = {

/**
 * @method getRelatedRequest
 * @return {mw.NetRequest}
 */
getRelatedRequest : function (
)
{
    return mw.NetRequest;
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
 * @param {mw.NetRequest} arg2
 * @return {mw.NetResponse}
 */
create : function (
str, 
str, 
mwnetrequest 
)
{
    return mw.NetResponse;
},

};

/**
 * @class MWNetProtocol
 */
mw.NetProtocol = {

/**
 * @method getRelatedHandler
 * @return {mw.NetHandler}
 */
getRelatedHandler : function (
)
{
    return mw.NetHandler;
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
 * @param {mw.NetHandler} arg2
 * @return {mw.NetProtocol}
 */
create : function (
str, 
str, 
mwnethandler 
)
{
    return mw.NetProtocol;
},

};

/**
 * @class MWNetCenter
 */
mw.NetCenter = {

/**
 * @method addNetService
 * @param {String} arg0
 * @param {mw.NetService} arg1
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
 * @param {mw.NetFilter} arg0
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
 * @param {mw.NetFilter} arg0
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
 * @param {mw.NetRequest} arg0
 */
sendMessage : function (
mwnetrequest 
)
{
},

/**
 * @method addNetProtocol
* @param {mw.NetProtocol|String} mwnetprotocol
* @param {String} str
* @param {mw.NetHandler} mwnethandler
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
 * @param {mw.NetResponse} arg0
 */
dispatchFailedMessage : function (
mwnetresponse 
)
{
},

/**
 * @method dispatchSuccessfulMessage
 * @param {mw.NetResponse} arg0
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
 * @return {mw.NetCenter}
 */
getInstance : function (
)
{
    return mw.NetCenter;
},

};
