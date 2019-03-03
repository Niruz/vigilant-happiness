#include "SimpleTimer.h"
#include "Shake.h"
#include <math.h>
#include "glm\common.hpp"
#include "EngineUtilities.h"
Shake::Shake(float duration, float frequency)
	:myDuration(duration), myFrequency(frequency), myIsShaking(false)
{
	float sampleCount = (myDuration / 1000.0f) * myFrequency;


	//srand( 54);

	float min = -1;
	float max = 1;

	for (int i = 0; i < sampleCount; i++)
	{
		mySamples.push_back(EngineUtilities::RandomFloat(-1, 1));
	}


	myStartTime = 0;
	myT = 0;

}
float Shake::Amplitude(float t)
{
	if (t == -1)
	{
		if (!myIsShaking)
			return 0;
		t = myT;
	}
	// Get the previous and next sample
	float s = t / 1000 * myFrequency;
	float s0 = abs(glm::floor(s));
	float s1 = s0 + 1;

	// Get the current decay
	float k = Decay(t);

	// Return the current amplitude
	return (Noise(s0) + (s - s0)*(Noise(s1) - Noise(s0))) * k;
}
void Shake::Start()
{
	myStartTime = Clock->GetCurrentTimeInMillis();
	myT = 0.0f;
	myIsShaking = true;
}
void Shake::Update()
{
	myT = Clock->GetCurrentTimeInMillis() - myStartTime;
	if (myT > myDuration /*/1000.0f*/)
		myIsShaking = false;

}/*
 float Shake::RandomFloat(float a, float b)
 {
 float random = ((float)rand()) / (float)RAND_MAX;
 float diff = b - a;
 float r = random * diff;
 return a + r;
 }*/
float Shake::Noise(float s)
{
	if (s >= mySamples.size()) return 0;
	return mySamples[s];
}
float Shake::Decay(float t)
{
	// Linear decay
	if (t >= myDuration) return 0;
	return (myDuration - t) / myDuration;
}