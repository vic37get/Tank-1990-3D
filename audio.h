//Implementa as coisas reltivas ao audio
#ifndef AUDIO_H
#define AUDIO_H
#include <mmsystem.h>

bool startGame = false;
bool gameOverAudio = false;
bool explosion = false;
bool atiraAudio = false;
bool audioLife = false;
bool audioApareceBonus = false;
bool audioPegaBonus = false;
bool audioHitMetal = false;

void playAudio(){
	if(startGame == false){
		mciSendString("play sounds/gamestart.wav", NULL, 0, NULL);
		startGame = true;
	}
	
	if(audioLife){
		mciSendString("play sounds/life.wav", NULL, 0, NULL);
		audioLife = false;
		audioPegaBonus = false;
	}
	
	if(audioHitMetal){
		mciSendString("play sounds/hitMetal.wav", NULL, 0, NULL);
		audioHitMetal = false;
	}
	
	if(audioPegaBonus){
		mciSendString("play sounds/pegaBonus.wav", NULL, 0, NULL);
		audioPegaBonus = false;
	}
	
	if(audioApareceBonus){
		mciSendString("play sounds/bonusAparecendo.wav", NULL, 0, NULL);
		audioApareceBonus = false;
	}
	
	if(gameOverAudio){
		mciSendString("play sounds/gameover.wav", NULL, 0, NULL);
		gameOverAudio = false;
	}
	
	if(explosion){
		mciSendString("play sounds/explosion.wav", NULL, 0, NULL);
		explosion = false;
	}
	
	if(atiraAudio){
		mciSendString("play sounds/fire.wav", NULL, 0, NULL);
		atiraAudio = false;
	}
}

#endif