#include "format.h"

#include <cstdint>
#include <iostream>
#include <sstream>

namespace Shell {
	struct {
			std::ostringstream oss;
			bool resetAtEnd;
			enum LastOperation {None, Text, Effect} last_addition;

			void flush() {
				oss.str("");
				oss.clear();
				last_addition = None;
			}

			void set_effect(uint8_t i) {
				if(last_addition == None || last_addition == Text)
					oss << "\e[";
				if(last_addition == Effect)
					oss << ';';
				last_addition = Effect;
				oss << (int)i;
			}

			void add_text(const std::string& str) {
				if(last_addition == Effect)
					oss << 'm';
				last_addition = Text;
				oss << str;
			}
	} impl;

	//Constructor
	Format::Format(bool r) {
		impl.flush();
		impl.resetAtEnd = r;
	}

	//Set colors
	Format& Format::fg(Color c) {
		static uint8_t fg[] = {39, 30, 31, 32, 33, 34, 35, 36, 37, 90, 91, 92, 93, 94, 95, 96, 97};
		impl.set_effect(fg[c]); return *this;
	}
	Format& Format::fg_default()  {impl.set_effect(39); return *this;}
	Format& Format::fg_black()    {impl.set_effect(30); return *this;}
	Format& Format::fg_red()      {impl.set_effect(31); return *this;}
	Format& Format::fg_green()    {impl.set_effect(32); return *this;}
	Format& Format::fg_yellow()   {impl.set_effect(33); return *this;}
	Format& Format::fg_blue()     {impl.set_effect(34); return *this;}
	Format& Format::fg_magenta()  {impl.set_effect(35); return *this;}
	Format& Format::fg_cyan()     {impl.set_effect(36); return *this;}
	Format& Format::fg_lgray()    {impl.set_effect(37); return *this;}
	Format& Format::fg_dgray()    {impl.set_effect(90); return *this;}
	Format& Format::fg_lred()     {impl.set_effect(91); return *this;}
	Format& Format::fg_lgreen()   {impl.set_effect(92); return *this;}
	Format& Format::fg_lyellow()  {impl.set_effect(93); return *this;}
	Format& Format::fg_lblue()    {impl.set_effect(94); return *this;}
	Format& Format::fg_lmagenta() {impl.set_effect(95); return *this;}
	Format& Format::fg_lcyan()    {impl.set_effect(96); return *this;}
	Format& Format::fg_white()    {impl.set_effect(97); return *this;}

	Format& Format::bg(Color c) {
		static uint8_t bg[] = {49, 40, 41, 42, 43, 44, 45, 46, 47, 100, 101, 102, 103, 104, 105, 106, 107};
		impl.set_effect(bg[c]); return *this;
	}
	Format& Format::bg_black()    {impl.set_effect(40);  return *this;}
	Format& Format::bg_red()      {impl.set_effect(41);  return *this;}
	Format& Format::bg_green()    {impl.set_effect(42);  return *this;}
	Format& Format::bg_yellow()   {impl.set_effect(43);  return *this;}
	Format& Format::bg_blue()     {impl.set_effect(44);  return *this;}
	Format& Format::bg_magenta()  {impl.set_effect(45);  return *this;}
	Format& Format::bg_cyan()     {impl.set_effect(46);  return *this;}
	Format& Format::bg_lgray()    {impl.set_effect(47);  return *this;}
	Format& Format::bg_dgray()    {impl.set_effect(100); return *this;}
	Format& Format::bg_lred()     {impl.set_effect(101); return *this;}
	Format& Format::bg_lgreen()   {impl.set_effect(102); return *this;}
	Format& Format::bg_lyellow()  {impl.set_effect(103); return *this;}
	Format& Format::bg_lblue()    {impl.set_effect(104); return *this;}
	Format& Format::bg_lmagenta() {impl.set_effect(105); return *this;}
	Format& Format::bg_lcyan()    {impl.set_effect(106); return *this;}
	Format& Format::bg_white()    {impl.set_effect(107); return *this;}

	//Apply effects
	Format& Format::apply(Effect effect) {
		static uint8_t effects[] = {1, 2, 4, 5, 7, 8, 0};
		impl.set_effect(effects[effect]); return *this;
	}
	Format& Format::bold()      {impl.set_effect(1); return *this;}
	Format& Format::dim()       {impl.set_effect(2); return *this;}
	Format& Format::underline() {impl.set_effect(4); return *this;}
	Format& Format::blink()     {impl.set_effect(5); return *this;}
	Format& Format::reverse()   {impl.set_effect(7); return *this;}
	Format& Format::hide()      {impl.set_effect(8); return *this;}

	//Reset functions
	Format& Format::reset(Effect effect) {
		static uint8_t effects[] = {21, 22, 24, 25, 27, 28, 0};
		impl.set_effect(effects[effect]); return *this;
	}
	Format& Format::rall()       {impl.set_effect(0);  return *this;}
	Format& Format::rbold()      {impl.set_effect(21); return *this;}
	Format& Format::rdim()       {impl.set_effect(22); return *this;}
	Format& Format::runderline() {impl.set_effect(24); return *this;}
	Format& Format::rblink()     {impl.set_effect(25); return *this;}
	Format& Format::rreverse()   {impl.set_effect(27); return *this;}
	Format& Format::rhide()      {impl.set_effect(28); return *this;}

	//Add text
	Format& Format::text(const char* str) {
		impl.add_text(str); return *this;
	}
	Format& Format::text(const std::string& str) {
		impl.add_text(str); return *this;
	}

	//Finally
	const std::string Format::operator ()() const {
		if(impl.resetAtEnd)
			impl.oss << "\e[0m";
		return impl.oss.str();
	}

	std::ostream& operator << (std::ostream& os, const Format& t) {
		return(os << t());
	}

}
