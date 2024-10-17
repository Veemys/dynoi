#pragma once

template<class ...ParamsType>
class EventHandler
{
protected:
    EventHandler() {}

    virtual bool isEqual(const EventHandler<ParamsType...>& other) const = 0;

public:
    virtual void call(ParamsType... params) = 0;

    bool operator==(const EventHandler<ParamsType...>& other)
    {
        return isEqual(other);
    }

    bool operator!=(const EventHandler<ParamsType...>& other)
    {
        return !(*this == other);
    }

};