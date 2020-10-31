/*
 * Copyright (C) 2020 Gwenhael Goavec-Merou <gwenhael.goavec-merou@trabucayre.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdexcept>

#include "configBitstreamParser.hpp"
#include "display.hpp"
#include "efinixHexParser.hpp"

using namespace std;

EfinixHexParser::EfinixHexParser(const string &filename, bool reverseOrder):
		ConfigBitstreamParser(filename, ConfigBitstreamParser::ASCII_MODE,
		false), _reverseOrder(reverseOrder)
{}

int EfinixHexParser::parse()
{
	char *c = new char[_file_size];
	_fd.read(c, sizeof(char) * _file_size);

	for (int offset = 0; offset < _file_size; offset += 3) {
		char val;
		sscanf(&c[offset], "%hhx", &val);
		_bit_data += val;
	}
	_bit_length = _bit_data.size() * 8;

	delete c;

	return EXIT_SUCCESS;
}
