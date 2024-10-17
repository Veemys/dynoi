#pragma once

#include <list>

#include "EventHandler.h"

template<class ...ParamsType>
class Event
{
private:
    std::list<EventHandler<ParamsType...>*> m_handlers;

    std::list<EventHandler<ParamsType...>*>::const_iterator findHandler(EventHandler& handler) const
    {
        return std::find_if(m_handlers.cbegin(), m_handlers.cend(), [&handler](const EventHandler<ParamsType...>* otherHandler)
            {
                return handler == *otherHandler;
            });
    }

    bool hasHandler(EventHandler& handler) const
    {
        return findHandler() != m_handlers.cend();
    }

public:
    Event()
        : m_handlers()
    {

    }

    ~Event()
    {
        for (EventHandler<ParamsType...>* handler : m_handlers)
        {
            delete handler;
        }
        m_handlers.clear();
    }

    void operator()(ParamsType... params)
    {
        for (EventHandler<ParamsType...>* handler : m_handlers)
        {
            handler->call(params...);
        }
    }

    bool operator+=(EventHandler<ParamsType...>& eventHandler)
    {
        if (hasHandler(eventHandler))
        {
            return false;
        }

        m_handlers.push_back(&eventHandler);
        return true;
    }

    bool operator-=(EventHandler<ParamsType...>& eventHandler)
    {
        if (!hasHandler(eventHandler))
        {
            return false;
        }

        auto eventHandlerIterator = findHandler(eventHandler);
        m_handlers.erase(eventHandlerIterator);
        delete eventHandlerIterator;
        return true;

    }

};