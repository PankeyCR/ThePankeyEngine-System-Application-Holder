
#ifndef makeShared_hpp
	#define makeShared_hpp

	#include "ReferenceCountModel.hpp"
	#include "MemoryHolder.hpp"
	#include "ClassType.hpp"
	#include "shared_ptr.hpp"

	#if defined(pankey_Log) && (defined(makeShared_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define makeSharedLog(status,method,mns) pankey_Log(status,"makeShared",method,mns)
	#else
		#define makeSharedLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			/*
				it calls a create method to separete the manager from the allocator and the holder
			*/

			template<class T, class M = ReferenceCountModel, class... Args>
			shared_ptr<T,M> makeShared(Args... a_args){
				typename M::HOLDER_TYPE* i_holder = create<T,Args...>(M(), a_args...);
				shared_ptr<T,M> i_memory;
				i_memory.moveHolder(i_holder);
				i_memory.setCount(1);
				return i_memory;
			}

			template<class B, class T, class M = ReferenceCountModel, class... Args>
			shared_ptr<B,M> makeDerivedShared(Args... a_args){
				typename M::HOLDER_TYPE* i_holder = create<T,Args...>(M(), a_args...);
				shared_ptr<B,M> i_memory;
				i_memory.moveHolder(i_holder);
				i_memory.setBaseType(Base::ClassType<B>::getId());
				i_memory.setCount(1);
				return i_memory;
			}

			template<class M = ReferenceCountModel>
			void destroyShared(typename M::HOLDER_TYPE* a_holder){
				destroy(M(), a_holder);
			}

			template<class T, class M = ReferenceCountModel>
			void destroyShared(shared_ptr<T,M>& a_holder){
				a_holder.release();
			}

		}

	}

#endif
