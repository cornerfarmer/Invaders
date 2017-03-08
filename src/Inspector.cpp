#include "Inspector.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Invader.hpp"
#include <LightBulb/NeuralNetwork/NeuralNetwork.hpp>
#include <LightBulb/NetworkTopology/AbstractNetworkTopology.hpp>
#include <LightBulb/ActivationOrder/TopologicalOrder.hpp>

std::string Inspector::renderFloat(float number)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << number;
	return stream.str();
}

Inspector::Inspector()
{
	selected = nullptr;
	font.loadFromFile("segoeui.ttf");
}

void Inspector::select(Invader* invader)
{
	selected = invader;
}

void Inspector::draw(sf::RenderWindow& window, sf::Vector2i offset)
{
	sf::Text text;
	sf::Vector2i size(window.getSize().x - offset.x, window.getSize().y - offset.y);

	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setPosition(offset.x, offset.y);

	if (selected) {
		LightBulb::Vector<> input(selected->getNeuralNetwork().getNetworkTopology().getInputSize());
		selected->getNNInput(input);

		std::string netInput = "Sight:\n";
		int side = 5;
		int inputIndex = 0;
		for (int i = 0; i < side * side; i++)
		{
			if (i == side * (side / 2) + side / 2)
			{
				netInput += "   .    ";
				continue;
			}
			netInput += renderFloat(input.getEigenValue()[inputIndex++]) + " ";
			if (i % side == side - 1)
				netInput += "\n";
		}
		
		text.setString(netInput);
		window.draw(text);

		offset.x += text.getLocalBounds().width;
		text.setPosition(offset.x, offset.y);

		netInput = "Dir:\n";
		netInput += renderFloat(input.getEigenValue()[inputIndex++]) + " ";
		netInput += renderFloat(input.getEigenValue()[inputIndex++]) + "\n";

		netInput += "Time:\n";
		netInput += renderFloat(input.getEigenValue()[inputIndex++]) + "\n";

		
		LightBulb::TopologicalOrder topologicalOrder;
		// Calculate the output from the the input
		const LightBulb::Vector<>& lastOutput = selected->getNeuralNetwork().calculateWithoutOutputCopy(input, topologicalOrder, false);

		netInput += "Action:\n";
		netInput += renderFloat(lastOutput.getEigenValue()[0]) + " ";
		netInput += renderFloat(lastOutput.getEigenValue()[1]) + " ";
		netInput += renderFloat(lastOutput.getEigenValue()[2]) + " ";
		netInput += renderFloat(lastOutput.getEigenValue()[3]) + "\n";


		text.setString(netInput);
		window.draw(text);
	}

}
