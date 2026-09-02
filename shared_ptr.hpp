
#ifndef shared_ptr_hpp
	#define shared_ptr_hpp

	#include "InvokeMethod.hpp"
	#include "type_traits.hpp"
	#include "MemoryHolder.hpp"
	#include "ClassType.hpp"
	#include "ReferenceCountModel.hpp"

	#if defined(pankey_Log) && (defined(shared_ptr_Log) || defined(pankey_Global_Log) || defined(pankey_shared_ptrSystem_Log))
		#include "Logger_status.hpp"
		#define shared_ptrLog(status,method,mns) pankey_Log(status,"shared_ptr",method,mns)
	#else
		#define shared_ptrLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<typename T, typename M = ReferenceCountModel>
			class shared_ptr : public MemoryHolder<M>{
				public:
					using HOLDER_TYPE = typename M::HOLDER_TYPE;
					using MANAGER_TYPE = typename M::MANAGER_TYPE;

					shared_ptr(const MemoryHolder<M>& a_shared){
						shared_ptrLog(pankey_Log_StartMethod, "Constructor", "const MemoryHolder<M>&");
						shared_ptrLog(pankey_Log_Statement, "Constructor", "input type");
						shared_ptrLog(pankey_Log_Statement, "Constructor", a_shared.getType());
						shared_ptrLog(pankey_Log_Statement, "Constructor", "this type");
						shared_ptrLog(pankey_Log_Statement, "Constructor", Base::ClassType<T>::getId());
						shared_ptrLog(pankey_Log_Statement, "Constructor", "before count:");
						shared_ptrLog(pankey_Log_Statement, "Constructor", a_shared.getCount());
						this->copyHolder(a_shared.getHolder());
						shared_ptrLog(pankey_Log_Statement, "Constructor", "after count:");
						shared_ptrLog(pankey_Log_Statement, "Constructor", a_shared.getCount());
						shared_ptrLog(pankey_Log_EndMethod, "Constructor", "");
					}

					shared_ptr(){
						shared_ptrLog(pankey_Log_StartMethod, "Constructor", "");
						shared_ptrLog(pankey_Log_EndMethod, "Constructor", "");
					}

					template<class U>
					shared_ptr(const shared_ptr<U,M>& a_shared){
						shared_ptrLog(pankey_Log_StartMethod, "Constructor", "template<U> const shared_ptr<U>&");
						shared_ptrLog(pankey_Log_Statement, "Constructor", "input type");
						shared_ptrLog(pankey_Log_Statement, "Constructor", Base::ClassType<U>::getId());
						shared_ptrLog(pankey_Log_Statement, "Constructor", "this type");
						shared_ptrLog(pankey_Log_Statement, "Constructor", Base::ClassType<T>::getId());
						shared_ptrLog(pankey_Log_Statement, "Constructor", "is base of:");
						shared_ptrLog(pankey_Log_Statement, "Constructor", bool(Base::is_base_of<T,U>()));
						shared_ptrLog(pankey_Log_Statement, "Constructor", "before count:");
						shared_ptrLog(pankey_Log_Statement, "Constructor", a_shared.getCount());
						if(Base::is_base_of<T,U>() || a_shared.getType() == Base::ClassType<T>::getId()){
							this->copyHolder(a_shared.getHolder());
						}
						shared_ptrLog(pankey_Log_Statement, "Constructor", "after count:");
						shared_ptrLog(pankey_Log_Statement, "Constructor", a_shared.getCount());
						shared_ptrLog(pankey_Log_EndMethod, "Constructor", "");
					}

					template<class U>
					shared_ptr(shared_ptr<U,M>&& a_shared){
						shared_ptrLog(pankey_Log_StartMethod, "Constructor", "template<U> shared_ptr<U>&&");
						shared_ptrLog(pankey_Log_Statement, "Constructor", "input type");
						shared_ptrLog(pankey_Log_Statement, "Constructor", Base::ClassType<U>::getId());
						shared_ptrLog(pankey_Log_Statement, "Constructor", "this type");
						shared_ptrLog(pankey_Log_Statement, "Constructor", Base::ClassType<T>::getId());
						shared_ptrLog(pankey_Log_Statement, "Constructor", "is base of:");
						shared_ptrLog(pankey_Log_Statement, "Constructor", bool(Base::is_base_of<T,U>()));
						shared_ptrLog(pankey_Log_Statement, "Constructor", "before count:");
						shared_ptrLog(pankey_Log_Statement, "Constructor", a_shared.getCount());
						if(Base::is_base_of<T,U>() || a_shared.getType() == Base::ClassType<T>::getId()){
							shared_ptrLog(pankey_Log_Statement, "Constructor", "is_base_of");
							this->moveHolder(a_shared.getHolder());
							a_shared.moveHolder(nullptr);
						}
						shared_ptrLog(pankey_Log_Statement, "Constructor", "after count:");
						shared_ptrLog(pankey_Log_Statement, "Constructor", a_shared.getCount());
						shared_ptrLog(pankey_Log_EndMethod, "Constructor", "");
					}

					virtual ~shared_ptr(){
						shared_ptrLog(pankey_Log_StartMethod, "Destructor", "");
						shared_ptrLog(pankey_Log_EndMethod, "Destructor", "");
					}

					shared_ptr& operator=(shared_ptr&& a_shared){
						this->m_holder = a_shared.m_holder;
						a_shared.m_holder = nullptr;
						return *this;
					}

					T* operator->() const {
						return (this->m_holder != nullptr) ? (T*)this->m_holder->m_pointer : nullptr;
					}

					T* get(){
						return (this->m_holder != nullptr) ? (T*)this->m_holder->m_pointer : nullptr;
						// return MANAGER_TYPE::template getPointerType<T>(this->m_holder);
					}

					// Safe method invocation (member function only)
					template<typename Method, typename... Args>
					void invoke(Method a_method, Args... a_args){
						if (this->m_holder != nullptr){
							if (this->m_holder->m_pointer != nullptr){
								invoke(*((T*)this->m_holder->m_pointer), a_method, a_args...);
							}
						}
					}
			};

		}

	}

#endif