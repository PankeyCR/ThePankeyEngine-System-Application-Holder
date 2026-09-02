
#ifndef make_memoryholder_hpp
	#define make_memoryholder_hpp

	#ifndef pankey_MAKE
		#define pankey_MAKE

		#include "ReferenceCountModel.hpp"
		#include "MemoryHolder.hpp"
		#include "ClassType.hpp"

		namespace pankey{

			namespace HolderSystem{

				/*
					it calls a create method to separete the manager from the allocator and the holder
				*/

				template<class T, class M = ReferenceCountModel, class... Args>
				MemoryHolder<M> make(Args... a_args){
					return makeMemoryHolder<T,M,Args...>(a_args...);
				}

				template<class B, class T, class M = ReferenceCountModel, class... Args>
				MemoryHolder<M> makeDerived(Args... a_args){
					return makeDerivedMemoryHolder<B,T,M,Args...>(a_args...);
				}

				template<class T, class M = ReferenceCountModel>
				void destroy(MemoryHolder<M>& a_holder){
					destroyMemoryHolder<M>(a_holder);
				}

			}

		}

	#endif

#endif
