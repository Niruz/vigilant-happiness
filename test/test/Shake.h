#pragma once
#include <vector>
struct Shake
{
	//milliseconds and hertz
	Shake(float duration, float frequency);


	//float RandomFloat(float a, float b);
	float Amplitude(float t = -1);
	float Noise(float s);
	float Decay(float t);

	void Start();
	void Update();

	float myDuration;
	float myFrequency;
	std::vector<float> mySamples;

	float myStartTime;
	float myT;

	bool myIsShaking;
};