#include "MWNetFilter.h"

#include "cocos2d.h"
#include "MWNetResponse.h"
#if MW_ENABLE_SCRIPT_BINDING

#endif

#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWNetFilter *MWNetFilter::create()
{
    auto pRet = new (nothrow) MWNetFilter();
    if (pRet) {
        pRet->autorelease();
        return pRet;
    }
    return nullptr;
}

void MWNetFilter::filterSuccessfulMessage(mwframework::MWNetResponse *response)
{
#if MW_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        // lua todo
    } else if (_scriptType == kScriptTypeJavascript) {
        // todo js
    }
#endif
}

void MWNetFilter::filterFailedMessage(mwframework::MWNetResponse *response)
{
#if MW_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        // lua todo
    } else if (_scriptType == kScriptTypeJavascript) {
        // todo js
    }
#endif
}

MW_FRAMEWORK_END
