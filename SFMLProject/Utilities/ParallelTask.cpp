#include "ParallelTask.hpp"

#include <SFML/System/Lock.hpp>


ParallelTask::ParallelTask()
	: m_thread(&ParallelTask::runTask, this)
	, m_finished(false)
{
}

void ParallelTask::execute()
{
	m_finished = false;
	m_elapsedTime.restart();
	m_thread.launch();
}

bool ParallelTask::isFinished()
{
	sf::Lock lock(m_mutex);
	return m_finished;
}

float ParallelTask::getCompletion()
{
	sf::Lock lock(m_mutex);

	// 100% at 10 seconds of elapsed time
	return m_elapsedTime.getElapsedTime().asSeconds() / 10.f;
}

void ParallelTask::runTask()
{
	// Dummy task - stall 10 seconds
	bool ended = false;
	while (!ended)
	{
		sf::Lock lock(m_mutex); // Protect the clock 
		if (m_elapsedTime.getElapsedTime().asSeconds() >= 10.f)
		{
			ended = true;
		}
	}

	{ // mFinished may be accessed from multiple threads, protect it
		sf::Lock lock(m_mutex);
		m_finished = true;
	}
}
