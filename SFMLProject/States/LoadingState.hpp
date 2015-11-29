#pragma once

#include "State.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../Utilities/ParallelTask.hpp"


class LoadingState : public State
{
public:
			LoadingState(StateStack& stack, Context context);

	void	draw() override;
	bool	update(sf::Time dt) override;
	bool	handleEvent(const sf::Event& event) override;

	void	setCompletion(float percent);

private:
	sf::Text				m_loadingText;
	sf::RectangleShape		m_progressBarBackground;
	sf::RectangleShape		m_progressBar;

	ParallelTask			m_loadingTask;
};
