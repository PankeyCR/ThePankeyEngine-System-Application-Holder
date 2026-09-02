
#ifndef MemberArrayTableStorage_hpp
	#define MemberArrayTableStorage_hpp

	#include "ArrayTableStorage.hpp"
	#include "MemberTableStorage.hpp"
	#include "MemoryHolderManager.hpp"

	#if defined(pankey_Log) && (defined(MemberArrayTableStorage_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define MemberArrayTableStorageLog(status,method,mns) pankey_Log(status,"MemberArrayTableStorage",method,mns)
	#else
		#define MemberArrayTableStorageLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class H, class M>
			class MemberArrayTableStorage : public ArrayTableStorage<H>, virtual public MemberTableStorage<H,M>{
				public:
					using MANAGER_TYPE = typename ArrayTableStorage<H>::MANAGER_TYPE;
					using HOLDER_TYPE = typename ArrayTableStorage<H>::HOLDER_TYPE;

					MemberArrayTableStorage(){
						MemberArrayTableStorageLog(pankey_Log_StartMethod, "Constructor", "");
						MemberArrayTableStorageLog(pankey_Log_EndMethod, "Constructor", "");
					}

					virtual ~MemberArrayTableStorage(){
						MemberArrayTableStorageLog(pankey_Log_StartMethod, "Destructor", "");
						this->destroy();
						MemberArrayTableStorageLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual void setManager(MANAGER_TYPE a_manager){
						MemberArrayTableStorageLog(pankey_Log_StartMethod, "setManager", "");
						MemberArrayTableStorageLog(pankey_Log_EndMethod, "setManager", "");
					}
					
					virtual MANAGER_TYPE getManager()const{
						MemberArrayTableStorageLog(pankey_Log_StartMethod, "getManager", "");
						MemberArrayTableStorageLog(pankey_Log_Statement, "getManager", "is Manager null: ");
						MemberArrayTableStorageLog(pankey_Log_Statement, "getManager", (StaticManagerInstance<H,M>::getManager() == nullptr));
						MemberArrayTableStorageLog(pankey_Log_EndMethod, "getManager", "");
						return StaticManagerInstance<H,M>::getManager();
					}
					
					virtual Member<H,M> get(int a_position)const{
						MemberArrayTableStorageLog(pankey_Log_StartMethod, "get", "");
						if(this->isNull() || a_position >= this->getSize() || a_position < 0){
							MemberArrayTableStorageLog(pankey_Log_EndMethod, "get", "");
							return Member<H,M>();
						}

						Member<H,M> i_pointer;
						// i_pointer.setHolder(this->m_values[a_position]);

						MemberArrayTableStorageLog(pankey_Log_EndMethod, "get", "");
						return i_pointer;
					}

					virtual Member<H,M> removeByIndex(int a_position){
						MemberArrayTableStorageLog(pankey_Log_StartMethod, "removeByIndex", "");
						if(this->isNull() || a_position >= this->getSize() || a_position < 0){
							MemberArrayTableStorageLog(pankey_Log_EndMethod, "removeByIndex", "");
							return Member<H,M>();
						}
						Member<H,M> i_pointer;
						// i_pointer.setHolder(this->m_values[a_position]);
						// MemoryHolderManager<H>::remove(this->getManager(), this->m_values[a_position]);
						// MemberArrayTableStorageLog(pankey_Log_EndMethod, "removeByIndex", "");
						return i_pointer;
					}
			};

		}

	}

#endif