#ifndef SOLAIRE_INTERFACES_ISTREAM_HPP
#define SOLAIRE_INTERFACES_ISTREAM_HPP

//Copyright 2016 Adam G. Smith
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//http ://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

#include "solaire/core/interfaces/stream.hpp"

namespace solaire { namespace interfaces {
	SOLAIRE_EXPORT_INTERFACE istream : public stream {
	private:
		virtual bool SOLAIRE_INTERFACE_CALL read_char(char&) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL read_bool(bool&) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL read_float(float&) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL read_double (double&) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL read_uint8_t(uint8_t&) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL read_uint16_t(uint16_t&) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL read_uint32_t(uint32_t&) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL read_uint64_t(uint64_t&) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL read_int8_t(int8_t&) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL read_int16_t(int16_t&) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL read_int32_t(int32_t&) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL read_int64_t(int64_t&) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL read_string(char*) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL read_bin(void*, uint32_t) throw() = 0;
    public:
		virtual SOLAIRE_INTERFACE_CALL ~istream() throw(){}

		inline istream& read(void* aAddress, uint32_t aBytes) {
			runtime_assert(read_bin(aAddress, aBytes), "solaire::interfaces::read : Failed to read bytes");
			return *this;
		}

		inline istream& operator>>(char& aValue) {
			runtime_assert(read_char(aValue), "solaire::interfaces::operator>>(char) : Failed to read value");
			return *this;
		}

		inline istream& operator>>(bool& aValue) {
			runtime_assert(read_bool(aValue), "solaire::interfaces::operator>>(bool) : Failed to read value");
			return *this;
		}

		inline istream& operator>>(float& aValue) {
			runtime_assert(read_float(aValue), "solaire::interfaces::operator>>(float) : Failed to read value");
			return *this;
		}

		inline istream& operator>>(double& aValue) {
			runtime_assert(read_double(aValue), "solaire::interfaces::operator>>(double) : Failed to read value");
			return *this;
		}

		inline istream& operator>>(uint8_t& aValue) {
			runtime_assert(read_uint8_t(aValue), "solaire::interfaces::operator>>(uint8_t) : Failed to read value");
			return *this;
		}

		inline istream& operator>>(uint16_t& aValue) {
			runtime_assert(read_uint16_t(aValue), "solaire::interfaces::operator>>(uint16_t) : Failed to read value");
			return *this;
		}

		inline istream& operator>>(uint32_t& aValue) {
			runtime_assert(read_uint32_t(aValue), "solaire::interfaces::operator>>(uint32_t) : Failed to read value");
			return *this;
		}

		inline istream& operator>>(uint64_t& aValue) {
			runtime_assert(read_uint64_t(aValue), "solaire::interfaces::operator>>(uint64_t) : Failed to read value");
			return *this;
		}

		inline istream& operator>>(int8_t& aValue) {
			runtime_assert(read_int8_t(aValue), "solaire::interfaces::operator>>(int8_t) : Failed to read value");
			return *this;
		}

		inline istream& operator>>(int16_t& aValue) {
			runtime_assert(read_int16_t(aValue), "solaire::interfaces::operator>>(int16_t) : Failed to read value");
			return *this;
		}

		inline istream& operator>>(int32_t& aValue) {
			runtime_assert(read_int32_t(aValue), "solaire::interfaces::operator>>(int32_t) : Failed to read value");
			return *this;
		}

		inline istream& operator>>(int64_t& aValue) {
			runtime_assert(read_int64_t(aValue), "solaire::interfaces::operator>>(int64_t) : Failed to read value");
			return *this;
		}

		inline istream& operator>>(char* aValue) {
			runtime_assert(read_string(aValue), "solaire::interfaces::operator>>(char*) : Failed to read value");
			return *this;
		}
	};
}}

#endif