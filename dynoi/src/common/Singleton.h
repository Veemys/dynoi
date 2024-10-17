#pragma once

#include <memory>

template<class T>
class Singleton
{
private:
	std::unique_ptr<T> m_singleton;

	Singleton();
	Singleton(const Singleton&);

public:
	static T* Instance()
	{
		if (!m_singleton)
		{
			m_singleton = std::make_unique<T>();
		}
		return m_singleton.get();
	}

};