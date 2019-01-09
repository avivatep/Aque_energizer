#pragma once
#include <exception>
#include <memory>
#include "Exeption.h"

template <class T>
class Singleton
{
private:
	std::map<std::string, T> m_resources;
	static std::shared_ptr<Singleton<T>> m_instance;

public:
	Singleton() { }
	~Singleton() { }

	void addResource(const std::pair<std::string, T>& pair);
	T* getResource(const std::string& rsc);

	static std::shared_ptr<Singleton<T>> getInstance();
	void removeResource(const std::string & rsc);
};

template <class T>
std::shared_ptr<Singleton<T>> Singleton<T>::m_instance;

template <class T>
void Singleton<T>::addResource(const std::pair<std::string, T>& pair)
{
	m_resources[pair.first] = pair.second;
}

template <class T>
T* Singleton<T>::getResource(const std::string& rsc)
{
	if (m_resources.find(rsc) == m_resources.end())
		throw Exception("No resource with name: " + rsc);
	return &m_resources[rsc];
}

template<class T>
inline std::shared_ptr<Singleton<T>> Singleton<T>::getInstance()
{
	if (!m_instance)
		m_instance = std::make_shared<Singleton<T>>();
	return m_instance;
}

template<class T>
void Singleton<T>::removeResource(const std::string& rsc)
{
	auto it = m_resources.find(rsc);
	if (it != m_resources.end())
		m_resources.erase(it);
}