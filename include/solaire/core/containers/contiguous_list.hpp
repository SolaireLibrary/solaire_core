#ifndef SOLAIRE_CONTIGUOUS_LIST_HPP
#define SOLAIRE_CONTIGUOUS_LIST_HPP

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

#include "solaire/core/list.hpp"
#include "solaire/core/iterators/contiguous_iterator.hpp"

namespace solaire {
	template<class T>
	SOLAIRE_EXPORT_CLASS contiguous_list : public list<T> {
	protected:
		T* mBasePointer;
		uint32_t mHeadPosition;

		virtual bool SOLAIRE_INTERFACE_CALL assert_size(const uint32_t) throw() = 0;

		// Inherited from container
		T* SOLAIRE_INTERFACE_CALL get(const uint32_t aIndex) throw() override {
			if (!mBasePointer) return nullptr;
			if (aIndex >= mHeadPosition) return nullptr;
			return mBasePointer + aIndex;
		}

		solaire::iterator<T> SOLAIRE_INTERFACE_CALL get_begin_iterator() throw() override {
			return solaire::iterator<T>(interfaces::contiguous_iterator<T>(mBasePointer, 0));
		}

		solaire::iterator<T> SOLAIRE_INTERFACE_CALL get_end_iterator() throw() override {
			return solaire::iterator<T>(interfaces::contiguous_iterator<T>(mBasePointer, mHeadPosition));
		}

		// Inherited from stack
		bool SOLAIRE_INTERFACE_CALL _push_back(const T& aValue) throw() override {
			if (!mBasePointer) return nullptr;
			if (!assert_size(mHeadPosition + 1)) return false;
			mBasePointer[mHeadPosition++] = aValue;
			return true;
		}

		bool SOLAIRE_INTERFACE_CALL _pop_back() throw() override {
			if (!mBasePointer) return nullptr;
			if (mHeadPosition == 0) return false;
			--mHeadPosition;
		}

		bool SOLAIRE_INTERFACE_CALL _clear() throw() override {
			mHeadPosition = 0;
			return true;
		}

		// Inherited from deque
		bool SOLAIRE_INTERFACE_CALL _push_front(const T& aValue) throw() override {
			return _insert(0, aValue);
		}

		bool SOLAIRE_INTERFACE_CALL _pop_front() throw() override {
			return _erase(0);
		}

		// Inherited from list
		bool SOLAIRE_INTERFACE_CALL _insert(const uint32_t aIndex, const T& aValue) throw() override {
			if (!mBasePointer) return nullptr;
			if (aIndex >= mHeadPosition) return false;
			if (!assert_size(mHeadPosition + 1)) return false;
			for (uint32_t i = mHeadPosition - 1; i > aIndex; --i) mBasePointer[i] = mBasePointer[i - 1];
			mBasePointer[aIndex] = aValue;
			++mHeadPosition;
			return true;
		}

		bool SOLAIRE_INTERFACE_CALL _erase(const uint32_t aIndex) throw() override {
			if (!mBasePointer) return nullptr;
			if (mHeadPosition == 0) return false;
			for (uint32_t i = aIndex; i < mHeadPosition; ++i) mBasePointer[i] = mBasePointer[i + 1];
			--mHeadPosition;
			return true;
		}
	public:
		contiguous_list(T* aPointer) :
			mBasePointer(aPointer),
			mHeadPosition(0)
		{}

		virtual SOLAIRE_INTERFACE_CALL ~contiguous_list() throw() {

		}

		// Inherited from container
		bool SOLAIRE_INTERFACE_CALL is_contiguous() const throw() override {
			return true;
		}

		uint32_t SOLAIRE_INTERFACE_CALL size() const throw() override {
			if(! mBasePointer) return 0;
			return mHeadPosition;
		}

		// Inherited from stack
		bool SOLAIRE_INTERFACE_CALL can_invalidate() const throw() override {
			return true;
		}
	};
}

#endif