/**
 * @module game_ext
 */
var ex = ex || {};

/**
 * @class UIProgressBy
 */
ex.UIProgressBy = {

/**
 * @method create
 * @param {float} arg0
 * @param {float} arg1
 * @return {ext.UIProgressBy}
 */
create : function (
float, 
float 
)
{
    return ext.UIProgressBy;
},

};

/**
 * @class UIProgressTo
 */
ex.UIProgressTo = {

/**
 * @method create
 * @param {float} arg0
 * @param {float} arg1
 * @return {ext.UIProgressTo}
 */
create : function (
float, 
float 
)
{
    return ext.UIProgressTo;
},

};

/**
 * @class UITextOneByOne
 */
ex.UITextOneByOne = {

};

/**
 * @class GameAudioEngine
 */
ex.GameAudioEngine = {

/**
 * @method play2d
 * @param {String} arg0
 * @param {bool} arg1
 * @param {float} arg2
 * @return {int}
 */
play2d : function (
str, 
bool, 
float 
)
{
    return 0;
},

/**
 * @method pause
 * @param {int} arg0
 */
pause : function (
int 
)
{
},

/**
 * @method getMaxAudioInstance
 * @return {int}
 */
getMaxAudioInstance : function (
)
{
    return 0;
},

/**
 * @method resume
 * @param {int} arg0
 */
resume : function (
int 
)
{
},

/**
 * @method setFinishCallback
 * @param {int} arg0
 * @param {function} arg1
 */
setFinishCallback : function (
int, 
func 
)
{
},

/**
 * @method uncache
 * @param {String} arg0
 */
uncache : function (
str 
)
{
},

/**
 * @method stop
 * @param {int} arg0
 */
stop : function (
int 
)
{
},

/**
 * @method setCurrentTime
 * @param {int} arg0
 * @param {float} arg1
 * @return {bool}
 */
setCurrentTime : function (
int, 
float 
)
{
    return false;
},

/**
 * @method getCurrentTime
 * @param {int} arg0
 * @return {float}
 */
getCurrentTime : function (
int 
)
{
    return 0;
},

/**
 * @method resumeAll
 */
resumeAll : function (
)
{
},

/**
 * @method setMaxAudioInstance
 * @param {int} arg0
 * @return {bool}
 */
setMaxAudioInstance : function (
int 
)
{
    return false;
},

/**
 * @method getVolume
 * @param {int} arg0
 * @return {float}
 */
getVolume : function (
int 
)
{
    return 0;
},

/**
 * @method isLoop
 * @param {int} arg0
 * @return {bool}
 */
isLoop : function (
int 
)
{
    return false;
},

/**
 * @method getDuration
 * @param {int} arg0
 * @return {float}
 */
getDuration : function (
int 
)
{
    return 0;
},

/**
 * @method pauseAll
 */
pauseAll : function (
)
{
},

/**
 * @method uncacheAll
 */
uncacheAll : function (
)
{
},

/**
 * @method setLoop
 * @param {int} arg0
 * @param {bool} arg1
 */
setLoop : function (
int, 
bool 
)
{
},

/**
 * @method stopAll
 */
stopAll : function (
)
{
},

/**
 * @method setVolume
 * @param {int} arg0
 * @param {float} arg1
 */
setVolume : function (
int, 
float 
)
{
},

/**
 * @method getInstance
 * @return {ext.GameAudioEngine}
 */
getInstance : function (
)
{
    return ext.GameAudioEngine;
},

};
