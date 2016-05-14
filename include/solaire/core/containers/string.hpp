#ifndef SOLAIRE_STRING_HPP
#define SOLAIRE_STRING_HPP

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

#include "solaire/core/containers/array_list.hpp"

namespace solaire {
	template<class T, const T TERMINATOR, class CONTAINER = array_list<T>>
	SOLAIRE_EXPORT_CLASS string : public list<T>{
	private:
		CONTAINER mChars;
	protected:
		// Inherited from container
		T* SOLAIRE_INTERFACE_CALL get(const uint32_t aIndex) throw() override {
			try {
				return &mChars[0];
			} catch (...) {
				return nullptr;
			}
		}

		solaire::iterator<T> SOLAIRE_INTERFACE_CALL get_begin_iterator() throw() override {
			return solaire::iterator<T>(interfaces::contiguous_iterator<T>(&mChars[0], 0));
		}

		solaire::iterator<T> SOLAIRE_INTERFACE_CALL get_end_iterator() throw() override {
			return solaire::iterator<T>(interfaces::contiguous_iterator<T>(&mChars[0], mChars.size() - 1));
		}

		// Inherited from stack
		bool SOLAIRE_INTERFACE_CALL _push_back(T&& aValue) throw() override {
			try {
				mChars.back() = std::move(aValue);
				mChars.push_back(TERMINATOR);
				return true;
			} catch(...){
				return false;
			}
		}

		bool SOLAIRE_INTERFACE_CALL _pop_back() throw() override {
			try {
				mChars.pop_back();
				mChars.back() = TERMINATOR;
				return true;
			} catch (...) {
				return false;
			}
		}

		bool SOLAIRE_INTERFACE_CALL _clear() throw() override {
			try {
				mChars.clear();
				mChars.push_back(TERMINATOR);
				return true;
			} catch (...) {
				return false;
			}
		}

		bool SOLAIRE_INTERFACE_CALL _reserve(const uint32_t aSize) throw() override {
			try {
				mChars.reserve(aSize);
				return true;
			}
			catch (...) {
				return false;
			}
		}

		// Inherited from deque
		bool SOLAIRE_INTERFACE_CALL _push_front(T&& aValue) throw() override {
			try {
				mChars.push_front(std::move(aValue));
				return true;
			}catch (...) {
				return false;
			}
		}

		bool SOLAIRE_INTERFACE_CALL _pop_front() throw() override {
			try {
				mChars.pop_front();
				return true;
			} catch (...) {
				return false;
			}
		}

		// Inherited from list
		bool SOLAIRE_INTERFACE_CALL _insert(const uint32_t aIndex, const T& aValue) throw() override {
			//! \todo prevent insertion after terminator
			try {
				mChars.insert_before(aIndex, aValue);
				return true;
			}catch (...) {
				return false;
			}
		}

		bool SOLAIRE_INTERFACE_CALL _erase(const uint32_t aIndex) throw() override {
			//! \todo prevent erasion of terminator
			try {
				mChars.erase(aIndex);
				return true;
			}
			catch (...) {
				return false;
			}
		}
	public:
		string() :
			mChars()
		{
			mChars.push_back(TERMINATOR);
		}

		string(const T aValue) :
			mChars()
		{
			mChars.push_back(aValue);
			mChars.push_back(TERMINATOR);
		}

		string(const T* aValue) :
			mChars()
		{
			mChars.push_back(TERMINATOR);
			operator+=(aValue);
		}

		SOLAIRE_INTERFACE_CALL ~string() {

		}

		string<T, TERMINATOR, CONTAINER>& operator=(const T aValue) {
			mChars.clear();
			mChars.push_back(aValue);
			mChars.push_back(TERMINATOR);
			return *this;
		}

		string<T, TERMINATOR, CONTAINER>& operator=(const T* aValue) {
			mChars.clear();
			mChars.push_back(TERMINATOR);
			return operator+=(aValue);
		}

		inline string<T, TERMINATOR, CONTAINER>& operator+=(const T aValue) {
			push_back(aValue);
			return *this;
		}

		string<T, TERMINATOR, CONTAINER>& operator+=(const T* aValue) {
			while(*aValue != TERMINATOR) {
				push_back(*aValue);
				++aValue;
			}
			return *this;
		}

		template<const T TERMINATOR2 = TERMINATOR, class CONTAINER2 = CONTAINER>
		inline string<T, TERMINATOR, CONTAINER>& operator+=(const string<T, TERMINATOR2, CONTAINER2>& aOther) {
			push_back(aOther);
			return *this;
		}

		inline bool operator==(const T aValue) const {
			if(size() != 1) return false;
			return back() == aValue;
		}

		bool operator==(const T* aValue) const {
			const uint32_t size = mChars.size() - 1;
			if(mChars.is_contiguous()) {
				const T* const tmp = &mChars[0];
				for(uint32_t i = 0; i < size; ++i, ++aValue) {
					if(*aValue == TERMINATOR) return false;
					if(tmp[i] != *aValue) return false;
				}
			}else {
				for(uint32_t i = 0; i < size; ++i, ++aValue) {
					if(*aValue == TERMINATOR) return false;
					if(mChars[i] != *aValue) return false;
				}
			}
			return true;
		}

		inline bool operator!=(const T aValue) const {
			return ! operator==(aValue);
		}

		inline bool operator!=(const T* aValue) const {
			return ! operator==(aValue);
		}

		// Inherited from generic_container
		bool SOLAIRE_INTERFACE_CALL is_contiguous() const throw() override {
			return mChars.is_contiguous();
		}

		uint32_t SOLAIRE_INTERFACE_CALL size() const throw() override {
			return mChars.size() - 1;
		}

		bool SOLAIRE_INTERFACE_CALL can_invalidate() const throw() override {
			return mChars.can_invalidate();
		}
	};

	typedef string<char, '\0', array_list<char>> c_string;
}

#endif