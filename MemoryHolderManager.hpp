
#ifndef MemoryHolderManager_hpp
	#define MemoryHolderManager_hpp

    #include "MemoryManager.hpp"

	#if defined(pankey_Log) && (defined(MemoryHolderManager_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
        #define MemoryHolderManagerLog(status,method,mns) pankey_Log(status,"MemoryHolderManager",method,mns)
    #else
        #define MemoryHolderManagerLog(status,method,mns)
    #endif

	namespace pankey{

		namespace HolderSystem{

            template<class H>
            class MemoryHolderManager{
                public:

                using MANAGER_TYPE = MemoryManager<H>*;
                using VOID_TYPE = typename MemoryManager<H>::VOID_TYPE;
                using HOLDER_TYPE = typename MemoryManager<H>::HOLDER_TYPE;

                static void setType(MANAGER_TYPE a_manager, HOLDER_TYPE& a_holder, long a_type){
                    MemoryHolderManagerLog(pankey_Log_StartMethod, "setType", "");
                    if(a_manager == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "setType", "m_allocator == nullptr");
                        return;
                    }
                    if(a_holder == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "setType", "a_holder == nullptr");
                        return;
                    }
                    MemoryHolderManagerLog(pankey_Log_EndMethod, "setType", "");
                    a_manager->setType(a_holder, a_type);
                }
                
                static long getType(MANAGER_TYPE a_manager, const HOLDER_TYPE& a_holder){
                    MemoryHolderManagerLog(pankey_Log_StartMethod, "getType", "");
                    if(a_manager == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "getType", "m_allocator == nullptr");
                        return -1;
                    }
                    if(a_holder == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "getType", "a_holder == nullptr");
                        return -1;
                    }
                    MemoryHolderManagerLog(pankey_Log_EndMethod, "getType", "");
                    return a_manager->getType(a_holder);
                }

                static void setBaseType(MANAGER_TYPE a_manager, HOLDER_TYPE& a_holder, long a_type){
                    MemoryHolderManagerLog(pankey_Log_StartMethod, "setBaseType", "");
                    if(a_manager == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "setBaseType", "m_allocator == nullptr");
                        return;
                    }
                    if(a_holder == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "setBaseType", "a_holder == nullptr");
                        return;
                    }
                    MemoryHolderManagerLog(pankey_Log_EndMethod, "setBaseType", "");
                    a_manager->setBaseType(a_holder, a_type);
                }
                
                static long getBaseType(MANAGER_TYPE a_manager, const HOLDER_TYPE& a_holder){
                    MemoryHolderManagerLog(pankey_Log_StartMethod, "getBaseType", "");
                    if(a_manager == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "getBaseType", "m_allocator == nullptr");
                        return -1;
                    }
                    if(a_holder == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "getBaseType", "a_holder == nullptr");
                        return -1;
                    }
                    MemoryHolderManagerLog(pankey_Log_EndMethod, "getBaseType", "");
                    return a_manager->getBaseType(a_holder);
                }
                
                static HOLDER_TYPE newHolder(MANAGER_TYPE a_manager){
                    MemoryHolderManagerLog(pankey_Log_StartMethod, "newHolder", "");
                    if(a_manager == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "newHolder", "m_allocator == nullptr");
                        return nullptr;
                    }
                    MemoryHolderManagerLog(pankey_Log_EndMethod, "newHolder", "");
                    return a_manager->newHolder();
                }
                
                static HOLDER_TYPE newInstance(MANAGER_TYPE a_manager, long a_type, Base::MemoryAllocator* a_allocator){
                    MemoryHolderManagerLog(pankey_Log_StartMethod, "newInstance", "");
                    if(a_manager == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "newInstance", "m_allocator == nullptr");
                        return nullptr;
                    }
                    MemoryHolderManagerLog(pankey_Log_EndMethod, "newInstance", "");
                    return a_manager->newInstance(a_type, a_allocator);
                }
                
                static HOLDER_TYPE newInstance(MANAGER_TYPE a_manager, long a_type, Base::memory_size a_size, Base::MemoryAllocator* a_allocator){
                    MemoryHolderManagerLog(pankey_Log_StartMethod, "newInstance", "");
                    if(a_manager == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "newInstance", "m_allocator == nullptr");
                        return nullptr;
                    }
                    MemoryHolderManagerLog(pankey_Log_EndMethod, "newInstance", "");
                    return a_manager->newInstance(a_type, a_size, a_allocator);
                }
                
                static void setManageableCheck(MANAGER_TYPE a_manager, HOLDER_TYPE& a_holder, bool a_check){
                    MemoryHolderManagerLog(pankey_Log_StartMethod, "setManageableCheck", "");
                    if(a_manager == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "setManageableCheck", "m_allocator == nullptr");
                        return;
                    }
                    MemoryHolderManagerLog(pankey_Log_EndMethod, "setManageableCheck", "");
                    a_manager->setManageableCheck(a_holder, a_check);
                }
                
                static void set(MANAGER_TYPE a_manager, HOLDER_TYPE& a_holder, HOLDER_TYPE& a_set_holder){
                    MemoryHolderManagerLog(pankey_Log_StartMethod, "set", "");
                    if(a_manager == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "set", "m_allocator == nullptr");
                        return;
                    }
                    if(a_holder == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "set", "a_holder == nullptr");
                        return;
                    }
                    MemoryHolderManagerLog(pankey_Log_EndMethod, "set", "");
                    a_manager->set(a_holder, a_set_holder);
                }
                
                static void add(MANAGER_TYPE a_manager, HOLDER_TYPE& a_holder){
                    MemoryHolderManagerLog(pankey_Log_StartMethod, "add", "");
                    if(a_manager == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "add", "m_allocator == nullptr");
                        return;
                    }
                    if(a_holder == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "add", "a_holder == nullptr");
                        return;
                    }
                    a_manager->add(a_holder);
                    MemoryHolderManagerLog(pankey_Log_EndMethod, "add", "");
                }
                
                static void remove(MANAGER_TYPE a_manager, HOLDER_TYPE& a_holder){
                    MemoryHolderManagerLog(pankey_Log_StartMethod, "remove", "");
                    if(a_manager == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "remove", "m_allocator == nullptr");
                        return;
                    }
                    if(a_holder == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "remove", "a_holder == nullptr");
                        return;
                    }
                    MemoryHolderManagerLog(pankey_Log_EndMethod, "remove", "");
                    a_manager->remove(a_holder);
                }
                
                static void destroy(MANAGER_TYPE a_manager, HOLDER_TYPE& a_holder){
                    MemoryHolderManagerLog(pankey_Log_StartMethod, "destroy", "");
                    if(a_manager == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "destroy", "m_allocator == nullptr");
                        return;
                    }
                    if(a_holder == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "destroy", "a_holder == nullptr");
                        return;
                    }
                    MemoryHolderManagerLog(pankey_Log_EndMethod, "destroy", "");
                    a_manager->destroy(a_holder);
                }
                
                static VOID_TYPE get(MANAGER_TYPE a_manager, const HOLDER_TYPE& a_holder){
                    MemoryHolderManagerLog(pankey_Log_StartMethod, "get", "");
                    if(a_manager == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "get", "m_allocator == nullptr");
                        return nullptr;
                    }
                    if(a_holder == nullptr){
                        MemoryHolderManagerLog(pankey_Log_EndMethod, "get", "a_holder == nullptr");
                        return nullptr;
                    }
                    MemoryHolderManagerLog(pankey_Log_EndMethod, "get", "");
                    return a_manager->get(a_holder);
                }
                
            };

        }

	}

#endif