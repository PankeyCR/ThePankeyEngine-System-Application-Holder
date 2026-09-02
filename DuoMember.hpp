
#ifndef DuoMember_hpp
	#define DuoMember_hpp

	#include "Member.hpp"

	#if defined(pankey_Log) && (defined(DuoMember_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
	    #include "Logger_status.hpp"
		#define DuoMemberLog(status,method,mns) pankey_Log(status,"DuoMember",method,mns)
	#else
		#define DuoMemberLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

            template <class H, class M>
            class DuoMember : public Member<H,M>{
                public:

                    using MANAGER_TYPE = typename MemoryHolder<H>::MANAGER_TYPE;
                    using VOID_TYPE = typename MemoryHolder<H>::VOID_TYPE;
                    using HOLDER_TYPE = typename MemoryHolder<H>::HOLDER_TYPE;

                    DuoMember(){
                        DuoMemberLog(pankey_Log_StartMethod, "Constructor", "");
                        DuoMemberLog(pankey_Log_EndMethod, "Constructor", "");
                    }
                    
                    DuoMember(Member<H,M> c_holder_0, Member<H,M> c_holder_1){
                        DuoMemberLog(pankey_Log_StartMethod, "Constructor", "");
                        this->setHolder(c_holder_0.getHolder());
                        this->setDuoHolder(c_holder_1.getHolder());
                        DuoMemberLog(pankey_Log_EndMethod, "Constructor", "");
                    }
                    
                    DuoMember(const DuoMember<H,M>& c_duo_holder){
                        DuoMemberLog(pankey_Log_StartMethod, "Constructor", "");
                        this->setHolder(c_duo_holder.getHolder());
                        this->setDuoHolder(c_duo_holder.getDuoHolder());
                        DuoMemberLog(pankey_Log_EndMethod, "Constructor", "");
                    }
                    
                    virtual ~DuoMember(){
                        DuoMemberLog(pankey_Log_StartMethod, "Destructor", "");
                        this->removeDuo();
                        DuoMemberLog(pankey_Log_EndMethod, "Destructor", "");
                    }

                    virtual void copyDuoMember(const Member<H,M>& a_holder){
                        DuoMemberLog(pankey_Log_StartMethod, "copyDuoMember", "");
                        this->setDuoHolder(a_holder.getHolder());
                        DuoMemberLog(pankey_Log_EndMethod, "copyDuoMember", "");
                    }

                    virtual Member<H,M> getDuoMember(){
                        DuoMemberLog(pankey_Log_StartMethod, "getDuoMember", "");
                        Member<H,M> i_member;
                        i_member.setHolder(this->m_duo_holder);
                        DuoMemberLog(pankey_Log_EndMethod, "getDuoMember", "");
                        return i_member;
                    }

                    virtual void removeDuo(){
                        DuoMemberLog(pankey_Log_StartMethod, "remove", "");
                        MemoryHolderManager<H>::remove(this->getManager(), this->m_duo_holder);
                        DuoMemberLog(pankey_Log_EndMethod, "remove", "");
                    }

                    virtual void destroyDuo(){
                        DuoMemberLog(pankey_Log_StartMethod, "destroy", "");
                        MemoryHolderManager<H>::destroy(this->getManager(), this->m_duo_holder);
                        DuoMemberLog(pankey_Log_EndMethod, "destroy", "");
                    }
                        
                    //unsafe method
                    virtual void setDuoHolder(HOLDER_TYPE a_holder){
                        DuoMemberLog(pankey_Log_StartMethod, "setDuoHolder", "");
                        MemoryHolderManager<H>::add(this->getManager(), a_holder);
                        MemoryHolderManager<H>::remove(this->getManager(), this->m_duo_holder);
                        this->m_duo_holder = a_holder;
                        DuoMemberLog(pankey_Log_EndMethod, "setDuoHolder", "");
                    }

                    //unsafe method
                    virtual HOLDER_TYPE getDuoHolder()const{
                        return this->m_duo_holder;
                    }

                    virtual HOLDER_TYPE& getDuoHolderReference(){
                        return this->m_duo_holder;
                    }

                    virtual bool isDuoHolderNull()const{
                        return this->m_duo_holder == nullptr;
                    }

                    virtual void copyDuoMemoryHolder(const MemoryHolder<H>& a_holder){
                        DuoMemberLog(pankey_Log_StartMethod, "copyDuoMemoryHolder", "");
                        if(a_holder.shareManager(this->getManager())){
                            this->setDuoHolder(a_holder.getHolder());
                        }
                        DuoMemberLog(pankey_Log_EndMethod, "copyDuoMemoryHolder", "");
                    }

                    virtual bool sameDuoType(long a_type)const{
                        DuoMemberLog(pankey_Log_StartMethod, "sameDuoType", "");
                        if(a_type == -1){
                            DuoMemberLog(pankey_Log_Error, "sameDuoType", "a_type == -1");
                            DuoMemberLog(pankey_Log_EndMethod, "sameDuoType", "");
                            return false;
                        }
                        long i_type = this->getDuoType();
                        if(i_type == -1){
                            DuoMemberLog(pankey_Log_Error, "sameDuoType", "i_type == -1");
                            DuoMemberLog(pankey_Log_EndMethod, "sameDuoType", "");
                            return false;
                        }
                        DuoMemberLog(pankey_Log_EndMethod, "sameDuoType", "");
                        return i_type == a_type;
                    }

                    virtual bool sameDuoBaseType(long a_type)const{
                        DuoMemberLog(pankey_Log_StartMethod, "sameDuoBaseType", "");
                        if(a_type == -1){
                            DuoMemberLog(pankey_Log_Error, "sameDuoBaseType", "a_type == -1");
                            DuoMemberLog(pankey_Log_EndMethod, "sameDuoBaseType", "");
                            return false;
                        }
                        long i_type = this->getDuoBaseType();
                        if(i_type == -1){
                            DuoMemberLog(pankey_Log_Error, "sameDuoBaseType", "i_type == -1");
                            DuoMemberLog(pankey_Log_EndMethod, "sameDuoBaseType", "");
                            return false;
                        }
                        DuoMemberLog(pankey_Log_EndMethod, "sameDuoBaseType", "");
                        return i_type == a_type;
                    }

                    virtual bool isDuoMember(MANAGER_TYPE a_manager, long a_type)const{
                        DuoMemberLog(pankey_Log_StartMethod, "isDuoMember", "");
                        DuoMemberLog(pankey_Log_EndMethod, "isDuoMember", "");
                        return this->shareManager(a_manager) && (this->sameDuoType(a_type) || this->sameDuoBaseType(a_type));
                    }

                    virtual bool isDuoMember(HOLDER_TYPE a_holder, MANAGER_TYPE a_manager)const{
                        DuoMemberLog(pankey_Log_StartMethod, "isDuoMember", "");
                        auto i_type = MemoryHolderManager<H>::getType(a_manager, a_holder);
                        DuoMemberLog(pankey_Log_EndMethod, "isDuoMember", "");
                        return this->isDuoMember(a_manager, i_type);
                    }

                    virtual bool isDuoMember(HOLDER_TYPE a_holder)const{
                        DuoMemberLog(pankey_Log_StartMethod, "isDuoMember", "");
                        DuoMemberLog(pankey_Log_EndMethod, "isDuoMember", "");
                        return this->isDuoMember(a_holder, this->getManager());
                    }

                    virtual bool isDuoMember(const MemoryHolder<H>& a_holder)const{
                        DuoMemberLog(pankey_Log_StartMethod, "isDuoMember", "");
                        auto i_manager = a_holder.getManager();
                        auto i_type = a_holder.getType();
                        DuoMemberLog(pankey_Log_EndMethod, "isDuoMember", "");
                        return this->isDuoMember(i_manager, i_type);
                    }

                    virtual void setDuoType(long a_type){
                        DuoMemberLog(pankey_Log_StartMethod, "setDuoType", "");
                        MemoryHolderManager<H>::setType(this->getManager(), this->m_duo_holder, a_type);
                        DuoMemberLog(pankey_Log_EndMethod, "setDuoType", "");
                    }

                    virtual long getDuoType()const{
                        DuoMemberLog(pankey_Log_StartMethod, "getDuoType", "");
                        DuoMemberLog(pankey_Log_EndMethod, "getDuoType", "");
                        return MemoryHolderManager<H>::getType(this->getManager(), this->m_duo_holder);
                    }

                    virtual void setDuoBaseType(long a_type){
                        DuoMemberLog(pankey_Log_StartMethod, "setDuoBaseType", "");
                        MemoryHolderManager<H>::setBaseType(this->getManager(), this->m_duo_holder, a_type);
                        DuoMemberLog(pankey_Log_EndMethod, "setDuoBaseType", "");
                    }

                    virtual long getDuoBaseType()const{
                        DuoMemberLog(pankey_Log_StartMethod, "getDuoBaseType", "");
                        DuoMemberLog(pankey_Log_EndMethod, "getDuoBaseType", "");
                        return MemoryHolderManager<H>::getBaseType(this->getManager(), this->m_duo_holder);
                    }

                    virtual bool isDuoMemoryNull()const{
                        DuoMemberLog(pankey_Log_StartMethod, "isDuoMemoryNull", "");
                        if(this->m_duo_holder == nullptr){
                            DuoMemberLog(pankey_Log_EndMethod, "isDuoMemoryNull", "this->m_duo_holder == nullptr");
                            return true;
                        }
                        VOID_TYPE i_pointer = MemoryHolderManager<H>::get(this->getManager(), this->m_duo_holder);
                        DuoMemberLog(pankey_Log_Statement, "isDuoMemoryNull", "isDuoNull: ");
                        DuoMemberLog(pankey_Log_Statement, "isDuoMemoryNull", i_pointer == nullptr);
                        DuoMemberLog(pankey_Log_EndMethod, "isDuoMemoryNull", "");
                        return i_pointer == nullptr;
                    }

                    //unsafe method
                    virtual VOID_TYPE getDuoRawPointer()const{
                        DuoMemberLog(pankey_Log_StartMethod, "getDuoRawPointer", "");
                        VOID_TYPE i_pointer = MemoryHolderManager<H>::get(this->getManager(), this->m_duo_holder);
                        DuoMemberLog(pankey_Log_Statement, "getDuoRawPointer", "VOID_TYPE is null?");
                        DuoMemberLog(pankey_Log_Statement, "getDuoRawPointer", i_pointer == nullptr);
                        DuoMemberLog(pankey_Log_EndMethod, "getDuoRawPointer", "");
                        return i_pointer;
                    }
                    
                    virtual DuoMember<H,M>& operator=(const DuoMember<H,M>& a_duo_member){
                        DuoMemberLog(pankey_Log_StartMethod, "operator=", "");
                        this->setHolder(a_duo_member.getHolder());
                        this->setDuoHolder(a_duo_member.getDuoHolder());
                        DuoMemberLog(pankey_Log_EndMethod, "operator=", "");
                        return *this;
                    }
                    
                    virtual bool operator==(const DuoMember<H,M>& a_duo_member){
                        DuoMemberLog(pankey_Log_StartMethod, "operator!=", "");
                        DuoMemberLog(pankey_Log_EndMethod, "operator!=", "");
                        return this->getHolder() == a_duo_member.getHolder() && this->getDuoHolder() == a_duo_member.getDuoHolder();
                    }

                    virtual bool operator!=(const DuoMember<H,M>& a_duo_member){
                        DuoMemberLog(pankey_Log_StartMethod, "operator==", "");
                        DuoMemberLog(pankey_Log_EndMethod, "operator==", "");
                        return this->getHolder() != a_duo_member.getHolder() || this->getDuoHolder() != a_duo_member.getDuoHolder();
                    }
                    
                    virtual bool isNull()const{
                        DuoMemberLog(pankey_Log_StartMethod, "isDuoMemberNull", "");
                        DuoMemberLog(pankey_Log_EndMethod, "isDuoMemberNull", "");
                        return this->isMemoryNull() && this->isDuoMemoryNull();
                    }
                
                protected:

                    HOLDER_TYPE m_duo_holder = nullptr;
            };

        }

	}

#endif