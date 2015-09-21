//
//  AudioEngine.hpp
//  PokemonRPG
//
//  Created by Xin Wan on 9/21/15.
//
//

#ifndef AudioEngine_hpp
#define AudioEngine_hpp

#include "../GameMacros.h"
#include "../../../Framework/base/FrameworkMacros.h"
#include <string>
#include <functional>

GAME_NS_BEGIN

class GameAudioEngine
{
    MW_SINGLETON(GameAudioEngine);
public:
    int play2d(const std::string& filePath, bool loop = false, float volume = 1.0f);
    void setLoop(int audioID, bool loop);
    bool isLoop(int audioID);
    void setVolume(int audioID, float volume);
    float getVolume(int audioID);
    void pause(int audioID);
    void pauseAll();
    void resume(int audioID);
    void resumeAll();
    void stop(int audioID);
    void stopAll();
    bool setCurrentTime(int audioID, float sec);
    float getCurrentTime(int audioID);
    float getDuration(int audioID);
    bool setMaxAudioInstance(int maxInstances);
    int getMaxAudioInstance();
    void setFinishCallback(int audioID, const std::function<void(int, std::string)> &callback);
    void uncache(const std::string& filePath);
    void uncacheAll();
};

GAME_NS_END

#endif /* AudioEngine_hpp */
