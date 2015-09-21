//
//  AudioEngine.cpp
//  PokemonRPG
//
//  Created by Xin Wan on 9/21/15.
//
//

#include "GameAudioEngine.h"

#include "cocos2d.h"
#include "AudioEngine.h"

using namespace cocos2d::experimental;

GAME_NS_BEGIN

GameAudioEngine::GameAudioEngine()
{
    CCASSERT(AudioEngine::lazyInit(), "GameAudioEngine init failed.");
}

int GameAudioEngine::play2d(const std::string& filePath, bool loop, float volume)
{
    return AudioEngine::play2d(filePath, loop, volume);
}

void GameAudioEngine::setLoop(int audioID, bool loop)
{
    AudioEngine::setLoop(audioID, loop);
}

bool GameAudioEngine::isLoop(int audioID)
{
    return AudioEngine::isLoop(audioID);
}

void GameAudioEngine::setVolume(int audioID, float volume)
{
    AudioEngine::setVolume(audioID, volume);
}

float GameAudioEngine::getVolume(int audioID)
{
    return AudioEngine::getVolume(audioID);
}

void GameAudioEngine::pause(int audioID)
{
    AudioEngine::pause(audioID);
}

void GameAudioEngine::pauseAll()
{
    AudioEngine::pauseAll();
}

void GameAudioEngine::resume(int audioID)
{
    AudioEngine::resume(audioID);
}

void GameAudioEngine::resumeAll()
{
    AudioEngine::resumeAll();
}

void GameAudioEngine::stop(int audioID)
{
    AudioEngine::stop(audioID);
}

void GameAudioEngine::stopAll()
{
    AudioEngine::stopAll();
}

bool GameAudioEngine::setCurrentTime(int audioID, float sec)
{
    return AudioEngine::setCurrentTime(audioID, sec);
}

float GameAudioEngine::getCurrentTime(int audioID)
{
    return AudioEngine::getCurrentTime(audioID);
}

float GameAudioEngine::getDuration(int audioID)
{
    return AudioEngine::getDuration(audioID);
}

bool GameAudioEngine::setMaxAudioInstance(int maxInstances)
{
    return AudioEngine::setMaxAudioInstance(maxInstances);
}

int GameAudioEngine::getMaxAudioInstance()
{
    return AudioEngine::getMaxAudioInstance();
}

void GameAudioEngine::setFinishCallback(int audioID, const std::function<void (int, std::string)> &callback)
{
    AudioEngine::setFinishCallback(audioID, callback);
}

void GameAudioEngine::uncache(const std::string &filePath)
{
    AudioEngine::uncache(filePath);
}

void GameAudioEngine::uncacheAll()
{
    AudioEngine::uncacheAll();
}

GAME_NS_END