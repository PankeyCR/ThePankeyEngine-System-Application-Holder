
#ifndef HolderManager_hpp
	#define HolderManager_hpp

	#include "Holder.hpp"
	#include "ClassType.hpp"

	#if defined(pankey_Log) && (defined(HolderManager_Log) || defined(pankey_Global_Log) || defined(pankey_Network_Log))
		#include "Logger_status.hpp"
		#define HolderManagerLog(status,method,mns) pankey_Log(status,"HolderManager",method,mns)
	#else
		#define HolderManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			struct HolderManager{

				static int increment(Holder* a_holder){
					if(a_holder != nullptr){
						++a_holder->m_count;
						return a_holder->m_count;
					}
					return 0;
				}

				static int decrement(Holder* a_holder){
					if(a_holder != nullptr){
						--a_holder->m_count;
						return a_holder->m_count;
					}
					return 0;
				}

				static void setCount(Holder* a_holder, unsigned int a_count){
					if(a_holder != nullptr){
						a_holder->m_count = a_count;
					}
				}

				static unsigned int getCount(Holder* a_holder){
					return (a_holder != nullptr) ? a_holder->m_count : 0;
				}

				static void setBaseType(Holder* a_holder, int a_type){
					if(a_holder != nullptr){
						a_holder->m_base_type = a_type;
					}
				}

				static int getBaseType(Holder* a_holder){
					return (a_holder != nullptr) ? a_holder->m_base_type : -1;
				}

				static void setType(Holder* a_holder, int a_type){
					if(a_holder != nullptr){
						a_holder->m_type = a_type;
					}
				}

				static int getType(Holder* a_holder){
					return (a_holder != nullptr) ? a_holder->m_type : -1;
				}

				static bool isNull(Holder* a_holder){
					if(a_holder != nullptr){
						return a_holder->m_pointer == nullptr;
					}
					return true;
				}

				template<class T>
				static T* getPointerType(Holder* a_holder){
					HolderManagerLog(pankey_Log_StartMethod, "getPointerType",  "");
					if(a_holder != nullptr){
						HolderManagerLog(pankey_Log_EndMethod, "getPointerType",  "a_holder != nullptr");
						if(a_holder->m_pointer != nullptr){
							HolderManagerLog(pankey_Log_EndMethod, "getPointerType",  "a_holder->m_pointer != nullptr");
							if(a_holder->m_type == Base::ClassType<T>::getId()){
								HolderManagerLog(pankey_Log_EndMethod, "getPointerType",  "a_holder->m_type == Base::ClassType<T>::getId()");
								return (T*)a_holder->m_pointer;
							}
						}
					}
					HolderManagerLog(pankey_Log_EndMethod, "getPointerType",  "nullptr");
					return nullptr;
				}

				static void* getRawPointer(Holder* a_holder){
					HolderManagerLog(pankey_Log_StartMethod, "getRawPointer",  "");
					if(a_holder != nullptr){
						HolderManagerLog(pankey_Log_EndMethod, "getRawPointer",  "a_holder != nullptr");
						if(a_holder->m_pointer != nullptr){
							HolderManagerLog(pankey_Log_EndMethod, "getRawPointer",  "a_holder->m_pointer != nullptr");
							return a_holder->m_pointer;
						}
					}
					HolderManagerLog(pankey_Log_EndMethod, "getRawPointer",  "nullptr");
					return nullptr;
				}

				static void destroy(Holder* a_holder){
					if(a_holder == nullptr){
						return;
					}
					--a_holder->m_count;

					if (a_holder->m_count <= 0){
						a_holder->destroyObject();
						a_holder->destroyHolder();
					}

					a_holder = nullptr;
				}
			};

		}

	}

#endif