
#ifndef Pointer_hpp
	#define Pointer_hpp

	#include "StaticManagerInstance.hpp"
	#include "MemoryHolderManager.hpp"
	#include "ClassCount.hpp"
	#include "MemoryHolder.hpp"
    #include "Member.hpp"
    #include "StaticAllocatorInstance.hpp"
    #include "SimpleMemoryAllocator.hpp"
    #include "MemorySize.hpp"

	#if defined(pankey_Log) && (defined(Pointer_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define PointerLog(status,method,mns) pankey_Log(status,"Pointer",method,mns)
	#else
		#define PointerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class P, class H, class M>
			class Pointer : public Member<H,M>{
				public:
					using INSTANCE_TYPE = P*;
					using MANAGER_TYPE = typename Member<H,M>::MANAGER_TYPE;
					using VOID_TYPE = typename Member<H,M>::VOID_TYPE;
					using HOLDER_TYPE = typename Member<H,M>::HOLDER_TYPE;
					
					Pointer(){
						PointerLog(pankey_Log_StartMethod, "Contructor", "");
						PointerLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Pointer(const MemoryHolder<H>& a_pointer){
						PointerLog(pankey_Log_StartMethod, "Contructor", "const MemoryHolder<H>&");
						if(!a_pointer.isMember(this->getManager(), Base::ClassCount<P>::get())){
							PointerLog(pankey_Log_EndMethod, "Constructor", "!a_pointer.isMember(this->getManager(), Base::ClassCount<P>::get())");
							return;
						}
						this->setHolder(a_pointer.getHolder());
						PointerLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Pointer(const Member<H,M>& a_pointer){
						PointerLog(pankey_Log_StartMethod, "Contructor", "const Member<H,M>&");
						if(!a_pointer.sameType(Base::ClassCount<P>::get())){
							PointerLog(pankey_Log_EndMethod, "Constructor", "!a_pointer.sameType(Base::ClassCount<P>::get())");
							return;
						}
						this->setHolder(a_pointer.getHolder());
						PointerLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Pointer(const Pointer<P,H,M>& a_pointer){
						PointerLog(pankey_Log_StartMethod, "Contructor", "const Pointer<P,H,M>&");
						this->setHolder(a_pointer.getHolder());
						PointerLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Pointer(P* a_pointer){
						PointerLog(pankey_Log_StartMethod, "Contructor", "const Pointer<P,H,M>&");
						this->m_holder = MemoryHolderManager<H>::newInstance(this->getManager(), Base::ClassCount<P>::get(), new Base::SimpleMemoryAllocator<P>(a_pointer));
						MemoryHolderManager<H>::add(this->getManager(), this->m_holder);
						PointerLog(pankey_Log_EndMethod, "Contructor", "");
					}

					virtual ~Pointer(){
						PointerLog(pankey_Log_StartMethod, "Destructor", "");
						PointerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual void create(){
						PointerLog(pankey_Log_StartMethod, "create",  "");
						PointerLog(pankey_Log_Statement, "create",  "Base::ClassCount<P>::get(): ");
						PointerLog(pankey_Log_Statement, "create",  Base::ClassCount<P>::get());
						PointerLog(pankey_Log_Statement, "create",  "sizeOfPointer<P>(): ");
						PointerLog(pankey_Log_Statement, "create",  sizeOfPointer<P>());
						VOID_TYPE i_pointer = this->getRawPointer();
						if(i_pointer != nullptr){
							return;
						}
						HOLDER_TYPE i_holder = MemoryHolderManager<H>::newInstance(this->getManager(), Base::ClassCount<P>::get(), sizeof(P), Base::StaticAllocatorInstance<P>::getAllocator());
						this->setHolder(i_holder);
						this->setBaseType(Base::ClassCount<P>::get());
						PointerLog(pankey_Log_EndMethod, "create", "");
					}

					//unsafe method
					virtual INSTANCE_TYPE operator ->(){
						PointerLog(pankey_Log_StartMethod, "operator ->", "");
						PointerLog(pankey_Log_EndMethod, "operator ->", "");
						return (INSTANCE_TYPE)MemoryHolderManager<H>::get(StaticManagerInstance<H,M>::getManager(), this->getHolder());
					}

					//unsafe method
					virtual INSTANCE_TYPE get()const{
						return (INSTANCE_TYPE)MemoryHolderManager<H>::get(StaticManagerInstance<H,M>::getManager(), this->getHolder());
					}
			};

		}

	}

#endif