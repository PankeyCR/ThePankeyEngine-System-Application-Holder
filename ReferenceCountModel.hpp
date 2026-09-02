
#ifndef ReferenceCountModel_hpp
	#define ReferenceCountModel_hpp

	#include "Holder.hpp"
	#include "HolderManager.hpp"
	#include "ClassType.hpp"

	#if defined(pankey_Log) && (defined(ReferenceCountModel_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define ReferenceCountModelLog(status,method,mns) pankey_Log(status,"ReferenceCountModel",method,mns)
	#else
		#define ReferenceCountModelLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			struct ReferenceCountModel{
				using HOLDER_TYPE = Holder;
				using MANAGER_TYPE = HolderManager;
			};

			template<class T>
			void RCDeletePointer(void* a_pointer){
				ReferenceCountModelLog(pankey_Log_StartMethod, "RCDeletePointer", "");
				if(a_pointer == nullptr){
					ReferenceCountModelLog(pankey_Log_EndMethod, "RCDeletePointer", "a_pointer == nullptr");
					return;
				}
				delete (T*)a_pointer;
				ReferenceCountModelLog(pankey_Log_EndMethod, "RCDeletePointer", "");
			}
			template<class H>
			void RCDeleteHolder(H* a_holder){
				ReferenceCountModelLog(pankey_Log_StartMethod, "RCDeleteHolder", "");
				if(a_holder == nullptr){
					ReferenceCountModelLog(pankey_Log_EndMethod, "RCDeleteHolder", "a_holder == nullptr");
					return;
				}
				delete a_holder;
				ReferenceCountModelLog(pankey_Log_EndMethod, "RCDeleteHolder", "");
			}

			void destroy(ReferenceCountModel a_model, Holder*& a_holder){
				ReferenceCountModelLog(pankey_Log_StartMethod, "destroy", "");
				if(a_holder == nullptr){
					ReferenceCountModelLog(pankey_Log_EndMethod, "destroy", "a_holder == nullptr");
					return;
				}
				ReferenceCountModelLog(pankey_Log_Statement, "destroy", "Count before decrement:");
				ReferenceCountModelLog(pankey_Log_Statement, "destroy", a_holder->m_count);
				--a_holder->m_count;
				ReferenceCountModelLog(pankey_Log_Statement, "destroy", "Count after decrement:");
				ReferenceCountModelLog(pankey_Log_Statement, "destroy", a_holder->m_count);

				if (a_holder->m_count <= 0){
					ReferenceCountModelLog(pankey_Log_Statement, "destroy", "a_holder->m_count <= 0");
					a_holder->destroyObject();
					a_holder->destroyHolder();
				}

				a_holder = nullptr;
				ReferenceCountModelLog(pankey_Log_EndMethod, "destroy", "");
			}

			template<class T, class... Args>
			Holder* create(ReferenceCountModel a_model, Args... a_args){
				ReferenceCountModelLog(pankey_Log_StartMethod, "create", "");
				T* i_obj = new T(a_args...);

				Holder* i_holder = new Holder;
				i_holder->m_pointer = i_obj;
				i_holder->m_type = Base::ClassType<T>::getId();
				i_holder->m_destroy_object = RCDeletePointer<T>;
				i_holder->m_destroy_holder = RCDeleteHolder<Holder>;

				ReferenceCountModelLog(pankey_Log_EndMethod, "create", "");
				return i_holder;
			}
			

		}

	}

#endif
