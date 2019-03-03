#pragma once
#include <iostream>
#include <math.h>

struct Message
{
	int mSender;
	int mReceiver;
	int mMsg;

	double dispatchTime;

	void* extraInfo;

	Message()
		: dispatchTime(-1), mSender(-1),
		mReceiver(-1), mMsg(-1)
	{}

	Message(double time, int sender, int receiver, int msg, void* info = nullptr)
		: dispatchTime(time), mSender(sender), mReceiver(receiver), mMsg(msg), extraInfo(info)
	{}
};

const double SmallestDelay = 0.25;

inline bool operator==(const Message& m1, const Message& m2)
{
	return (fabs(m1.dispatchTime - m2.dispatchTime) < SmallestDelay) &&
		(m1.mSender == m2.mSender) &&
		(m1.mReceiver == m2.mReceiver) &&
		(m1.mMsg == m2.mMsg);
}

inline bool operator < (const Message& m1, const Message& m2)
{
	if (m1 == m2)
		return false;

	else
	{
		return (m1.dispatchTime < m2.dispatchTime);
	}
}

inline std::ostream& operator<<(std::ostream& os, const Message& m)
{
	os << "time: " << m.dispatchTime << "  Sender: " << m.mSender
		<< "   Receiver: " << m.mReceiver << "   Msg: " << m.mMsg;
	return os;
}

//This is neat :)
template <class T>
inline T DereferenceToType(void* p)
{
	return *(T*)(p);
}