
#ifndef MemberStorage_hpp
	#define MemberStorage_hpp

	#include "MemoryStorage.hpp"
	#include "Member.hpp"

	#if defined(pankey_Log) && (defined(MemberStorage_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define MemberStorageLog(status,method,mns) pankey_Log(status,"MemberStorage",method,mns)
	#else
		#define MemberStorageLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class H, class M>
			class MemberStorage : virtual public MemoryStorage<H>{
				public:

					using MANAGER_TYPE = typename MemoryStorage<H>::MANAGER_TYPE;
					using HOLDER_TYPE = typename MemoryStorage<H>::HOLDER_TYPE;
					using HOLDER_ARRAY_TYPE = typename MemoryStorage<H>::HOLDER_ARRAY_TYPE;

					virtual ~MemberStorage(){
						MemberStorageLog(pankey_Log_StartMethod, "Destructor", "");
						MemberStorageLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual Member<H,M> get(int a_position)const=0;

					virtual Member<H,M> removeByIndex(int a_position)=0;
					
					template<class IM>
					Member<H,M> getMember(IM a_iteration_method){
						MemoryStorageLog(pankey_Log_StartMethod, "getMember", "");
						if(this->isNull() || this->getSize() <= 0){
							MemoryStorageLog(pankey_Log_EndMethod, "getMember", "this->isNull() || this->getSize() <= 0");
							return Member<H,M>();
						}
						for(int x = 0; x < this->getSize(); x++){
							Member<H,M> f_member = this->get(x);
							if (a_iteration_method(x, this->getSize(), f_member)){
								return f_member;
							}
						}
						MemoryStorageLog(pankey_Log_EndMethod, "getMember", "");
						return Member<H,M>();
					}
					
			};

		}

	}

#endif