
#ifndef StaticManagerInstance_hpp
	#define StaticManagerInstance_hpp

    #include "MemoryManager.hpp"

	#if defined(pankey_Log) && (defined(StaticManagerInstance_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
        #define StaticManagerInstanceLog(status,method,mns) pankey_Log(status,"StaticManagerInstance",method,mns)
    #else
        #define StaticManagerInstanceLog(status,method,mns)
    #endif

	namespace pankey{

		namespace HolderSystem{

			template<class H, class M>
			struct StaticManagerInstance{
				static MemoryManager<H>* m_Manager;

				static MemoryManager<H>* getManager(){
					StaticManagerInstanceLog(pankey_Log_StartMethod, "getManager", "");
					StaticManagerInstanceLog(pankey_Log_Statement, "getManager",  m_Manager == nullptr);
					StaticManagerInstanceLog(pankey_Log_EndMethod, "getManager", "");
					return m_Manager;
				}
			};

			template<class H, class M>
			MemoryManager<H>* StaticManagerInstance<H,M>::m_Manager = nullptr;

			template<class H, class M, class HA>
			void createManager(){
				StaticManagerInstanceLog(pankey_Log_StartMethod, "createManager", "");
				MemoryManager<H>* i_Manager = StaticManagerInstance<H,M>::m_Manager;
				if(i_Manager != nullptr){
					StaticManagerInstanceLog(pankey_Log_EndMethod, "createManager", "i_Manager != nullptr");
					return;
				}
				StaticManagerInstance<H,M>::m_Manager = new HA();
				StaticManagerInstanceLog(pankey_Log_EndMethod, "createManager", "");
			}
			 
		}
			 
	}

#endif