#include "messageWrapper.h"

std::string MessageWrapper::onEvent(std::string event, int64_t id ) {
	if (event == EventToString(Event::trackreactor) ||
		event == EventToString(Event::trackcatalyst) ||
		event == EventToString(Event::trackforma))
	{
		if (saveObserver(id, event))
		{
			if (event == EventToString(Event::trackreactor)) { return "You're now tracking Orokin Reactor in the Origin System."; }
			if (event == EventToString(Event::trackcatalyst)) { return "You're now tracking Orokin Catalyst in the Origin System."; }
			if (event == EventToString(Event::trackforma)) { return "You're now tracking Forma in the Origin System."; }
		}
		else
		{
			return "Something went wrong, please, try again.";
		}
	}else if(event == EventToString(Event::unsubscride))
	{
		if (deleteObserver(id))
		{
			return "You've unsubscribed from all events in Origin System.";
		}
		else
		{
			return "Something went wrong, please, try again.";
		}
	}
};