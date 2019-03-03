#pragma once

#include "Message.h"
#include <set>
class Entity;

const double SEND_MSG_IMMEDIATELY = 0.0f;
const int NO_ADDITIONAL_INFO = 0;

#define MessageMan MessageDispatcher::Instance()

const int    SENDER_ID_IRRELEVANT = -1;
const int    BROADCAST_TO_ALL = -2;

class MessageDispatcher
{
private:

	std::set<Message> PriorityQ;

	void Discharge(Entity* receiver, const Message& msg);

	MessageDispatcher() {};
	MessageDispatcher(const MessageDispatcher&);
	MessageDispatcher& operator=(const MessageDispatcher&);

public:

	static MessageDispatcher* Instance();

	void dispatchMessage(double delay, int sender, int receiver, int msg, void* extraInfo);

	void dispatchDelayedMessages();
};