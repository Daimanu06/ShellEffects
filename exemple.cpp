#include "format.h"
#include <iostream> //std::cout
#include <string>

int main(int, char**) {
	namespace sh = Shell;

	std::cout << sh::Format().bg(sh::Color::Black).text("Black").text(" bg") << std::endl;
	std::cout << sh::Format().text("Hello World") << std::endl;
	std::cout << sh::Format().text("Hello").bg(sh::Color::Red).text("World") << std::endl;
	std::cout << sh::Format().fg(sh::Color::Green).text("Green").rall().text("White") << std::endl;
	std::cout << sh::Format().underline().text("U").rblink().text("U").runderline().text("N") << std::endl;
	std::cout << sh::Format().underline().bold().fg(sh::Color::LightBlue).text("U&B") << std::endl;

	return 0;
}
