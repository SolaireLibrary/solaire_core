#ifndef SOLAIRE_INTERFACES_OSTREAM_HPP
#define SOLAIRE_INTERFACES_OSTREAM_HPP

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
#include "solaire/core/containers/string.hpp"

namespace solaire { namespace interfaces {
	SOLAIRE_EXPORT_INTERFACE ostream : public stream {
	private:
		virtual bool SOLAIRE_INTERFACE_CALL write_char(char) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL write_bool(bool) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL write_float(float) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL write_double (double) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL write_uint8_t(uint8_t) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL write_uint16_t(uint16_t) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL write_uint32_t(uint32_t) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL write_uint64_t(uint64_t) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL write_int8_t(int8_t) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL write_int16_t(int16_t) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL write_int32_t(int32_t) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL write_int64_t(int64_t) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL write_string(const char*) throw() = 0;
		virtual bool SOLAIRE_INTERFACE_CALL write_bin(const void*, uint32_t) throw() = 0;
    public:
		virtual SOLAIRE_INTERFACE_CALL ~ostream() throw(){}

		inline ostream& write(const void* aAddress, uint32_t aBytes) {
			runtime_assert(write_bin(aAddress, aBytes), "solaire::interfaces::write : Failed to write bytes");
			return *this;
		}

		inline ostream& operator<<(char aValue) {
			runtime_assert(write_char(aValue), "solaire::interfaces::operator<<(char) : Failed to write value");
			return *this;
		}

		inline ostream& operator<<(bool aValue) {
			runtime_assert(write_bool(aValue), "solaire::interfaces::operator<<(bool) : Failed to write value");
			return *this;
		}

		inline ostream& operator<<(float aValue) {
			runtime_assert(write_float(aValue), "solaire::interfaces::operator<<(float) : Failed to write value");
			return *this;
		}

		inline ostream& operator<<(double aValue) {
			runtime_assert(write_double(aValue), "solaire::interfaces::operator<<(double) : Failed to write value");
			return *this;
		}

		inline ostream& operator<<(uint8_t aValue) {
			runtime_assert(write_uint8_t(aValue), "solaire::interfaces::operator<<(uint8_t) : Failed to write value");
			return *this;
		}

		inline ostream& operator<<(uint16_t aValue) {
			runtime_assert(write_uint16_t(aValue), "solaire::interfaces::operator<<(uint16_t) : Failed to write value");
			return *this;
		}

		inline ostream& operator<<(uint32_t aValue) {
			runtime_assert(write_uint32_t(aValue), "solaire::interfaces::operator<<(uint32_t) : Failed to write value");
			return *this;
		}

		inline ostream& operator<<(uint64_t aValue) {
			runtime_assert(write_uint64_t(aValue), "solaire::interfaces::operator<<(uint64_t) : Failed to write value");
			return *this;
		}

		inline ostream& operator<<(int8_t aValue) {
			runtime_assert(write_int8_t(aValue), "solaire::interfaces::operator<<(int8_t) : Failed to write value");
			return *this;
		}

		inline ostream& operator<<(int16_t aValue) {
			runtime_assert(write_int16_t(aValue), "solaire::interfaces::operator<<(int16_t) : Failed to write value");
			return *this;
		}

		inline ostream& operator<<(int32_t aValue) {
			runtime_assert(write_int32_t(aValue), "solaire::interfaces::operator<<(int32_t) : Failed to write value");
			return *this;
		}

		inline ostream& operator<<(int64_t aValue) {
			runtime_assert(write_int64_t(aValue), "solaire::interfaces::operator<<(int64_t) : Failed to write value");
			return *this;
		}

		inline ostream& operator<<(const char* aValue) {
			runtime_assert(write_string(aValue), "solaire::interfaces::operator<<(const char*) : Failed to write value");
			return *this;
		}

		inline ostream& operator<<(const c_string& aValue) {
			return operator<<(&aValue[0]);
		}
	};
}}

#endif