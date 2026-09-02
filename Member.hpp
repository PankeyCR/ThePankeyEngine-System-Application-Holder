
#ifndef Member_hpp
	#define Member_hpp

    #include "MemoryHolder.hpp"
    #include "StaticManagerInstance.hpp"

	#if defined(pankey_Log) && (defined(Member_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
        #define MemberLog(status,method,mns) pankey_Log(status,"Member",method,mns)
    #else
        #define MemberLog(status,method,mns)
    #endif

	namespace pankey{

		namespace HolderSystem{

            template<class H, class M>
            class Member : public MemoryHolder<H>{
                public:
                
                    using MANAGER_TYPE = typename MemoryHolder<H>::MANAGER_TYPE;

                    Member(){
                        MemberLog(pankey_Log_StartMethod, "Constructor", "");
                        MemberLog(pankey_Log_EndMethod, "Constructor", "");
                    }

                    Member(const MemoryHolder<H>& a_holder){
                        MemberLog(pankey_Log_StartMethod, "Constructor", "const MemoryHolder<H>& a_holder");
                        if(!a_holder.shareManager(this->getManager())){
                            MemberLog(pankey_Log_EndMethod, "Constructor", "!a_holder.shareManager(this->getManager())");
                            return;
                        }
                        this->setHolder(a_holder.getHolder());
                        MemberLog(pankey_Log_EndMethod, "Constructor", "");
                    }

                    Member(const Member<H,M>& a_holder){
                        MemberLog(pankey_Log_StartMethod, "Constructor", "const Member<H,M>& a_holder");
                        this->setHolder(a_holder.getHolder());
                        MemberLog(pankey_Log_EndMethod, "Constructor", "");
                    }
                    
                    virtual ~Member(){
                        MemberLog(pankey_Log_StartMethod, "Destructor", "");
                        this->remove();
                        MemberLog(pankey_Log_EndMethod, "Destructor", "");
                    }

                    virtual MANAGER_TYPE getManager()const{
                        MemberLog(pankey_Log_StartMethod, "getManager", "");
                        MemberLog(pankey_Log_Statement, "getManager", "Is Null?");
                        MemberLog(pankey_Log_Statement, "getManager", (StaticManagerInstance<H,M>::getManager() == nullptr));
                        MemberLog(pankey_Log_EndMethod, "getManager", "");
                        return StaticManagerInstance<H,M>::getManager();
                    }

                    virtual void copyMemoryHolder(const MemoryHolder<H>& a_holder){
                        MemoryHolderLog(pankey_Log_StartMethod, "copyMemoryHolder", "");
                        if(!this->shareManager(a_holder)){
                            MemberLog(pankey_Log_EndMethod, "copyMemoryHolder", "");
                            return;
                        }
                        this->setHolder(a_holder.getHolder());
                        MemoryHolderLog(pankey_Log_EndMethod, "copyMemoryHolder", "");
                    }

                    virtual void copyMember(const Member<H,M>& a_holder){
                        MemberLog(pankey_Log_StartMethod, "copyMember", "");
                        this->setHolder(a_holder.getHolder());
                        MemberLog(pankey_Log_EndMethod, "copyMember", "");
                    }

                    virtual Member<H,M> getMember(){
                        MemberLog(pankey_Log_StartMethod, "getMember", "");
                        MemberLog(pankey_Log_EndMethod, "getMember", "");
                        Member<H,M> i_member;
                        i_member.setHolder(this->getHolder());
                        return i_member;
                    }

                    virtual void operator=(const Member<H,M>& a_holder){
                        MemberLog(pankey_Log_StartMethod, "operator=", "");
                        this->setHolder(a_holder.getHolder());
                        MemberLog(pankey_Log_EndMethod, "operator=", "");
                    }

                
            };

        }

	}

#endif