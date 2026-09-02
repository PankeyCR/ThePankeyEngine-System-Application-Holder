
#ifndef InvokeList_hpp
	#define InvokeList_hpp
	
	#include "pankey_HolderSystem.hpp"

	#include "InvokeMethod.hpp"

	#if defined(pankey_Log) && (defined(InvokeList_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define InvokeListLog(status,method,mns) pankey_Log(status,"InvokeList",method,mns)
	#else
		#define InvokeListLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class T>
			using invoking = obj<T>;

			template<class T>
			using InvokerList = OList<T>;

			template<class T, class... Args>
			void invoke(invoking<T> a_invoke, Base::InvokeClassMethod<T,Args...> a_method, Args... args){
				InvokeListLog(pankey_Log_StartMethod, "invoke", "");
				if(a_invoke.isNull()){
					InvokeListLog(pankey_Log_EndMethod, "invoke", "i_event.isNull()");
					return;
				}
				void* i_pointer = a_invoke.getRawPointer();
				invoke<T,Args...>(*((T*)i_pointer), a_method, args...);
				InvokeListLog(pankey_Log_EndMethod, "invoke", "");
			}

			template<class T, class... Args>
			void invoke(const InvokerList<T>& a_list, int a_index, Base::InvokeClassMethod<T,Args...> a_method, Args... args){
				InvokeListLog(pankey_Log_StartMethod, "invoke", "");
				invoking<T> i_event = a_list.get(a_index);
				if(i_event.isNull()){
					InvokeListLog(pankey_Log_EndMethod, "invoke", "i_event.isNull()");
					return;
				}
				void* i_pointer = i_event.getRawPointer();
				invoke<T,Args...>(*((T*)i_pointer), a_method, args...);
				InvokeListLog(pankey_Log_EndMethod, "invoke", "");
			}

			template<class T, class... Args>
			void invokeAll(const InvokerList<T>& a_list, Base::InvokeClassMethod<T,Args...> a_method, Args... args){
				InvokeListLog(pankey_Log_StartMethod, "invokeAll", "");
				for(int x = 0; x < a_list.length(); x++){
					invoking<T> i_event = a_list.get(x);
					if(i_event.isNull()){
						InvokeListLog(pankey_Log_EndMethod, "invokeAll", "");
						return;
					}
					void* i_pointer = i_event.getRawPointer();
					invoke<T,Args...>(*((T*)i_pointer), a_method, args...);
				}
				InvokeListLog(pankey_Log_EndMethod, "invokeAll", "");
			}
	/*
			template<class R, class... Args>
			R invoke(const CommandReturnList<R,Args...>& a_list, int a_index, Args... args){
				InvokeListLog(pankey_Log_StartMethod, "invoke", "");
				commandReturn<R,Args...> i_event = a_list.get(a_index);
				if(i_event.isNull()){
					InvokeListLog(pankey_Log_EndMethod, "invoke", "");
					return R();
				}
				InvokeListLog(pankey_Log_EndMethod, "invoke", "");
				return i_event->execute(args...);
			}

			template<class R, class... Args>
			R invokeAll(const CommandReturnList<R,Args...>& a_list, Args... args){
				InvokeListLog(pankey_Log_StartMethod, "invokeAll", "");
				for(int x = 0; x < a_list.length(); x++){
					commandReturn<R,Args...> i_event = a_list.get(x);
					if(i_event.isNull()){
						InvokeListLog(pankey_Log_EndMethod, "invokeAll", "");
						return R();
					}
					i_event->execute(args...);
				}
				InvokeListLog(pankey_Log_EndMethod, "invokeAll", "");
			}*/

		}
		
	}

#endif