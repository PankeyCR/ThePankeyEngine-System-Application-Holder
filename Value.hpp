
#ifndef Value_hpp
	#define Value_hpp

	#include "Pointer.hpp"

	#if defined(pankey_Log) && (defined(Value_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define ValueLog(status,method,mns) pankey_Log(status,"Value",method,mns)
	#else
		#define ValueLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class P, class H, class M>
			class Value : public Pointer<P,H,M>{
				public:
					using VALUE_TYPE = P;
					using VOID_TYPE = typename Member<H,M>::VOID_TYPE;
					using HOLDER_TYPE = typename Member<H,M>::HOLDER_TYPE;
					
					Value(){
						ValueLog(pankey_Log_StartMethod, "Contructor", "");
						ValueLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Value(const VALUE_TYPE& a_value){
						ValueLog(pankey_Log_StartMethod, "Contructor", "const VALUE_TYPE &a_value");
						this->create();
						this->setValue(a_value);
						ValueLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Value(const MemoryHolder<H>& a_value){
						ValueLog(pankey_Log_StartMethod, "Contructor", "const MemoryHolder &a_value");
						if(!a_value.isMember(this->getManager(), Base::ClassCount<P>::get())){
							PointerLog(pankey_Log_EndMethod, "Constructor", "not member");
							return;
						}
						this->setHolder(a_value.getHolder());
						ValueLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Value(const Member<H,M>& a_value){
						ValueLog(pankey_Log_StartMethod, "Contructor", "const Member &a_value");
						if(a_value.sameType(Base::ClassCount<P>::get()) || a_value.sameBaseType(Base::ClassCount<P>::get())){
							ValueLog(pankey_Log_Statement, "Contructor", "seting holder");
							this->setHolder(a_value.getHolder());
						}
						ValueLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Value(const Pointer<P,H,M>& a_pointer){
						PointerLog(pankey_Log_StartMethod, "Contructor", "const Pointer &a_pointer");
						this->setHolder(a_pointer.getHolder());
						PointerLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Value(const Value<P,H,M>& a_pointer){
						PointerLog(pankey_Log_StartMethod, "Contructor", "const Pointer &a_pointer");
						this->setHolder(a_pointer.getHolder());
						PointerLog(pankey_Log_EndMethod, "Contructor", "");
					}

					virtual ~Value(){
						ValueLog(pankey_Log_StartMethod, "Destructor", "");
						ValueLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual void setValue(VALUE_TYPE a_value){
						ValueLog(pankey_Log_StartMethod, "setValue", "");
						VOID_TYPE i_pointer = this->getRawPointer();
						if(i_pointer != nullptr){
							VALUE_TYPE* i_value_1 = (VALUE_TYPE*)i_pointer;
							*i_value_1 = a_value;
						}
						ValueLog(pankey_Log_EndMethod, "setValue", "");
					}

					virtual VALUE_TYPE getValue(){
						ValueLog(pankey_Log_StartMethod, "getValue", "");
						VOID_TYPE i_pointer = this->getRawPointer();

						ValueLog(pankey_Log_Statement, "getValue",  "Is Holder == nullptr");
						ValueLog(pankey_Log_Statement, "getValue",  this->m_holder == nullptr);
						if(i_pointer != nullptr){
							ValueLog(pankey_Log_Statement, "getValue",  "i_pointer != nullptr");
							return *((VALUE_TYPE*)i_pointer);
						}
						ValueLog(pankey_Log_EndMethod, "getValue", "");
						return VALUE_TYPE();
					}

					virtual VALUE_TYPE& getReference(){
						ValueLog(pankey_Log_StartMethod, "getValue", "");
						VOID_TYPE i_pointer = this->getRawPointer();
						ValueLog(pankey_Log_EndMethod, "getValue", "");
						return *((VALUE_TYPE*)i_pointer);
					}

					virtual Pointer<P,H,M> clone(){
						ValueLog(pankey_Log_StartMethod, "clone", "");
						VOID_TYPE i_pointer = this->getRawPointer();
						if(i_pointer == nullptr){
							ValueLog(pankey_Log_StartMethod, "clone", "i_pointer == nullptr");
							return Pointer<P,H,M>();
						}
						Pointer<P,H,M> i_clone;
						i_clone.create();
						VOID_TYPE i_pointer_2 = i_clone.getRawPointer();
						if(i_pointer_2 == nullptr){
							ValueLog(pankey_Log_StartMethod, "clone", "i_pointer_2 == nullptr");
							return Pointer<P,H,M>();
						}
						VALUE_TYPE* i_value_1 = (VALUE_TYPE*)i_pointer;
						VALUE_TYPE* i_value_2 = (VALUE_TYPE*)i_pointer_2;
						*i_value_2 = *i_value_1;
						ValueLog(pankey_Log_EndMethod, "clone", "");
						return i_clone;
					}

					virtual void operator=(const VALUE_TYPE& a_value){
						ValueLog(pankey_Log_StartMethod, "operator=", "");
						VOID_TYPE i_pointer = this->getRawPointer();
						if(i_pointer == nullptr){
							this->create();
						}
						this->setValue(a_value);
						ValueLog(pankey_Log_EndMethod, "operator=", "");
					}

					virtual bool operator==(const VALUE_TYPE& a_value){
						ValueLog(pankey_Log_StartMethod, "operator==", "");
						ValueLog(pankey_Log_EndMethod, "operator==", "");
						return this->getValue() == a_value;
					}

					virtual bool operator!=(const VALUE_TYPE& a_value){
						ValueLog(pankey_Log_StartMethod, "operator!=", "");
						ValueLog(pankey_Log_EndMethod, "operator!=", "");
						return this->getValue() != a_value;
					}

				protected:
			};

		}

	}

#endif