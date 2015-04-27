#include "format.h"

#include <array>
#include <cstdint>
#include <iostream>
#include <sstream>

namespace Shell {

	struct {
			std::ostringstream oss;

			bool resetAtEnd;

			enum LastOperation {NONE, TEXT, EFFECT} last_addition;

			void flush() {
				oss.str("");
				oss.clear();
				last_addition = NONE;
			}

			void set_effect(uint8_t i) {
				if(last_addition == NONE || last_addition == TEXT)
					oss << "\e[";
				if(last_addition == EFFECT)
					oss << ';';
				last_addition = EFFECT;
				oss << (int)i;
			}

			void add_text(const std::string& str) {
				if(last_addition == EFFECT)
					oss << 'm';
				last_addition = TEXT;
				oss << str;
			}
	} e;

	//Constructor
	Format::Format(bool r) {
		e.flush();
		e.resetAtEnd = r;
	}

	//Set colors
	Format& Format::fg(Color::Value c) {
		static uint8_t fg[] = {39, 30, 31, 32, 33, 34, 35, 36, 37, 90, 91, 92, 93, 94, 95, 96, 97};
		e.set_effect(fg[c]);
		return *this;
	}
	Format& Format::bg(Color::Value c) {
		static uint8_t bg[] = {49, 40, 41, 42, 43, 44, 45, 46, 47, 100, 101, 102, 103, 104, 105, 106, 107};
		e.set_effect(bg[c]);
		return *this;
	}

	//Apply effects
	Format& Format::bold() {
		e.set_effect(1);
		return *this;
	}

	Format& Format::dim() {
		e.set_effect(2);
		return *this;
	}

	Format& Format::underline() {
		e.set_effect(4);
		return *this;
	}

	Format& Format::blink() {
		e.set_effect(5);
		return *this;
	}

	Format& Format::reverse() {
		e.set_effect(7);
		return *this;
	}

	Format& Format::hide() {
		e.set_effect(8);
		return *this;
	}

	//Reset functions
	Format& Format::rall() {
		e.set_effect(0);
		return *this;
	}
	Format& Format::rbold() {
		e.set_effect(21);
		return *this;
	}

	Format& Format::rdim() {
		e.set_effect(22);
		return *this;
	}

	Format& Format::runderline() {
		e.set_effect(24);
		return *this;
	}

	Format& Format::rblink() {
		e.set_effect(25);
		return *this;
	}

	Format& Format::rreverse() {
		e.set_effect(27);
		return *this;
	}

	Format& Format::rhide() {
		e.set_effect(28);
		return *this;
	}

	//Add text

	Format& Format::text(const char* str) {
		e.add_text(str);
		return *this;
	}
	Format& Format::text(const std::string& str) {
		e.add_text(str);
		return *this;
	}

	const std::string Format::operator ()() const {
		if(e.resetAtEnd)
			e.oss << "\e[0m";
		return e.oss.str();
	}

	std::ostream& operator << (std::ostream& os, const Format& t) {
		return(os << t());
	}

}
