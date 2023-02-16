#include <stdafx.h>

#include "ISignalManager.h"

void ISignalManager::Connect(ISignalManager* receiver, std::string message)
{
	auto find = m_signals.find(message);
	if (find == m_signals.end())
	{
		m_signals[message] = std::vector<ISignalManager*>({ receiver });
		return;
	}
	
	auto& receivers = m_signals[message];
	assert("System already connected." && std::find(receivers.begin(), receivers.end(), receiver) == receivers.end());
	receivers.push_back(receiver);
}

void ISignalManager::EmitSignal(std::string message, Entity id)
{
	auto& find = m_signals.find(message);
	if (find != m_signals.end())
		for (ISignalManager* system : m_signals[message])
			system->ReceiveSignal(message, id);
}

void ISignalManager::ReceiveSignal(std::string message, Entity id)
{
	return;
}

