
#ifndef InvokeCommandMap_hpp
	#define InvokeCommandMap_hpp
	
	#include "pankey_HolderSystem.hpp"

	#include "Command.hpp"
	#include "CommandReturn.hpp"

	#if defined(pankey_Log) && (defined(InvokeCommandMap_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define InvokeCommandMapLog(status,method,mns) pankey_Log(status,"InvokeCommandMap",method,mns)
	#else
		#define InvokeCommandMapLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class K, class... Args>
			using CommandMap = Map;

			template<class K, class R, class... Args>
			using CommandReturnMap = OList<Base::CommandReturn<R,Args...>>;

			template<class K, class... Args>
			void invoke(const CommandMap<K,Args...>& a_map, int a_index, Args... args){
				InvokeCommandMapLog(pankey_Log_StartMethod, "invoke", "");
				command<Args...> i_event = a_map.getValue(a_index);
				if(i_event.isNull()){
					InvokeCommandMapLog(pankey_Log_EndMethod, "invoke", "");
					return;
				}
				i_event->execute(args...);
				InvokeCommandMapLog(pankey_Log_EndMethod, "invoke", "");
			}
	/*
			template<class... Args>
			void invokeAll(const CommandList<Args...>& a_list, Args... args){
				InvokeCommandMapLog(pankey_Log_StartMethod, "invokeAll", "");
				for(int x = 0; x < a_list.length(); x++){
					command<Args...> i_event = a_list.get(x);
					if(i_event.isNull()){
						InvokeCommandMapLog(pankey_Log_EndMethod, "invokeAll", "");
						return;
					}
					i_event->execute(args...);
				}
				InvokeCommandMapLog(pankey_Log_EndMethod, "invokeAll", "");
			}

			template<class R, class... Args>
			R invoke(const CommandReturnList<R,Args...>& a_list, int a_index, Args... args){
				InvokeCommandMapLog(pankey_Log_StartMethod, "invoke", "");
				commandReturn<R,Args...> i_event = a_list.get(a_index);
				if(i_event.isNull()){
					InvokeCommandMapLog(pankey_Log_EndMethod, "invoke", "");
					return R();
				}
				InvokeCommandMapLog(pankey_Log_EndMethod, "invoke", "");
				return i_event->execute(args...);
			}

			template<class R, class... Args>
			R invokeAll(const CommandReturnList<R,Args...>& a_list, Args... args){
				InvokeCommandMapLog(pankey_Log_StartMethod, "invokeAll", "");
				for(int x = 0; x < a_list.length(); x++){
					commandReturn<R,Args...> i_event = a_list.get(x);
					if(i_event.isNull()){
						InvokeCommandMapLog(pankey_Log_EndMethod, "invokeAll", "");
						return R();
					}
					i_event->execute(args...);
				}
				InvokeCommandMapLog(pankey_Log_EndMethod, "invokeAll", "");
			}*/
		
		}
			
	}

#endif