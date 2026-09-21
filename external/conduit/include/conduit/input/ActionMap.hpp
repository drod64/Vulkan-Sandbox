#ifndef CONDUIT_ACTION_MAP_HPP
#define CONDUIT_ACTION_MAP_HPP
#include <cassert>
#include <cstdlib>
#include <conduit/core/containers/unordered_map.hpp>
#include <conduit/core/containers/vector.hpp>
#include <conduit/input/ActionState.hpp>
#include <conduit/input/Binding.hpp>
#include <conduit/input/Input.hpp>

namespace conduit {
/**
 * Logical action tracker that allows multiple bindings to affect one action.
 */
template <typename Action>
class ActionMap {
private:
    const Input&                                m_input;
    sizet                                       m_gamepad{};
    unordered_map<Action, vector<Binding>>      m_bindings{};
    unordered_map<Action, ActionState>          m_action_states{};

    /**
     * Helper function that evaluates a binding.
     * 
     * @param binding the binding to evaluate
     * 
     * @return the value of the binding
     */
    real evaluate(const Binding &binding) const;

    /**
     * Helper function that evaluates a GamepadAxis.
     * 
     * @param gamepadAxis the gamepad axis to query
     * 
     * @return the value of the gamepad axis
     */
    real evaluate(GamepadAxis gamepadAxis) const;
    
    /**
     * Helper function that evaluates a GamepadButton.
     * 
     * @param gamepadButton the gamepad button to query
     * 
     * @return the value of the gamepad button
     */
    real evaluate(GamepadButton gamepadButton) const;

    /**
     * Helper function that evaluates a Key.
     * 
     * @param key the key to query
     * 
     * @return the value of the key
     */
    real evaluate(Key key) const;

    /**
     * Helper function that evaluates a MouseButton.
     * 
     * @param mouseButton the mouse button to query
     * 
     * @return the value of the mouse button
     */
    real evaluate(MouseButton mouseButton) const;

public:
    /**
     * Parameterized constructor.
     * 
     * @param input a required input source to read states from
     * @param gamepad an optional index to query a specific gamepad
     */
    ActionMap(const Input &input, sizet gamepad = 0);
    ~ActionMap() = default;

    /**
     * Polls the stored conduit::Input to update the action states.
     */
    void poll();

    /**
     * @param action the action to check
     * 
     * @return true if a binding linked to the action is down, false otherwise
     */
    bool isDown(Action action) const;

    /**
     * @param action the action to check
     * 
     * @return true if a binding linked to the action was pressed, false otherwise
     */
    bool wasPressed(Action action) const;

    /**
     * @param action the action to check
     * 
     * @return true if a binding linked to the action was released, false otherwise
     */
    bool wasReleased(Action action) const;

    /**
     * @param action the action to query
     * 
     * @return the raw value of the action (useful for analog cases)
     */
    real value(Action action) const;

    /**
     * Binds a specified binding to an action.
     * 
     * @param action the action
     * @param binding the binding linked to the action
     */
    void bind(Action action, const Binding &binding);

    /**
     * Binds a specified binding to an action.
     * 
     * @param action the action
     * @param inputControl the control linked to the action
     * @param scale optional scale that is multiplied to the action's raw value (defaulted to 1)
     */
    void bind(Action action, InputControl inputControl, real scale = static_cast<real>(1));

    /**
     * Unbinds a specified binding from an action.
     * 
     * @param action the action
     * @param binding the binding to unlink/unbind
     */
    void unbind(Action action, const Binding &binding);
}; // class ActionMap<Action>
} // namespace conduit

// Implementation
template <typename Action>
conduit::real conduit::ActionMap<Action>::evaluate(const Binding &binding) const
{
    return std::visit(
        [this, &binding](const auto& control)
        {
            return evaluate(control) * binding.scale;
        },
        binding.control
    );
}

template <typename Action>
conduit::real conduit::ActionMap<Action>::evaluate(GamepadAxis gamepadAxis) const
{
    return m_input.gamepads()[m_gamepad].axisValue(gamepadAxis);
}

template <typename Action>
conduit::real conduit::ActionMap<Action>::evaluate(GamepadButton gamepadButton) const
{
    return (m_input.gamepads()[m_gamepad].isDown(gamepadButton)) ?
            static_cast<real>(1) : static_cast<real>(0);
}

template <typename Action>
conduit::real conduit::ActionMap<Action>::evaluate(Key key) const
{
    return (m_input.keyboard().isDown(key)) ?
        static_cast<real>(1) : static_cast<real>(0);
}

template <typename Action>
conduit::real conduit::ActionMap<Action>::evaluate(MouseButton mouseButton) const
{
    return (m_input.mouse().isDown(mouseButton)) ?
        static_cast<real>(1) : static_cast<real>(0);
}

template <typename Action>
inline conduit::ActionMap<Action>::ActionMap(const Input &input, sizet gamepad) :
m_input(input),
m_gamepad(gamepad)
{}

template <typename Action>
inline void conduit::ActionMap<Action>::poll()
{
    for (const auto &[action, bindings] : m_bindings)
    {
        ActionState &action_state = m_action_states[action];

        action_state.previous = action_state.current;
        action_state.current = static_cast<real>(0);

        for (const Binding &binding : bindings)
        {
            action_state.current += evaluate(binding);
        }

        action_state.current = std::clamp(action_state.current, static_cast<real>(-1), static_cast<real>(1));
    }
}

template <typename Action>
inline bool conduit::ActionMap<Action>::isDown(Action action) const
{
    const ActionState &action_state = m_action_states.at(action);
    return action_state.current != static_cast<real>(0);
}

template <typename Action>
inline bool conduit::ActionMap<Action>::wasPressed(Action action) const
{
    const ActionState &action_state = m_action_states.at(action);
    return action_state.previous == 0 && action_state.current != 0;
}

template <typename Action>
inline bool conduit::ActionMap<Action>::wasReleased(Action action) const
{
    const ActionState &action_state = m_action_states.at(action);
    return action_state.previous != 0 && action_state.current == 0;
}

template <typename Action>
inline conduit::real conduit::ActionMap<Action>::value(Action action) const
{
    const ActionState &action_state = m_action_states.at(action);
    return action_state.current;
}

template <typename Action>
void conduit::ActionMap<Action>::bind(Action action, const Binding &binding)
{
    m_bindings[action].push_back(binding);
}

template <typename Action>
void conduit::ActionMap<Action>::bind(Action action, InputControl inputControl, real scale)
{
    bind(action, Binding(inputControl, scale));
}

template <typename Action>
void conduit::ActionMap<Action>::unbind(Action action, const Binding &binding)
{
    auto &bindings = m_bindings[action];

    auto it = std::erase_if(bindings, [&binding](const Binding &b) -> bool {
        return b.control == binding.control;
    });

    bindings.erase(it);
}

#endif // CONDUIT_ACTION_MAP_HPP