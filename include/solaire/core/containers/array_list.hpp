#ifndef SOLAIRE_ARRAY_LIST_HPP
#define SOLAIRE_ARRAY_LIST_HPP

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

#include "solaire/core/containers/heap_array.hpp"

namespace solaire {
	namespace interfaces {
		template<class T>
		SOLAIRE_EXPORT_CLASS array_list : public heap_array<T>{
			// Inherited from ContiguousArray
			virtual bool SOLAIRE_INTERFACE_CALL assert_size(const uint32_t aSize) throw() override {
				return aSize < mSize;
			}
		public:
			array_list() :
				heap_array(32)
			{
				mHeadPosition = 0;
			}

			array_list(const uint32_t aSize) :
				heap_array(aSize)
			{
				mHeadPosition = 0;
			}
		};
	}

	template<class T>
	using array_list = value_list<T, interfaces::array_list<T>>;
}

#endif