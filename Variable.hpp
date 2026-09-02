
#ifndef Variable_hpp
	#define Variable_hpp

    #include "Member.hpp"
    #include "ClassCount.hpp"
    #include "Data.hpp"
    #include "Pointer.hpp"
    #include "Value.hpp"
    #include "Self.hpp"
    #include "StaticAllocatorInstance.hpp"
    #include "MemorySize.hpp"
    #include "type_traits.hpp"

	#if defined(pankey_Log) && (defined(Variable_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
        #define VariableLog(status,method,mns) pankey_Log(status,"Variable",method,mns)
    #else
        #define VariableLog(status,method,mns)
    #endif

	namespace pankey{

		namespace HolderSystem{

            template<class H, class M>
            class Variable : public Member<H,M>{
                public:

                    using MANAGER_TYPE = typename Member<H,M>::MANAGER_TYPE;
                    using VOID_TYPE = typename Member<H,M>::VOID_TYPE;
                    using HOLDER_TYPE = typename Member<H,M>::HOLDER_TYPE;

                    Variable(){
                        VariableLog(pankey_Log_StartMethod, "Constructor", "default");
                        VariableLog(pankey_Log_EndMethod, "Constructor", "");
                    }

                    Variable(const Member<H,M>& a_holder){
                        VariableLog(pankey_Log_StartMethod, "Constructor", "");
                        this->setHolder(a_holder.getHolder());
                        VariableLog(pankey_Log_EndMethod, "Constructor", "");
                    }

                    Variable(const Variable<H,M>& a_holder){
                        VariableLog(pankey_Log_StartMethod, "Constructor", "");
                        this->setHolder(a_holder.getHolder());
                        VariableLog(pankey_Log_EndMethod, "Constructor", "");
                    }

                    Variable(const Data<H>& a_holder){
                        VariableLog(pankey_Log_StartMethod, "Constructor", "");
                        if(!a_holder.shareManager(this->getManager())){
                            VariableLog(pankey_Log_EndMethod, "Constructor", "");
                            return;
                        }
                        this->setHolder(a_holder.getHolder());
                        VariableLog(pankey_Log_EndMethod, "Constructor", "");
                    }

                    template<class P>
                    Variable(const Pointer<P,H,M>& a_holder){
                        VariableLog(pankey_Log_StartMethod, "Constructor", "");
                        this->setHolder(a_holder.getHolder());
                        VariableLog(pankey_Log_EndMethod, "Constructor", "");
                    }

                    template<class P>
                    Variable(const Value<P,H,M>& a_holder){
                        VariableLog(pankey_Log_StartMethod, "Constructor", "");
                        this->setHolder(a_holder.getHolder());
                        VariableLog(pankey_Log_EndMethod, "Constructor", "");
                    }

                    // template<class O>
                    // Variable(const Object<O,H,M>& a_holder){
                    //     VariableLog(pankey_Log_StartMethod, "Constructor", "");
                    //     this->setHolder(a_holder.getHolder());
                    //     VariableLog(pankey_Log_EndMethod, "Constructor", "");
                    // }

                    template<class P>
                    Variable(const Self<P,H,M>& a_holder){
                        VariableLog(pankey_Log_StartMethod, "Constructor", "");
                        this->setHolder(a_holder.getHolder());
                        VariableLog(pankey_Log_EndMethod, "Constructor", "");
                    }

                    template<class P>
                    Variable(const P& a_value){
                        VariableLog(pankey_Log_StartMethod, "Constructor", "value constructor");

                        if(Base::is_base_of<MemoryHolder<H>, P>::value){
                            this->copyType(&a_value);
                            VariableLog(pankey_Log_EndMethod, "Constructor", "memoryholder asignment");
                            return;
                        }

                        this->create<P>();
                        this->setValue<P>(a_value);
                        VariableLog(pankey_Log_EndMethod, "Constructor", "");
                    }
                    
                    virtual ~Variable(){
                        VariableLog(pankey_Log_StartMethod, "Destructor", "");
                        VariableLog(pankey_Log_EndMethod, "Destructor", "");
                    }

                    void copyType(const void* a_holder){
                        VariableLog(pankey_Log_StartMethod, "copyType", "fix");
                        const MemoryHolder<H>* i_holder = (const MemoryHolder<H>*)a_holder;
                        if(i_holder == nullptr){
                            return;
                        }
                        if(!i_holder->shareManager(this->getManager())){
                            VariableLog(pankey_Log_StartMethod, "copyType", "holder not a member");
                            return;
                        }
                        this->copyMemoryHolder(*i_holder);
                        VariableLog(pankey_Log_EndMethod, "copyType", "");
                    }

                    template<class P>
                    void create(){
                        VariableLog(pankey_Log_StartMethod, "create", "");
                        VOID_TYPE i_pointer = this->getRawPointer();
                        if(i_pointer != nullptr){
                            VariableLog(pankey_Log_EndMethod, "create", "");
                            return;
                        }
                        VariableLog(pankey_Log_Statement, "create", "creating new instance");
                        HOLDER_TYPE i_holder = MemoryHolderManager<H>::newInstance(this->getManager(), Base::ClassCount<P>::get(), sizeof(P), Base::StaticAllocatorInstance<P>::getAllocator());
                        VariableLog(pankey_Log_Statement, "create", "is Holder null:");
                        VariableLog(pankey_Log_Statement, "create", i_holder == nullptr);
                        this->setHolder(i_holder);
                        this->setBaseType(Base::ClassCount<P>::get());
                        VariableLog(pankey_Log_EndMethod, "create", "");
                    }

                    template<class P>
                    void setValue(P a_value){
                        VariableLog(pankey_Log_StartMethod, "setValue", "");
                        VOID_TYPE i_pointer = this->getRawPointer();
                        if(i_pointer != nullptr && this->getType() == Base::ClassCount<P>::get()){
                            P* i_value_1 = (P*)i_pointer;
                            VariableLog(pankey_Log_Statement, "setValue", "asign value with assignment operator");
                            *i_value_1 = a_value;
                        }
                        VariableLog(pankey_Log_EndMethod, "setValue", "");
                    }

                    template<class P>
                    P getValue(){
                        VariableLog(pankey_Log_StartMethod, "getValue", "");
                        VOID_TYPE i_pointer = this->getRawPointer();

                        VariableLog(pankey_Log_Statement, "getValue",  "Is Holder == nullptr");
                        VariableLog(pankey_Log_Statement, "getValue",  this->m_holder == nullptr);
                        if(i_pointer != nullptr){
                            if(this->getType() == Base::ClassCount<P>::get() || this->getBaseType() == Base::ClassCount<P>::get()){
                                VariableLog(pankey_Log_Statement, "getValue",  "i_pointer != nullptr");
                                //VariableLog(pankey_Log_EndMethod, "getValue",  *((P*)i_pointer));
                                return *((P*)i_pointer);
                            }
                        }
                        VariableLog(pankey_Log_EndMethod, "getValue", "");
                        return P();
                    }

                    template<class P>
                    P& getReference(){
                        VariableLog(pankey_Log_StartMethod, "getValue", "");
                        VOID_TYPE i_pointer = this->getRawPointer();
                        VariableLog(pankey_Log_EndMethod, "getValue", "");
                        return *((P*)i_pointer);
                    }

                    void operator=(const Member<H,M>& a_holder){
                        VariableLog(pankey_Log_StartMethod, "void operator=", "");
                        this->setHolder(a_holder.getHolder());
                        VariableLog(pankey_Log_EndMethod, "void operator=", "");
                    }

                    void operator=(const Variable<H,M>& a_holder){
                        VariableLog(pankey_Log_StartMethod, "void operator=", "");
                        this->setHolder(a_holder.getHolder());
                        VariableLog(pankey_Log_EndMethod, "void operator=", "");
                    }

                    void operator=(const Data<H>& a_holder){
                        VariableLog(pankey_Log_StartMethod, "void operator=", "");
                        if(!this->isMember(a_holder)){
                            VariableLog(pankey_Log_EndMethod, "void operator=", "");
                            return;
                        }
                        this->setHolder(a_holder.getHolder());
                        VariableLog(pankey_Log_EndMethod, "void operator=", "");
                    }

                    template<class P>
                    void operator=(const Pointer<P,H,M>& a_holder){
                        VariableLog(pankey_Log_StartMethod, "void operator=", "");
                        this->setHolder(a_holder.getHolder());
                        VariableLog(pankey_Log_EndMethod, "void operator=", "");
                    }

                    template<class P>
                    void operator=(const Value<P,H,M>& a_holder){
                        VariableLog(pankey_Log_StartMethod, "void operator=", "");
                        this->setHolder(a_holder.getHolder());
                        VariableLog(pankey_Log_EndMethod, "void operator=", "");
                    }

                    // template<class O>
                    // void operator=(const Object<O,H,M>& a_holder){
                    //     VariableLog(pankey_Log_StartMethod, "void operator=", "");
                    //     this->setHolder(a_holder.getHolder());
                    //     VariableLog(pankey_Log_EndMethod, "void operator=", "");
                    // }

                    template<class P>
                    void operator=(const Self<P,H,M>& a_holder){
                        VariableLog(pankey_Log_StartMethod, "void operator=", "");
                        this->setHolder(a_holder.getHolder());
                        VariableLog(pankey_Log_EndMethod, "void operator=", "");
                    }

                    template<class P>
                    void operator=(const P& a_value){
                        VariableLog(pankey_Log_StartMethod, "operator=", "");

                        if(Base::is_base_of<MemoryHolder<H>, P>::value){
                            this->copyType(&a_value);
                            VariableLog(pankey_Log_EndMethod, "operator=", "memoryholder asignment");
                            return;
                        }

                        VOID_TYPE i_pointer = this->getRawPointer();
                        if(i_pointer == nullptr){
                            this->create<P>();
                        }
                        this->setValue<P>(a_value);
                        VariableLog(pankey_Log_EndMethod, "operator=", "");
                    }
                
            };

            template<class H, class M>
            Variable<H,M> Var(const Member<H,M>& a_holder){
                Variable<H,M> i_var;
                i_var.copyMember(a_holder);
                return i_var;
            }

            template<class H, class M>
            Variable<H,M> VarMemoryHolder(const MemoryHolder<H>& a_holder){
                Variable<H,M> i_var;
                i_var.copyMemoryHolder(a_holder);
                return i_var;
            }

        }

	}

#endif