#pragma once

#include <memory>
#include <stack>

#include "State.h"

using namespace std;

namespace Tokyo {

    typedef unique_ptr<state> StateRef;

    // The StateMachine handles the currently running state and any input for the current state like the manager of the states. 
    // It also handles switching between states and adding/removing states from the stack.
    class StateMachine {
        public:
        StateMachine() {}
        ~StateMachine() {}

        // Add a new state to the stack which will be the currently running state, with an option to replace the current state or not.
        void AddState( StateRef newState, bool isReplacing = true );
        // Remove the current state from the stack and return to the previous state. 
        void RemoveState();

        void ProcessStateChanges();

        // Retruns the pointer to the currently active state on the stack.
        StateRef& GetActiveState();

        private:
        // Stack that holds all the states in the game, with the currently active state being the one on top of the stack.
        stack<StateRef> _states;
        // The new state that is being added to the stack.
        StateRef _newState;

        bool _isRemoving;
        bool _isAdding;
        bool _isReplacing;
    };
}