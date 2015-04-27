/**
 * Format output in a terminal (Unix) / Command Prompt (Windows).
 * Provide text colorization, and other nice effects like blinking, bold or hidden text etc… depending on the platform.
 * @author Daïmanu
 */

#ifndef SHEFFECTS
#define SHEFFECTS

#include <iosfwd>
#include <string>
#include <cstddef>

namespace Shell {
	struct Color {
			static const int count = 17;
			enum Value {
				Default, Black, Red, Green, Yellow, Blue, Magenta, Cyan, LightGray, DarkGray, LightRed, LightGreen, LightYellow, LightBlue, LightMagenta, LigthCyan, White
			};
	};

	class Format {
		public:
			Format(bool reset = true);
			//TODO cpy ctor, operator =

		public:
			Format& fg(Color::Value);
			Format& bg(Color::Value);

			Format& bold();
			Format& dim();
			Format& underline();
			Format& blink();
			Format& reverse();
			Format& hide();

			Format& rall();
			Format& rbold();
			Format& rdim();
			Format& runderline();
			Format& rblink();
			Format& rreverse();
			Format& rhide();

		public:
			Format& text(const std::string&);
			Format& text(const char*);
			Format& text(std::nullptr_t);

		public:
			const std::string operator()() const;

	};

	std::ostream& operator << (std::ostream& os, const Format& t);
}

#endif
