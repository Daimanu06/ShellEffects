/**
 * Format output in a terminal (Unix) / Command Prompt (Windows).
 *
 * Provide text colorization, and other nice effects like blinking, bold or hidden text etc… depending on the platform.
 *
 * @author Daïmanu
 */

#ifndef SHEFFECTS
#define SHEFFECTS

#include <iosfwd>
#include <string>
#include <cstddef>

namespace Shell {
	enum Color {
		Default, Black, Red, Green, Yellow, Blue, Magenta, Cyan, LightGray, DarkGray, LightRed, LightGreen, LightYellow, LightBlue, LightMagenta, LigthCyan, White
	};
	enum Effect {
		Bold, Dim, Underline, Blink, Reverse, Hidden, All
	};

	class Format {
		public:
			/**
			 * Creates an empty format
			 * @param reset Indicates if the effects will be reset at the end.
			 */
			Format(bool reset = true);
			//TODO cpy ctor, operator =

		public: //Colors
			Format& fg(Color); ///<Set the supplied color as foreground color.
			Format& bg(Color); ///<Set the supplied color as background color.

			Format& fg_default();  ///<Set foreground color to default.
			Format& fg_black();    ///<Set foreground color to black.
			Format& fg_red();      ///<Set foreground color to red.
			Format& fg_green();    ///<Set foreground color to green.
			Format& fg_yellow();   ///<Set foreground color to yellow.
			Format& fg_blue();     ///<Set foreground color to blue.
			Format& fg_magenta();  ///<Set foreground color to magenta.
			Format& fg_cyan();     ///<Set foreground color to cyan.
			Format& fg_lgray();    ///<Set foreground color to light gray.
			Format& fg_dgray();    ///<Set foreground color to dark gray.
			Format& fg_lred();     ///<Set foreground color to light red.
			Format& fg_lgreen();   ///<Set foreground color to light green.
			Format& fg_lyellow();  ///<Set foreground color to light yellow.
			Format& fg_lblue();    ///<Set foreground color to light blue.
			Format& fg_lmagenta(); ///<Set foreground color to light magenta.
			Format& fg_lcyan();    ///<Set foreground color to light cyan.
			Format& fg_white();    ///<Set foreground color to white.

			Format& bg_default();  ///<Set background color to default.
			Format& bg_black();    ///<Set background color to black.
			Format& bg_red();      ///<Set background color to red.
			Format& bg_green();    ///<Set background color to green.
			Format& bg_yellow();   ///<Set background color to yellow.
			Format& bg_blue();     ///<Set background color to blue.
			Format& bg_magenta();  ///<Set background color to magenta.
			Format& bg_cyan();     ///<Set background color to cyan.
			Format& bg_lgray();    ///<Set background color to light gray.
			Format& bg_dgray();    ///<Set background color to dark gray.
			Format& bg_lred();     ///<Set background color to light red.
			Format& bg_lgreen();   ///<Set background color to light green.
			Format& bg_lyellow();  ///<Set background color to light yellow.
			Format& bg_lblue();    ///<Set background color to light blue.
			Format& bg_lmagenta(); ///<Set background color to light magenta.
			Format& bg_lcyan();    ///<Set background color to light cyan.
			Format& bg_white();    ///<Set background color to white.

		public: //Effects
			Format& apply(Effect);       ///<Apply the supplied effect. @note "All" must not be used in this function.
			Format& reset(Effect = All); ///<Reset the supplied effect if any, all effects otherwise.

			Format& bold();      ///<Bold the text.
			Format& dim();       ///<Diminish the text.
			Format& underline(); ///<Underline the text.
			Format& blink();     ///<Blink the text.
			Format& reverse();   ///<Reverse the background and foreground colors.
			Format& hide();      ///<Hide the text. Note that the background color and the underline may be still visible.

			Format& rall();       ///<Reset all effects and colors.
			Format& rbold();      ///<Unbold the text.
			Format& rdim();       ///<Remove the diminish effect.
			Format& runderline(); ///<Remove the underline.
			Format& rblink();     ///<Remove the blink effect.
			Format& rreverse();   ///<Remove the reverse effect.
			Format& rhide();      ///<Unhide the text.

		public:
			Format& text(const std::string&); ///<Append a text.
			Format& text(const char*);        ///<Append a text.
			Format& text(std::nullptr_t);     ///<Does nothing. Called if a null pointer is supplied.

		public:
			const std::string operator()() const; ///<Return the formatted text.

	};

	std::ostream& operator << (std::ostream& os, const Format& t);
}

#endif
