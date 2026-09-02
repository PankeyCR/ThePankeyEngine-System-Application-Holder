
#ifndef Object_hpp
	#define Object_hpp

    #include "Member.hpp"
    #include "ClassCount.hpp"
    #include "Data.hpp"
    #include "Pointer.hpp"
    #include "Value.hpp"
    #include "Variable.hpp"
    #include "StaticAllocatorInstance.hpp"
    #include "MemorySize.hpp"
    #include "type_traits.hpp"

	#if defined(pankey_Log) && (defined(Object_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define ObjectLog(status,method,mns) pankey_Log(status,"Object",method,mns)
	#else
		#define ObjectLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class O, class H, class M>
			class Object : public Member<H,M>{
				public:
					using OBJECT_TYPE = O;
					using INSTANCE_TYPE = O*;
					using MANAGER_TYPE = typename Member<H,M>::MANAGER_TYPE;
					using VOID_TYPE = typename Member<H,M>::VOID_TYPE;
					using HOLDER_TYPE = typename Member<H,M>::HOLDER_TYPE;
					
					Object(){
						ObjectLog(pankey_Log_StartMethod, "Contructor", "");
						ObjectLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Object(const Object<O,H,M>& a_obj){
						ObjectLog(pankey_Log_StartMethod, "Contructor", "const Object<O,H,M>&");
						this->setHolder(a_obj.getHolder());
						ObjectLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Object(const Member<H,M>& a_holder){
						ObjectLog(pankey_Log_StartMethod, "Constructor", "const Member<H,M>&");
						if(a_holder.isMember(this->getManager(), Base::ClassCount<O>::get())){
							ObjectLog(pankey_Log_StartMethod, "Constructor", "holder is member");
							this->setHolder(a_holder.getHolder());
						}
						ObjectLog(pankey_Log_EndMethod, "Constructor", "");
					}

					Object(const Data<H>& a_holder){
						ObjectLog(pankey_Log_StartMethod, "Constructor", "const Data<H>&");
						if(a_holder.isMember(this->getManager(), Base::ClassCount<O>::get())){
							ObjectLog(pankey_Log_StartMethod, "Constructor", "holder is member");
							this->setHolder(a_holder.getHolder());
						}
						ObjectLog(pankey_Log_EndMethod, "Constructor", "");
					}

					template<class P>
					Object(const Pointer<P,H,M>& a_holder){
						ObjectLog(pankey_Log_StartMethod, "Constructor", "const Pointer<P,H,M>&");
						if(a_holder.isMember(this->getManager(), Base::ClassCount<O>::get())){
							ObjectLog(pankey_Log_StartMethod, "Constructor", "holder is member");
							this->setHolder(a_holder.getHolder());
						}
						ObjectLog(pankey_Log_EndMethod, "Constructor", "");
					}

					template<class P>
					Object(const Value<P,H,M>& a_holder){
						ObjectLog(pankey_Log_StartMethod, "Constructor", "const Value<P,H,M>&");
						if(a_holder.isMember(this->getManager(), Base::ClassCount<O>::get())){
							ObjectLog(pankey_Log_StartMethod, "Constructor", "holder is member");
							this->setHolder(a_holder.getHolder());
						}
						ObjectLog(pankey_Log_EndMethod, "Constructor", "");
					}

					template<class P>
					Object(const P& a_value){
						ObjectLog(pankey_Log_StartMethod, "Constructor", "const P&");

						if(Base::is_base_of<MemoryHolder<H>, P>::value){
							this->copyType(&a_value);
							ObjectLog(pankey_Log_EndMethod, "Constructor", "memoryholder asignment");
							return;
						}

						if(Base::is_base_of<O, P>::value){
							this->create<P>();
							this->setValue<P>(a_value);
							ObjectLog(pankey_Log_EndMethod, "Constructor", "object asignment");
							return;
						}

						ObjectLog(pankey_Log_EndMethod, "Constructor", "no initialization");
					}

					virtual ~Object(){
						ObjectLog(pankey_Log_StartMethod, "Destructor", "");
						ObjectLog(pankey_Log_EndMethod, "Destructor", "");
					}

					void copyType(const void* a_holder){
						ObjectLog(pankey_Log_StartMethod, "copyType", "fix");
						const MemoryHolder<H>* i_holder = (const MemoryHolder<H>*)a_holder;
						if(i_holder == nullptr){
							return;
						}
						if(!i_holder->isMember(this->getManager(), Base::ClassCount<O>::get())){
							ObjectLog(pankey_Log_StartMethod, "copyType", "holder not a member");
							return;
						}
						this->copyMemoryHolder(*i_holder);
						ObjectLog(pankey_Log_EndMethod, "copyType", "");
					}

					template<class P>
					void create(){
						ObjectLog(pankey_Log_StartMethod, "create", "");
						VOID_TYPE i_pointer = this->getRawPointer();
						if(i_pointer != nullptr){
							ObjectLog(pankey_Log_EndMethod, "create", "");
							return;
						}
						ObjectLog(pankey_Log_Statement, "create", "creating new instance");
						HOLDER_TYPE i_holder = MemoryHolderManager<H>::newInstance(this->getManager(), Base::ClassCount<P>::get(), sizeof(P), Base::StaticAllocatorInstance<P>::getAllocator());
						this->setHolder(i_holder);
						this->setBaseType(Base::ClassCount<O>::get());
						ObjectLog(pankey_Log_EndMethod, "create", "");
					}

					template<class P>
					void setValue(P a_value){
						ObjectLog(pankey_Log_StartMethod, "setValue", "");
						VOID_TYPE i_pointer = this->getRawPointer();
						if(i_pointer != nullptr && (this->getType() == Base::ClassCount<P>::get() || this->getBaseType() == Base::ClassCount<P>::get())){
							P* i_value_1 = (P*)i_pointer;
							ObjectLog(pankey_Log_Statement, "setValue", "asign value with assignment operator");
							*i_value_1 = a_value;
						}
						ObjectLog(pankey_Log_EndMethod, "setValue", "");
					}

					template<class P>
					P getValue(){
						ObjectLog(pankey_Log_StartMethod, "getValue", "");
						VOID_TYPE i_pointer = this->getRawPointer();

						ObjectLog(pankey_Log_Statement, "getValue",  "Is Holder == nullptr");
						ObjectLog(pankey_Log_Statement, "getValue",  this->m_holder == nullptr);
						if(i_pointer != nullptr){
							if(this->getType() == Base::ClassCount<P>::get() || this->getBaseType() == Base::ClassCount<P>::get()){
								ObjectLog(pankey_Log_Statement, "getValue",  "i_pointer != nullptr");
								//ObjectLog(pankey_Log_EndMethod, "getValue",  *((P*)i_pointer));
								return *((P*)i_pointer);
							}
						}
						ObjectLog(pankey_Log_EndMethod, "getValue", "");
						return P();
					}

					template<class P>
					bool isValidObject(){
						ObjectLog(pankey_Log_StartMethod, "isValidObject", "");
						VOID_TYPE i_pointer = this->getRawPointer();
						if(i_pointer == nullptr){
							ObjectLog(pankey_Log_EndMethod, "isValidObject",  "notValidObject");
							return false;
						}
						ObjectLog(pankey_Log_Statement, "isValidObject", "");
						if(this->getType() == Base::ClassCount<P>::get()){
							ObjectLog(pankey_Log_EndMethod, "isValidObject",  "isValidObject");
							return true;
						}
						ObjectLog(pankey_Log_EndMethod, "isValidObject", "notValidObject");
						return false;
					}

					template<class P>
					P& getReference(){
						ObjectLog(pankey_Log_StartMethod, "getReference", "");
						VOID_TYPE i_pointer = this->getRawPointer();
						ObjectLog(pankey_Log_EndMethod, "getReference", "");
						return *((P*)i_pointer);
					}

					//unsafe method
					virtual INSTANCE_TYPE operator ->(){
						ObjectLog(pankey_Log_StartMethod, "operator ->", "");
						ObjectLog(pankey_Log_EndMethod, "operator ->", "");
						return (INSTANCE_TYPE)MemoryHolderManager<H>::get(StaticManagerInstance<H,M>::getManager(), this->getHolder());
					}

					void operator=(const Object<O,H,M>& a_holder){
						ObjectLog(pankey_Log_StartMethod, "void operator=", "");
						this->setHolder(a_holder.getHolder());
						ObjectLog(pankey_Log_EndMethod, "void operator=", "");
					}

					void operator=(const Member<H,M>& a_holder){
						ObjectLog(pankey_Log_StartMethod, "void operator=", "");
						if(Base::ClassCount<O>::get() != a_holder.getBaseType()){
							ObjectLog(pankey_Log_StartMethod, "void operator=", "holder doesnt have same base clase");
							return;
						}
						this->setHolder(a_holder.getHolder());
						ObjectLog(pankey_Log_EndMethod, "void operator=", "");
					}

					void operator=(const Data<H>& a_holder){
						ObjectLog(pankey_Log_StartMethod, "void operator=", "");
						if(Base::ClassCount<O>::get() != a_holder.getBaseType()){
							ObjectLog(pankey_Log_StartMethod, "void operator=", "holder doesnt have same base clase");
							return;
						}
						if(!this->isMember(a_holder)){
							ObjectLog(pankey_Log_EndMethod, "void operator=", "holder isnt member");
							return;
						}
						this->setHolder(a_holder.getHolder());
						ObjectLog(pankey_Log_EndMethod, "void operator=", "");
					}

					template<class P>
					void operator=(const Pointer<P,H,M>& a_holder){
						ObjectLog(pankey_Log_StartMethod, "void operator=", "");
						if(Base::ClassCount<O>::get() != a_holder.getBaseType()){
							ObjectLog(pankey_Log_StartMethod, "void operator=", "holder doesnt have same base clase");
							return;
						}
						this->setHolder(a_holder.getHolder());
						ObjectLog(pankey_Log_EndMethod, "void operator=", "");
					}

					template<class P>
					void operator=(const Value<P,H,M>& a_holder){
						ObjectLog(pankey_Log_StartMethod, "void operator=", "");
						if(Base::ClassCount<O>::get() != a_holder.getBaseType()){
							ObjectLog(pankey_Log_StartMethod, "void operator=", "holder doesnt have same base clase");
							return;
						}
						this->setHolder(a_holder.getHolder());
						ObjectLog(pankey_Log_EndMethod, "void operator=", "");
					}


					template<class P>
					void operator=(const P& a_value){
						ObjectLog(pankey_Log_StartMethod, "operator=", "");

						if(Base::is_base_of<MemoryHolder<H>, P>::value){
							this->copyType(&a_value);
							ObjectLog(pankey_Log_EndMethod, "Constructor", "memoryholder asignment");
							return;
						}

						if(Base::is_base_of<O, P>::value){
							VOID_TYPE i_pointer = this->getRawPointer();
							if(i_pointer == nullptr){
								this->create<P>();
							}
							this->setValue<P>(a_value);
							ObjectLog(pankey_Log_EndMethod, "Constructor", "object asignment");
							return;
						}

						ObjectLog(pankey_Log_EndMethod, "operator=", "");
					}

					template<class... Args>
					void invoke(char* a_method, Args... args){
						ObjectLog(pankey_Log_StartMethod, "create", "");
						
						ObjectLog(pankey_Log_EndMethod, "create", "");
					}

				protected:
			};

			template<class O, class H, class M>
			Object<O,H,M> Var(const Member<H,M>& a_holder){
				Object<O,H,M> i_obj;
				i_obj.copyMember(a_holder);
				return i_obj;
			}

			template<class O, class H, class M>
			Object<O,H,M> VarMemoryHolder(const MemoryHolder<H>& a_holder){
				Object<O,H,M> i_obj;
				i_obj.copyMemoryHolder(a_holder);
				return i_obj;
			}

			// template<>
			// template<>
			// void MemoryHolder<UniversalHolder>::copyType<MemoryHolder<UniversalHolder>>(const MemoryHolder<UniversalHolder>& a_holder){
			//     MemoryHolderLog(pankey_Log_StartMethod, "copyMemoryHolder", "");
			//     if(!this->isMember(a_holder)){
			//         MemoryHolderLog(pankey_Log_Error, "copyMemoryHolder",  "Variable is not Member of Variable");
			//         MemoryHolderLog(pankey_Log_EndMethod, "copyMemoryHolder", "");
			//         return;
			//     }
			//     this->setHolder(a_holder.getHolder());
			//     MemoryHolderLog(pankey_Log_EndMethod, "copyMemoryHolder", "");
			// }

		}
	}

#endif