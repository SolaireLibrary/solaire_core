#ifndef SOLAIRE_CONTIGUOUS_ITERATOR_HPP
#define SOLAIRE_CONTIGUOUS_ITERATOR_HPP

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

#include "solaire/core/interfaces/iterator.hpp"

namespace solaire {
	template<class T>
	SOLAIRE_EXPORT_CLASS contiguous_iterator : public interfaces::iterator<T> {
		private:
		T* mPointer;
		int32_t mOffset;
	public:
		contiguous_iterator(T* const aPointer, const int32_t aOffset) throw() :
			mPointer(aPointer),
			mOffset(aOffset)
		{}

		SOLAIRE_INTERFACE_CALL ~contiguous_iterator() {

		}

		// Inherited from interfaces::iterator
		const T* SOLAIRE_INTERFACE_CALL dereference() const throw() override {
			return mPointer + mOffset;
		}

		void SOLAIRE_INTERFACE_CALL increment(const uint32_t aOffset) throw() override {
			mOffset += aOffset;
		}

		void SOLAIRE_INTERFACE_CALL decrement(const uint32_t aOffset) throw() override {
			mOffset -= aOffset;
		}

		void SOLAIRE_INTERFACE_CALL copy(interfaces::iterator<T>* const aOther) const throw() override {
			new(aOther) contiguous_iterator<T>(mPointer, mOffset);
		}

		int32_t SOLAIRE_INTERFACE_CALL get_offset() const throw() override {
			return mOffset;
		}
	};

	template<class T>
	SOLAIRE_EXPORT_CLASS reverse_contiguous_iterator : public interfaces::iterator<T> {
	private:
		T* mPointer;
		int32_t mOffset;
	public:
		reverse_contiguous_iterator(T* const aPointer, const int32_t aOffset) throw() :
			mPointer(aPointer),
			mOffset(aOffset)
		{}

		// Inherited from interfaces::iterator
		const T* SOLAIRE_INTERFACE_CALL dereference() const throw() override {
			return mPointer - mOffset;
		}

		void SOLAIRE_INTERFACE_CALL increment(const uint32_t aOffset) throw() override {
			mOffset += aOffset;
		}

		void SOLAIRE_INTERFACE_CALL decrement(const uint32_t aOffset) throw() override {
			mOffset -= aOffset;
		}

		void SOLAIRE_INTERFACE_CALL copy(interfaces::iterator<T>* const aOther) const throw() override {
			new(aOther) contiguous_iterator<T>(mPointer, mOffset);
		}

		int32_t SOLAIRE_INTERFACE_CALL get_offset() const throw() override {
			return mOffset;
		}
	};
}

#endif