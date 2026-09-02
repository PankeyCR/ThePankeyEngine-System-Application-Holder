
#ifndef MemoryHolder_hpp
	#define MemoryHolder_hpp

	#include "Holder.hpp"
	#include "InvokeMethod.hpp"
	#include "type_traits.hpp"

	#if defined(pankey_Log) && (defined(MemoryHolder_Log) || defined(pankey_Global_Log) || defined(pankey_MemoryHolderSystem_Log))
		#include "Logger_status.hpp"
		#define MemoryHolderLog(status,method,mns) pankey_Log(status,"MemoryHolder",method,mns)
	#else
		#define MemoryHolderLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<typename M>
			class MemoryHolder{
				public:
					using HOLDER_TYPE = typename M::HOLDER_TYPE;
					using MANAGER_TYPE = typename M::MANAGER_TYPE;

					MemoryHolder(){}

					MemoryHolder(const MemoryHolder<M>& a_shared){
						MemoryHolderLog(pankey_Log_StartMethod, "Constructor", "const MemoryHolder<M>&");
						MemoryHolderLog(pankey_Log_Statement, "Constructor", "before count:");
						MemoryHolderLog(pankey_Log_Statement, "Constructor", a_shared.getCount());
						this->copyHolder(a_shared.m_holder);
						MemoryHolderLog(pankey_Log_Statement, "Constructor", "after count:");
						MemoryHolderLog(pankey_Log_Statement, "Constructor", a_shared.getCount());
					}

					MemoryHolder(MemoryHolder<M>&& a_shared){
						m_holder = a_shared.m_holder;
						a_shared.m_holder = nullptr;
					}

					virtual ~MemoryHolder(){
						this->release();
					}

					virtual void copyHolder(HOLDER_TYPE* a_holder){
						MemoryHolderLog(pankey_Log_StartMethod, "copyHolder", "const MemoryHolder<M>&");
						MemoryHolderLog(pankey_Log_Statement, "copyHolder", "before count:");
						MemoryHolderLog(pankey_Log_Statement, "copyHolder", MANAGER_TYPE::getCount(a_holder));
						m_holder = a_holder;
						MANAGER_TYPE::increment(a_holder);
						MemoryHolderLog(pankey_Log_Statement, "copyHolder", "before count:");
						MemoryHolderLog(pankey_Log_Statement, "copyHolder", MANAGER_TYPE::getCount(a_holder));
					}

					virtual void moveHolder(HOLDER_TYPE* a_holder){
						m_holder = a_holder;
					}

					MemoryHolder& operator=(const MemoryHolder& a_shared){
						if (this != &a_shared){
							this->release();
							this->copyHolder(a_shared.m_holder);
						}
						return *this;
					}

					MemoryHolder& operator=(MemoryHolder&& a_shared){
						this->m_holder = a_shared.m_holder;
						a_shared.m_holder = nullptr;
						return *this;
					}

					void setBaseType(int a_type){
						MANAGER_TYPE::setBaseType(m_holder, a_type);
					}

					void setCount(unsigned int a_count){
						MANAGER_TYPE::setCount(m_holder, a_count);
					}

					unsigned int getCount() const {
						return MANAGER_TYPE::getCount(m_holder);
					}

					unsigned int getType() const {
						return MANAGER_TYPE::getType(m_holder);
					}

					bool isNull() const {
						return MANAGER_TYPE::isNull(m_holder);
					}

					bool isHolderNull() const {
						return m_holder == nullptr;
					}

					HOLDER_TYPE* getHolder()const{
						return this->m_holder;
					}

					void* getRawPointer(){
						return MANAGER_TYPE::template getRawPointer(this->m_holder);
					}

					void release(){
						if (m_holder == nullptr){
							return;
						}
						
						destroy(M(), m_holder);
						m_holder = nullptr;
					}

					void unHold(){
						if (m_holder == nullptr){
							return;
						}
						
						MANAGER_TYPE::decrement(m_holder);
						m_holder = nullptr;
					}

				protected:
					HOLDER_TYPE* m_holder = nullptr;
			};


		}

	}

#endif