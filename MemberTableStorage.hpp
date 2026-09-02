
#ifndef MemberTableStorage_hpp
	#define MemberTableStorage_hpp

	#include "TableStorage.hpp"
	#include "Member.hpp"

	#if defined(pankey_Log) && (defined(MemberTableStorage_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define MemberTableStorageLog(status,method,mns) pankey_Log(status,"MemberTableStorage",method,mns)
	#else
		#define MemberTableStorageLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class H, class M>
			class MemberTableStorage : virtual public TableStorage<H>{
				public:

					using MANAGER_TYPE = typename MemoryStorage<H>::MANAGER_TYPE;
					using HOLDER_TYPE = typename MemoryStorage<H>::HOLDER_TYPE;

					virtual ~MemberTableStorage(){
						MemberTableStorageLog(pankey_Log_StartMethod, "Destructor", "");
						MemberTableStorageLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual Member<H,M> get(int a_position)const=0;

					virtual Member<H,M> removeByIndex(int a_position)=0;
					
			};

		}

	}

#endif