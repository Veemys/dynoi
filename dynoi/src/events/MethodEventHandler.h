#pragma once

#include "EventHandler.h"

template<class ObjectType, class ...ParamsType>
class MethodEventHandler : public EventHandler<ParamsType...>
{
    using MethodType = void(ObjectType::*)(ParamsType...);

private:
    ObjectType& m_object;
    MethodType m_method;

public:
    MethodEventHandler(ObjectType& object, MethodType method)
        : EventHandler<ParamsType...>(),
        m_object(object),
        m_method(method)
    {
        assert(m_method != nullptr);
    }

    void call(ParamsType... params) override final
    {
        (m_object.*m_method)(params...);
    }

    bool isEqual(const EventHandler<ParamsType...>& other) const override final
    {
        const MethodEventHandler<ObjectType, ParamsType...>* otherCastedPtr = dynamic_cast<const MethodEventHandler<ObjectType, ParamsType...>*>(&other);
        return otherCastedPtr != nullptr && &otherCastedPtr->m_object == &m_object && otherCastedPtr->m_method == m_method;
    }

};

template<class ObjectType, class ...ParamsType>
EventHandler<ParamsType...>& createMethodEventHandler(ObjectType& object, void(ObjectType::* method)(ParamsType...))
{
    return *new MethodEventHandler<ObjectType, ParamsType...>(object, method);
}

#define METHOD_HANDLER( Object, Method ) createMethodEventHandler( Object, &Method )
#define MY_METHOD_HANDLER( Method ) METHOD_HANDLER( *this, Method )