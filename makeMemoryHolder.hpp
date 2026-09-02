
#ifndef makeMemoryHolder_hpp
	#define makeMemoryHolder_hpp

	#include "ReferenceCountModel.hpp"
	#include "MemoryHolder.hpp"
	#include "ClassType.hpp"

	#if defined(pankey_Log) && (defined(makeMemoryHolder_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define makeMemoryHolderLog(status,method,mns) pankey_Log(status,"makeMemoryHolder",method,mns)
	#else
		#define makeMemoryHolderLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			/*
				it calls a create method to separete the manager from the allocator and the holder
			*/

			template<class T, class M = ReferenceCountModel, class... Args>
			MemoryHolder<M> makeMemoryHolder(Args... a_args){
				typename M::HOLDER_TYPE* i_holder = create<T,Args...>(M(), a_args...);
				MemoryHolder<M> i_memory;
				i_memory.moveHolder(i_holder);
				i_memory.setCount(1);
				return i_memory;
			}

			template<class B, class T, class M = ReferenceCountModel, class... Args>
			MemoryHolder<M> makeDerivedMemoryHolder(Args... a_args){
				typename M::HOLDER_TYPE* i_holder = create<T,Args...>(M(), a_args...);
				MemoryHolder<M> i_memory;
				i_memory.moveHolder(i_holder);
				i_memory.setBaseType(Base::ClassType<B>::getId());
				i_memory.setCount(1);
				return i_memory;
			}

			template<class M = ReferenceCountModel>
			void destroyMemoryHolder(typename M::HOLDER_TYPE*& a_holder){
				destroy(M(), a_holder);
			}

			template<class M = ReferenceCountModel>
			void destroyMemoryHolder(MemoryHolder<M>& a_holder){
				a_holder.release();
			}

		}

	}

#endif
