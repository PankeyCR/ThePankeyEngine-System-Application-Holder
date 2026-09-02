
#ifndef make_shared_hpp
	#define make_shared_hpp

	#ifndef pankey_MAKE
		#define pankey_MAKE

		#include "ReferenceCountModel.hpp"
		#include "MemoryHolder.hpp"
		#include "ClassType.hpp"
		#include "makeShared.hpp"

		namespace pankey{

			namespace HolderSystem{

				/*
					it calls a create method to separete the manager from the allocator and the holder
				*/

				template<class T, class M = ReferenceCountModel, class... Args>
				MemoryHolder<M> make(Args... a_args){
					return makeShared<T,M,Args...>(a_args...);
				}

				template<class B, class T, class M = ReferenceCountModel, class... Args>
				MemoryHolder<M> makeDerived(Args... a_args){
					return makeDerivedShared<B,T,M,Args...>(a_args...);
				}

				template<class T, class M = ReferenceCountModel>
				void destroy(MemoryHolder<M>& a_holder){
					destroyShared<T,M>(a_holder);
				}

			}

		}

	#endif

#endif
