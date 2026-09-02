
#ifndef MemberArrayStorage_hpp
	#define MemberArrayStorage_hpp

	#include "ArrayStorage.hpp"
	#include "MemberStorage.hpp"
	#include "MemoryHolderManager.hpp"

	#if defined(pankey_Log) && (defined(MemberArrayStorage_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define MemberArrayStorageLog(status,method,mns) pankey_Log(status,"MemberArrayStorage",method,mns)
	#else
		#define MemberArrayStorageLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class H, class M>
			class MemberArrayStorage : public ArrayStorage<H>, virtual public MemberStorage<H,M>{
				public:
					using MANAGER_TYPE = typename ArrayStorage<H>::MANAGER_TYPE;
					using HOLDER_TYPE = typename ArrayStorage<H>::HOLDER_TYPE;
					using HOLDER_ARRAY_TYPE = typename ArrayStorage<H>::HOLDER_ARRAY_TYPE;

					MemberArrayStorage(){
						MemberArrayStorageLog(pankey_Log_StartMethod, "Constructor", "");
						MemberArrayStorageLog(pankey_Log_EndMethod, "Constructor", "");
					}

					virtual ~MemberArrayStorage(){
						MemberArrayStorageLog(pankey_Log_StartMethod, "Destructor", "");
						this->destroy();
						MemberArrayStorageLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual void setManager(MANAGER_TYPE a_manager){
						MemberArrayStorageLog(pankey_Log_StartMethod, "setManager", "");
						MemberArrayStorageLog(pankey_Log_EndMethod, "setManager", "");
					}
					
					virtual MANAGER_TYPE getManager()const{
						MemberArrayStorageLog(pankey_Log_StartMethod, "getManager", "");
						MemberArrayStorageLog(pankey_Log_Statement, "getManager", "is Manager null: ");
						MemberArrayStorageLog(pankey_Log_Statement, "getManager", (StaticManagerInstance<H,M>::getManager() == nullptr));
						MemberArrayStorageLog(pankey_Log_EndMethod, "getManager", "");
						return StaticManagerInstance<H,M>::getManager();
					}
					
					virtual Member<H,M> get(int a_position)const{
						MemberArrayStorageLog(pankey_Log_StartMethod, "get", "");
						if(this->isNull() || a_position >= this->getSize() || a_position < 0){
							MemberArrayStorageLog(pankey_Log_EndMethod, "get", "");
							return Member<H,M>();
						}

						Member<H,M> i_pointer;
						i_pointer.setHolder(this->m_values[a_position]);

						MemberArrayStorageLog(pankey_Log_EndMethod, "get", "");
						return i_pointer;
					}

					virtual Member<H,M> removeByIndex(int a_position){
						MemberArrayStorageLog(pankey_Log_StartMethod, "removeByIndex", "");
						if(this->isNull() || a_position >= this->getSize() || a_position < 0){
							MemberArrayStorageLog(pankey_Log_EndMethod, "removeByIndex", "");
							return Member<H,M>();
						}
						Member<H,M> i_pointer;
						i_pointer.setHolder(this->m_values[a_position]);
						MemoryHolderManager<H>::remove(this->getManager(), this->m_values[a_position]);
						MemberArrayStorageLog(pankey_Log_EndMethod, "removeByIndex", "");
						return i_pointer;
					}
			};

		}

	}

#endif