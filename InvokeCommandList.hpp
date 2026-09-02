
#ifndef InvokeCommandList_hpp
	#define InvokeCommandList_hpp

	#include "Command.hpp"
	#include "CommandReturn.hpp"

	#if defined(pankey_Log) && (defined(InvokeCommandList_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define InvokeCommandListLog(status,method,mns) pankey_Log(status,"InvokeCommandList",method,mns)
	#else
		#define InvokeCommandListLog(status,method,mns)
	#endif
	
	namespace pankey{

		namespace HolderSystem{

			template<class... Args>
			using CommandList = OList<Base::Command<Args...>>;

			template<class R, class... Args>
			using CommandReturnList = OList<Base::CommandReturn<R,Args...>>;

			template<class... Args>
			void invoke(const CommandList<Args...>& a_list, int a_index, Args... args){
				InvokeCommandListLog(pankey_Log_StartMethod, "invoke", "");
				command<Args...> i_event = a_list.get(a_index);
				if(i_event.isNull()){
					InvokeCommandListLog(pankey_Log_EndMethod, "invoke", "");
					return;
				}
				i_event->execute(args...);
				InvokeCommandListLog(pankey_Log_EndMethod, "invoke", "");
			}

			template<class... Args>
			void invokeAll(const CommandList<Args...>& a_list, Args... args){
				InvokeCommandListLog(pankey_Log_StartMethod, "invokeAll", "");
				for(int x = 0; x < a_list.length(); x++){
					command<Args...> i_event = a_list.get(x);
					if(i_event.isNull()){
						InvokeCommandListLog(pankey_Log_EndMethod, "invokeAll", "");
						return;
					}
					i_event->execute(args...);
				}
				InvokeCommandListLog(pankey_Log_EndMethod, "invokeAll", "");
			}

			template<class R, class... Args>
			R invoke(const CommandReturnList<R,Args...>& a_list, int a_index, Args... args){
				InvokeCommandListLog(pankey_Log_StartMethod, "invoke", "");
				commandReturn<R,Args...> i_event = a_list.get(a_index);
				if(i_event.isNull()){
					InvokeCommandListLog(pankey_Log_EndMethod, "invoke", "");
					return R();
				}
				InvokeCommandListLog(pankey_Log_EndMethod, "invoke", "");
				return i_event->execute(args...);
			}

			template<class R, class... Args>
			R invokeAll(const CommandReturnList<R,Args...>& a_list, Args... args){
				InvokeCommandListLog(pankey_Log_StartMethod, "invokeAll", "");
				for(int x = 0; x < a_list.length(); x++){
					commandReturn<R,Args...> i_event = a_list.get(x);
					if(i_event.isNull()){
						InvokeCommandListLog(pankey_Log_EndMethod, "invokeAll", "");
						return R();
					}
					i_event->execute(args...);
				}
				InvokeCommandListLog(pankey_Log_EndMethod, "invokeAll", "");
			}

		}
		
	}
			

#endif