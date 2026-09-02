
#ifndef UniversalManager_hpp
	#define UniversalManager_hpp

	#include "MemoryManager.hpp"
	#include "UniversalHolder.hpp"
	#include "MemorySize.hpp"

	#if defined(pankey_Log) && (defined(UniversalManager_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define UniversalManagerLog(status,method,mns) pankey_Log(status,"UniversalManager",method,mns)
	#else
		#define UniversalManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			class UniversalManager : public MemoryManager<UniversalHolder>{
				public:
					using VOID_TYPE = typename MemoryManager<UniversalHolder>::VOID_TYPE;
					using HOLDER_TYPE = typename MemoryManager<UniversalHolder>::HOLDER_TYPE;
					
					UniversalManager(){
						UniversalManagerLog(pankey_Log_StartMethod, "Constructor", "");
						UniversalManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~UniversalManager(){
						UniversalManagerLog(pankey_Log_StartMethod, "Destructor", "");
						UniversalManagerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual void setType(HOLDER_TYPE& a_holder, long a_type){
						UniversalManagerLog(pankey_Log_StartMethod, "setType", "");
						if(a_holder == nullptr){
							UniversalManagerLog(pankey_Log_EndMethod, "setType", "a_holder == nullptr");
							return;
						}
						a_holder->m_type = a_type;
						UniversalManagerLog(pankey_Log_EndMethod, "setType", "");
					}

					virtual long getType(const HOLDER_TYPE& a_holder){
						UniversalManagerLog(pankey_Log_StartMethod, "getType", "");
						if(a_holder == nullptr){
							UniversalManagerLog(pankey_Log_EndMethod, "getType", "a_holder == nullptr");
							return -1;
						}
						UniversalManagerLog(pankey_Log_EndMethod, "getType", "");
						return a_holder->m_type;
					}

					virtual void setBaseType(HOLDER_TYPE& a_holder, long a_type){
						UniversalManagerLog(pankey_Log_StartMethod, "setBaseType", "");
						if(a_holder == nullptr){
							UniversalManagerLog(pankey_Log_EndMethod, "setBaseType", "a_holder == nullptr");
							return;
						}
						a_holder->m_base_type = a_type;
						UniversalManagerLog(pankey_Log_EndMethod, "setBaseType", "");
					}

					virtual long getBaseType(const HOLDER_TYPE& a_holder){
						UniversalManagerLog(pankey_Log_StartMethod, "getBaseType", "");
						if(a_holder == nullptr){
							UniversalManagerLog(pankey_Log_EndMethod, "getBaseType", "a_holder == nullptr");
							return -1;
						}
						UniversalManagerLog(pankey_Log_EndMethod, "getBaseType", "");
						return a_holder->m_base_type;
					}

					virtual HOLDER_TYPE newHolder(){
						UniversalManagerLog(pankey_Log_StartMethod, "newHolder", "");
						UniversalHolder* i_erf =  new UniversalHolder();
						UniversalManagerLog(pankey_Log_EndMethod, "newHolder", "");
						return i_erf;
					}

					virtual HOLDER_TYPE newInstance(long a_type, Base::MemoryAllocator* a_allocator){
						UniversalManagerLog(pankey_Log_StartMethod, "newInstance", "with void*");
						UniversalHolder* i_holder =  new UniversalHolder();
						i_holder->m_allocator = a_allocator;
						if(a_allocator != nullptr){
							i_holder->m_pointer = a_allocator->create();
						}
						i_holder->m_type = a_type;
						UniversalManagerLog(pankey_Log_EndMethod, "newInstance", "");
						return i_holder;
					}

					virtual HOLDER_TYPE newInstance(long a_type, Base::memory_size a_size, Base::MemoryAllocator* a_allocator){
						UniversalManagerLog(pankey_Log_StartMethod, "newInstance", "with void*");
						UniversalHolder* i_holder =  new UniversalHolder();
						i_holder->m_allocator = a_allocator;
						if(a_allocator != nullptr){
							i_holder->m_pointer = a_allocator->create(a_size);
						}
						i_holder->m_type = a_type;
						UniversalManagerLog(pankey_Log_EndMethod, "newInstance", "");
						return i_holder;
					}

					virtual void setManageableCheck(HOLDER_TYPE& a_holder, bool a_check){
						UniversalManagerLog(pankey_Log_StartMethod, "setManageableCheck", "with void*");
						if(a_holder == nullptr){
							UniversalManagerLog(pankey_Log_EndMethod, "setManageableCheck", "a_holder == nullptr");
							return;
						}
						a_holder->m_maneged = a_check;
						UniversalManagerLog(pankey_Log_EndMethod, "setManageableCheck", "");
					}

					virtual void set(HOLDER_TYPE& a_holder, HOLDER_TYPE& a_set_holder){
						UniversalManagerLog(pankey_Log_StartMethod, "set", "");
						a_holder = a_set_holder;
						UniversalManagerLog(pankey_Log_EndMethod, "set", "");
					}

					virtual void add(HOLDER_TYPE& a_holder){
						UniversalManagerLog(pankey_Log_StartMethod, "add", "");
						if(a_holder == nullptr){
							UniversalManagerLog(pankey_Log_EndMethod, "add", "a_holder == nullptr");
							return;
						}
						a_holder->m_count++;
						UniversalManagerLog(pankey_Log_Statement, "add", "Count: ");
						UniversalManagerLog(pankey_Log_Statement, "add", a_holder->m_count);
						UniversalManagerLog(pankey_Log_EndMethod, "add", "");
					}

					virtual void remove(HOLDER_TYPE& a_holder){
						UniversalManagerLog(pankey_Log_StartMethod, "remove", "");
						if(a_holder == nullptr){
							UniversalManagerLog(pankey_Log_EndMethod, "remove", "a_holder == nullptr");
							return;
						}

						UniversalManagerLog(pankey_Log_Statement, "remove", "Count before: ");
						UniversalManagerLog(pankey_Log_Statement, "remove", a_holder->m_count);

						a_holder->m_count--;

						UniversalManagerLog(pankey_Log_Statement, "remove", "Count after: ");
						UniversalManagerLog(pankey_Log_Statement, "remove", a_holder->m_count);

						if(a_holder->m_count <= 0){
							if(a_holder->m_allocator != nullptr){
								UniversalManagerLog(pankey_Log_Statement, "remove", "a_holder->m_allocator != nullptr");
								if(a_holder->m_pointer != nullptr && a_holder->m_maneged){
									UniversalManagerLog(pankey_Log_Statement, "remove", "a_holder->m_pointer != nullptr");
									UniversalManagerLog(pankey_Log_Statement, "remove", "m_allocator->destroy");
									a_holder->m_allocator->destroy(a_holder->m_pointer);
								}
								if(a_holder->m_allocator->isManaged()){
									delete a_holder->m_allocator;
								}
							}

							delete a_holder;

							a_holder->m_allocator = nullptr;
							a_holder->m_pointer = nullptr;
							a_holder = nullptr;
							UniversalManagerLog(pankey_Log_Statement, "remove", "full remove");
						}else{
							a_holder = nullptr;
							UniversalManagerLog(pankey_Log_Statement, "remove", "partial null remove");
						}
						UniversalManagerLog(pankey_Log_EndMethod, "remove", "");
					}

					virtual void destroy(HOLDER_TYPE& a_holder){
						UniversalManagerLog(pankey_Log_StartMethod, "destroy", "");
						if(a_holder == nullptr){
							UniversalManagerLog(pankey_Log_EndMethod, "destroy", "a_holder == nullptr");
							return;
						}

						UniversalManagerLog(pankey_Log_Statement, "destroy", "Count before: ");
						UniversalManagerLog(pankey_Log_Statement, "destroy", a_holder->m_count);

						a_holder->m_count--;

						UniversalManagerLog(pankey_Log_Statement, "destroy", "Count after: ");
						UniversalManagerLog(pankey_Log_Statement, "destroy", a_holder->m_count);

						if(a_holder->m_count <= 0){
							if(a_holder->m_allocator != nullptr){
								UniversalManagerLog(pankey_Log_Statement, "destroy", "a_holder->m_allocator != nullptr");
								if(a_holder->m_pointer != nullptr && a_holder->m_maneged){
									UniversalManagerLog(pankey_Log_Statement, "destroy", "a_holder->m_pointer != nullptr");
									UniversalManagerLog(pankey_Log_Statement, "remove", "m_allocator->destroy");
									a_holder->m_allocator->destroy(a_holder->m_pointer);
								}
								if(a_holder->m_allocator->isManaged()){
									delete a_holder->m_allocator;
								}
							}

							delete a_holder;

							a_holder->m_allocator = nullptr;
							a_holder->m_pointer = nullptr;
							a_holder = nullptr;
							UniversalManagerLog(pankey_Log_Statement, "destroy", "full remove");
						}else{
							if(a_holder->m_allocator != nullptr){
								UniversalManagerLog(pankey_Log_Statement, "destroy", "a_holder->m_allocator != nullptr");
								if(a_holder->m_pointer != nullptr && a_holder->m_maneged){
									UniversalManagerLog(pankey_Log_Statement, "destroy", "a_holder->m_pointer != nullptr");
									UniversalManagerLog(pankey_Log_Statement, "remove", "m_allocator->destroy");
									a_holder->m_allocator->destroy(a_holder->m_pointer);
								}
								if(a_holder->m_allocator->isManaged()){
									delete a_holder->m_allocator;
								}
							}

							a_holder->m_allocator = nullptr;
							a_holder->m_pointer = nullptr;
							a_holder = nullptr;
							UniversalManagerLog(pankey_Log_Statement, "destroy", "partial null remove");
						}
						UniversalManagerLog(pankey_Log_EndMethod, "destroy", "");
					}

					virtual VOID_TYPE get(const HOLDER_TYPE& a_holder){
						UniversalManagerLog(pankey_Log_StartMethod, "get", "");
						if(a_holder == nullptr){
							UniversalManagerLog(pankey_Log_EndMethod, "get", "a_holder == nullptr");
							return nullptr;
						}
						UniversalManagerLog(pankey_Log_EndMethod, "get", "");
						return a_holder->m_pointer;
					}
			};

		}

	}

#endif