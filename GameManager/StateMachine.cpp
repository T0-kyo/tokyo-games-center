#include "StateMachine.h"

namespace Tokyo {

    void StateMachine::AddState( StateRef newState, bool isReplacing ) {
        this->_isAdding = true;
        this->_isReplacing = isReplacing;

        this->_newState = move( newState );
    }

    void StateMachine::RemoveState( int x ) {
        this->_isRemoving = true;
        this->_x = x;
    }
    
    void StateMachine::ProcessStateChanges() {
        if ( this->_isRemoving ) {
            while ( !this->_states.empty() && _x > 0 ){
                this->_states.pop();
                _x--;
            }

            if (!this->_states.empty() ) {
                this->_states.top()->Resume();
            }

            this->_isRemoving = false;
        }

        if ( this->_isAdding ) {

            if ( !this->_states.empty() ) {

                if ( this->_isReplacing ){
                    this->_states.pop();
                }

                else {
                    this->_states.top()->Pause();
                }
            }
            this->_states.push( move( this->_newState ) );
            this->_states.top()->Init();
            this->_isAdding = false;
        }
    }

    StateRef& StateMachine::GetActiveState() {
        return this->_states.top();
    }
}
