#pragma once
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>
#include <SDL_mixer.h>
class App;

class AudioManager
{

public:
	AudioManager(App* app);
	AudioManager(int channels, App* app);

	virtual ~AudioManager();

	//SFX
	Mix_Chunk* loadSFX(const std::string& fileName);
	virtual void playSFX(Mix_Chunk* sound, int loops, int channel = -1);

	// music
	Mix_Music* loadMusic(const std::string& fileName);
	void playMusic(Mix_Music* music, bool loops);
	
    virtual int setSFXVolume( int volume);
	virtual int setMusicVolume(int volume);
	
	void stopMusic();
	virtual void pauseMusic();
	virtual bool pausedMusic();
	void silenceMusic();

	virtual void resumeMusic();
	void resumeAll();
	void resumeChannel(int channel);
	//void playChunk(int channel,Mix_Chunk* music, bool loops);
	//void pauseChannel(int channel);
	//int getGeneralVolume() const;
	int getMusicVolume() const;
	int getSFXVolume() const;
	//bool isSilenced() { return silenced; }

	//for settings
	//void setGeneralVolume(float MaxVolume, float volume_ratio);
	//void setChannelvolume(int channel, float volume_ratio);

private:
	App* app_;
	bool initialized_ = false;
	int channels_ = -1;
	int startGeneralVolume = 20, startSFXVolume = 20;
	int volumeSFX = startSFXVolume;
	
	bool silenced=false;
};

