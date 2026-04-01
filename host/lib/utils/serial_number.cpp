//
// Copyright 2020 Ettus Research, a National Instruments Brand
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <uhdlib/utils/serial_number.hpp>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace uhd { namespace utils {
bool serial_numbers_match(const std::string& serial_a, const std::string& serial_b)
{
    try {
        const uint32_t a = std::stoi(serial_a, 0, 16);
        const uint32_t b = std::stoi(serial_b, 0, 16);
        return a == b;
    } catch (std::out_of_range& e) {
        return false;
    } catch (std::invalid_argument& e) {
        // Fallback to case-insensitive string comparison for serials
        // containing non-hex characters (e.g. LibreSDR "GQTEFBB")
        if (serial_a.size() != serial_b.size()) {
            return false;
        }
        for (size_t i = 0; i < serial_a.size(); i++) {
            if (std::toupper(static_cast<unsigned char>(serial_a[i]))
                != std::toupper(static_cast<unsigned char>(serial_b[i]))) {
                return false;
            }
        }
        return !serial_a.empty();
    }
}
}} // namespace uhd::utils
